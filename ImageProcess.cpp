#include "ImageProcess.h"

/************************************************************************/
/* 函数名称： GetGray()
参数： const UPCHAR src --------待处理的24位bmp位图
ULONG width,ULONG height --------图像宽高
UPCHAR dis --------存放灰度图像
返回值 无
说明 ： 该函数用来得到24为位图的灰度图像
/************************************************************************/
void ImageProcess::GetGray(const unsigned char * src, long width, long height, unsigned char ** dis)
{
	assert(src!=NULL);
	int i, j;
	int nwidth =width * 3;
	if (width & 0x11) width += 4 - width & 0x11;//width必须是4的倍数
	if (nwidth & 0x11) nwidth += 4 - nwidth & 0x11;//width必须是4的倍数
	*dis = new UCHAR[width*height];
	for (i = 0; i < height; i++)
		for (j = 0; j < nwidth; j +=3)
		{
			UCHAR b = src[i*nwidth + j];
			UCHAR g = src[i*nwidth + j + 1];
			UCHAR r = src[i*nwidth + j + 2];
			UCHAR h = (r * 30 + g * 59 + b * 11) / 100;
			//BYTE h=(r*9798+19235*g+3735*b)/32768;
			(*dis)[i*width + j/3] = h;
		}
}

/************************************************************************/
/* 函数名称： GetGrayIntensity()
参数： unsigned char *gray --------待处理的灰度图
int *grayInt --------存放灰度直方图的数组
long width,long height-------图像的宽度和高度
返回值 无
说明 ： 该函数用来得到灰度图像的直方图
/************************************************************************/
void ImageProcess::GetGrayIntensity(unsigned char *gray, int *grayInt, long width, long height)
{
	long i, j;
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)
		{
			int temp = gray[i*width + j];
			grayInt[temp]++;
		}
}

void ImageProcess::GetIntensity(unsigned char *bmp, long width, long height, int *R, int *G, int *B)
{
	width *= 3;
	if (width & 0x11) width += 4 - width & 0x11;//width必须是4的倍数
	long i, j;
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)
		{
			R[bmp[i*width + j]]++;
			j++;
			G[bmp[i*width + j]]++;
			j++;
			B[bmp[i*width + j]]++;
		}
}

void ImageProcess::GetInvert(unsigned char *src, long width, long height, unsigned char **des)
{
	if (width & 0x11) width += 4 - width & 0x11;//width必须是4的倍数
	assert(src != NULL);
	*des = new unsigned char[width*height];
	for (int i = 0; i<height; i++)
		for (int j = 0; j<width; j++)
		{
			(*des)[i*width + j] = 255 - src[i*width + j];
		}
}
void ImageProcess::GetStretch(unsigned char *src, long width, long height, unsigned char bx1, unsigned char by1, unsigned char bx2, unsigned char by2, unsigned char **des)
{

	long i, j;//循环变量
	unsigned char bMap[256];
	for (i = 0; i <= bx1; i++)
	{
		//判断bx1是否大于0（防止分母为0）
		if (bx1>0)
		{
			//线性变换
			bMap[i] = (unsigned char)by1*i / bx1;
		}
		else
		{
			bMap[i] = 0;
		}
	}
	for (; i <= bx2; i++)
	{
		//判断bx2是否大于0（防止分母为0）
		if (bx2 != bx1)
		{
			//线性变换
			bMap[i] = (unsigned char)(by2 - by1)*(i - bx1) / (bx2 - bx1);
		}
		else
		{
			bMap[i] = by1;
		}
	}
	for (; i<256; i++)
	{
		if (bx2 != 255)
		{
			bMap[i] = by2 + (unsigned char)((255 - by2)*(i - bx2) / (255 - bx2));
		}
		else
		{
			bMap[i] = by2;
		}
	}
	if (width & 0x11) width += 4 - width & 0x11;//width必须是4的倍数
	*des = new unsigned char[width*height];
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)
		{
			unsigned char temp = src[i*width + j];
			(*des)[i*width + j] = bMap[temp];
		}
}

void ImageProcess::GetWindowTrans(unsigned char *src, long width, long height, unsigned char bLow, unsigned char bUp, unsigned char** des)
{
	long i, j;
	if (width & 0x11) width += 4 - width & 0x11;//width必须是4的倍数
	*des = new unsigned char[width*height];
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)
		{
			unsigned char temp = src[i*width + j];
			if (temp < bLow) (*des)[i*width + j] = 0;
			else if (temp > bUp) (*des)[i*width + j] = 255;
			else (*des)[i*width + j] = temp;
		}
}
void ImageProcess::GetDynamicCompress(unsigned char *src, long width, long height, int C, unsigned char** des)
{
	long i, j;
	if (width & 0x11) width += 4 - width & 0x11;//width必须是4的倍数
	*des = new unsigned char[width*height];
	for (i = 0; i<height; i++)
		for (j = 0; j<width; j++)
		{
		(*des)[i*width + j] = C*log(1 + src[i*width + j]);
		}
}