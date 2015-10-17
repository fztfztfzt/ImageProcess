#include <windows.h>
#include "ProcessBmp.h"

#include <cmath>
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;//λͼ�ļ������ͣ�����ΪBM(1-2�ֽڣ�
	DWORD bfSize;//λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ��3-6�ֽڣ���λ��ǰ��
	WORD bfReserved1;//λͼ�ļ������֣�����Ϊ0(7-8�ֽڣ�
	WORD bfReserved2;//λͼ�ļ������֣�����Ϊ0(9-10�ֽڣ�
	DWORD bfOffBits;//λͼ���ݵ���ʼλ�ã��������λͼ��11-14�ֽڣ���λ��ǰ��
					//�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
}BITMAPFILEHEADER;
typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;//���ṹ��ռ���ֽ�����15-18�ֽڣ�
	LONG biWidth;//λͼ�Ŀ�ȣ�������Ϊ��λ��19-22�ֽڣ�
	LONG biHeight;//λͼ�ĸ߶ȣ�������Ϊ��λ��23-26�ֽڣ�
	WORD biPlanes;//Ŀ���豸�ļ��𣬱���Ϊ1(27-28�ֽڣ�
	WORD biBitCount;//ÿ�����������λ����������1��˫ɫ������29-30�ֽڣ�
					//4(16ɫ����8(256ɫ��16(�߲�ɫ)��24�����ɫ��֮һ
	DWORD biCompression;//λͼѹ�����ͣ�������0����ѹ��������31-34�ֽڣ�
						//1(BI_RLE8ѹ�����ͣ���2(BI_RLE4ѹ�����ͣ�֮һ
	DWORD biSizeImage;//λͼ�Ĵ�С(���а�����Ϊ�˲���������4�ı�������ӵĿ��ֽ�)�����ֽ�Ϊ��λ��35-38�ֽڣ�
	LONG biXPelsPerMeter;//λͼˮƽ�ֱ��ʣ�ÿ����������39-42�ֽڣ�
	LONG biYPelsPerMeter;//λͼ��ֱ�ֱ��ʣ�ÿ����������43-46�ֽ�)
	DWORD biClrUsed;//λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ�
	DWORD biClrImportant;//λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ�
}BITMAPINFOHEADER;
typedef struct tagRGBQUAD{
	BYTE rgbBlue;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	BYTE rgbGreen;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	BYTE rgbRed;//��ɫ�����ȣ�ֵ��ΧΪ0-255)
	BYTE rgbReserved;//����������Ϊ0
}RGBQUAD;
void ProcessBmp::LoadBmp(unsigned char * filepath,BYTE *bmp,long &width,long &height)
{
	FILE *file = fopen(filepath, "rb");
	assert(file != NULL);
	//��ȡbmpͷ
	fread(&bmpFileHead, sizeof(BITMAPFILEHEADER), 1, file);
	assert(bmpFileHead.bfType == 0x4d42);
	DWORD sumNum = bmpFileHead.bfSize;//������������ݳ���
	DWORD offNum = bmpFileHead.bfOffBits;//����ƫ��ͷ������
	fread(&bmpInfoHead, sizeof(BITMAPINFOHEADER), 1, file);
	assert(bmpInfoHead.biCompression == 0);
	biBitCount = bmpInfoHead.biBitCount;
	long nPlantNum;
	if (bmpInfoHead.biBitCount < 24)//��ȡ��ɫ��
	{
		nPlantNum = long(pow(2, double(bmpInfoHead.biBitCount)));    //   Mix color Plant Number;
		pPal = new tagRGBQUAD[nPlantNum*sizeof(tagRGBQUAD)];
		memset(pPal, 0, nPlantNum*sizeof(tagRGBQUAD));
		fread(pPal, 4, nPlantNum, file);
	}
	else pPal = NULL;
	bmpWidth = width = bmpInfoHead.biWidth;//��ȱ�����4B�ı���
	height = bmpInfoHead.biHeight;
	if (bmpInfoHead.biBitCount < 24)//ע���ȵļ��㷽ʽ
	{
		width = (width % (32 / biBitCount) == 0) ? width : (width / (32 / biBitCount) + 1) * (32 / biBitCount);//��ȵ���Ϊ4B 32�ı���
																											   // width = (width+3)/4*4;
		width = width*biBitCount / 8;
	}
	else
		width = (width*biBitCount / 8 + 3) / 4 * 4;
	height = abs(height);
	bmp = new unsigned char[height*width];
	fread(bmp, 1, height*width, file);
	fclose(file);
}
void ProcessBmp::ShowBmp(int x, int y, unsigned char * bmp, long width, long height)
{
	HDC dc = GetWindowDC(GetDesktopWindow());
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)//��ȱ䳤������2����ͼ�����ʾ2�����ڶ���Ϊ��һ���ĸ���
		{
			b = bmp[j*width*3 + i*3];
			g = bmp[j*width*3 + i*3 + 1];
			r = bmp[j*width*3 + i*3 + 2];
			SetPixel(dc,x + i, y + height - j, RGB(r, g, b));
		}
}