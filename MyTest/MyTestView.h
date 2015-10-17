// MyTestView.h : interface of the CMyTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTESTVIEW_H__B2AE50F1_0630_45FC_9361_05241B731579__INCLUDED_)
#define AFX_MYTESTVIEW_H__B2AE50F1_0630_45FC_9361_05241B731579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyBitmap.h"

class CMyTestView : public CView
{
protected: // create from serialization only
	CMyTestView();
	DECLARE_DYNCREATE(CMyTestView)

// Attributes
public:
	CMyTestDoc* GetDocument();
	unsigned char * gray;
	int *grayIns;
	MyBitmap myBmp;
	CDC dcMemory;
	LONG width;
	LONG height;
	int BmpORGray;//处理24位位图还是灰度图，0--彩色，1--灰度
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateDlg(CString name,BYTE *bmp=NULL,int type=0);
	virtual ~CMyTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyTestView)
	afx_msg void OnFileOpen();
	afx_msg void OnGray();
	afx_msg void OnGrayInst();
	afx_msg void OnInvert();
	afx_msg void OnStretch();
	afx_msg void OnWindowsTran();
	afx_msg void OnDynamicCompress();
	afx_msg void OnEqua();
	afx_msg void OnIDDBmp();
	afx_msg void OnIDDGray();
	afx_msg void OnFourier();
	afx_msg void OnDct();
	afx_msg void OnWalsh();
	afx_msg void OnKernel();
	afx_msg void OnSfilter();
	afx_msg void OnMedianfilter();
	afx_msg void OnEmboss1();
	afx_msg void OnEmboss2();
	afx_msg void OnEmboss3();
	afx_msg void OnEmboss4();
	afx_msg void OnEmboss5();
	afx_msg void OnEmboss6();
	afx_msg void OnEmboss7();
	afx_msg void OnEmboss8();
	afx_msg void OnButterworthl();
	afx_msg void OnButterwg();
	afx_msg void OnSproberts();
	afx_msg void OnPrewitt();
	afx_msg void OnSobel();
	afx_msg void OnKirsch();
	afx_msg void OnContour();
	afx_msg void OnHoufu();
	afx_msg void OnThreshold();
	afx_msg void OnRgngrow();
	afx_msg void OnVerosion();
	afx_msg void OnHerosion();
	afx_msg void On4erosion();
	afx_msg void On8erosion();
	afx_msg void On4dilation();
	afx_msg void On8dilation();
	afx_msg void OnHdilation();
	afx_msg void OnVdilation();
	afx_msg void OnCloseoperate();
	afx_msg void OnOpenoperate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyTestView.cpp
inline CMyTestDoc* CMyTestView::GetDocument()
   { return (CMyTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTESTVIEW_H__B2AE50F1_0630_45FC_9361_05241B731579__INCLUDED_)
