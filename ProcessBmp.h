#pragma once
#include <windows.h>
#include <stdio.h>
#include <cmath>
#include <assert.h>
#define UCHAR unsigned char 
#define UPCHAR UCHAR*
#define ssize long

/*
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
}RGBQUAD;*/
class ProcessBmp
{
public:
	void LoadBmp(char* filepath, unsigned char ** bmp, ssize &width, ssize &height);
	void ShowBmp(int x, int y, unsigned char * bmp, long width, long height,int type=0);
protected:
private:
};