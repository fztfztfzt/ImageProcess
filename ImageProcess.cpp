#include "ImageProcess.h"
void ImageProcess::GetGray(const UPCHAR src, ULONG width, ULONG height, UPCHAR dis)
{
	assert(src!=NULL);
	int i, j;
	dis = new UCHAR[width*height];
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j ++)
		{
			UCHAR b = src[i*width*3 + j*3];
			UCHAR g = src[i*width*3 + j*3 + 1];
			UCHAR r = src[i*width*3 + j*3 + 2];
			UCHAR h = (r * 30 + g * 59 + b * 11) / 100;
			//BYTE h=(r*9798+19235*g+3735*b)/32768;
			dis[i*width + j] = h;
		}
}