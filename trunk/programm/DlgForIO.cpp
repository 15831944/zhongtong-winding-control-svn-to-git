// DlgForIO.cpp : implementation file
//

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "DlgForIO.h"
#include "Mpc2810.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define  MAIN_AXE_POS_DIR  ((byte)(0x04))
#define  MAIN_AXE_NEG_DIR  ((byte)(0x02))


#define  IO_IN_JIASHA     6
#define  IO_IN_HUANXIANG       (IO_IN_JIASHA+1)
#define  IO_IN_QINGLING        (IO_IN_JIASHA+2)
#define  IO_IN_ZIDONG          (IO_IN_JIASHA+3)
#define  IO_IN_SHOUDONG        (IO_IN_JIASHA+4)
#define  IO_IN_XIAOCHEJIANSU   (IO_IN_JIASHA+5)
#define  IO_IN_XIAOCHEJIASU    (IO_IN_JIASHA+6)
#define  IO_IN_XIAOCHE_NEGDIR  (IO_IN_JIASHA+7)
#define  IO_IN_XIAOCHE_POSDIR  (IO_IN_JIASHA+8)
#define  IO_IN_ZHUZHOU_NEGDIR  (IO_IN_JIASHA+9)
#define  IO_IN_ZHUZHOU_POSDIR  (IO_IN_JIASHA+10)

/////////////////////////////////////////////////////////////////////////////
// CDlgForIO dialog


CDlgForIO::CDlgForIO(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgForIO::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgForIO)
	m_CarConsRpm = 60.0f;
	m_CarRounds = 10.0;
	//}}AFX_DATA_INIT
}


void CDlgForIO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgForIO)
	DDX_Control(pDX, IDS_ICON_IN_9, m_Icon_IN9);
	DDX_Control(pDX, IDS_ICON_IN_8, m_Icon_IN8);
	DDX_Control(pDX, IDS_ICON_IN_7, m_Icon_IN7);
	DDX_Control(pDX, IDS_ICON_IN_6, m_Icon_IN6);
	DDX_Control(pDX, IDS_ICON_IN_5, m_Icon_IN5);
	DDX_Control(pDX, IDS_ICON_IN_4, m_Icon_IN4);
	DDX_Control(pDX, IDS_ICON_IN_3, m_Icon_IN3);
	DDX_Control(pDX, IDS_ICON_IN_2, m_Icon_IN2);
	DDX_Control(pDX, IDS_ICON_IN_16, m_Icon_IN16);
	DDX_Control(pDX, IDS_ICON_IN_15, m_Icon_IN15);
	DDX_Control(pDX, IDS_ICON_IN_14, m_Icon_IN14);
	DDX_Control(pDX, IDS_ICON_IN_13, m_Icon_IN13);
	DDX_Control(pDX, IDS_ICON_IN_12, m_Icon_IN12);
	DDX_Control(pDX, IDS_ICON_IN_11, m_Icon_IN11);
	DDX_Control(pDX, IDS_ICON_IN_10, m_Icon_IN10);
	DDX_Control(pDX, IDS_ICON_IN_1, m_Icon_IN1);
	DDX_Control(pDX, IDB_MAIN_POS_DIR, m_IndiButton_MainPosDir);
	DDX_Control(pDX, IDB_MAIN_NEG_DIR, m_IndiButton_MainNegDir);
	DDX_Text(pDX, IDE_CAR_CONS_SPEED, m_CarConsRpm);
	DDX_Text(pDX, IDE_CAR_GO_DISTANCE, m_CarRounds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgForIO, CDialog)
	//{{AFX_MSG_MAP(CDlgForIO)
	ON_BN_CLICKED(IDB_MAIN_NEG_DIR, OnMainNegDir)
	ON_BN_CLICKED(IDB_MAIN_POS_DIR, OnMainPosDir)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_CAR_POS_DIR, OnCarPosDir)
	ON_BN_CLICKED(IDB_CAR_NEGDIR, OnCarNegdir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgForIO message handlers

void CDlgForIO::OnMainNegDir() 
{
	// TODO: Add your control notification handler code here
    byte tempbyte = this->m_IOout&MAIN_AXE_NEG_DIR;
	if (tempbyte!=0)
	{
		
		this->m_IndiButton_MainNegDir.SetBkColor(RGB(34,189,17));
		this->m_IOout&=(~MAIN_AXE_NEG_DIR);
		outport_bit(1,3,0);
	}
	else
	{
		this->m_IndiButton_MainNegDir.SetBkColor(RGB(255,0,0));
		this->m_IOout|=MAIN_AXE_NEG_DIR;
		outport_bit(1,3,1);
	}

}

void CDlgForIO::OnMainPosDir() 
{
	// TODO: Add your control notification handler code here
    byte tempbyte = this->m_IOout&MAIN_AXE_POS_DIR;
	if (tempbyte!=0)
	{
		
		this->m_IndiButton_MainPosDir.SetBkColor(RGB(34,189,17));
		this->m_IOout&=(~MAIN_AXE_POS_DIR);
		outport_bit(1,4,0);
	}
	else
	{
		this->m_IndiButton_MainPosDir.SetBkColor(RGB(255,0,0));
		this->m_IOout|=MAIN_AXE_POS_DIR;
		outport_bit(1,4,1);
	}
}

BOOL CDlgForIO::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	int i;
    byte tempbyte = this->m_IOout&MAIN_AXE_POS_DIR;
	if (tempbyte!=0)
	{
		this->m_IndiButton_MainPosDir.SetBkColor(RGB(255,0,0));
	}
	else
	{
       this->m_IndiButton_MainPosDir.SetBkColor(RGB(34,189,17));
	}
	tempbyte = this->m_IOout&MAIN_AXE_NEG_DIR;
	if (tempbyte!=0)
	{
		this->m_IndiButton_MainNegDir.SetBkColor(RGB(255,0,0));
	}
	else
	{
		this->m_IndiButton_MainNegDir.SetBkColor(RGB(34,189,17));
	}
	
    for (i=0;i<16;i++)
    {
		CheckIO_IN(i+1);
    }

	SetTimer(37,1000,0);
    
	
    m_iPulseNumPerRound = 1000;

    set_maxspeed(1,1000000);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgForIO::OnTimer(UINT nIDEvent) 
{
	int i;
	switch (nIDEvent)
    {
    case 37:
		for (i=0;i<16;i++)
		{
			CheckIO_IN(i+1);
		}		
		break;
    default:
		MessageBox("default: KillTimer");
		KillTimer(nIDEvent);
		break;
    }
}


void CDlgForIO::CheckIO_IN(int num)
{
	CStatic *local;
	
	int ret = check_sfr_bit(1,num);

	switch (num)
	{
	  case 1:
		  local = &m_Icon_IN1;
		  break;
      case 2:
		  local = &m_Icon_IN2;
		  break;
      case 3:
		  local = &m_Icon_IN3;
		  break;
	  case 4:
		  local = &m_Icon_IN4;
		  break;
	  case 5:
		  local = &m_Icon_IN5;
		  break;
	  case 6:
		  local = &m_Icon_IN6;
		  break;
      case 7:
		  local = &m_Icon_IN7;
		  break;
      case 8:
		  local = &m_Icon_IN8;
		  break;
	  case 9:
		  local = &m_Icon_IN9;
		  break;
	  case 10:
		  local = &m_Icon_IN10;
		  break;
	  case 11:
		  local = &m_Icon_IN11;
		  break;
      case 12:
		  local = &m_Icon_IN12;
		  break;
      case 13:
		  local = &m_Icon_IN13;
		  break;
	  case 14:
		  local = &m_Icon_IN14;
		  break;
	  case 15:
		  local = &m_Icon_IN15;
		  break;
	  case 16:
		  local = &m_Icon_IN16;
		  break;
	  default:
		  return;
		  ;
	}
	if (ret==0)
    {
		local->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_GREENLIGHT));
    }
    else if (ret==1)
    {
		local->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_REDLIGHT));
    }
    else
	{
		local->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_BLUELIGHT));
	}

    enable_isr(1,1);
	set_isr_factor(1,0x01);
//	set_isr_routine(this->MyIsr);

}

void CDlgForIO::OnDestroy() 
{
	CDialog::OnDestroy();
	
    KillTimer(37);	
}

void CDlgForIO::OnCarPosDir() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	double conspeed = m_iPulseNumPerRound*(m_CarConsRpm/60);
	set_conspeed(1,conspeed);
	double step = m_CarRounds*m_iPulseNumPerRound;
	set_dir(1,1);
	con_pmove(1,step);
	
}

void CDlgForIO::OnCarNegdir() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	double conspeed = m_iPulseNumPerRound*(m_CarConsRpm/60);
	set_conspeed(1,conspeed);
	double step = m_CarRounds*m_iPulseNumPerRound;
	set_dir(1,-1);
	con_pmove(1,step);
}

void CDlgForIO::MyIsr()
{
   MessageBox("aa");
}
