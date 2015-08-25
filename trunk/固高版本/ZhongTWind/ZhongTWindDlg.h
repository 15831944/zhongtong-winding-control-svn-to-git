// ZhongTWindDlg.h : header file
//

#if !defined(AFX_ZHONGTWINDDLG_H__2FC7AF9A_32B9_401A_9EF6_0421DD57C318__INCLUDED_)
#define AFX_ZHONGTWINDDLG_H__2FC7AF9A_32B9_401A_9EF6_0421DD57C318__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyButton.h"
/////////////////////////////////////////////////////////////////////////////
// CZhongTWindDlg dialog

class CZhongTWindDlg : public CDialog
{
// Construction
public:
	void Ges_error(short rtn);
	int InitBoard(void);
	CZhongTWindDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZhongTWindDlg)
	enum { IDD = IDD_ZHONGTWIND_DIALOG };
	CMyButton	m_BtnSysParamSet;
	CMyButton	m_BtnStartWind;
	CMyButton	m_BtnIOtest;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZhongTWindDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZhongTWindDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartwind();
	afx_msg void OnIotest();
	afx_msg void OnSysparamset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZHONGTWINDDLG_H__2FC7AF9A_32B9_401A_9EF6_0421DD57C318__INCLUDED_)
