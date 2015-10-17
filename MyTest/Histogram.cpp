// Histogram.cpp : implementation file
//

#include "stdafx.h"
#include "Histogram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Histogram dialog


Histogram::Histogram(CWnd* pParent /*=NULL*/)
	: CDialog(Histogram::IDD, pParent)
{

	//{{AFX_DATA_INIT(Histogram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void Histogram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Histogram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Histogram, CDialog)
	//{{AFX_MSG_MAP(Histogram)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Histogram message handlers

void Histogram::OnPaint() 
{
	
	// TODO: Add your message handler code here
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0,0,500,500,&dcMemory,0,0,SRCCOPY);
	// Do not call CDialog::OnPaint() for painting messages
}
void Histogram::DrawCoordinate(int x,int y,int dx,int dy,int maxX,int maxY)
{
	int i;
	int insert=5;
	dcMemory.MoveTo(x,y);
	dcMemory.LineTo(x,maxY);
	dcMemory.MoveTo(x,y);
	dcMemory.LineTo(maxX,y);
	for(i=x;i<maxX;i+=dx)//x÷·
	{
		dcMemory.MoveTo(i,y);
		dcMemory.LineTo(i,y-insert);
		CString s;
		s.Format("%d",i-50);
		CSize size = dcMemory.GetTextExtent(s);
		if((i-50)%30==0 && i < 256+50) dcMemory.TextOut(i,y+size.cy,s);
	}
	for(i=y;i>maxY;i-=dy)//y÷·
	{
		dcMemory.MoveTo(x,i);
		dcMemory.LineTo(x+insert,i);
		CString s;
		s.Format("%d",y-i);
		CSize size = dcMemory.GetTextExtent(s);
		if(i%8==0) dcMemory.TextOut(x-size.cx,i,s);
	}
	CString s;
	s.Format("%c%d",'x',10);
	CSize size = dcMemory.GetTextExtent(s);
	dcMemory.TextOut(x,maxY-size.cy,s);
	dcMemory.MoveTo(maxX-insert,y-insert);
	dcMemory.LineTo(maxX,y);
	dcMemory.MoveTo(maxX-insert,y+insert);
	dcMemory.LineTo(maxX,y);

	dcMemory.MoveTo(x-insert,maxY+insert);
	dcMemory.LineTo(x,maxY);
	dcMemory.MoveTo(x+insert,maxY+insert);
	dcMemory.LineTo(x,maxY);
}

void Histogram::DrawValue(int x,int y)
{
	for(int j=0;j<type;j++)
	{
		CPen pen(PS_SOLID,1,color[j]);
		dcMemory.SelectObject(&pen);
		for(int i=0;i<256;i++)
		{
			dcMemory.MoveTo(x+i,y);
			dcMemory.LineTo(x+i,y-value[j][i]/10);
		}
	}
}

BOOL Histogram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CPaintDC dc(this); // device context for painting
	CRect rect;
	this->GetWindowRect(&rect);
	dcMemory.CreateCompatibleDC(&dc);
	
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	dcMemory.SelectObject(&bitmap);
	CRect rect2(0,0,rect.Width(),rect.Height()); 
	dcMemory.FillSolidRect(&rect2,RGB(255,255,255));
	// TODO: Add extra initialization here
	DrawCoordinate(50,rect.Height()-100,10,10,256+50+100,50);
	DrawValue(50,rect.Height()-100);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void Histogram::Init(int t,int v[3][256],COLORREF *c)
{
	type = t;
	for(int i=0;i<t;i++)
	{
		color[i] = c[i];
	
	}
		memcpy(value,v,3*256*sizeof(int));
}
void Histogram::Init(int *v,COLORREF c)
{
	type = 1;
	color[0] = c;
	memcpy(value[0],v,256*sizeof(int));
}