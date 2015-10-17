// MyTestView.cpp : implementation of the CMyTestView class
//

#include "stdafx.h"
#include "MyTest.h"
#include "MyProcess.h"
#include "MyTestDoc.h"
#include "MyTestView.h"
#include "Histogram.h"
#include "BmpDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTestView

IMPLEMENT_DYNCREATE(CMyTestView, CView)

BEGIN_MESSAGE_MAP(CMyTestView, CView)
	//{{AFX_MSG_MAP(CMyTestView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_GRAY, OnGray)
	ON_COMMAND(ID_GRAYINST,OnGrayInst)
	ON_COMMAND(ID_INVERT,OnInvert)
	ON_COMMAND(ID_STRETCH,OnStretch)
	ON_COMMAND(ID_WINDOWSTRANS,OnWindowsTran)
	ON_COMMAND(ID_DYNAMICCOMPRESS,OnDynamicCompress)
	ON_COMMAND(ID_EQUA,OnEqua)
	ON_COMMAND(IDD_BMP, OnIDDBmp)
	ON_COMMAND(IDD_GRAY, OnIDDGray)
	ON_COMMAND(ID_FOURIER, OnFourier)
	ON_COMMAND(ID_DCT, OnDct)
	ON_COMMAND(ID_WALSH, OnWalsh)
	ON_COMMAND(ID_KERNEL, OnKernel)
	ON_COMMAND(ID_SFILTER, OnSfilter)
	ON_COMMAND(ID_MEDIANFILTER, OnMedianfilter)
	ON_COMMAND(ID_EMBOSS1, OnEmboss1)
	ON_COMMAND(ID_EMBOSS2, OnEmboss2)
	ON_COMMAND(ID_EMBOSS3, OnEmboss3)
	ON_COMMAND(ID_EMBOSS4, OnEmboss4)
	ON_COMMAND(ID_EMBOSS5, OnEmboss5)
	ON_COMMAND(ID_EMBOSS6, OnEmboss6)
	ON_COMMAND(ID_EMBOSS7, OnEmboss7)
	ON_COMMAND(ID_EMBOSS8, OnEmboss8)
	ON_COMMAND(ID_BUTTERWORTHL, OnButterworthl)
	ON_COMMAND(ID_BUTTERWG, OnButterwg)
	ON_COMMAND(ID_SPROBERTS, OnSproberts)
	ON_COMMAND(ID_PREWITT, OnPrewitt)
	ON_COMMAND(ID_SOBEL, OnSobel)
	ON_COMMAND(ID_KIRSCH, OnKirsch)
	ON_COMMAND(ID_CONTOUR, OnContour)
	ON_COMMAND(ID_HOUFU, OnHoufu)
	ON_COMMAND(ID_THRESHOLD, OnThreshold)
	ON_COMMAND(ID_RGNGROW, OnRgngrow)
	ON_COMMAND(ID_VEROSION, OnVerosion)
	ON_COMMAND(ID_HEROSION, OnHerosion)
	ON_COMMAND(ID_4EROSION, On4erosion)
	ON_COMMAND(ID_8EROSION, On8erosion)
	ON_COMMAND(ID_4DILATION, On4dilation)
	ON_COMMAND(ID_8DILATION, On8dilation)
	ON_COMMAND(ID_HDILATION, OnHdilation)
	ON_COMMAND(ID_VDILATION, OnVdilation)
	ON_COMMAND(ID_CLOSEOPERATE, OnCloseoperate)
	ON_COMMAND(ID_OPENOPERATE, OnOpenoperate)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTestView construction/destruction

CMyTestView::CMyTestView()
{
	// TODO: add construction code here
	myBmp.GetBmp()=NULL;
	gray = NULL;
	BmpORGray=0;
}

CMyTestView::~CMyTestView()
{
}

BOOL CMyTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//RECT rect;
	//GetWindowRect(&rect);
	//width = rect.right - rect.left;
	//height = rect.bottom - rect.top;
	width = cs.cx=900;
	height = cs.cy=800;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyTestView drawing

void CMyTestView::OnDraw(CDC* pDC)
{
	CMyTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *dc = GetDC();
	dc->BitBlt(0, 0, width, height, &dcMemory, 0, 0, SRCCOPY);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyTestView printing

BOOL CMyTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyTestView diagnostics

#ifdef _DEBUG
void CMyTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMyTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyTestDoc* CMyTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyTestDoc)));
	return (CMyTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTestView message handlers

void CMyTestView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	CFileDialog fileDlg(true);
	fileDlg.m_ofn.lpstrTitle="读取文件";
	fileDlg.m_ofn.lpstrFilter="位图(*.bmp)\0*.bmp\0\0";
	if(IDOK==fileDlg.DoModal())
	{
		CString s_name = fileDlg.GetFileName();
		CString s_path = fileDlg.GetPathName(); 
		myBmp.GetBmpByFilepath(s_path.GetBuffer(s_path.GetLength()+1));//获取图片数组
		myBmp.SetBmpName(s_name.GetBuffer(s_name.GetLength()+1));//设置图片名称
		s_name.ReleaseBuffer();
		s_path.ReleaseBuffer();
	}
	if(myBmp.GetBmp()!=NULL)//如果图片读取成功，显示图片
	{
		CDC *dc = GetDC();
		dcMemory.DeleteDC();//先删除双重缓冲，防止创建兼容缓冲时因为已经创建而失败
		dcMemory.CreateCompatibleDC(dc);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(dc, width, height);
		dcMemory.SelectObject(&bitmap);
		CRect rect2(0,0,width,height); 
		dcMemory.FillSolidRect(&rect2,RGB(255,255,255));
		BmpDlg *bmpdlg = new BmpDlg();
		bmpdlg->Init(NULL,myBmp.GetBmpWidth(),myBmp.GetHeight());
		bmpdlg->Create(IDD_HISTOGRAM,this);
		bmpdlg->SetWindowText(myBmp.GetBmpName());	
		myBmp.ShowBmpToDevice(&bmpdlg->dcMemory,0,0);//在双重缓冲中绘图
		bmpdlg->ShowWindow(SW_SHOW);
		gray=NULL;	
	//	dc->BitBlt(0, 0, myBmp.GetBmpWidth(), myBmp.GetHeight(), &dcMemory, 0, 0, SRCCOPY);//显示在dc中
	}
}

void CMyTestView::OnGray() 
{
	// TODO: Add your command handler code here
	if(myBmp.GetBmp()==NULL) 
	{
		MessageBox("请先打开一张BMP格式位图！！！");
		return ;
	}
	gray = new unsigned char[myBmp.GetBmpWidth()*myBmp.GetHeight()];
	MyProcess myProcess;
	myProcess.GetGray(myBmp,gray);
//	
	BmpDlg *bmpdlg = new BmpDlg();
	bmpdlg->Init(NULL,myBmp.GetBmpWidth(),myBmp.GetHeight());
	bmpdlg->Create(IDD_HISTOGRAM,this);
	CString s("灰度图");
	s+=myBmp.GetBmpName();
	bmpdlg->SetWindowText(s);
	myProcess.ShowArrayToDevice(&bmpdlg->dcMemory,0,0,gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
	bmpdlg->ShowWindow(SW_SHOW);
//	Invalidate();	
}
void CMyTestView::OnGrayInst()
{
	if(BmpORGray == 1 && gray==NULL) 
	{
		MessageBox("请先转换成灰度图像！！！");
		return ;
	}
	if(BmpORGray == 0 && myBmp.GetBmp()==NULL)
	{
		MessageBox("请先打开一张BMP格式位图！！！");
		return ;
	}
	if(BmpORGray == 1)
	{
		Histogram *hisDlg = new Histogram();
		grayIns = new int[256];
		for(int i=0;i<256;i++)
			grayIns[i]=0;
		MyProcess myProcess;
		myProcess.GetGrayIntensity(gray,grayIns,myBmp.GetBmpWidth(),myBmp.GetHeight());
		hisDlg->Init(grayIns,0);
		hisDlg->m_fileName = myBmp.GetBmpName();
		hisDlg->Create(IDD_HISTOGRAM,this);
		CString s("Histogram ");
		s+=myBmp.GetBmpName();
		hisDlg->SetWindowText(s);
		hisDlg->ShowWindow(SW_SHOW);
	}
	if(BmpORGray == 0)
	{
		Histogram *hisDlg = new Histogram();
		int R[3][256];
		memset(R,0,sizeof(R));
		COLORREF c[3]={RGB(255,0,0),RGB(0,255,0),RGB(0,0,255)};
		MyProcess myProcess;
		myProcess.GetIntensity(myBmp.GetBmp(),myBmp.GetWidth(),myBmp.GetHeight(),R[0],R[1],R[2]);
		hisDlg->Init(3,R,c);
		hisDlg->m_fileName = myBmp.GetBmpName();
		hisDlg->Create(IDD_HISTOGRAM,this);
		CString s("Histogram ");
		s+=myBmp.GetBmpName();
		hisDlg->SetWindowText(s);
		hisDlg->ShowWindow(SW_SHOW);
	}
}
void CMyTestView::OnInvert()
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.PointInvert(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
		CreateDlg("灰度图反色",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.PointInvert(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		CreateDlg("彩色图反色",temp_bmp);
	}
}
void CMyTestView::OnStretch()
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.GrayStretch(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),50,100,150,220);
		CreateDlg("灰度图折线变换",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.GrayStretch(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),50,100,150,220);
		CreateDlg("彩色图折线变换",temp_bmp);
	}
}
void CMyTestView::OnWindowsTran()
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.WindowTrans(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),50,200);
		CreateDlg("灰度图 灰度窗口变换",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.WindowTrans(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),50,200);
		CreateDlg("彩色图灰度窗口变换",temp_bmp);
	}
}
void CMyTestView::OnDynamicCompress()
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.DynamicCompress(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),45);
		CreateDlg("灰度图 动态压缩",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.DynamicCompress(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),45);
		CreateDlg("彩色图 动态压缩",temp_bmp);
	}
}
void CMyTestView::OnEqua()
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.PointEqua(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),1);
		CreateDlg("灰度图 均衡变换",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.PointEqua(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		CreateDlg("彩色图 均衡变换",temp_bmp);
	}
}

void CMyTestView::CreateDlg(CString name,BYTE *bmp,int type)
{
	MyProcess myProcess;
	BmpDlg *bmpdlg = new BmpDlg();
	bmpdlg->Init(NULL,myBmp.GetBmpWidth(),myBmp.GetHeight());
	bmpdlg->Create(IDD_HISTOGRAM,this);
	name+=myBmp.GetBmpName();
	bmpdlg->SetWindowText(name);
	if(type==0) myProcess.ShowArrayToDevice(&bmpdlg->dcMemory,0,0,bmp,myBmp.GetWidth(),myBmp.GetHeight(),0);
	else if(type==1) myProcess.ShowArrayToDevice(&bmpdlg->dcMemory,0,0,bmp,myBmp.GetBmpWidth(),myBmp.GetHeight());
	bmpdlg->ShowWindow(SW_SHOW);
}

void CMyTestView::OnIDDBmp() 
{
	// TODO: Add your command handler code here
	BmpORGray = 0;
}
void CMyTestView::OnIDDGray() 
{
	// TODO: Add your command handler code here
	BmpORGray=1;
}

void CMyTestView::OnFourier() 
{
	// TODO: Add your command handler code here
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		MessageBox("请先转换为24位bmp位图！！");
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.BmpFourier(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("彩色图 傅立叶变换",temp_bmp);
	}
}

void CMyTestView::OnDct() 
{
	// TODO: Add your command handler code here
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		MessageBox("请先转换为24位bmp位图！！");
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.BmpDCT(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("彩色图 离散余弦变换",temp_bmp);
	}
}

void CMyTestView::OnWalsh() 
{
	// TODO: Add your command handler code here
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		MessageBox("请先转换为24位bmp位图！！");
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.BmpWalsh(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("彩色图 离散余弦变换",temp_bmp);
	}
}

void CMyTestView::OnKernel() 
{
	// TODO: Add your command handler code here
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[3]);
		CreateDlg("灰度图 模版滤波",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[2]);
		EndWaitCursor();
		CreateDlg("模版滤波",temp_bmp);
	}
}

void CMyTestView::OnSfilter() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[5]);
		CreateDlg("灰度图 线性锐化",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[5]);
		EndWaitCursor();
		CreateDlg("线性锐化",temp_bmp);
	}
	// TODO: Add your command handler code here
	
}

void CMyTestView::OnMedianfilter() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.MedianFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
		CreateDlg("灰度图 中值滤波",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.MedianFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("中值滤波",temp_bmp);
	}	
}

void CMyTestView::OnEmboss1() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[7],1);
		CreateDlg("灰度图 浮雕特效一",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[7],1);
		EndWaitCursor();
		CreateDlg("浮雕特效一",temp_bmp);
	}	
}

void CMyTestView::OnEmboss2() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[8],1);
		CreateDlg("灰度图 浮雕特效二",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[8],1);
		EndWaitCursor();
		CreateDlg("浮雕特效二",temp_bmp);
	}
	// TODO: Add your command handler code here
	
}

void CMyTestView::OnEmboss3() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[9],1);
		CreateDlg("灰度图 浮雕特效三",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[9],1);
		EndWaitCursor();
		CreateDlg("浮雕特效三",temp_bmp);
	}
	
}

void CMyTestView::OnEmboss4() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[10],1);
		CreateDlg("灰度图 浮雕特效四",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[10],1);
		EndWaitCursor();
		CreateDlg("浮雕特效四",temp_bmp);
	}
	
}

void CMyTestView::OnEmboss5() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[11],1);
		CreateDlg("灰度图 浮雕特效五",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[11],1);
		EndWaitCursor();
		CreateDlg("浮雕特效五",temp_bmp);
	}
	
}

void CMyTestView::OnEmboss6() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[12],1);
		CreateDlg("灰度图 浮雕特效六",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[12],1);
		EndWaitCursor();
		CreateDlg("浮雕特效六",temp_bmp);
	}
	
}

void CMyTestView::OnEmboss7() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[13],1);
		CreateDlg("灰度图 浮雕特效七",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[13],1);
		EndWaitCursor();
		CreateDlg("浮雕特效七",temp_bmp);
	}
	
}

void CMyTestView::OnEmboss8() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.KernelFilter(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel[14],1);
		CreateDlg("灰度图 浮雕特效八",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.KernelFilter(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel[14],1);
		EndWaitCursor();
		CreateDlg("浮雕特效八",temp_bmp);
	}
	
}

void CMyTestView::OnButterworthl() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.ButterworthL(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),250);
		CreateDlg("灰度图 布特沃斯低通",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.ButterworthL(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),250);
		CreateDlg("布特沃斯低通",temp_bmp);
		myProcess.BmpFourier(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("布特沃斯低通",temp_bmp);
	}
		
}

void CMyTestView::OnButterwg() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.ButterworthL(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),250,1);
		CreateDlg("灰度图 布特沃斯高通",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.ButterworthL(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),1000,1);
		CreateDlg("布特沃斯高通",temp_bmp);
		myProcess.BmpFourier(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("布特沃斯高通",temp_bmp);
	}
}

void CMyTestView::OnSproberts() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.SplitRoberts(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
		CreateDlg("灰度图 罗伯特交叉算子",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.SplitRoberts(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("罗伯特交叉算子",temp_bmp);
	}
}

void CMyTestView::OnPrewitt() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.SplitRoberts(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),1);
		CreateDlg("灰度图 薄瑞维特边缘算子",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.SplitRoberts(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),1);
		EndWaitCursor();
		CreateDlg("薄瑞维特边缘算子",temp_bmp);
	}
	
}

void CMyTestView::OnSobel() 
{//索贝尔边缘算子
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.SplitRoberts(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),2);
		CreateDlg("灰度图 索贝尔边缘算子",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.SplitRoberts(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),2);
		EndWaitCursor();
		CreateDlg("索贝尔边缘算子",temp_bmp);
	}
}

void CMyTestView::OnKirsch() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.SplitKirsch(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
		CreateDlg("灰度图 Kirsch方向算子",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.SplitKirsch(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("Kirsch方向算子",temp_bmp);
	}	
}

void CMyTestView::OnContour() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.SplitContour(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
		CreateDlg("灰度图 轮廓提取",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.SplitContour(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight());
		EndWaitCursor();
		CreateDlg("轮廓提取",temp_bmp);
	}		
}

void CMyTestView::OnHoufu() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.HoufuLine(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
		CreateDlg("直线检测",temp_gray,1);
	}else if(BmpORGray == 0)
	{
		MessageBox("请先转换成灰度图像！！！");
	}
}

void CMyTestView::OnThreshold() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{	
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		int t = myProcess.Threshold(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight());
		CString s;
		s.Format("区域检测 迭代阈值%d ",t);
		CreateDlg(s,temp_gray,1);
	}else if(BmpORGray == 0)
	{
		MessageBox("请先转换成灰度图像！！！");
	}
}

void CMyTestView::OnRgngrow() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{	
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.RgnGrow(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),100,200);
		CreateDlg("区域生长",temp_gray,1);
	}else if(BmpORGray == 0)
	{
		MessageBox("请先转换成灰度图像！！！");
	}	
}

void CMyTestView::OnVerosion() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Erosion(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[0]);
		CreateDlg("垂直腐蚀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Erosion(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[0]);
		EndWaitCursor();
		CreateDlg("垂直腐蚀",temp_bmp);
	}
}

void CMyTestView::OnHerosion() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Erosion(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[1]);
		CreateDlg("水平腐蚀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Erosion(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[1]);
		EndWaitCursor();
		CreateDlg("水平腐蚀",temp_bmp);
	}
}

void CMyTestView::On4erosion() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Erosion(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		CreateDlg("4方向腐蚀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Erosion(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		EndWaitCursor();
		CreateDlg("4方向腐蚀",temp_bmp);
	}
	
}

void CMyTestView::On8erosion() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Erosion(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[3]);
		CreateDlg("8方向腐蚀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Erosion(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[3]);
		EndWaitCursor();
		CreateDlg("8方向腐蚀",temp_bmp);
	}	
}

void CMyTestView::On4dilation() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Dilation(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		CreateDlg("4方向膨胀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Dilation(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		EndWaitCursor();
		CreateDlg("4方向膨胀",temp_bmp);
	}
	
}

void CMyTestView::On8dilation() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Dilation(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[3]);
		CreateDlg("8方向膨胀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Dilation(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[3]);
		EndWaitCursor();
		CreateDlg("8方向膨胀",temp_bmp);
	}
}

void CMyTestView::OnHdilation() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Dilation(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[1]);
		CreateDlg("水平膨胀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Dilation(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[1]);
		EndWaitCursor();
		CreateDlg("水平膨胀",temp_bmp);
	}
}

void CMyTestView::OnVdilation() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.Dilation(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[0]);
		CreateDlg("垂直膨胀",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.Dilation(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[0]);
		EndWaitCursor();
		CreateDlg("垂直膨胀",temp_bmp);
	}	
}

void CMyTestView::OnCloseoperate() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.CloseOperate(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		CreateDlg("闭运算",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.CloseOperate(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		EndWaitCursor();
		CreateDlg("闭运算",temp_bmp);
	}
}

void CMyTestView::OnOpenoperate() 
{
	MyProcess myProcess;
	if(BmpORGray == 1)
	{
		if(gray==NULL) {MessageBox("请先转换成灰度图像！！！");	return ;}
		BYTE *temp_gray = new BYTE [myBmp.GetBmpWidth()*myBmp.GetHeight()];
		memcpy(temp_gray,gray,myBmp.GetBmpWidth()*myBmp.GetHeight()*sizeof(BYTE));
		myProcess.OpenOperate(temp_gray,myBmp.GetBmpWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		CreateDlg("开运算",temp_gray,1);
	}
	if(BmpORGray == 0)
	{
		if(myBmp.GetBmp()==NULL) 
		{
			MessageBox("请先打开一张BMP格式位图！！！");
			return ;
		}
		BYTE *temp_bmp = new BYTE [myBmp.GetWidth()*myBmp.GetHeight()];
		memcpy(temp_bmp,myBmp.GetBmp(),myBmp.GetWidth()*myBmp.GetHeight()*sizeof(BYTE));
		BeginWaitCursor();
		myProcess.OpenOperate(temp_bmp,myBmp.GetWidth(),myBmp.GetHeight(),kernel_erosion[2]);
		EndWaitCursor();
		CreateDlg("开运算",temp_bmp);
	}
}
