// SysParamSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "SysParamSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CZhongTWindApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSysParamSetDlg dialog


CSysParamSetDlg::CSysParamSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysParamSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysParamSetDlg)
	m_CarDistancePerRound = 0.0;
	m_Car_MaxSpeed = 0.0;
	m_Car_Pulses = 0;
	m_CarSpeedDownP = 0.0;
	m_MainAxe_levelFactor1 = 0.0;
	m_MainAxe_levelFactor2 = 0.0;
	m_MainAxe_levelFactor3 = 0.0;
	m_MainAxe_levelFactor4 = 0.0;
	m_MainAxe_levelFactor5 = 0.0;
	m_MainAxe_levelFactor6 = 0.0;
	m_MainAxe_MaxSpeed = 0.0;
	m_MainAxe_pulses = 0;
	m_SpeedupA = 0.0;
	m_SpeedAFactor = 0.0;
	m_ZeroLuoju = 0.0;
	//}}AFX_DATA_INIT
}


void CSysParamSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysParamSetDlg)
	DDX_Control(pDX, IDC_BUTTON_UPDATEDATA, m_BtnUpdate);
	DDX_Text(pDX, IDE_CAR_DISTANCE_PER_R, m_CarDistancePerRound);
	DDX_Text(pDX, IDE_CAR_MAXSPEED, m_Car_MaxSpeed);
	DDX_Text(pDX, IDE_CAR_PULSES, m_Car_Pulses);
	DDX_Text(pDX, IDE_CAR_SPEEDDOWNP, m_CarSpeedDownP);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_1, m_MainAxe_levelFactor1);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_2, m_MainAxe_levelFactor2);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_3, m_MainAxe_levelFactor3);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_4, m_MainAxe_levelFactor4);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_5, m_MainAxe_levelFactor5);
	DDX_Text(pDX, IDE_MAIN_AXE_LEVELFACTOR_6, m_MainAxe_levelFactor6);
	DDX_Text(pDX, IDE_MAIN_AXE_MAXSPEED, m_MainAxe_MaxSpeed);
	DDX_Text(pDX, IDE_MAIN_AXE_PULSES, m_MainAxe_pulses);
	DDX_Text(pDX, IDE_SPEEDUP_A, m_SpeedupA);
	DDX_Text(pDX, IDE_SPEEDUP_A_FACTOR, m_SpeedAFactor);
	DDX_Text(pDX, IDE_ZERO_LUOJU, m_ZeroLuoju);
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
	theApp.GlobalParam.m_fMainAxeLevelFactor[0] = m_MainAxe_levelFactor1;
	theApp.GlobalParam.m_fMainAxeLevelFactor[1] = m_MainAxe_levelFactor2;
	theApp.GlobalParam.m_fMainAxeLevelFactor[2] = m_MainAxe_levelFactor3;
	theApp.GlobalParam.m_fMainAxeLevelFactor[3] = m_MainAxe_levelFactor4;
	theApp.GlobalParam.m_fMainAxeLevelFactor[4] = m_MainAxe_levelFactor5;
	theApp.GlobalParam.m_fMainAxeLevelFactor[5] = m_MainAxe_levelFactor6;
	theApp.GlobalParam.m_fMainAxeMaxSpeed       = m_MainAxe_MaxSpeed;
	theApp.GlobalParam.m_iMainAxePulses         = m_MainAxe_pulses;
	theApp.GlobalParam.m_fAccelerationFactor    = m_SpeedAFactor;
	theApp.GlobalParam.m_fAcceleration          = m_SpeedupA;
	theApp.GlobalParam.m_fZeroPitch             = m_ZeroLuoju;
	theApp.GlobalParam.m_fCarSpeedDownP         = m_CarSpeedDownP;
	theApp.GlobalParam.m_fCarDistancePerRound   = m_CarDistancePerRound;
	theApp.GlobalParam.m_iCarPulses             = m_Car_Pulses;
    theApp.GlobalParam.m_fCarMaxSpeed           = m_Car_MaxSpeed;
}
