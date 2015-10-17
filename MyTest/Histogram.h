#if !defined(AFX_HISTOGRAM_H__398F3131_E17A_4FF0_9CB8_F34799C536A3__INCLUDED_)
#define AFX_HISTOGRAM_H__398F3131_E17A_4FF0_9CB8_F34799C536A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Histogram.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// Histogram dialog
class Histogram : public CDialog
{
// Construction
public:
	CString m_fileName;
	/************************************************************************/
	/* 函数名称 Init
	/* 参数 int *v ---直方图的值
	/* COLORREF c -------显示时的颜色
	/* 返回值 void -----无
	/* 说明 初始化灰度直方图对话框
	/************************************************************************/
	void Init(int *v,COLORREF c);
	/************************************************************************/
	/* 函数名称 Init
	/* 参数 
		int t -------- 直方图的条数
		int *v ---直方图的值
	/* COLORREF c -------显示时的颜色
	/* 返回值 void -----无
	/* 说明 初始化彩色直方图对话框
	/************************************************************************/
	void Init(int t,int v[3][256],COLORREF *c);
	/************************************************************************/
	/* 构造函数                                                                     */
	/************************************************************************/
	Histogram(CWnd* pParent = NULL);   // standard constructor
private:
	void DrawValue(int x,int y);//绘制值
	void DrawCoordinate(int x,int y,int dx,int dy,int maxX,int maxY);//绘制坐标系
	int  value[3][256];
	int type;
	CDC dcMemory;
	COLORREF color[3];

// Dialog Data
	//{{AFX_DATA(Histogram)
	enum { IDD = IDD_HISTOGRAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Histogram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(Histogram)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAM_H__398F3131_E17A_4FF0_9CB8_F34799C536A3__INCLUDED_)
