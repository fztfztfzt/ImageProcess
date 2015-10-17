// Histogram.cpp : implementation file
//

#include "stdafx.h"
#include "BmpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Histogram dialog


BmpDlg::BmpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BmpDlg::IDD, pParent)
{

	bmp=NULL;
	//{{AFX_DATA_INIT(Histogram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void BmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Histogram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BmpDlg, CDialog)
	//{{AFX_MSG_MAP(Histogram)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Histogram message handlers

void BmpDlg::OnPaint() 
{
	
	// TODO: Add your message handler code here
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0,0,width,height,&dcMemory,0,0,SRCCOPY);
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL BmpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CPaintDC dc(this); // device context for painting
	dcMemory.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,width,height);
	dcMemory.SelectObject(&bitmap);
	if(bmp!=NULL)
	{
		for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			dcMemory.SetPixel(j,height-i,RGB(bmp[i*(width)+j],bmp[i*(width)+j],bmp[i*(width)+j]));
			//else dcMemory.SetPixel(j,height-i,RGB(huidubmp[i*(width+2)+j],huidubmp[i*(width+2)+j],huidubmp[i*(width+2)+j]));
		}
	}
	CRect rect(0,0,width,height);
	this->MoveWindow(&rect,true);
//	Invalidate();
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void BmpDlg::Init(unsigned char * array,int width,int height)
{
	this->width=width;
	this->height = height;
	if(array!=NULL) 
	{
		bmp = new unsigned char [width*height];
//	strcpy((char *)bmp,(char*)array);
		memcpy(bmp,array,width*height*sizeof(unsigned char));
	}
	
}
