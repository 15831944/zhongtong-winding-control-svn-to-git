#if !defined(AFX_WORKMONITORDLG_H__866A5E2A_12DC_4EDB_8778_D58480392FD8__INCLUDED_)
#define AFX_WORKMONITORDLG_H__866A5E2A_12DC_4EDB_8778_D58480392FD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkMonitorDlg.h : header file
//

#include "DlgWorkPlan.h"
#include "Mmsystem.h"
#include "arControlParam.h"

#define  WM_THREAD_BUTTON_CHANGE  (WM_USER+73)
#define  WM_MMTIMER_MEASURE_SPEED (WM_USER+37)
#define  WM_THREAD_POS_UPDATE     (WM_USER+88)

UINT QueryPressButton(LPVOID pParam);
UINT WindingProcessThread(LPVOID pParam);  

/////////////////////////////////////////////////////////////////////////////
// CWorkMonitorDlg dialog

class CWorkMonitorDlg : public CDialog
{
// Construction
public:
	double AdjustAngle(double nowlength, double circlelen,int i);
	int CrossWindProcessq(int index, int *runningflag);
	int CircleWindProcess(int index, int *runningflag);
	void ComputeCarMoveParam(int index, CarControlParam* lpparam);
	CWinThread* m_WindProcThread;
	int m_WindProcessRunningFlag;
	double myAbs(double a);
//	void DestroyWindow();
	volatile double m_MainAxeRealV;
	int m_CurrTaskIndex;
	int m_iUpdateInterval;
	long m_MainAxeDeltaEncoderCount[100];
	long m_iThisEncoderValueMainAxe;
	long m_iLastEncoderValueMainAxe;

	int m_iUpdateCount;
	int m_iMeasureInterval;
	MMRESULT m_wTimerID;
	UINT wTimerRes;
	bool CreateTimer();
	double m_CarCurSpeed;
	int m_flagTimerSpeed;
	LRESULT OnButtonChanged(WPARAM wparam, LPARAM lparam);
	void ButtonProcess(int buttonStatus);
	CWinThread* m_queryThread;
	int m_QueryThreadRunningFlag;
	void LoadTask(int TaskIndex);
	CDlgWorkPlan * m_lpWorkPlanDlg;
	CWorkMonitorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkMonitorDlg)
	enum { IDD = IDD_INWORKING };
	CMyButton	m_BtnStartWork;
	CMyButton	m_Btn_StopCarEmerg;
	CMyButton	m_BtnStopCar;
	CMyButton	m_BtnMeasureStart;
	CMyButton	m_ButtonInitial;
	CString	m_WorkingOutHint;
	CString	m_WorkingProgress1;
	CString	m_WorkingProgress2;
	CString	m_WorkingProgress3;
	double	m_MainAxeSpeed;
	double	m_MainAxePos;
	CString	m_MainAxeDir;
	double	m_CarPos;
	double	m_CarSpeed;
	CString	m_CarDir;
	int		m_AlreadyWindNum;
	double	m_PipeDiam;
	double	m_BandageWidth;
	double	m_StartPos;
	double	m_EndPos;
	double	m_StartStopAngle;
	double	m_StopStopAngle;
	int		m_WindNum;
	double	m_CrossAngle;
	int		m_WindStartLayer;
	CString	m_WindMethod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkMonitorDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorkMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnInitial();
	afx_msg void OnMeasurestart();
	afx_msg LRESULT OnMMTimerMeasureSpeed(WPARAM wparam, LPARAM lparam);
	afx_msg void OnSetZeropot();
	afx_msg void OnStop();
	afx_msg void OnStopEmerg();
	afx_msg void OnStartwork();
	afx_msg LRESULT OnUpdateCarPos(WPARAM wparam, LPARAM lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKMONITORDLG_H__866A5E2A_12DC_4EDB_8778_D58480392FD8__INCLUDED_)
