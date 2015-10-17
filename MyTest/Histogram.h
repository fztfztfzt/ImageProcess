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
	/* �������� Init
	/* ���� int *v ---ֱ��ͼ��ֵ
	/* COLORREF c -------��ʾʱ����ɫ
	/* ����ֵ void -----��
	/* ˵�� ��ʼ���Ҷ�ֱ��ͼ�Ի���
	/************************************************************************/
	void Init(int *v,COLORREF c);
	/************************************************************************/
	/* �������� Init
	/* ���� 
		int t -------- ֱ��ͼ������
		int *v ---ֱ��ͼ��ֵ
	/* COLORREF c -------��ʾʱ����ɫ
	/* ����ֵ void -----��
	/* ˵�� ��ʼ����ɫֱ��ͼ�Ի���
	/************************************************************************/
	void Init(int t,int v[3][256],COLORREF *c);
	/************************************************************************/
	/* ���캯��                                                                     */
	/************************************************************************/
	Histogram(CWnd* pParent = NULL);   // standard constructor
private:
	void DrawValue(int x,int y);//����ֵ
	void DrawCoordinate(int x,int y,int dx,int dy,int maxX,int maxY);//��������ϵ
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
