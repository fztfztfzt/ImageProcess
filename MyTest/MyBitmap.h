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
	bool HavePalette();//�ж��Ƿ��е�ɫ��
	unsigned char *&GetBmp();
	LONG GetBmpWidth();//��ȡ��ʾ���
	LONG GetWidth();//��ȡͼƬ�����ֽڿ��
	LONG GetHeight();
	char *GetBmpName();
	void SetBmpName(char * filename);
	char *GetBmpPath();
	BITMAPFILEHEADER GetBMPFileHead();
	BITMAPINFOHEADER GetBMPInfoHead();
		
private:
	BITMAPFILEHEADER bmpFileHead;//bmpͷ
	BITMAPINFOHEADER bmpInfoHead;//bmp����ͷ
	WORD biBitCount;//λͼ��λ��
	tagRGBQUAD *pPal;//λͼ�ĵ�ɫ��
	unsigned char *bmp;//λͼ����
	LONG width;//λͼ��ȵ��ֽ���
	LONG bmpWidth;//λͼ��ʾʱ���
	LONG height;//λͼ�߶�
	char *name;
	char *path;//λͼ·��

};