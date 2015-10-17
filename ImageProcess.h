#pragma once
#include <assert.h>
#include <stdio.h>
#include <cmath>
#define UCHAR unsigned char 
class ImageProcess
{
public:
	/************************************************************************/
	/* �������ƣ� GetGray()
	������ const UPCHAR src --------�������24λbmpλͼ
	ULONG width,ULONG height --------ͼ����
	UPCHAR dis --------��ŻҶ�ͼ��
	����ֵ ��
	˵�� �� �ú��������õ�24Ϊλͼ�ĻҶ�ͼ��
	/************************************************************************/
	void GetGray(const unsigned char * src, long width, long height, unsigned char ** dis);//������ͼ��ת��Ϊ�Ҷ�ͼ��ֻ����24λbmp

	/************************************************************************/
	/* �������ƣ� GetGrayIntensity()
	������ unsigned char *gray --------������ĻҶ�ͼ
	int *grayInt --------��ŻҶ�ֱ��ͼ������
	long width,long height-------ͼ��Ŀ�Ⱥ͸߶�
	����ֵ ��
	˵�� �� �ú��������õ��Ҷ�ͼ���ֱ��ͼ
	/************************************************************************/
	void GetGrayIntensity(unsigned char *gray, int *grayInt, long width, long height);

	/************************************************************************/
	/* �������ƣ� GetIntensity()
	������ unsigned char *bmp --------�������ͼ��
	long width,long height-------ͼ��Ŀ�Ⱥ͸߶�
	int *R,int *G,int *B -------��Ÿ�������ֱ��ͼ������
	����ֵ ��
	˵�� �� �ú��������õ���ɫͼ���ֱ��ͼ
	/************************************************************************/
	void GetIntensity(unsigned char *bmp, long width, long height, int *R, int *G, int *B);

	/************************************************************************/
	/* �������ƣ� GetInvert()
	������ unsigned char *bmp --------�������ͼ��
	long width,long height-------ͼ�����صĿ�Ⱥ͸߶�
	unsigned char *des ------ת�����ͼ��
	����ֵ ��
	˵�� �� �ú�����ͼ����з�ɫ�任����,��ΪRGB��ʽ��widthҪ����3
	/************************************************************************/
	void GetInvert(unsigned char *src, long width, long height,unsigned char **des);

	/************************************************************************/
	/* �������ƣ� GetStretch()
	������ unsigned char *src --------�������ͼ��
	long width,long height-------ͼ��Ŀ�Ⱥ͸߶�
	BYTE bx1 -------����1��ԭʼ�Ҷ�
	BYTE by1
	unsigned char *des ------ת�����ͼ��
	����ֵ ��
	˵�� �� �ú�����ͼ��������߱任������0-255�Ҷ�ӳ�䵽��һ����Χ��
	/************************************************************************/
	void GetStretch(unsigned char *src, long width, long height, unsigned char bx1, unsigned char by1, unsigned char bx2, unsigned char by2,unsigned char **des);

	/************************************************************************/
	/* �������ƣ� GetWindowTrans()
	������ unsigned char *bmp --------�������ͼ��
	long width,long height-------ͼ��Ŀ�Ⱥ͸߶�
	unsigned char bLow	 -------- ��������
	unsigned char bUp	 -------- ��������
	unsigned char *des ------ת�����ͼ��
	����ֵ ��
	˵�� �� ��ͼ����лҶȴ��ڱ任����С������Ϊ0����������Ϊ255���м����Ա任
	/************************************************************************/
	void GetWindowTrans(unsigned char *src, long width, long height, unsigned char bLow, unsigned char bUp, unsigned char** des);

	/************************************************************************ /
		/* �������ƣ� GetDynamicCompress()
		������ unsigned char *bmp --------�������ͼ��
		LONG width,LONG height-------ͼ��Ŀ�Ⱥ͸߶�
		int C --------- �����Ա任��������
		����ֵ ��
		˵�� �� ��ͼ����з����Ա任 ��ʽ��D0=EH(D1)=Clog(1+|D1|),���ڶ�̬��Χ����ʱ
	/************************************************************************/
	void GetDynamicCompress(unsigned char *src, long width, long height, int C, unsigned char** des);
};
