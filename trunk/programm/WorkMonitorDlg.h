#if !defined(AFX_WORKMONITORDLG_H__08EDC4EC_0BD6_4353_90CB_18E4441C80B9__INCLUDED_)
#define AFX_WORKMONITORDLG_H__08EDC4EC_0BD6_4353_90CB_18E4441C80B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkMonitorDlg.h : header file
//

#include "MyButton.h"
#include "MainOperationDlg.h"
#include "Mmsystem.h"
#include "arControlParam.h"


UINT QueryPressButton(LPVOID pParam);
UINT WindingProcessThread(LPVOID pParam);   /// Ïß³Ìº¯Êý


#define  WM_MMTIMER_MEASURE_SPEED (WM_USER+37)
#define  WM_THREAD_BUTTON_CHANGE  (WM_USER+73)
#define  WM_THREAD_POS_UPDATE     (WM_USER+74)
#define  WM_DEBUGOUTPUT           (WM_USER+66)
#define  WM_DEBUGOUTPUTMM         (WM_USER+88)
#define  WM_WIND_NUM_UPDATE       (WM_USER+99)
/////////////////////////////////////////////////////////////////////////////
// CWorkMonitorDlg dialog

class CWorkMonitorDlg : public CDialog
{
// Construction
public:
	double m_TickEncoderDelta;
	double AdjustAngle(double nowlength,double circlelen,int i);
	long m_iniCarEncoderVal;
	int CrossWindProcessq(int index, int *runningflag);
	long m_MainAxeDeltaEncoderCount[100];
	int CircleWindProcessq(int index, int *runningflag);
	int CircleWindProcess(int index, int *runningflag);
	int m_WindProcessRunningFlag;
	int CrossWindProcess(int index, int* runningflag);
	void ComputeCarMoveParam(int index , CarControlParam* lpparam);
	double myAbs(double a);
	double GetMainAxeSpeedRatio(int index);
	int m_CurTaskIndex;
	int m_flagTimerSpeed;
	double m_CarCurSpeed;
    volatile double m_MainAxeRealV;
	long	m_ThisEncoder_Show;
	long	m_LastEncoder_Show;
	int m_iUpdateInterval;
    int m_iUpdateCount;
	long m_iThisEncoderValue;
	long m_iLastEncoderValue;

	long m_2ThisEncoderValue;
	long m_2LastEncoderValue;
	void DestroyTimer(void);
	int m_iMeasureInterval;
	MMRESULT m_wTimerID;
	UINT wTimerRes;
	bool CreateTimer(void);
	int m_ControlStatus;
	void ButtonProcess(int buttonStatus);
	int m_CurrentWindTaskIndex;
	CMainOperationDlg* m_lpOpDlg;
	int m_QueryThreadRunningFlag;
	CWinThread* m_queryThread;
	CWinThread* m_WindProcThread;
	CWorkMonitorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkMonitorDlg)
	enum { IDD = IDD_INWORKING };
	CMyButton	m_ButtonTest;
	CMyButton	m_ButtonZeroSet;
	CMyButton	m_ButtonInitial;
	CMyButton	m_ButtonStartWork;
	CString	m_WorkingProg1;
	CString	m_WorkingProg2;
	CString	m_WorkingProg3;
	CString	m_WorkingOutput;
	int		m_WindNum;
	int		m_Already_WindNum;
	CString	m_CarDir;
	double	m_CarPos;
	double	m_CarSpeed;
	double	m_CrossAngle;
	double	m_EndPos;
	double	m_EndStopAngle;
	CString	m_MainAxeDir;
	double	m_MainAxePos;
	double	m_MainAxeSpeed;
	double	m_PipeDiam;
	int		m_PucengStartLayer;
	double	m_ShaPianWidth;
	double	m_StartPos;
	double	m_StartStopAngle;
	long	m_test1;
	long	m_test2;
	long	m_record1;
	long	m_record2;
	CString	m_DebugOutEdit;
	double	m_MonitorMainAxe;
	double	m_AdjMainAxeAngle;
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
	afx_msg void OnInitial();
	afx_msg void OnStartwork();
	afx_msg void OnSetZeropot();
	afx_msg LRESULT OnMMTimerMeasureSpeed(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnButtonChanged(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnUpdateCarPos(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnUpdateDebugOut(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnUpdateDebugOutMM(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnUpdateWindNum(WPARAM wparam,LPARAM lparam);
	afx_msg void OnTest();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKMONITORDLG_H__08EDC4EC_0BD6_4353_90CB_18E4441C80B9__INCLUDED_)
