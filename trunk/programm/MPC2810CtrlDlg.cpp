// MPC2810CtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "MPC2810CtrlDlg.h"
#include "Mpc2810.h"
#include "DlgTest.h"
#include "DlgForIO.h"
#include "MainOperationDlg.h"
#include "SysParamSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPC2810CtrlDlg dialog

CMPC2810CtrlDlg::CMPC2810CtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMPC2810CtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMPC2810CtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMPC2810CtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMPC2810CtrlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMPC2810CtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CMPC2810CtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_TEST, OnTest)
	ON_BN_CLICKED(IDB_IO_TEST, OnIoTest)
	ON_BN_CLICKED(IDB_RUN_OPERATION, OnRunOperation)
	ON_BN_CLICKED(IDB_SET_PARAMETER, OnSetParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPC2810CtrlDlg message handlers

BOOL CMPC2810CtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	ShowWindow(SW_MAXIMIZE);
    if (InitBoard()==0)
    {
		MessageBox("OK");
    }
	else
	{
		;//MessageBox("failed");
	}    
	m_gMainAxeIOout = 0xFF;
    SysInitial();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMPC2810CtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMPC2810CtrlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMPC2810CtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CMPC2810CtrlDlg::InitBoard()
{
	int i;
	//	CString str;
	//////////////////
	//初始化板卡
	glTotalAxes=auto_set();			//自动设置
	if(glTotalAxes<=0 )
	{
		MessageBox("检测不到卡!");
		return -1;
	}
	
	glTotalCards=init_board();		//初始化
	if(glTotalCards<=0)
	{
		MessageBox("初始化错误!");
		return -1;
	}
	
	for(i=0;i<glTotalAxes;i++)
	{
		enable_sd(i,0);
        enable_el(i,0);
		enable_org(i,0);
		enable_alm(i,0);
	    //set_sd_logic(i+1,0);   //减速信号低电平有效
		//set_el_logic(i+1,0);   //限位信号低电平有效
		//set_org_logic(i+1,0);  //原点信号低电平有效
		//set_alm_logic(i+1,0);  //报警信号低电平有效
	}

	m_gMainAxeIOout = 0xFF;
	/*
	outport_byte(1,255);
	for (i = 0;i<8;i++)
	{
		outport_bit(1,i+1,1);
	}
	*/
	outport_bit(1,3,1);
    outport_bit(1,4,1);
	return 0;
}

void CMPC2810CtrlDlg::OnTest() 
{
	// TODO: Add your control notification handler code here
	CDlgTest localDLG;
	localDLG.DoModal();
}

void CMPC2810CtrlDlg::OnIoTest() 
{
	// TODO: Add your control notification handler code here
	CDlgForIO localDLG;
	localDLG.m_IOout = this->m_gMainAxeIOout;
	localDLG.DoModal();
	this->m_gMainAxeIOout = localDLG.m_IOout;
}

void CMPC2810CtrlDlg::OnRunOperation() 
{
	// TODO: Add your control notification handler code here
	CMainOperationDlg localDLG;
	localDLG.m_lpMainDlg = this;
	localDLG.DoModal();
}

void CMPC2810CtrlDlg::OnSetParameter() 
{
	// TODO: Add your control notification handler code here
	CSysParamSetDlg localDLG;
	localDLG.m_lpMainDlg = this;
	localDLG.m_MainAxe_levelFactor1 = this->m_Gsysparam.m_fMainAxeLevelFactor_1;
	localDLG.m_MainAxe_levelFactor2 = this->m_Gsysparam.m_fMainAxeLevelFactor_2;
	localDLG.m_MainAxe_levelFactor3 = this->m_Gsysparam.m_fMainAxeLevelFactor_3;
	localDLG.m_MainAxe_levelFactor4 = this->m_Gsysparam.m_fMainAxeLevelFactor_4;
	localDLG.m_MainAxe_levelFactor5 = this->m_Gsysparam.m_fMainAxeLevelFactor_5;
	localDLG.m_MainAxe_levelFactor6 = this->m_Gsysparam.m_fMainAxeLevelFactor_6;
	localDLG.m_MainAxe_MaxSpeed     = this->m_Gsysparam.m_fMainAxeMaxSpeed;
	localDLG.m_MainAxe_pulses       = this->m_Gsysparam.m_iMainAxePulses;
	localDLG.m_SpeedAFactor         = this->m_Gsysparam.m_fASpeedFactor;
	localDLG.m_SpeedupA             = this->m_Gsysparam.m_fAspeed;
	localDLG.m_ZeroLuoju            = this->m_Gsysparam.m_fZeroLuoju;
    localDLG.m_CarSpeedDownP        = this->m_Gsysparam.m_fCarSpeedDownP;
	localDLG.m_CarDistancePerRound  = this->m_Gsysparam.m_fCarDistancePerRound;
	localDLG.m_Car_Pulses           = this->m_Gsysparam.m_iCarPulses;
	localDLG.m_Car_MaxSpeed         = this->m_Gsysparam.m_fCarMaxSpeed;

	localDLG.DoModal();
}

void CMPC2810CtrlDlg::SysInitial()
{
  m_Gsysparam.m_fAspeed = 1;
  m_Gsysparam.m_fASpeedFactor =1;
  m_Gsysparam.m_fCarDistancePerRound = 424.115001;
  m_Gsysparam.m_fCarMaxSpeed = 3000;
  m_Gsysparam.m_fCarSpeedDownP = 11;
  m_Gsysparam.m_fMainAxeLevelFactor_1 = 23;
  m_Gsysparam.m_fMainAxeLevelFactor_2 = 47.31428571;
  m_Gsysparam.m_fMainAxeLevelFactor_3 = 23;
  m_Gsysparam.m_fMainAxeLevelFactor_4 = 23;
  m_Gsysparam.m_fMainAxeLevelFactor_5 = 23;
  m_Gsysparam.m_fMainAxeLevelFactor_6 = 23;
  m_Gsysparam.m_fMainAxeMaxSpeed = 1460;
  m_Gsysparam.m_fZeroLuoju = 80;
  m_Gsysparam.m_iCarPulses = 10000;
  m_Gsysparam.m_iMainAxePulses = 2000;
}
