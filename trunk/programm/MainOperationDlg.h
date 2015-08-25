#if !defined(AFX_MAINOPERATIONDLG_H__803BCA7D_DF91_45AE_BD77_FD85A4C32D72__INCLUDED_)
#define AFX_MAINOPERATIONDLG_H__803BCA7D_DF91_45AE_BD77_FD85A4C32D72__INCLUDED_

#include "WindTaskInfo.h"	// Added by ClassView
#include "MPC2810CtrlDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainOperationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainOperationDlg dialog

class CMainOperationDlg : public CDialog
{
// Construction
public:
	void AddOneTask(int index);
	void UpdateResultData(int index);
	int m_iResultLayerNum[6];
	double m_fResultStopAngle[6];
	double m_fResultStartAngle[6];
	double m_fResultAngle[6];
	double m_fResultBandWidth[6];
	void UpdateLayerComputeData(void);
	int m_intLayerNumLayer[6];
	double m_fLayerEndPos[6];
	double m_fLayerStartPos[6];
	int m_intLayerMethodSel[6];
	BOOL m_intLayerCheck[6];
	void ComputeCircle(int index,int MainAxeSpeedFactor,int ComputeMethod);
	int m_ListNum;
	void Compute_Cross(int index,int MainAxeSpeedFactor,int ComputeMethod);
	CMPC2810CtrlDlg* m_lpMainDlg;
	int m_WindTaskNum;
	CWindTaskInfo m_WindTask[64];
	int m_DataSetNum;
	void test();
	CMainOperationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainOperationDlg)
	enum { IDD = IDD_DLG_OPERATION };
	CListCtrl	m_LayerShowList;
	double	m_BandageWidth;
	double	m_CrossAngle;
	double	m_LeftBuffLength;
	double	m_RightBuffLength;
	double	m_PipeDiameter;
	double	m_PipeTotalLen;
	int		m_RadioWindRule;
	int		m_RadioMainAxeSpeedFactor;
	int		m_WindMethod_Layer1;
	int		m_WindMethod_Layer2;
	int		m_RadioContinueOrManual;
	double	m_StartStopAngle;
	double	m_EndStopAngle;
	double	m_StartPosLayer1;
	double	m_EndPosLayer1;
	int		m_TaskLayerNum_L1;
	BOOL	m_CheckLayer1;
	BOOL	m_CheckLayer2;
	BOOL	m_CheckLayer3;
	BOOL	m_CheckLayer4;
	BOOL	m_CheckLayer5;
	BOOL	m_CheckLayer6;
	int		m_ShowCishuLayer1;
	int		m_ShowCishuLayer2;
	int		m_ShowCishuLayer3;
	int		m_ShowCishuLayer4;
	int		m_ShowCishuLayer5;
	int		m_ShowCishuLayer6;
	double	m_EndPosLayer2;
	double	m_EndPosLayer3;
	double	m_EndPosLayer4;
	double	m_EndPosLayer5;
	double	m_EndPosLayer6;
	double	m_CrossShowLayer1;
	double	m_CrossShowLayer2;
	double	m_CrossShowLayer3;
	double	m_CrossShowLayer4;
	double	m_CrossShowLayer5;
	double	m_CrossShowLayer6;
	int		m_WindMethod_Layer3;
	int		m_WindMethod_Layer4;
	int		m_WindMethod_Layer5;
	int		m_WindMethod_Layer6;
	int		m_TaskLayerNum_L2;
	int		m_TaskLayerNum_L3;
	int		m_TaskLayerNum_L4;
	int		m_TaskLayerNum_L5;
	int		m_TaskLayerNum_L6;
	double	m_StartPosLayer2;
	double	m_StartPosLayer3;
	double	m_StartPosLayer4;
	double	m_StartPosLayer5;
	double	m_StartPosLayer6;
	double	m_QiTingJiaoShow_Layer1;
	double	m_QiTingJiaoShow_Layer2;
	double	m_QiTingJiaoShow_Layer3;
	double	m_QiTingJiaoShow_Layer4;
	double	m_QiTingJiaoShow_Layer5;
	double	m_QiTingJiaoShow_Layer6;
	double	m_ZhongTingJiaoShowLayer1;
	double	m_ZhongTingJiaoShowLayer2;
	double	m_ZhongTingJiaoShowLayer3;
	double	m_ZhongTingJiaoShowLayer4;
	double	m_ZhongTingJiaoShowLayer5;
	double	m_ZhongTingJiaoShowLayer6;
	double	m_ShaWidthShow_Layer1;
	double	m_ShaWidthShow_Layer2;
	double	m_ShaWidthShow_Layer3;
	double	m_ShaWidthShow_Layer4;
	double	m_ShaWidthShow_Layer5;
	double	m_ShaWidthShow_Layer6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainOperationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainOperationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCompute();
	afx_msg void OnFirmShaWidth();
	afx_msg void OnFirmCrossangle();
	afx_msg void OnAlter();
	afx_msg void OnRun();
	afx_msg void OnAddworktask();
	afx_msg void OnCheckLayer1();
	afx_msg void OnCheckLayer2();
	afx_msg void OnCheckLayer3();
	afx_msg void OnCheckLayer4();
	afx_msg void OnCheckLayer5();
	afx_msg void OnCheckLayer6();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINOPERATIONDLG_H__803BCA7D_DF91_45AE_BD77_FD85A4C32D72__INCLUDED_)
