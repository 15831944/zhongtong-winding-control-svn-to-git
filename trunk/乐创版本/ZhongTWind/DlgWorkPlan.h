#if !defined(AFX_DLGWORKPLAN_H__AB4B357E_CF1B_418D_B8E3_6EB6A8668CEE__INCLUDED_)
#define AFX_DLGWORKPLAN_H__AB4B357E_CF1B_418D_B8E3_6EB6A8668CEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWorkPlan.h : header file
//

#include "ListCtrlEx.h"
#include "MyButton.h"
#include "TaskComputeParam.h"
#include "WindTaskInfo.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CDlgWorkPlan dialog

class CDlgWorkPlan : public CDialog
{
// Construction
public:
	int m_TaskNum;
	void DelTask(void);
	CWindTaskInfo m_WindTask[64];
	void Compute_Cross(int ListIndex);
	TaskComputeParam m_TaskParamForCreate[6];
	void ComputeCircle(int Listindex);
	void GetComputeParam(TaskComputeParam *param,int listIndex);
	void SetDataInitial(void);
	int m_ListReportNum;
	CDlgWorkPlan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWorkPlan)
	enum { IDD = IDD_DLG_WORKPLAN };
	CMyButton	m_BtnRun;
	CMyButton	m_BtnAddTask;
	CMyButton	m_BtnDelTask;
	CMyButton	m_BtnCompute;
	CListCtrlEx	mListCreateTaskList;
	CListCtrl	m_LayerShowList;
	double	m_PipeTotalLen;
	double	m_BandageWidth;
	double	m_SandWidth;
	double	m_CrossAngle;
	double	m_BuffLength;
	double	m_PipeDiameter;
	double	m_SandRate;
	double	m_StartStopAngle;
	double	m_StopStopAngle;
	int		m_RadioMainAxeSpeedFactor;
	int		m_RadioWindRule;
	int		m_RadioCutOffPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWorkPlan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWorkPlan)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickShowLayer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCompute();
	afx_msg void OnAddtask();
	afx_msg void OnBtnDeltask();
	afx_msg void OnMenuDeleteTask();
//	afx_msg void OnItemchangedCreatetask(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWORKPLAN_H__AB4B357E_CF1B_418D_B8E3_6EB6A8668CEE__INCLUDED_)
