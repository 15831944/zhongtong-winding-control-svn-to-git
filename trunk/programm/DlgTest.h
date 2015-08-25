#if !defined(AFX_DLGTEST_H__43A95A7A_409B_4611_AB5A_B078E96E880D__INCLUDED_)
#define AFX_DLGTEST_H__43A95A7A_409B_4611_AB5A_B078E96E880D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTest.h : header file
//

#include "Mmsystem.h"

#define  WM_MMTIMER_MEASURE_SPEED (WM_USER+37)

/////////////////////////////////////////////////////////////////////////////
// CDlgTest dialog

class CDlgTest : public CDialog
{
// Construction
public:
	int m_iUpdateCount;
	int m_iUpdateInterval;
	int m_iMeasureInterval;
	long m_iThisEncoderValue;
	long m_iLastEncoderValue;
	UINT wTimerRes;
//	void CALLBACK MeasureMainAxeSpeed(UINT wTimerID,UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2);
	bool CreateTimer(void);
	void DestroyTimer(void);
	MMRESULT m_wTimerID;
	int m_Axe1runningStatus;
	int m_Axe2runningStatus;
	CDlgTest(CWnd* pParent = NULL);   // standard constructor
    afx_msg LRESULT OnMMTimerMeasureSpeed(WPARAM wparam, LPARAM lparam);
// Dialog Data
	//{{AFX_DATA(CDlgTest)
	enum { IDD = IDD_DLGTEST };
	CString	m_Axe1Position;
	CString	m_Axe1SpeedShow;
	int		m_UpdateInterval;
	long	m_ThisEncoder_Show;
	int		m_MeasureInterval;
	long	m_LastEncoder_Show;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTest)
	afx_msg void OnAxe2Setup();
	afx_msg void OnAxe2start();
	virtual BOOL OnInitDialog();
	afx_msg void OnPosReset();
	afx_msg void OnDestroy();
	afx_msg void OnAxe1Set();
	afx_msg void OnStartAxe1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEST_H__43A95A7A_409B_4611_AB5A_B078E96E880D__INCLUDED_)
