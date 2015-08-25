// ZhongTWindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "ZhongTWindDlg.h"
#include "DlgWorkPlan.h"
#include "DlgIOTest.h"
#include "SysParamSetDlg.h"
#include "gep.h"//固高头文件


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CZhongTWindApp theApp;

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
// CZhongTWindDlg dialog

CZhongTWindDlg::CZhongTWindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZhongTWindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZhongTWindDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZhongTWindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZhongTWindDlg)
	DDX_Control(pDX, IDB_SYSPARAMSET, m_BtnSysParamSet);
	DDX_Control(pDX, IDB_STARTWIND, m_BtnStartWind);
	DDX_Control(pDX, IDB_IOTEST, m_BtnIOtest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZhongTWindDlg, CDialog)
	//{{AFX_MSG_MAP(CZhongTWindDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_STARTWIND, OnStartwind)
	ON_BN_CLICKED(IDB_IOTEST, OnIotest)
	ON_BN_CLICKED(IDB_SYSPARAMSET, OnSysparamset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZhongTWindDlg message handlers

BOOL CZhongTWindDlg::OnInitDialog()
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
	if (0!=InitBoard())
	{
	   MessageBox(L"aa");
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CZhongTWindDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZhongTWindDlg::OnPaint() 
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
HCURSOR CZhongTWindDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CZhongTWindDlg::OnStartwind() 
{
	// TODO: Add your control notification handler code here
	CDlgWorkPlan localDLG;
	localDLG.DoModal();
}

void CZhongTWindDlg::OnIotest() 
{
	// TODO: Add your control notification handler code here
	CDlgIOTest localDLG;
	localDLG.DoModal();
}

void CZhongTWindDlg::OnSysparamset() 
{
	CSysParamSetDlg localDLG;
	localDLG.m_MainAxe_levelFactor1 = theApp.GlobalParam.m_fMainAxeLevelFactor[0];
	localDLG.m_MainAxe_levelFactor2 = theApp.GlobalParam.m_fMainAxeLevelFactor[1];
	localDLG.m_MainAxe_levelFactor3 = theApp.GlobalParam.m_fMainAxeLevelFactor[2];
	localDLG.m_MainAxe_levelFactor4 = theApp.GlobalParam.m_fMainAxeLevelFactor[3];
	localDLG.m_MainAxe_levelFactor5 = theApp.GlobalParam.m_fMainAxeLevelFactor[4];
	localDLG.m_MainAxe_levelFactor6 = theApp.GlobalParam.m_fMainAxeLevelFactor[5];
	localDLG.m_MainAxe_MaxSpeed     = theApp.GlobalParam.m_fMainAxeMaxSpeed;
	localDLG.m_MainAxe_pulses       = theApp.GlobalParam.m_iMainAxePulses;
	localDLG.m_SpeedAFactor         = theApp.GlobalParam.m_fAccelerationFactor;
	localDLG.m_SpeedupA             = theApp.GlobalParam.m_fAcceleration;
	localDLG.m_ZeroLuoju            = theApp.GlobalParam.m_fZeroPitch;
    localDLG.m_CarSpeedDownP        = theApp.GlobalParam.m_fCarSpeedDownP;
	localDLG.m_CarDistancePerRound  = theApp.GlobalParam.m_fCarDistancePerRound;
	localDLG.m_Car_Pulses           = theApp.GlobalParam.m_iCarPulses;
	localDLG.m_Car_MaxSpeed         = theApp.GlobalParam.m_fCarMaxSpeed;
	
	localDLG.DoModal();
	
}

int CZhongTWindDlg::InitBoard()
{
	//////////////////
	// 初始化板卡

	if ((0!=GT_Open())||(0!=GT_Reset()))
	{
       return 1;
	}
	return 0;


}

BOOL CZhongTWindDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	GT_Close();
	return CDialog::DestroyWindow();
}

void CZhongTWindDlg::Ges_error(short rtn)
{
    switch (rtn)
    {
    	case -1:
            break;
		case  0:
			break;
		case  1:
			break;
		case  2:
			break;
		case  3:
			break;
		case  4:
		    break;
		case  5:
			break;
		case  7:
			break;
		default:
			break;
    }
}
