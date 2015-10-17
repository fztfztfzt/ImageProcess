#pragma once
#include "stdafx.h"
#include <cmath>
#include <string>
class MyBitmap
{
public:
	MyBitmap();
	~MyBitmap();
	MyBitmap(char *filename,char *filepath);
	void GetBmpByFilepath(char *filepath);
	void ShowBmpToDevice(CDC *dc, int xDes, int yDes, const unsigned char *desfile,WORD BitCount=24, tagRGBQUAD *pPal=NULL);
	void ShowBmpToDevice(CDC *dc, int xDes, int yDes);
	WORD GetBitCount();
	bool HavePalette();//判断是否有调色板
	unsigned char *&GetBmp();
	LONG GetBmpWidth();//获取显示宽度
	LONG GetWidth();//获取图片像素字节宽度
	LONG GetHeight();
	char *GetBmpName();
	void SetBmpName(char * filename);
	char *GetBmpPath();
	BITMAPFILEHEADER GetBMPFileHead();
	BITMAPINFOHEADER GetBMPInfoHead();
		
private:
	BITMAPFILEHEADER bmpFileHead;//bmp头
	BITMAPINFOHEADER bmpInfoHead;//bmp数据头
	WORD biBitCount;//位图复位数
	tagRGBQUAD *pPal;//位图的调色板
	unsigned char *bmp;//位图数据
	LONG width;//位图宽度的字节数
	LONG bmpWidth;//位图显示时宽度
	LONG height;//位图高度
	char *name;
	char *path;//位图路径

};