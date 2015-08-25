#if !defined(AFX_SYSPARAMSETDLG_H__6C32BF05_9B0C_4522_B394_79E6C5422278__INCLUDED_)
#define AFX_SYSPARAMSETDLG_H__6C32BF05_9B0C_4522_B394_79E6C5422278__INCLUDED_

#include "MPC2810CtrlDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysParamSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysParamSetDlg dialog

class CSysParamSetDlg : public CDialog
{
// Construction
public:
	CMPC2810CtrlDlg* m_lpMainDlg;
	CSysParamSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysParamSetDlg)
	enum { IDD = IDD_DLG_SYSPARAM };
	double	m_ZeroLuoju;
	double	m_SpeedAFactor;
	double	m_SpeedupA;
	int		m_MainAxe_pulses;
	double	m_MainAxe_MaxSpeed;
	double	m_MainAxe_levelFactor6;
	double	m_MainAxe_levelFactor5;
	double	m_MainAxe_levelFactor4;
	double	m_MainAxe_levelFactor3;
	double	m_MainAxe_levelFactor2;
	double	m_MainAxe_levelFactor1;
	double	m_CarSpeedDownP;
	int		m_Car_Pulses;
	double	m_Car_MaxSpeed;
	double	m_CarDistancePerRound;
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

#endif // !defined(AFX_SYSPARAMSETDLG_H__6C32BF05_9B0C_4522_B394_79E6C5422278__INCLUDED_)
