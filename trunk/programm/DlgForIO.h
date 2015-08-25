#if !defined(AFX_DLGFORIO_H__6B4CA2E1_CF4D_4D61_9722_B41D748B9326__INCLUDED_)
#define AFX_DLGFORIO_H__6B4CA2E1_CF4D_4D61_9722_B41D748B9326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgForIO.h : header file
//


#include "MyButton.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgForIO dialog

class CDlgForIO : public CDialog
{
// Construction
public:
	void MyIsr(void);
	int m_iPulseNumPerRound;
	void CheckIO_IN(int num);
	byte m_IOout;
	CDlgForIO(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgForIO)
	enum { IDD = IDD_DLGIO };
	CStatic	m_Icon_IN9;
	CStatic	m_Icon_IN8;
	CStatic	m_Icon_IN7;
	CStatic	m_Icon_IN6;
	CStatic	m_Icon_IN5;
	CStatic	m_Icon_IN4;
	CStatic	m_Icon_IN3;
	CStatic	m_Icon_IN2;
	CStatic	m_Icon_IN16;
	CStatic	m_Icon_IN15;
	CStatic	m_Icon_IN14;
	CStatic	m_Icon_IN13;
	CStatic	m_Icon_IN12;
	CStatic	m_Icon_IN11;
	CStatic	m_Icon_IN10;
	CStatic	m_Icon_IN1;
	CMyButton	m_IndiButton_MainPosDir;
	CMyButton	m_IndiButton_MainNegDir;
	float	m_CarConsRpm;
	double	m_CarRounds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgForIO)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgForIO)
	afx_msg void OnMainNegDir();
	afx_msg void OnMainPosDir();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnButton1();
	afx_msg void OnCarPosDir();
	afx_msg void OnCarNegdir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFORIO_H__6B4CA2E1_CF4D_4D61_9722_B41D748B9326__INCLUDED_)
