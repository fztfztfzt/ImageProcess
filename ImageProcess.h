#pragma once
typedef unsigned char UCHAR;
typedef UCHAR * UPCHAR;
typedef unsigned long ULONG;
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
	void GetGray(const UPCHAR src,ULONG width,ULONG height, UPCHAR dis);//将输入图像转换为灰度图，只处理24位bmp
};
