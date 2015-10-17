#pragma once
#include <assert.h>
#include <stdio.h>
#include <cmath>
#define UCHAR unsigned char 
class ImageProcess
{
public:
	/************************************************************************/
	/* 函数名称： GetGray()
	参数： const UPCHAR src --------待处理的24位bmp位图
	ULONG width,ULONG height --------图像宽高
	UPCHAR dis --------存放灰度图像
	返回值 无
	说明 ： 该函数用来得到24为位图的灰度图像
	/************************************************************************/
	void GetGray(const unsigned char * src, long width, long height, unsigned char ** dis);//将输入图像转换为灰度图，只处理24位bmp

	/************************************************************************/
	/* 函数名称： GetGrayIntensity()
	参数： unsigned char *gray --------待处理的灰度图
	int *grayInt --------存放灰度直方图的数组
	long width,long height-------图像的宽度和高度
	返回值 无
	说明 ： 该函数用来得到灰度图像的直方图
	/************************************************************************/
	void GetGrayIntensity(unsigned char *gray, int *grayInt, long width, long height);

	/************************************************************************/
	/* 函数名称： GetIntensity()
	参数： unsigned char *bmp --------待处理的图像
	long width,long height-------图像的宽度和高度
	int *R,int *G,int *B -------存放各个分量直方图的数组
	返回值 无
	说明 ： 该函数用来得到彩色图像的直方图
	/************************************************************************/
	void GetIntensity(unsigned char *bmp, long width, long height, int *R, int *G, int *B);

	/************************************************************************/
	/* 函数名称： GetInvert()
	参数： unsigned char *bmp --------待处理的图像
	long width,long height-------图像像素的宽度和高度
	unsigned char *des ------转换后的图像
	返回值 无
	说明 ： 该函数将图像进行反色变换处理,若为RGB格式，width要乘以3
	/************************************************************************/
	void GetInvert(unsigned char *src, long width, long height,unsigned char **des);

	/************************************************************************/
	/* 函数名称： GetStretch()
	参数： unsigned char *src --------待处理的图像
	long width,long height-------图像的宽度和高度
	BYTE bx1 -------折线1的原始灰度
	BYTE by1
	unsigned char *des ------转换后的图像
	返回值 无
	说明 ： 该函数将图像进行折线变换，即将0-255灰度映射到另一个范围内
	/************************************************************************/
	void GetStretch(unsigned char *src, long width, long height, unsigned char bx1, unsigned char by1, unsigned char bx2, unsigned char by2,unsigned char **des);

	/************************************************************************/
	/* 函数名称： GetWindowTrans()
	参数： unsigned char *bmp --------待处理的图像
	long width,long height-------图像的宽度和高度
	unsigned char bLow	 -------- 窗口下限
	unsigned char bUp	 -------- 窗口上限
	unsigned char *des ------转换后的图像
	返回值 无
	说明 ： 对图像进行灰度窗口变换，即小于下限为0，大于上限为255，中间线性变换
	/************************************************************************/
	void GetWindowTrans(unsigned char *src, long width, long height, unsigned char bLow, unsigned char bUp, unsigned char** des);

	/************************************************************************ /
		/* 函数名称： GetDynamicCompress()
		参数： unsigned char *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		int C --------- 非线性变换比例常数
		返回值 无
		说明 ： 对图像进行非线性变换 公式：D0=EH(D1)=Clog(1+|D1|),用于动态范围过大时
	/************************************************************************/
	void GetDynamicCompress(unsigned char *src, long width, long height, int C, unsigned char** des);
};
