#if !defined(AFX_DLGIOTEST_H__131B9846_3AA4_43FF_82EA_D64AFD5DE818__INCLUDED_)
#define AFX_DLGIOTEST_H__131B9846_3AA4_43FF_82EA_D64AFD5DE818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIOTest.h : header file
//

#include "MyButton.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgIOTest dialog

class CDlgIOTest : public CDialog
{
// Construction
public:
	void CheckIO_IN(int num);
	byte m_IOout;
	CDlgIOTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIOTest)
	enum { IDD = IDD_DLGIO };
	CMyButton	m_BtnMainAxePosDir;
	CMyButton	m_BtnMainAxeNegDir;
	CStatic	m_iconIN_9;
	CStatic	m_iconIN_8;
	CStatic	m_iconIN_7;
	CStatic	m_iconIN_6;
	CStatic	m_iconIN_5;
	CStatic	m_iconIN_4;
	CStatic	m_iconIN_3;
	CStatic	m_iconIN_2;
	CStatic	m_iconIN_16;
	CStatic	m_iconIN_15;
	CStatic	m_iconIN_14;
	CStatic	m_iconIN_13;
	CStatic	m_iconIN_12;
	CStatic	m_iconIN_11;
	CStatic	m_iconIN_10;
	CStatic	m_iconIN_1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIOTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIOTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnMainNegDir();
	afx_msg void OnMainPosDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOTEST_H__131B9846_3AA4_43FF_82EA_D64AFD5DE818__INCLUDED_)
