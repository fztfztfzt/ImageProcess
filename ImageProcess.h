#pragma once
typedef unsigned char UCHAR;
typedef UCHAR * UPCHAR;
typedef unsigned long ULONG;
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
	void GetGray(const UPCHAR src,ULONG width,ULONG height, UPCHAR dis);//������ͼ��ת��Ϊ�Ҷ�ͼ��ֻ����24λbmp
};
