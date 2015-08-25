// MPC2810CtrlDlg.h : header file
//

#if !defined(AFX_MPC2810CTRLDLG_H__6486FBA3_88D9_4E6F_AFBF_FCDCAEE2EBBC__INCLUDED_)
#define AFX_MPC2810CTRLDLG_H__6486FBA3_88D9_4E6F_AFBF_FCDCAEE2EBBC__INCLUDED_

#include "SysSetParam.h"	// Added by ClassView
#include "AxeCtrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMPC2810CtrlDlg dialog

class CMPC2810CtrlDlg : public CDialog
{
// Construction
public:
	SysSetParam m_Gsysparam;
	void SysInitial(void);
	byte m_gMainAxeIOout;
	CAxeCtrl Axe_ClockSource;
	CAxeCtrl Axe_Carriage;
	int glTotalCards;
	int glTotalAxes;
	int InitBoard(void);
	CMPC2810CtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMPC2810CtrlDlg)
	enum { IDD = IDD_MPC2810CTRL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPC2810CtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMPC2810CtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	afx_msg void OnIoTest();
	afx_msg void OnRunOperation();
	afx_msg void OnSetParameter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPC2810CTRLDLG_H__6486FBA3_88D9_4E6F_AFBF_FCDCAEE2EBBC__INCLUDED_)
