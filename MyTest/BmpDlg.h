#if !defined(AFX_BMPDLG_H__398F3131_E17A_4FF0_9CB8_F34799C536A3__INCLUDED_)
#define AFX_BMPDLG_H__398F3131_E17A_4FF0_9CB8_F34799C536A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Histogram.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// Histogram dialog
class BmpDlg : public CDialog
{
// Construction
public:
	void Init(unsigned char * array,int width,int height);
	BmpDlg(CWnd* pParent = NULL);   // standard constructor

//private:
	CDC dcMemory;
	unsigned char *bmp;
	unsigned char *huidubmp;
	int width;
	int height;
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
