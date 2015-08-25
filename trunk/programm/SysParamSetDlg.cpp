// SysParamSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "SysParamSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysParamSetDlg dialog


CSysParamSetDlg::CSysParamSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysParamSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysParamSetDlg)
	m_ZeroLuoju = 0.0;
	m_SpeedAFactor = 0.0;
	m_SpeedupA = 0.0;
	m_MainAxe_pulses = 0;
	m_MainAxe_MaxSpeed = 0.0;
	m_MainAxe_levelFactor6 = 0.0;
	m_MainAxe_levelFactor5 = 0.0;
	m_MainAxe_levelFactor4 = 0.0;
	m_MainAxe_levelFactor3 = 0.0;
	m_MainAxe_levelFactor2 = 0.0;
	m_MainAxe_levelFactor1 = 0.0;
	m_CarSpeedDownP = 0.0;
	m_Car_Pulses = 0;
	m_Car_MaxSpeed = 0.0;
	m_CarDistancePerRound = 0.0;
	//}}AFX_DATA_INIT
}


void CSysParamSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysParamSetDlg)
	DDX_Text(pDX, IDE_ZERO_LUOJU, m_ZeroLuoju);
	DDX_Text(pDX, IDE_SPEEDUP_A_FACTOR, m_SpeedAFactor);
	DDX_Text(pDX, IDE_SPEEDUP_A, m_SpeedupA);
	DDX_Text(pDX, IDE_MAIN_AXE_PULSES, m_MainAxe_pulses);
	DDX_Text(pDX, IDE_MAIN_AXE_MAXSPEED, m_MainAxe_MaxSpeed);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_6, m_MainAxe_levelFactor6);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_5, m_MainAxe_levelFactor5);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_4, m_MainAxe_levelFactor4);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_3, m_MainAxe_levelFactor3);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_2, m_MainAxe_levelFactor2);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_1, m_MainAxe_levelFactor1);
	DDX_Text(pDX, IDE_CAR_SPEEDDOWNP, m_CarSpeedDownP);
	DDX_Text(pDX, IDE_CAR_PULSES, m_Car_Pulses);
	DDX_Text(pDX, IDE_CAR_MAXSPEED, m_Car_MaxSpeed);
	DDX_Text(pDX, IDE_CAR_DISTANCE_PER_R, m_CarDistancePerRound);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysParamSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSysParamSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEDATA, OnButtonUpdatedata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysParamSetDlg message handlers

void CSysParamSetDlg::OnButtonUpdatedata() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);

	  m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_1 = m_MainAxe_levelFactor1;
	  m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_2 = m_MainAxe_levelFactor2;
	  m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_3 = m_MainAxe_levelFactor3;
	  m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_4 = m_MainAxe_levelFactor4;
	  m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_5 = m_MainAxe_levelFactor5;
	  m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_6 = m_MainAxe_levelFactor6;
	  m_lpMainDlg->m_Gsysparam.m_fMainAxeMaxSpeed      = m_MainAxe_MaxSpeed;
	  m_lpMainDlg->m_Gsysparam.m_iMainAxePulses        = m_MainAxe_pulses;
	  m_lpMainDlg->m_Gsysparam.m_fASpeedFactor         = m_SpeedAFactor;
	  m_lpMainDlg->m_Gsysparam.m_fAspeed               = m_SpeedupA;
	  m_lpMainDlg->m_Gsysparam.m_fZeroLuoju            = m_ZeroLuoju;
      m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP        = m_CarSpeedDownP;
	  m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound  = m_CarDistancePerRound;
	  m_lpMainDlg->m_Gsysparam.m_iCarPulses            = m_Car_Pulses;
	  m_lpMainDlg->m_Gsysparam.m_fCarMaxSpeed          = m_Car_MaxSpeed;

}
