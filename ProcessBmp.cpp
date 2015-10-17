
#include "ProcessBmp.h"
void ProcessBmp::LoadBmp(char * filepath, UPCHAR* bmp, long &width, long &height)
{
	FILE *file = fopen(filepath, "rb");
	assert(file != NULL);
	//读取bmp头
	BITMAPFILEHEADER bmpFileHead;
	fread(&bmpFileHead, sizeof(BITMAPFILEHEADER), 1, file);
	assert(bmpFileHead.bfType == 0x4d42);
	DWORD sumNum = bmpFileHead.bfSize;//这个长度是数据长度
	DWORD offNum = bmpFileHead.bfOffBits;//数据偏移头部长度
	BITMAPINFOHEADER bmpInfoHead;
	fread(&bmpInfoHead, sizeof(BITMAPINFOHEADER), 1, file);
	assert(bmpInfoHead.biCompression == 0);
	WORD biBitCount = bmpInfoHead.biBitCount;
	long nPlantNum;
	tagRGBQUAD *pPal;
	if (bmpInfoHead.biBitCount < 24)//读取调色板
	{
		nPlantNum = long(pow(2, double(bmpInfoHead.biBitCount)));    //   Mix color Plant Number;
		pPal = new tagRGBQUAD[nPlantNum*sizeof(tagRGBQUAD)];
		memset(pPal, 0, nPlantNum*sizeof(tagRGBQUAD));
		fread(pPal, 4, nPlantNum, file);
	}
	else pPal = NULL;
	width = bmpInfoHead.biWidth;//宽度必须是4B的倍数
	height = bmpInfoHead.biHeight;
	if (bmpInfoHead.biBitCount < 24)//注意宽度的计算方式
	{
		width = (width % (32 / biBitCount) == 0) ? width : (width / (32 / biBitCount) + 1) * (32 / biBitCount);//宽度调整为4B 32的倍数
																											   // width = (width+3)/4*4;
		width = width*biBitCount / 8;
	}
	else
		width = (width*biBitCount / 8 + 3) / 4 * 4;
	height = abs(height);
	*bmp = new unsigned char[height*width];
	fread(*bmp, 1, height*width, file);
	width /= 3;
	fclose(file);
}
void ProcessBmp::ShowBmp(int x, int y, unsigned char * bmp, long width, long height,int type)
{
	if (type == 0)
	{
		width *= 3;
	}
	if (width & 0x11) width += 4 - width & 0x11;//width必须是4的倍数
	HDC dc = GetWindowDC(GetDesktopWindow());//获取窗口句柄
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width;)
		{
			if (type == 0)
			{
				UCHAR b = bmp[j*width + i];
				UCHAR g = bmp[j*width + i + 1];
				UCHAR r = bmp[j*width + i + 2];
				SetPixel(dc, x + i / 3, y + height - j, RGB(r, g, b));
				i += 3;
			}
			else
			{
				UCHAR g = bmp[j*width + i];
				SetPixel(dc, x + i, y + height - j, RGB(g,g,g));
				i++;
			}
		}
}