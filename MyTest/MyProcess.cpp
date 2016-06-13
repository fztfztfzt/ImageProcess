#include "MyProcess.h"

using namespace std;
void MyProcess::GetGray(MyBitmap myBmp,unsigned char *srcchar)
{
	if(myBmp.GetBitCount()!=24)return ;
	int i,j;
	for(i=0;i<myBmp.GetHeight();i++)
		for(j=0;j<myBmp.GetWidth();j+=3)
		{
			unsigned char b=myBmp.GetBmp()[i*myBmp.GetWidth()+j];
			unsigned char g=myBmp.GetBmp()[i*myBmp.GetWidth()+j+1];
			unsigned char r=myBmp.GetBmp()[i*myBmp.GetWidth()+j+2];
			unsigned char h= (r*30+g*59+b*11)/100 ;
			//BYTE h=(r*9798+19235*g+3735*b)/32768;
			srcchar[i*myBmp.GetBmpWidth()+j/3] = h;
		}
}
void MyProcess::ShowArrayToDevice(CDC *dc, int x, int y,unsigned char *array,LONG width,LONG height,int type)
{
	for (int j = 0; j < height; j++)
	for (int i = 0; i < width; i++)
	{
		if(type==1)dc->SetPixel(x + i, y + height - j, RGB(array[j*width+i],array[j*width+i],array[j*width+i]));
		else if(type==0) 
		{
		//	b = array[j*width + i];
		//	g = array[j*width + i + 1];
		//	r = array[j*width + i + 2];
			dc->SetPixel(x+i/3,y+height-j,RGB(array[j*width+i+2],array[j*width+i+1],array[j*width+i]));
			i+=2;
		}
	}
}
void MyProcess::GetGrayIntensity(unsigned char *gray,int *grayInt,LONG width,LONG height)
{
	LONG i,j;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			int temp = gray[i*width+j];
			grayInt[temp]++;
		}
}
void MyProcess::GetIntensity(unsigned char *bmp,LONG width,LONG height,int *R,int *G,int *B)
{
	LONG i,j;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			R[bmp[i*width+j]]++;
			j++;
			G[bmp[i*width+j]]++;
			j++;
			B[bmp[i*width+j]]++;
		}
}
void MyProcess::PointInvert(unsigned char *bmp,LONG width,LONG height)
{
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			bmp[i*width+j] = 255-bmp[i*width+j];
		}
}
void MyProcess::GrayStretch(unsigned char *bmp,LONG width,LONG height,BYTE bx1,BYTE by1,BYTE bx2,BYTE by2)
{
	LONG i,j;//ѭ������
	BYTE bMap[256];
	for(i=0;i<=bx1;i++)
	{
		//�ж�bx1�Ƿ�����0����ֹ��ĸΪ0��
		if(bx1>0)
		{
			//���Ա任
			bMap[i] = (BYTE) by1*i/bx1;
		}else 
		{
			bMap[i]=0;
		}
	}
	for(;i<=bx2;i++)
	{
		//�ж�bx2�Ƿ�����0����ֹ��ĸΪ0��
		if(bx2!=bx1)
		{
			//���Ա任
			bMap[i] = (BYTE) (by2-by1)*(i-bx1)/(bx2-bx1);
		}else 
		{
			bMap[i]=by1;
		}
	}
	for(;i<256;i++)
	{
		if(bx2!=255)
		{
			bMap[i]=by2+(BYTE)((255-by2)*(i-bx2)/(255-bx2));
		}else
		{
			bMap[i]=255;
		}
	}
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			BYTE temp = bmp[i*width+j];
			bmp[i*width+j] = bMap[temp];
		}

}
void MyProcess::WindowTrans(BYTE *bmp,LONG width,LONG height ,BYTE bLow,BYTE bUp)
{
	LONG i,j;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			BYTE temp = bmp[i*width+j];
			if(temp < bLow) bmp[i*width+j]=0;
			else if(temp > bUp) bmp[i*width+j]=255;
		}
}
void MyProcess::DynamicCompress(BYTE *bmp,LONG width,LONG height,int C)
{
	LONG i,j;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			bmp[i*width+j] = C*log(1+bmp[i*width+j]);
		}
}
void MyProcess::PointEqua(BYTE *bmp,LONG width,LONG height,int type)
{
	LONG i,j;
	int R[256],G[256],B[256];
	memset(R,0,sizeof(R));
	memset(G,0,sizeof(G));
	memset(B,0,sizeof(B));
	if(type==0) GetIntensity(bmp,width,height,R,G,B);
	else if(type==1) GetGrayIntensity(bmp,R,width,height);
	float temp_r[256],temp_g[256],temp_b[256];
	memset(temp_r,0,sizeof(temp_r));
	memset(temp_g,0,sizeof(temp_g));
	memset(temp_b,0,sizeof(temp_b));
	double sum ;
	if(type==0) sum = width*height/3;
	else if(type==1) sum=width*height;
	for(i=0;i<256;i++)
	{
		if(i==0)
		{
			if(type==0)
			{
				temp_r[0] = (double)R[0]/sum;
				temp_g[0] = (double)G[0]/sum;
				temp_b[0] = (double)B[0]/sum;
			}else if(type==1)
			{
				temp_r[0] = (double)R[0]/sum;
			}
		}
		else
		{
			if(type==0)
			{
				temp_r[i]=temp_r[i-1]+(double)R[i]/sum;
				temp_g[i]=temp_g[i-1]+(double)G[i]/sum;
				temp_b[i]=temp_b[i-1]+(double)B[i]/sum;
			}else if(type==1)
			{
				temp_r[i]=temp_r[i-1]+(double)R[i]/sum;
			}
		}
	}
	for(i=0;i<256;i++)
	{
		if(type==0)
		{
			temp_r[i] = (int)(255.0f*temp_r[i]+0.5);
			temp_g[i] = (int)(255.0f*temp_g[i]+0.5);
			temp_b[i] = (int)(255.0f*temp_b[i]+0.5);
		}else if(type==1)
		{
			temp_r[i] = (int)(255.0f*temp_r[i]+0.5);
		}
	}
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			if(type==0)
			{
				bmp[i*width+j]=temp_r[bmp[i*width+j]];
				j++;
				bmp[i*width+j]=temp_g[bmp[i*width+j]];
				j++;
				bmp[i*width+j]=temp_b[bmp[i*width+j]];
			}else if(type==1)
			{
				bmp[i*width+j]=temp_r[bmp[i*width+j]];
			}
		}
	
}
void MyProcess::PointSML(BYTE *bmp,LONG width,LONG height,BYTE bNum,int *Nu,float *Pu,int type)
{
	LONG i,j;
	int R[256],G[256],B[256];
	int mMap_r[256],mMap_g[256],mMap_b[256];
	memset(R,0,sizeof(R));
	memset(G,0,sizeof(G));
	memset(B,0,sizeof(B));
	if(type==0) GetIntensity(bmp,width,height,R,G,B);
	else if(type==1) GetGrayIntensity(bmp,R,width,height);
	float temp_r[256],temp_g[256],temp_b[256];
	double sum ;
	if(type==0) sum = width*height/3;
	else if(type==1) sum=width*height;
	//����ԭʼ�ۼ�ֱ��ͼ
	for(i=0;i<256;i++)
	{
		if(i==0)
		{
			if(type==0)
			{
				temp_r[0] = (double)R[0]/sum;
				temp_g[0] = (double)G[0]/sum;
				temp_b[0] = (double)B[0]/sum;
			}else if(type==1)
			{
				temp_r[0] = (double)R[0]/sum;
			}
		}
		else
		{
			if(type==0)
			{
				temp_r[i]=temp_r[i-1]+(double)R[i]/sum;
				temp_g[i]=temp_g[i-1]+(double)G[i]/sum;
				temp_b[i]=temp_b[i-1]+(double)B[i]/sum;
			}else if(type==1)
			{
				temp_r[i]=temp_r[i-1]+(double)R[i]/sum;
			}
		}
	}
	//�����涨�ۼ�ֱ��ͼ
	for(i=1;i<bNum;i++)
	{
		Pu[i]=Pu[i-1]+Pu[i];
	}
	//ȷ��ӳ����Ӧ��ϵ
	for(i=0;i<256;i++)
	{
		//���ӽ��Ĺ涨ֱ��ͼ�Ҷȼ�
		int m_r=0,m_g=0,m_b=0;
		//��С��ֵ
		float f_r=1,f_g=1,f_b=1;
		//Ѱ����С��ֵ
		for(j=0;j<bNum;j++)
		{
			float f_now=abs(temp_r[i]-Pu[j]);
			if(f_now < f_r)
			{
				f_r=f_now;
				mMap_r[i]=j;
			}
			if(type==0)
			{
				float f_now_g=abs(temp_g[i]-Pu[j]);
				if(f_now < f_g)
				{
					f_g=f_now;
					mMap_g[i]=j;
				}
				float f_now_b=abs(temp_b[i]-Pu[j]);
				if(f_now < f_b)
				{
					f_b=f_now;
					mMap_b[i]=j;
				}
			}
		}
	}
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			if(type==0)
			{
				bmp[i*width+j]=mMap_r[bmp[i*width+j]];
				j++;
				bmp[i*width+j]=mMap_g[bmp[i*width+j]];
				j++;
				bmp[i*width+j]=mMap_b[bmp[i*width+j]];
			}else if(type==1)
			{
				bmp[i*width+j]=mMap_r[bmp[i*width+j]];
			}
		}	
}
void MyProcess::FFT(std::complex<double>*TD,std::complex<double>*FD,int r)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;
	
	// �м�����
	int		p;
	
	// �Ƕ�
	double	angle;
	
	complex<double> *W,*X1,*X2,*X;
	
	// ���㸶��Ҷ�任����
	LONG N = 1 << r;
	
	// �������������洢��
	W  = new complex<double>[N / 2];
	X1 = new complex<double>[N];
	X2 = new complex<double>[N];
	
	// ������Ȩϵ��
	for(i = 0; i < N / 2; i++)
	{
		angle = -i * PI * 2 / N;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	// ��ʱ����д��X1
	memcpy(X1, TD, sizeof(complex<double>) * N);
	
	// ���õ����㷨���п��ٸ���Ҷ�任
	for(k = 0; k < r; k++)
	{
		for(j = 0; j < 1 << k; j++)
		{
			for(i = 0; i < 1<<(r - k -1); i++)
			{
				p = j * (1<<(r - k));
				X2[i + p] = X1[i + p] + X1[i + p + (int)(1<<(r - k -1))];
				X2[i + p + (int)(1<<(r - k -1))] = (X1[i + p] - X1[i + p + (int)(1<<(r - k -1))]) * W[i * (1<<k)];
			}
		}
		X  = X1;
		X1 = X2;
		X2 = X;
	}
	
	// ��������
	for(j = 0; j < N; j++)
	{
		p = 0;
		for(i = 0; i < r; i++)
		{
			if (j&(1<<i))
			{
				p+=1<<(r - i - 1);
			}
		}
		FD[j] = X1[p];
	}
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}
void MyProcess::IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// ѭ������
	int	i;
	
	complex<double> *X;
	
	// ���㸶��Ҷ�任����
	LONG N = 1<<r;
	
	// �������������洢��
	X = new complex<double>[N];
	
	// ��Ƶ����д��X
	memcpy(X, FD, sizeof(complex<double>) * N);
	
	// ������
	for (i = 0; i < N; i++)
	{
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	}
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X, TD, r);
	
	// ��ʱ�����Ĺ���
	for (i = 0; i < N; i++)
	{
		TD[i] = complex<double> (TD[i].real() / N, -TD[i].imag() / N);
	}
	
	// �ͷ��ڴ�
	delete X;
}
BOOL MyProcess::Fourier(std::complex<double> * TD, LONG width, LONG height, std::complex<double> * FD)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;
	
	// ���и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// �������и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while (w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while (h < height)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	complex<double> *TempT, *TempF;
	TempT = new complex<double>[h];
	TempF = new complex<double>[h];
	
	// ��y�������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempT[j] = TD[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		FFT(TempT, TempF, hp);
		
		// �����任����
		for (j = 0; j < h; j++)
			TD[j * w * 3 + i] = TempF[j];
	}
	
	// �ͷ��ڴ�
	delete TempT;
	delete TempF;
	
	// �����ڴ�
	TempT = new complex<double>[w];
	TempF = new complex<double>[w];
	
	// ��x�������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempT[j] = TD[i * w * 3 + j * 3 + k];
			
			// һά���ٸ���Ҷ�任
			FFT(TempT, TempF, wp);
			
			// �����任����
			for (j = 0; j < w; j++)
				FD[i * w * 3 + j * 3 + k] = TempF[j];
		}
	}
	
	// �ͷ��ڴ�
	delete TempT;
	delete TempF;
	
	return TRUE;
}
BOOL MyProcess::IFourier(BYTE *TD, LONG width, LONG height, std::complex<double> * FD)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;
	
	// ���и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// �������и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while(w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while(h < height)
	{
		h *= 2;
		hp++;
	}
	
	// ����ͼ��ÿ�е��ֽ���
	
	// �����ڴ�
	complex<double> *TempT, *TempF;
	TempT = new complex<double>[w];
	TempF = new complex<double>[w];
	
	// ��x�������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempF[j] = FD[i * w * 3 + j * 3 + k];
			
			// һά���ٸ���Ҷ�任
			IFFT(TempF, TempT, wp);
			
			// �����任����
			for (j = 0; j < w; j++)
				FD[i * w * 3 + j * 3 + k] = TempT[j];
		}
	}
	
	// �ͷ��ڴ�
	delete TempT;
	delete TempF;
	
	TempT = new complex<double>[h];
	TempF = new complex<double>[h];
	
	// ��y�������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempF[j] = FD[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		IFFT(TempF, TempT, hp);
		
		// �����任����
		for (j = 0; j < h; j++)
			FD[j * w * 3 + i] = TempT[j];
	}
	
	// �ͷ��ڴ�
	delete TempT;
	delete TempF;

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < height && j < width)
				*(TD + i * width + j) = FD[i * w * 3 + j].real();
		}
	}

	return TRUE;
}
BOOL MyProcess::BmpTD(BYTE *bmp,LONG width,LONG height,complex<double>*TD)
{
	LONG i,j;//ѭ������
	// �м�����
	LONG TI,TJ;
	// ���и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	// �������и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while(w < width/3)
	{
		w *= 2;
		wp++;
	}
	while(h < height)
	{
		h *= 2;
		hp++;
	}// �����ڴ�
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < height && j < width)
			{
				// ��ȡʱ����ֵ
				unsigned char Value = bmp[i*width+j];
				
				// ʱ����ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ��������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}	
	return true;
}
BOOL MyProcess::BmpFourier(BYTE* bmp,LONG width,LONG height)
{
	LONG i,j;//ѭ������
	// �м�����
	double	dTemp;
	LONG TI,TJ;
	// ���и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	// �������и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while(w < width/3)
	{
		w *= 2;
		wp++;
	}
	while(h < height)
	{
		h *= 2;
		hp++;
	}// �����ڴ�
	complex<double> *FD, *TD, *TempD;
	FD = new complex<double>[w * h * 3];
	TD = new complex<double>[w * h * 3];
	TempD =  new complex<double>[w * h * 3];
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < 3 * w; j++)
		{
			if(i < height && j < width)
			{
				// ��ȡʱ����ֵ
				unsigned char Value = bmp[i*width+j];
				
				// ʱ����ֵ
				TD[w * i * 3 + j] = complex<double>(Value, 0.0f);
			}
			else
			{
				// ��������
				TD[w * i * 3 + j] = complex<double>(0.0f, 0.0f);
			}
		}
	}
	
	// ����Ƶ�׷���
	if (Fourier(TD, width, height, FD) == FALSE)
		return FALSE;
	
	// �ͷ��ڴ�
	delete []TD;
	
	// ��ԭ��������ͼ������λ��
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < 3 * w; j++)
		{
			if (i < h / 2)
				TI = i + h / 2;
			else
				TI = i - h / 2;
			
			if (j < w * 3 /2)
				TJ = j + 3 * w / 2;
			else 
				TJ = j - 3 * w / 2;
			
			// ����ת������Ƶ��ͼ��
			TempD[i * w * 3 + j] = FD[TI * w * 3 + TJ];
		}
	}
	
	// ��
	for(i = (int)(h - height) / 2; i < (int)(h + height) / 2; i++)
	{
		// ��
		for(j = (int)(w * 3 - width) / 2; j < (int)(w * 3 + width) / 2; j += 3)
		{
			// ����Ƶ��
			dTemp = sqrt(TempD[w * 3 * i + j].real() * TempD[w * 3 * i + j].real() + 
				TempD[w * 3 * i + j].imag() * TempD[w * 3 * i + j].imag()) / 100;
			
			// �ж��Ƿ񳬹�255
			if (dTemp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				dTemp = 255;
			}
			
			// ����Ϊԭͼ��С��Χ
			TI = i - (h - height) / 2;
			TJ = j / 3 - (w - width/3) / 2;
			
			// ��Ӧ����ָ��
			LONG p = width * TI + TJ * 3;
			
			// ����Դͼ��
			bmp[p] = (BYTE) (dTemp);
			bmp[p+1] = (BYTE) (dTemp);
			bmp[p+2] = (BYTE) (dTemp);
		}
	}
	// ɾ����ʱ����
	delete []FD;
	delete []TempD;
	return TRUE;
}
void MyProcess::DCT(double *f, double *F, int r)
{
	// ѭ������
	int		i;
	
	// �м�����
	double	dTemp;
	
	// ������ɢ���ұ任����
	LONG N = 1<<r;
	
	// ���벢�����ڴ�
	complex<double> *XIn;
	complex<double> *XOut;
	XIn = new complex<double>[N * 2];
	XOut = new complex<double>[N * 2];
	
	// ����ֵΪ0
	memset(XIn, 0, sizeof(complex<double>) * N * 2);
	memset(XOut, 0, sizeof(complex<double>) * N * 2);
	
	// ��ʱ����д������X
	for (i = 0; i < N; i++)
		XIn[i] = complex<double>(*(f + i), 0);
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(XIn, XOut, r + 1);
	
	// ����ϵ��
	dTemp = 1 / sqrt(N);
	
	// ��F[0]
	F[0] = XOut[0].real() * dTemp;
	
	dTemp *= sqrt(2);
	
	// ��F[u]
	for (i = 1; i < N; i++)
		*(F + i) = (XOut[i].real() * cos(i * PI / (N * 2)) + XOut[i].imag() * sin(i * PI / (N * 2))) * dTemp;
	
	// �ͷ��ڴ�
	delete[] XIn;
	delete[] XOut;
}
void MyProcess::IDCT(double *F, double *f, int r)
{
	// ѭ������
	int		i;
	
	// �м�����
	double	dTemp, d0;
	
	// ������ɢ���ұ任����
	LONG N = 1<<r;
	
	// �����ڴ�
	complex<double> *XIn;
	complex<double> *XOut;
	XIn = new complex<double>[N * 2];
	XOut = new complex<double>[N * 2];
	
	// ����ֵΪ0
	memset(XIn, 0, sizeof(complex<double>) * N * 2);
	memset(XOut, 0, sizeof(complex<double>) * N * 2);
	
	// ��Ƶ���任����д������X
	for (i = 0; i < N; i++)
		XIn[i] = complex<double>(F[i] * cos(i * PI / (N * 2)), F[i] * sin(i * PI / (N * 2)));
	
	// ���ÿ��ٸ���Ҷ���任
	IFFT(XIn, XOut, r + 1);
	
	// ����ϵ��
	dTemp = sqrt(2.0 / N);
	d0 = (sqrt(1.0 / N) - dTemp) * F[0];
	
	// ����f(x)
	for (i = 0; i < N; i++)
		f[i] = d0 + XOut[i].real()* dTemp * 2 * N;
	
	// �ͷ��ڴ�
	delete[] XIn;
	delete[] XOut;
}
BOOL MyProcess::FreqDCT(double *f, double *F, LONG width, LONG height)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;
	
	// ������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ����������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while (w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while (h < height)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	double* TempIn = new double[h];
	double* TempOut = new double[h];
	
	// ��y����������ɢ���ұ任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = f[j * w * 3 + i];
		
		// һά������ɢ���ұ任
		DCT(TempIn, TempOut, hp);
		
		// �����任����
		for (j = 0; j < h; j++)
			f[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	// �����ڴ�
	TempIn = new double[w];
	TempOut = new double[w];
	
	// ��x�������п�����ɢ���ұ任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = f[i * w * 3 + j * 3 + k];
			
			// һά������ɢ���ұ任
			DCT(TempIn, TempOut, wp);
			
			// �����任����
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	return TRUE;
}
BOOL MyProcess::IFreqDCT(double *f, double *F, LONG width, LONG height)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;
	
	// ������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// �������и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while (w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while (h < height)
	{
		h *= 2;
		hp++;
	}
		
	// �����ڴ�
	double* TempIn = new double[w];
	double* TempOut = new double[w];
	
	// ��x�������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = F[i * w * 3 + j * 3 + k];
			
			// һά���ٸ���Ҷ�任
			IDCT(TempIn, TempOut, wp);
			
			// �����任����
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	TempIn = new double[h];
	TempOut = new double[h];
	
	// ��y�������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = F[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		IDCT(TempIn, TempOut, hp);
		
		// �����任����
		for (j = 0; j < h; j++)
			F[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < height && j < width)
				*(f + i * width + j) = F[i * w * 3 + j];
		}
	}
	
	return TRUE;
}
BOOL MyProcess::BmpDCT(BYTE* bmp,LONG width,LONG height)
{
	// ������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG	i;
	LONG	j;
	
	// ������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ����������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while (w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while (h < height)
	{
		h *= 2;
		hp++;
	}

	// �����ڴ�
	double *f = new double[w * h * 3];
	double *F = new double[w * h * 3];

	// ��ʱ����ֵ������
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < height && j < width)
				f[i * w * 3 + j] = bmp[width * i + j];
			else
				f[w * i * 3 + j] = 0.0f;
		}
	}

	// ����Ƶ�׷���
	if (FreqDCT(f, F,width, height) == FALSE)
		return FALSE;

	// ������������
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			// �ж��Ƿ񳬹�255
			if (fabs(F[i * w * 3 + j]) > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				bmp[width * (height - 1 - i) + j] = 255;
			}
			else
			{
				// ����û�г���������ʵ�ʼ���������ֵ
				bmp[width * (height - 1 - i) + j] = fabs(F[i * w * 3 + j]);
			}
		}
	}
	// �ͷ��ڴ�
	delete []f;
	delete[] F;

	// ����
	return TRUE;
}
void MyProcess::WALSH(double *f, double *F, int r)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;
	
	// �м�����
	int		p;	
	double* X;
	
	// ���������ֶ�ʲ�任����
	LONG N = 1 << r;
	
	// ������������������
	double* X1 = new double[N];
	double* X2 = new double[N];
	
	// ��ʱ����д������X1
	memcpy(X1, f, sizeof(double) * N);
	
	// ��������
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1<<k; j++)
		{
			for (i = 0; i < 1<<(r - k - 1); i++)
			{
				p = j * (1<<(r - k));
				X2[i + p] = X1[i + p] + X1[i + p + (int)(1<<(r - k - 1))];
				X2[i + p + (int)(1<<(r - k - 1))] = X1[i + p] - X1[i + p + (int)(1<<(r - k - 1))];
			}
		}
		
		// ����X1��X2  
		X = X1;
		X1 = X2;
		X2 = X;
	}
	
	// ����ϵ��
	for (j = 0; j < N; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r - i - 1);
			}
		}
		
		F[j] = X1[p] / N;
	}
	
	// �ͷ��ڴ�
	delete X1;
	delete X2;
}
void MyProcess::IWALSH(double *F, double *f, int r)
{
	// ѭ������
	int		i;
	
	// �����任����
	LONG N = 1 << r;
	
	// ���ÿ����ֶ�ʲ���������任���з��任
	WALSH(F, f, r);
	
	// ����ϵ��
	for (i = 0; i < N; i++)
		f[i] *= N;
}
BOOL MyProcess::FreqWALSH(double *f, double *F, LONG width, LONG height)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;
	
	// ������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ����������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while (w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while (h < height)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	double* TempIn = new double[h];
	double* TempOut = new double[h];
	
	// ��y����������ɢ���ұ任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = f[j * w * 3 + i];
		
		// һά������ɢ���ұ任
		WALSH(TempIn, TempOut, hp);
		
		// �����任����
		for (j = 0; j < h; j++)
			f[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	// �����ڴ�
	TempIn = new double[w];
	TempOut = new double[w];
	
	// ��x�������п�����ɢ���ұ任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = f[i * w * 3 + j * 3 + k];
			
			// һά������ɢ���ұ任
			WALSH(TempIn, TempOut, wp);
			
			// �����任����
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	return TRUE;
}
BOOL MyProcess::IFreqWALSH(double *f, double *F, LONG width, LONG height)
{
	// ѭ������
	LONG	i;
	LONG	j;
	LONG    k;
	
	// ����ֵ
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// �������и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while (w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while (h < height)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	double* TempIn = new double[w];
	double* TempOut = new double[w];
	
	// ��x�������п��ٸ���Ҷ�任
	for (i = 0; i < h; i++)
	{
		for (k = 0; k < 3; k++)
		{
			// ��ȡ����
			for (j = 0; j < w; j++)
				TempIn[j] = F[i * w * 3 + j * 3 + k];
			
			// һά���ٸ���Ҷ�任
			IWALSH(TempIn, TempOut, wp);
			
			// �����任����
			for (j = 0; j < w; j++)
				F[i * w * 3 + j * 3 + k] = TempOut[j];
		}
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	TempIn = new double[h];
	TempOut = new double[h];
	
	// ��y�������п��ٸ���Ҷ�任
	for (i = 0; i < w * 3; i++)
	{
		// ��ȡ����
		for (j = 0; j < h; j++)
			TempIn[j] = F[j * w * 3 + i];
		
		// һά���ٸ���Ҷ�任
		IWALSH(TempIn, TempOut, hp);
		
		// �����任����
		for (j = 0; j < h; j++)
			F[j * w * 3 + i] = TempOut[j];
	}
	
	// �ͷ��ڴ�
	delete TempIn;
	delete TempOut;
	
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < height && j < width)
				*(f + i * width + j) = F[i * w * 3 + j];
		}
	}
	
	return TRUE;
}
BOOL MyProcess::BmpWalsh(BYTE* bmp,LONG width,LONG height)
{
	// ѭ������
	LONG	i;
	LONG	j;
	
	// �����ֶ�ʲ�����������任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// ����������ɢ���ұ任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while (w < width/3)
	{
		w *= 2;
		wp++;
	}
	
	while (h < height)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	double *f = new double[w * h * 3];
	double *F = new double[w * h * 3];
	
	// ��ʱ����ֵ������
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w * 3; j++)
		{
			if (i < height && j < width)
				f[i * w * 3 + j] = bmp[width * i + j];
			else
				f[w * i * 3 + j] = 0.0f;
		}
	}

	// ����Ƶ�׷���
	if (FreqWALSH(f, F,width, height) == FALSE)
		return FALSE;
	
	// ������������
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			// �ж��Ƿ񳬹�255
			if (fabs(F[i * w * 3 + j] * 1000) > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				bmp[width * (height - 1 - i) + j] = 255;
			}
			else
			{
				// ����û�г���������ʵ�ʼ���������ֵ
				bmp[width * (height - 1 - i) + j]= fabs(F[i * w * 3 + j] * 1000);
			}
		}
	}

	//�ͷ��ڴ�
	delete[] f;
	delete[] F;

	// ����
	return TRUE;
}
void MyProcess::BmpFilter(BYTE *desBmp,BYTE *srcBmp,LONG width,LONG height)
{
	LONG i,j;
	memset(desBmp,0,(width+6)*(height+2));
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			desBmp[(i+1)*(width+6)+j+3]=srcBmp[i*width+j];
		}

}
void MyProcess::KernelFilter(BYTE *bmp,LONG width,LONG height,KERNEL kernel,int type)
{
	LONG i,j;
	//����һ����ʱ�ռ䣬��1��Χbmpͼ�񣬷�������ģ�洦��
	BYTE *temp_bmp = new BYTE[(width+6)*(height+2)];
	BmpFilter(temp_bmp,bmp,width,height);
	//ģ���˲�
	for(i=1;i<height+1;i++)
		for(j=3;j<width+3;j++)
		{
			LONG k,m,temp=0;
			for(k=-1;k<kernel.Dimension-1;k++)
				for(m=-1;m<kernel.Dimension-1;m++)
				{
					int a = temp_bmp[(i+k)*(width+6)+j+m*3];
					int b = kernel.Element[k+1][m+1];
					temp+=a*b;
				}
			temp/=kernel.Divisor;
			//////////////////////////////////////////////////////////////////////////
			//�˴�ע�⣬��Ӧ��ֵ�����������󣬶�Ӧ����δ������ԭͼ��
		//	temp_bmp[i*(width+6)+j] = (BYTE)temp;
			if(type==1) 
			{
				temp = max(0,min(temp+128,255));
			}
			 bmp[(i-1)*width+j-3] = temp;
		}
		delete[] temp_bmp;
}
void MyProcess::MedianFilter(BYTE *bmp,LONG width,LONG height)
{
	LONG i,j;
	//����һ����ʱ�ռ䣬��1��Χbmpͼ�񣬷�������ģ�洦��
	BYTE *temp_bmp = new BYTE[(width+6)*(height+2)];
	BmpFilter(temp_bmp,bmp,width,height);
	//��ֵ�˲�
	//������ֵ
	int value[9];
	for(i=1;i<height+1;i++)
		for(j=3;j<width+3;j++)
		{
			LONG k,m,temp=0;
			for(k=-1;k<2;k++)
				for(m=-1;m<2;m++)
				{
					value[(k+1)*3+(m+1)] = temp_bmp[(i+k)*(width+6)+j+m*3];
				}
				sort(value,value+9);
				//////////////////////////////////////////////////////////////////////////
				//�˴�ע�⣬��Ӧ��ֵ�����������󣬶�Ӧ����δ������ԭͼ��
				//	temp_bmp[i*(width+6)+j] = (BYTE)temp;
				bmp[(i-1)*width+j-3] = value[4];
		}
		delete[] temp_bmp;
}
void MyProcess::ButterworthL(BYTE *bmp,LONG width,LONG height,float fd,int type)
{
	LONG i,j;//ѭ������
	// ���и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	LONG w = 1;
	LONG h = 1;
	int wp = 0;
	int hp = 0;
	
	// �������и���Ҷ�任�Ŀ��Ⱥ͸߶ȣ�2�������η���
	while(w < width/3)
	{
		w *= 2;
		wp++;
	}
	while(h < height)
	{
		h *= 2;
		hp++;
	}// �����ڴ�
	complex<double>*TD;
	complex<double>*FD;
	TD = new complex<double>[w * h * 3];
	FD = new complex<double> [w*h*3];
	BmpTD(bmp,width,height,TD);	
	this->Fourier(TD,width,height,FD);
	//��ǰƵ��
	float now_FD;
	for(i=0;i<h;i++)
		for(j=0;j<w*3;j++)
		{
			//��������
			int k=(int)j/3;
			now_FD = (float)sqrt(i*i+k*k);

			if(type==0) FD[i*3*w+j] *=complex<double>(1/(1+0.414*(now_FD/fd)*(now_FD/fd)),0.0f); 
			else if(type==1) FD[i*3*w+j] *=complex<double>(1/(1+0.414*(fd/now_FD)*(fd/now_FD)),0.0f); 
		}
	//Ƶ��->ʱ��
	if(this->IFourier(bmp,width,height,FD)==false) return;
	//�ͷ��ڴ�	
	delete []FD;
	delete []TD;
}
void MyProcess::SplitRoberts(BYTE *bmp,LONG width,LONG height,int type)
{
	LONG i,j;
	BYTE *temp_bmp = new BYTE [(width+6)*(height+2)];
	//����temp_bmp
	BmpFilter(temp_bmp,bmp,width,height);
	//2*2ģ��
	for(i=1;i<height+1;i++)
		for(j=3;j<width+3;j++)
		{
			if(type==0)//�޲��ؽ�������
			{
				int a = temp_bmp[i*(width+6)+j];
				int b = temp_bmp[(i+1)*(width+6)+j+1];
				int c = temp_bmp[i*(width+6)+j+1];
				int d = temp_bmp[(i+1)*(width+6)+j];
				bmp[(i-1)*width+j-3] = sqrt((a-b)*(a-b)+(c-d)*(c-d));
			}
			else if(type==1)//����ά�ر�Ե����
			{
				int a = temp_bmp[i*(width+6)+j] * -1;
				a+= temp_bmp[i*(width+6)+j+2];
				a+= temp_bmp[(i+1)*(width+6)+j] * -1;
				a+= temp_bmp[(i+1)*(width+6)+j+2];
			if(i<height)
			{
				a+= temp_bmp[(i+2)*(width+6)+j] * -1;
				a+= temp_bmp[(i+2)*(width+6)+j+2];
			}
				int b = temp_bmp[i*(width+6)+j];
				b+= temp_bmp[i*(width+6)+j+1];
				b+= temp_bmp[i*(width+6)+j+2];
			if(i<height)
			{
				b+= temp_bmp[(i+2)*(width+6)+j]*-1;
				b+= temp_bmp[(i+2)*(width+6)+j+1]*-1;
				b+= temp_bmp[(i+2)*(width+6)+j+2]*-1;
			}
				bmp[(i-1)*width+j-3] = sqrt((a)*(a)+(b)*(b));
			}else if(type==2)//��������Ե����
			{
				int a = temp_bmp[i*(width+6)+j] * -1;
				a+= temp_bmp[i*(width+6)+j+2];
				a+= temp_bmp[(i+1)*(width+6)+j] * -2;
				a+= temp_bmp[(i+1)*(width+6)+j+2]*2;
				if(i<height)
				{
					a+= temp_bmp[(i+2)*(width+6)+j] * -1;
					a+= temp_bmp[(i+2)*(width+6)+j+2];
				}
				int b = temp_bmp[i*(width+6)+j];
				b+= temp_bmp[i*(width+6)+j+1]*2;
				b+= temp_bmp[i*(width+6)+j+2];
				if(i<height)
				{
					b+= temp_bmp[(i+2)*(width+6)+j]*-1;
					b+= temp_bmp[(i+2)*(width+6)+j+1]*-2;
					b+= temp_bmp[(i+2)*(width+6)+j+2]*-1;
			}
				bmp[(i-1)*width+j-3] = sqrt((a)*(a)+(b)*(b));
			}
		}
	delete []temp_bmp;
}
void MyProcess::SplitKirsch(BYTE *bmp,LONG width,LONG height)
{
	LONG i,j;
	//����һ����ʱ�ռ䣬��1��Χbmpͼ�񣬷�������ģ�洦��
	BYTE *temp_bmp = new BYTE[(width+6)*(height+2)];
	BmpFilter(temp_bmp,bmp,width,height);
	//ģ���˲�
	for(i=1;i<height+1;i++)
		for(j=3;j<width+3;j++)
		{
			LONG g,max=-99999;
			for(g=0;g<4;g++)
			{
				LONG k,m,temp=0;
			for(k=-1;k<kernel_kirsch[g].Dimension-1;k++)
				for(m=-1;m<kernel_kirsch[g].Dimension-1;m++) 
				{
					int a = temp_bmp[(i+k)*(width+6)+j+m*3];
					int b = kernel_kirsch[g].Element[k+1][m+1];
					temp+=a*b;
				}
				//temp/=kernel.Divisor;
				//////////////////////////////////////////////////////////////////////////
				//�˴�ע�⣬��Ӧ��ֵ�����������󣬶�Ӧ����δ������ԭͼ��
				//	temp_bmp[i*(width+6)+j] = (BYTE)temp;
				if(temp>max) max = temp;
			}
			bmp[(i-1)*width+j-3] = max;
		}
		delete[] temp_bmp;
}
void MyProcess::SplitContour(BYTE *bmp,LONG width,LONG height)
{
	LONG i,j;
	BYTE *temp_bmp = new BYTE[width*height];
	memcpy(temp_bmp,bmp,width*height);
	for(i=0;i<height;i++)
		for(j=0;j<width/3;j++)
		{
			int I=0,temp_r,temp_g,temp_b;
			temp_r = temp_bmp[i*width+j*3];
			temp_g = temp_bmp[i*width+j*3+1];
			temp_b = temp_bmp[i*width+j*3+2];
			for(int k=i-1;k<i+2;k++)
				for(int l=j-1;l<j+2;l++)
				{
					if(k>=0 && l>=0 && l<width && k<height)
					{
						if(abs(temp_bmp[k*width+l*3]-temp_r) < 10 &&
							abs(temp_bmp[k*width+l*3+1]-temp_g) <10 &&
							abs(temp_bmp[k*width+l*3+2]-temp_b) <10)
						{
							I++;
						}
					}
				}
				if(I==9)
				{
					bmp[i*width+j*3]=255;
					bmp[i*width+j*3+1]=255;
					bmp[i*width+j*3+2]=255;
				}
		}
		delete[] temp_bmp;
}
void MyProcess::HoufuLine(BYTE *bmp,LONG width,LONG height)
{
	LONG i,j,angle,p;
	BYTE *temp_bmp = new BYTE[width*height];
	//ͼ����ֵ��
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			if(bmp[i*width+j]>128) temp_bmp[i*width+j]=255;
			else temp_bmp[i*width+j]=0;
		}
	//�洢�ۼƱ���������
		//��������
	int maxDis = sqrt(width*width+height*height);
	int *num = new int [360*maxDis];
	//��ʼ������
	memset(num,0,(360*maxDis)*sizeof(int));
	//����ֱ�ߣ�p=xcos(angle)+ysin(angle);
	//���ҳ�������num[angle][p],����ȷ��һ��ֱ��
	int max=0,maxa,maxp;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			if(temp_bmp[i*width+j]==0)
			for(angle=0;angle<360;angle++)
			{
				p=abs(i*sin(angle/360.0*6.28)+j*cos(angle/360.0*6.28));
				num[p*360+angle]++;
				if(max < num[p*360+angle])
				{
					max=num[p*360+angle];
					maxa=angle;
					maxp=p;
				}
			}
		}
	//�ҳ�ֱ�ߵĲ���---��Ŀ����һ��ֵ����Ϊ��ֱ��
		int line = width/10;
//	for(i=0;i<360;i++)
//		for(j=0;j<width+height;j++)
		{
//			if(num[i*maxDis+j]>line)
			{
				 /*double k=tan(i/360.0*6.28);
				 double b=j/sin(i/360.0*6.28);
				 for(int m=0;m<width;m++)
				 {
					 int y = k*m+b;
					 bmp[y*width+m]=0;
				 }*/
				int k,m;
				for(k=0;k<height;k++)
					for(m=0;m<width;m++)
					{
					//	if(temp_bmp[k*width+m]==0)
						{
								if(maxp==abs(m*cos(maxa/360.0*6.28)+k*sin(maxa/360.0*6.28)))
								{
									bmp[k*width+m]=0;
								}
						}
					}
		
				
			}
		}
	
}
int MyProcess::Threshold(BYTE *bmp,LONG width,LONG height)
{
	//�õ��Ҷȷֲ�ֱ��ͼ��ֵ
	int *grayInt = new int [256];
	memset(grayInt,0,256*sizeof(int));
	this->GetGrayIntensity(bmp,grayInt,width,height);
	//������ֵ
	long T1=127,T2=0;
	long i,j;
	//������ֵѡȡ
	long temp0=0,temp1=0,temp2=0,temp3=0;
	while(1)
	{
		//������ʱ����
		for(i=0;i<T1+1;i++)
		{
			temp0+=grayInt[i]*i;
			temp1+=grayInt[i];
		}
		for(;i<256;i++)
		{
			temp2+=grayInt[i]*i;
			temp3+=grayInt[i];
		}
		T2 = (temp0/temp1+temp2/temp3)/2;
		//�����Ƿ�����
		if(T1==T2) break;
		else T1=T2;
	}
	//��bmp����ת��
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			if(bmp[i*width+j]<T1) bmp[i*width+j]=0;
			else bmp[i*width+j]=255;
		}
		delete[] grayInt;
	return T1;
}
void MyProcess::RgnGrow(BYTE *bmp,LONG width,LONG height,BYTE c1,BYTE c2)
{
	LONG i,j;
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
		{
			BYTE temp=bmp[i*width+j];
			if(abs(temp-c1)<abs(temp-c2))
			{
				bmp[i*width+j]=c1;
			}
			else
			{
				bmp[i*width+j]=c2;
			}
		}
}

void MyProcess::Erosion(BYTE *bmp,LONG width,LONG height,KERNEL kernel)
{
	LONG i,j,k,m;//ѭ������
	LONG door=128;//������ֵ
	BYTE *temp_bmp = new BYTE[(width+6)*(height+2)];
	BmpFilter(temp_bmp,bmp,width,height);
	//��ʴ������ȡ����������ֵ
	for(i=1;i<height+1;i++)
		for(j=3;j<width+3;j++)
		{
			for(k=-1;k<kernel.Dimension-1;k++)
				for(m=-1;m<kernel.Dimension-1;m++)
				{
					int a = temp_bmp[(i+k)*(width+6)+j+m*3];
					int b = kernel.Element[k+1][m+1];
					if(a*b>door) bmp[(i-1)*width+j-3] = 255;	
				}
		}
	delete[] temp_bmp;

}
void MyProcess::Dilation(BYTE *bmp,LONG width,LONG height,KERNEL kernel)
{
	LONG i,j,k,m;//ѭ������
	LONG door=128;//������ֵ
	BYTE *temp_bmp = new BYTE[(width+6)*(height+2)];
	BmpFilter(temp_bmp,bmp,width,height);
	//���ʹ�����ȡ��������Сֵ
	for(i=1;i<height+1;i++)
		for(j=3;j<width+3;j++)
		{
			for(k=-1;k<kernel.Dimension-1;k++)
				for(m=-1;m<kernel.Dimension-1;m++)
				{
					int a = temp_bmp[(i+k)*(width+6)+j+m*3];
					int b = kernel.Element[k+1][m+1];
					if(b!=0 && a*b<=door) bmp[(i-1)*width+j-3] = 0;	
				}
		}
		delete[] temp_bmp;
		
}
void MyProcess::OpenOperate(BYTE *bmp,LONG width,LONG height,KERNEL array)
{
	Erosion(bmp,width,height,array);
	Dilation(bmp,width,height,array);
}
void MyProcess::CloseOperate(BYTE *bmp,LONG width,LONG height,KERNEL array)
{
	Dilation(bmp,width,height,array);
	Erosion(bmp,width,height,array);
}