#if !defined(AFX_SYSPARAMSETDLG_H__F18A5C2A_1F66_4965_A250_F702FE2847EF__INCLUDED_)
#define AFX_SYSPARAMSETDLG_H__F18A5C2A_1F66_4965_A250_F702FE2847EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysParamSetDlg.h : header file
//
#include "MyButton.h"

/////////////////////////////////////////////////////////////////////////////
// CSysParamSetDlg dialog

class CSysParamSetDlg : public CDialog
{
// Construction
public:
	CSysParamSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysParamSetDlg)
	enum { IDD = IDD_DLG_SYSPARAM };
	CMyButton	m_BtnUpdate;
	double	m_CarDistancePerRound;
	double	m_Car_MaxSpeed;
	int		m_Car_Pulses;
	double	m_CarSpeedDownP;
	double	m_MainAxe_levelFactor1;
	double	m_MainAxe_levelFactor2;
	double	m_MainAxe_levelFactor3;
	double	m_MainAxe_levelFactor4;
	double	m_MainAxe_levelFactor5;
	double	m_MainAxe_levelFactor6;
	double	m_MainAxe_MaxSpeed;
	int		m_MainAxe_pulses;
	double	m_SpeedupA;
	double	m_SpeedAFactor;
	double	m_ZeroLuoju;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysParamSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSysParamSetDlg)
	afx_msg void OnButtonUpdatedata();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSPARAMSETDLG_H__F18A5C2A_1F66_4965_A250_F702FE2847EF__INCLUDED_)
