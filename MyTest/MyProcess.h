#pragma once
#include "MyBitmap.h"
#include "algorithm"
#include "cmath"
#include <complex>
#define PI 3.1415926
struct KERNEL//滤波模版结构
{
	int Element[3][3];//模版元素
	int Divisor;//除以的系数
	int Dimention;//维数
};
//滤波模版
const KERNEL kernel[]={
	{   0,1,0,
		1,1,1,
		0,1,0,
		5,3
	},
	{
		1,1,1,
		1,0,1,
		1,1,1,
		8,3
	},
	{
		1,1,1,
		1,1,1,
		1,1,1,
		9,3
	},
	{
		1,1,1,
		1,2,1,
		1,1,1,
		10,3
	},
	{/////////////////高斯滤波模版 下标4
		1,2,1,
		2,4,2,
		1,2,1,
		16,3
	},
/////////////线性锐化模版
		{///拉普拉斯算子  下标5
			-1,-1,-1,
			-1,8,-1,
			-1,-1,-1,
			9,3
		},
		{	
			-2,-2,-2,
			-2,16,-2,
			-2,-2,-2,
			9,3
		},
	//////浮雕效果模版 下标7到13
			{-1,0,0,
			0,0,0,
			0,0,1,
			1,3
			},
			{1,0,0,
			0,0,0,
			0,0,-1,
			1,3
			},
			{0,0,-1,
			0,0,0,
			1,0,0,
			1,3
			},
			{0,0,1,
			0,0,0,
			-1,0,0,
			1,3
			},
			{-1,0,-1,
			0,0,0,
			1,0,1,
			1,3
			},
			{-1,0,1,
			0,0,0,
			1,0,-1,
			1,3
			},
			{1,0,1,
			0,0,0,
			-1,0,-1,
			1,3
			},
			{1,0,-1,
			0,0,0,
			-1,0,1,
			1,3
			}


};
//Kirsch方向算子数组
const KERNEL kernel_kirsch[]={
	{5,5,5,
	-3,0,-3,
	-3,-3,-3,
	1,3},
	{-3,5,5,
	-3,0,5,
	-3,-3,-3,
	1,3},
	{-3,-3,5,
	-3,0,5,
	-3,-3,5,
	1,3},
	{-3,-3,-3,
	-3,0,5,
	-3,5,5,
	1,3}
};
//腐蚀OR膨胀数组
const KERNEL kernel_erosion[]=
{
	//垂直方向
	{0,1,0,
	0,1,0,
	0,1,0,
	1,3
	},
	//水平方向
	{0,0,0,
	1,1,1,
	0,0,0,
	1,3
	},
	//十方向
	{0,1,0,
	1,1,1,
	0,1,0,
	1,3
	},
	//8方向
	{1,1,1,
	1,1,1,
	1,1,1,
	1,3
	}
};
class MyProcess
{
public:
	/************************************************************************/
	/* 函数名称： GetGray()
		参数： MyBitmap myBmp --------待处理的24位bmp位图
		unsigned char* srcchar --------存放灰度图像的数组
		返回值 无
		说明 ： 该函数用来得到24为位图的灰度图像
	/************************************************************************/
	void GetGray(MyBitmap myBmp,unsigned char *srcchar);//将输入图像转换为灰度图，只处理24位bmp


	/************************************************************************/
	/* 函数名称： GetGrayIntensity()
		参数： unsigned char *gray --------待处理的灰度图
		int *grayInt --------存放灰度直方图的数组
		LONG width,LONG height-------图像的宽度和高度
		返回值 无
		说明 ： 该函数用来得到灰度图像的直方图
	/************************************************************************/
	void GetGrayIntensity(unsigned char *gray,int *grayInt,LONG width,LONG height);//得到灰度图的灰度直方图

	/************************************************************************/
	/* 函数名称： GetIntensity()
		参数： unsigned char *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		int *R,int *G,int *B -------存放各个分量直方图的数组
		返回值 无
		说明 ： 该函数用来得到彩色图像的直方图
	/************************************************************************/
	void GetIntensity(unsigned char *bmp,LONG width,LONG height,int *R,int *G,int *B);


	/************************************************************************/
	/* 函数名称： ShowArrayToDevice()
		参数： CDC *dc --------设备句柄
		int x, int y ----------显示的位置
		unsigned char* srcchar --------存放图像的数组
		LONG width,LONG height-------图像的宽度和高度
		int type ----图像类型 0---彩色，1---灰度,默认是灰度图
		返回值 无
		说明 ： 该函数用来在设备的指定位置上显示图像
	/************************************************************************/
	void ShowArrayToDevice(CDC *dc, int x, int y,unsigned char *array,LONG width,LONG height,int type=1);//将图像数组显示在设备上


	/************************************************************************/
	/* 函数名称： PointInvert()
		参数： unsigned char *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		返回值 无
		说明 ： 该函数将图像进行反色变换处理,注意：会改变原图片
	/************************************************************************/
	void PointInvert(unsigned char *bmp,LONG width,LONG height);


	/************************************************************************/
	/* 函数名称： GrayStretch()
		参数： unsigned char *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		BYTE bx1 -------折线1的原始灰度
		BYTE by1
		返回值 无
		说明 ： 该函数将图像进行折线变换，即将0-255灰度映射到另一个范围内
	/************************************************************************/
	void GrayStretch(unsigned char *bmp,LONG width,LONG height,BYTE bx1,BYTE by1,BYTE bx2,BYTE by2);

	/************************************************************************/
	/* 函数名称： WindowTrans()
		参数： unsigned char *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		BYTE bLow	 -------- 窗口下限
		BYTE bUp	 -------- 窗口上限
		返回值 无
		说明 ： 对图像进行灰度窗口变换，即小于下限为0，大于上限为255，中间线性变换
	/************************************************************************/
	void WindowTrans(BYTE *bmp,LONG width,LONG height ,BYTE bLow,BYTE bUp);

	/************************************************************************/
	/* 函数名称： DynamicCompress()
		参数： unsigned char *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		int C --------- 非线性变换比例常数
		返回值 无
		说明 ： 对图像进行非线性变换 公式：D0=EH(D1)=Clog(1+|D1|),用于动态范围过大时
	/************************************************************************/
	void DynamicCompress(BYTE *bmp,LONG width,LONG height,int C);

	/************************************************************************/
	/* 函数名称： PointEqua()
		参数： BYTE *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		int type --------图像类型，0：24位彩色，1：灰度
		返回值 无
		说明 ： 对图像进行均衡变换
	/************************************************************************/
	void PointEqua(BYTE *bmp,LONG width,LONG height,int type=0);
	/************************************************************************/
	/* 函数名称： PointEqua()
		参数： BYTE *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
		BYTE bNum ----规定直方图灰度级数
		int *Nu-------规定直方图灰度映射关系
		float *Pu-----规定直方图各灰度的分布概率
		int type --------图像类型，0：24位彩色，1：灰度
		返回值 无
		说明 ： 对图像进行单映射规则直方图规定化变换
	/************************************************************************/
	void PointSML(BYTE *bmp,LONG width,LONG height,BYTE bNum,int *Nu,float *Pu,int type=0);
	
	/*************************************************************************
	*
	* 函数名称：
	*   FFT()
	*
	* 参数:
	*   complex<double> * TD	- 指向时域数组的指针
	*   complex<double> * FD	- 指向频域数组的指针
	*   r						－2的幂数，即迭代次数
	*
	* 返回值:
	*   无。
	*
	* 说明:
	*   该函数用来实现快速付立叶变换。
	*
 ************************************************************************/
	void FFT(std::complex<double>*TD,std::complex<double>*FD,int r);
	
	/*************************************************************************
	*
	* 函数名称：
	*   IFFT()
	*
	* 参数:
	*   complex<double> * FD	- 指向频域值的指针
	*   complex<double> * TD	- 指向时域值的指针
	*   r						－2的幂数
	*
	* 返回值:
	*   无。
	*
	* 说明:
	*   该函数用来实现快速付立叶逆变换。
	*
	************************************************************************/
	void IFFT(std::complex<double> * FD, std::complex<double> * TD, int r);
	/*************************************************************************
	*
	* 函数名称：
	*   Fourier()
	*
	* 参数:
	*   complex* TD		- 输入的时域序列
	*	 LONG lWidth		- 图象宽度
	*	 LONG lHeight		- 图象高度
	*	 complex* FD		- 输出的频域序列
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行二维快速付立叶变换。
	*
	************************************************************************/
	BOOL Fourier(std::complex<double> * TD, LONG width, LONG height, std::complex<double> * FD);

	/*************************************************************************
	*
	* 函数名称：
	*   IFourier()
	*
	* 参数:
	*   LPBYTE TD			- 返回的空域数据
	*   LONG lWidth		- 空域图象的宽度
	*	 LONG lHeight		- 空域图象的高度
	*	 complex* FD		- 输入的频域数据
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行二维快速付立叶逆变换。
	*
	************************************************************************/
	BOOL IFourier(LPBYTE TD, LONG width, LONG height, std::complex<double> * FD);

	/*************************************************************************
	*
	* 函数名称：
	*   BmpFourier()
	*
	* 参数:
	*   BYTE *bmp --------待处理的图像
		LONG width,LONG height-------图像的宽度和高度
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数用来对图像进行付立叶变换。
	*
	************************************************************************/
	BOOL BmpFourier(BYTE* bmp,LONG width,LONG height);
	/************************************************************************/
	/* 回去bmp的时域                                                                     */
	/************************************************************************/
	BOOL BmpTD(BYTE *bmp,LONG width,LONG height,std::complex<double>*TD);
	/*************************************************************************
	*
	* 函数名称：
	*   DCT()
	*
	* 参数:
	*   double * f				- 指向时域值的指针
	*   double * F				- 指向频域值的指针
	*   r						－2的幂数
	*
	* 返回值:
	*   无。
	*
	* 说明:
	*   该函数用来实现一维快速离散余弦变换
	*
	************************************************************************/
	void DCT(double *f, double *F, int r);
	
	/*************************************************************************
	*
	* 函数名称：
	*   IDCT()
	*
	* 参数:
	*   double * F				- 指向频域值的指针
	*   double * f				- 指向时域值的指针
	*   r						－2的幂数
	*
	* 返回值:
	*   无。
	*
	* 说明:
	*   该函数实现一维快速离散余弦逆变换
	*
	************************************************************************/
	void IDCT(double *F, double *f, int r);

	/*************************************************************************
	*
	* 函数名称：
	*   FreqDCT()
	*
	* 参数:
	*   double* f			- 输入的时域序列
	*   double* F			- 输出的频域序列
	*	 LONG width			- 图象宽度
	*	 LONG h		- 图象高度
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行二维快速离散余弦变换。
	*
	************************************************************************/
	BOOL FreqDCT(double *f, double *F, LONG width, LONG height);

	/*************************************************************************
	*
	* 函数名称：
	*   IFreqDCT()
	*
	* 参数:
	*   double* f			- 输入的时域序列
	*   double* F			- 输出的频域序列
	*	 LONG width			- 图象宽度
	*	 LONG height		- 图象高度
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行二维快速离散余弦逆变换。
	*
	************************************************************************/
	BOOL IFreqDCT(double *f, double *F, LONG lWidth, LONG lHeight);

	/*************************************************************************
	*
	* 函数名称：
	*   DIBDCT()
	*
	* 参数:
	*   BYTE* bmp,LONG width,LONG height
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数用来对图像进行离散余弦变换。
	*
	************************************************************************/
	BOOL BmpDCT(BYTE* bmp,LONG width,LONG height);

	/*************************************************************************
	*
	* 函数名称：
	*   WALSH()
	*
	* 参数:
	*   double* f			- 输入的时域序列
	*   double* F			- 输出的频域序列
	*   int r				- 2的幂数		
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行一维快速沃尔什——哈达马变换。
	*
	************************************************************************/
	void WALSH(double *f, double *F, int r);

	/*************************************************************************
	*
	* 函数名称：
	*   IWALSH()
	*
	* 参数:
	*   double* f			- 输入的时域序列
	*   double* F			- 输出的频域序列
	*   int r				- 2的幂数		
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行一维快速沃尔什——哈达马逆变换。
	*
	************************************************************************/
	void IWALSH(double *F, double *f, int r);

	/*************************************************************************
	*
	* 函数名称：
	*   FreqWALSH()
	*
	* 参数:
	*   double* f			- 输入的时域序列
	*   double* F			- 输出的频域序列
	*	 LONG width			- 图象宽度
	*	 LONG height		- 图象高度
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行二维快速沃尔什——哈达玛变换。
	*
	************************************************************************/
	BOOL FreqWALSH(double *f, double *F, LONG width, LONG height);

	/*************************************************************************
	*
	* 函数名称：
	*   IFreqWALSH()
	*
	* 参数:
	*   double* f			- 输入的时域序列
	*   double* F			- 输出的频域序列
	*	 LONG width		- 图象宽度
	*	 LONG height		- 图象高度
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数进行二维快速沃尔什——哈达玛逆变换。
	*
	************************************************************************/
	BOOL IFreqWALSH(double *f, double *F, LONG width, LONG height);

	/*************************************************************************
	*
	* 函数名称：
	*   BmpWalsh()
	*
	* 参数:
	*   BYTE* bmp,LONG width,LONG height
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数对图象进行二维快速沃尔什——哈达马变换。
	*
	************************************************************************/
	BOOL BmpWalsh(BYTE* bmp,LONG width,LONG height);

//////////////////////////////////////////////////////////////////////////
// 图像增强 滤波
//////////////////////////////////////////////////////////////////////////
	
	/*************************************************************************
	*
	* 函数名称：
	*   KernelFilter()
	*
	* 参数:
	*   BYTE* bmp,LONG width,LONG height ------图像参数
		KERNEL kernel ---------模版
		int type ---------用来判断是否要进行浮雕处理--要加强对比度+128,默认为0，不要
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE
	*
	* 说明:
	*   该函数对图象进行模版滤波。
	*
	************************************************************************/
	void KernelFilter(BYTE *bmp,LONG width,LONG height,KERNEL kernel,int type=0);

	/*************************************************************************
	*
	* 函数名称：
	*   BmpFilter()
	*
	* 参数:
	*   BYTE *srcBmp	--------原图像
		BYTE *desBmp	--------转换后图像
		LONG width,LONG height ------图像参数
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数将原图像转换为由1填充的图像，方便进行模版滤波。
	*
	************************************************************************/
	void BmpFilter(BYTE *desBmp,BYTE *srcBmp,LONG width,LONG height);

	/*************************************************************************
	* 函数名称：
	*   MedianFilter()
	*
	* 参数:
	*   BYTE* bmp,LONG width,LONG height ------图像参数
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数对图象进行中值滤波。
	*
	************************************************************************/
	void MedianFilter(BYTE *bmp,LONG width,LONG height);

	/*************************************************************************
	* 函数名称：
	*   ButterworthL()
	*
	* 参数:
	*   BYTE* bmp,LONG width,LONG height ------图像参数
		float fd -------滤波阀值
		int type -------低通还是高通  0--低通，1--高通
	*
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	*
	* 说明:
	*   该函数对图象进行布特沃斯滤波。
	*
	************************************************************************/
	void ButterworthL(BYTE *bmp,LONG width,LONG height,float fd,int type=0);



	//////////////////////////////////////////////////////////////////////////
	// 图像分割
	//
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	// 并行边界分割法
	
	/*************************************************************************
	* 函数名称：
	*   SplitRoberts()
	* 参数:
	*   BYTE* bmp,LONG width,LONG height ------图像参数
		int type ----边缘检测类型 0:罗伯特交叉算子 1:薄瑞维特边缘算子 2:索贝尔边缘算子
	
	* 返回值:
	*   BOOL               - 成功返回TRUE，否则返回FALSE。
	* 说明:该函数对图象进行边缘检测。
	0： 1  0      0 1                
		0 -1     -1 0 采用2*2算子，所以只能对具有陡峭的低噪声图像才有很好的效果
	1： -1  0  1          1 1 1       采用3*3模版，效果优与罗伯特交叉算子
		-1  0  1          0 0 0
		-1  0  1          1 1 1
	2： -1  0  1          1 2 1       由于前面2种
		-2  0  2          0 0 0
		-1  0  1          1 2 1
	拉普拉斯算子在滤波中有，这里不再实现，其适合无噪声的情况
	************************************************************************/
	void SplitRoberts(BYTE *bmp,LONG width,LONG height,int type=0);

	/*************************************************************************
	* 函数名称:SplitKirsch()
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
	* 返回值:无
	* 说明:该函数进行Kirsch方向算子边缘检测。
	************************************************************************/
	void SplitKirsch(BYTE *bmp,LONG width,LONG height);

	/*************************************************************************
	* 函数名称:SplitContour()
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
	* 返回值:无
	* 说明:轮廓提取，8领域与中间像素一致则改为白色，为非边界
	************************************************************************/
	void SplitContour(BYTE *bmp,LONG width,LONG height);

	/*************************************************************************
	* 函数名称:HoufuLine()
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
	* 返回值:无
	* 说明:Houfu直线检测,图像必须为灰度图，且直线是<128,检测出一条最长直线;
	************************************************************************/
	void HoufuLine(BYTE *bmp,LONG width,LONG height);

	//////////////////////////////////////////////////////////////////////////
	//并行区域分割算法

	/*************************************************************************
	* 函数名称:Threshold()
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
	* 返回值:int 阈值，返回迭代的阈值
	* 说明:并行区域分割，迭代求阈值，先取一阈值，分割图像，分别积分并平均，反复迭代，直到阈值不变
	积分即离散值加权和
	************************************************************************/
	int Threshold(BYTE *bmp,LONG width,LONG height);

	//////////////////////////////////////////////////////////////////////////
	//串行区域分割

	/*************************************************************************
	* 函数名称:RgnGrow() 
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
		BYTE c1,BYTE c2 种子1和种子二的值
	* 返回值:无
	* 说明:串行区域分割，区域生长 对灰度图进行处理
	************************************************************************/
	void RgnGrow(BYTE *bmp,LONG width,LONG height,BYTE c1,BYTE c2);

	//////////////////////////////////////////////////////////////////////////
	//腐蚀与膨胀
	//////////////////////////////////////////////////////////////////////////
	
	/*************************************************************************
	* 函数名称:Erosion() 
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
		KERNEL array 腐蚀方向数组
	* 返回值:无
	* 说明:对图像进行不同方向的腐蚀处理
	************************************************************************/
	void Erosion(BYTE *bmp,LONG width,LONG height,KERNEL array);

	/*************************************************************************
	* 函数名称:Dilation() 
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
		KERNEL array 膨胀方向数组
	* 返回值:无
	* 说明:对图像进行不同方向的膨胀处理
	************************************************************************/
	void Dilation(BYTE *bmp,LONG width,LONG height,KERNEL array);

	/*************************************************************************
	* 函数名称:OpenOperate() 
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
		KERNEL array 方向数组
	* 返回值:无
	* 说明:对图像进行开运算，即先腐蚀再膨胀
	************************************************************************/
	void OpenOperate(BYTE *bmp,LONG width,LONG height,KERNEL array);

	/*************************************************************************
	* 函数名称:CloseOperate() 
	* 参数:BYTE* bmp,LONG width,LONG height ------图像参数
		KERNEL array 方向数组
	* 返回值:无
	* 说明:对图像进行闭运算，即先膨胀再腐蚀
	************************************************************************/
	void CloseOperate(BYTE *bmp,LONG width,LONG height,KERNEL array);
};