#include "MyBitmap.h"
#include "string.h"
MyBitmap::MyBitmap(){}
MyBitmap::~MyBitmap()
{
//	if(bmp) free(bmp);
}
MyBitmap::MyBitmap(char *filename,char *filepath)
{
	name = filename;
	GetBmpByFilepath(filepath);
}

void MyBitmap::GetBmpByFilepath(char *filepath)
{
	path = filepath;
	FILE *file = NULL;
	file = fopen(filepath, "rb");
	if (file == NULL) { AfxMessageBox("�ļ���ȡʧ��!"); return; }
	//��ȡbmpͷ
	fread(&bmpFileHead, sizeof(BITMAPFILEHEADER), 1, file);
	if (bmpFileHead.bfType != 0x4d42)  { AfxMessageBox("ͼ����bmp��ʽ��"); return; }
	DWORD sumNum = bmpFileHead.bfSize;//������������ݳ���

	DWORD offNum = bmpFileHead.bfOffBits;//����ƫ��ͷ������
	
	fread(&bmpInfoHead, sizeof(BITMAPINFOHEADER), 1, file);
	if (bmpInfoHead.biCompression != 0){ AfxMessageBox("�޷������bmpѹ����ʽ��"); return; }
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
	bmpWidth= width = bmpInfoHead.biWidth;//��ȱ�����4B�ı���
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
WORD MyBitmap::GetBitCount()
{
	return biBitCount;
}
bool MyBitmap::HavePalette()
{
	if (pPal) return false;
	return true;
}
unsigned char *&MyBitmap::GetBmp()
{
	return bmp;
}
LONG MyBitmap::GetHeight()
{
	return height;
}
LONG MyBitmap::GetBmpWidth()
{
	return bmpWidth;
}
LONG MyBitmap::GetWidth()
{
	return width;
}
char *MyBitmap::GetBmpName()
{
	return name;
}
void MyBitmap::SetBmpName(char *filename)
{
	int l = strlen(filename);
	name = new char[l+1];
	//name = filename;
	strcpy(name,filename);
}
char *MyBitmap::GetBmpPath()
{
	return path;
}
BITMAPFILEHEADER MyBitmap::GetBMPFileHead()
{
	return bmpFileHead;
}
BITMAPINFOHEADER MyBitmap::GetBMPInfoHead()
{
	return bmpInfoHead;
}
void MyBitmap::ShowBmpToDevice(CDC *dc, int xDes, int yDes)
{
	ShowBmpToDevice(dc,xDes,yDes,bmp,biBitCount,pPal);
}
void MyBitmap::ShowBmpToDevice(CDC *dc, int x, int y, const unsigned char *desfile,WORD BitCount, tagRGBQUAD *pPal)
{
	int k;
	for (int j = 0; j < height; j++)
	for (int i = 0; i < width; i++)//��ȱ䳤������2����ͼ�����ʾ2�����ڶ���Ϊ��һ���ĸ���
	{
		unsigned char r, g, b, gray;
		COLORREF c;
		BYTE w16;
		switch (BitCount)
		{
		case 1://��ȡ��ɫbmp
			// fread(&gray, sizeof(BYTE), 1, file);
			gray = bmp[(height-j)*width + i];
			for (k = 0; k < 8; k++)
			{
				c = gray & 0x80;
				if (c == 0x80) c = RGB(255, 255, 255);
				else c = 0;
				dc->SetPixel(x + i * 8 + k, y + j, c);
				//  SetPixel(hdc, x + i++, y + height - j, c);
				gray = gray << 1;
			}
			break;
		case 4://��ȡ4λ16ɫ
			w16 = bmp[j*width + i];
			dc->SetPixel(x + i * 2, y + height - j, RGB(pPal[w16 >> 4].rgbRed, pPal[w16 >> 4].rgbGreen, pPal[w16 >> 4].rgbBlue));
			dc->SetPixel(x + i * 2 + 1, y + height - j, RGB(pPal[w16 & 0x0f].rgbRed, pPal[w16 & 0x0f].rgbGreen, pPal[w16 & 0x0f].rgbBlue));
			break;
		case 8://��ȡ8λ256ɫ
			gray = bmp[j*width + i];
			if(pPal!=NULL) dc->SetPixel(x + i, y + height - j, RGB(pPal[gray].rgbRed, pPal[gray].rgbGreen, pPal[gray].rgbBlue));
			else dc->SetPixel(x + i, y + height - j, RGB(bmp[j*width+i],bmp[j*width+i],bmp[j*width+i]));
			break;
		case 24:
			b = bmp[j*width + i];
			g = bmp[j*width + i + 1];
			r = bmp[j*width + i + 2];
			dc->SetPixel(x + i / 3, y + height - j, RGB(r, g, b));
			i += 2;
			break;
		}
	}
}
