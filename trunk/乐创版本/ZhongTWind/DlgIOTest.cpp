// DlgIOTest.cpp : implementation file
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "DlgIOTest.h"
#include "Mpc2810.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




#define  MAIN_AXE_POS_DIR  ((byte)(0x04))
#define  MAIN_AXE_NEG_DIR  ((byte)(0x02))


#define  IO_IN_ADDSAND           6
#define  IO_IN_CROSSWIND       (IO_IN_ADDSAND+ 1)
#define  IO_IN_CLEARPOS        (IO_IN_ADDSAND+ 2)
#define  IO_IN_AUTOWIND        (IO_IN_ADDSAND+ 3)
#define  IO_IN_MANUALWIND      (IO_IN_ADDSAND+ 4)
#define  IO_IN_CAR_SPEEDDOWN   (IO_IN_ADDSAND+ 5)
#define  IO_IN_CAR_SPEEDUP     (IO_IN_ADDSAND+ 6)
#define  IO_IN_CAR_NEGDIR      (IO_IN_ADDSAND+ 7)
#define  IO_IN_CAR_POSDIR      (IO_IN_ADDSAND+ 8)
#define  IO_IN_MAINAXE_NEGDIR  (IO_IN_ADDSAND+ 9)
#define  IO_IN_MAINAXE_POSDIR  (IO_IN_ADDSAND+10)



#define	 IO_FOR_MAINAXE_POSITIVE_DIR   4
#define	 IO_FOR_MAINAXE_NEGETIVE_DIR   3
/////////////////////////////////////////////////////////////////////////////
// CDlgIOTest dialog


CDlgIOTest::CDlgIOTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIOTest)
	//}}AFX_DATA_INIT
}


void CDlgIOTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIOTest)
	DDX_Control(pDX, IDB_MAIN_POS_DIR, m_BtnMainAxePosDir);
	DDX_Control(pDX, IDB_MAIN_NEG_DIR, m_BtnMainAxeNegDir);
	DDX_Control(pDX, IDS_ICON_IN_9, m_iconIN_9);
	DDX_Control(pDX, IDS_ICON_IN_8, m_iconIN_8);
	DDX_Control(pDX, IDS_ICON_IN_7, m_iconIN_7);
	DDX_Control(pDX, IDS_ICON_IN_6, m_iconIN_6);
	DDX_Control(pDX, IDS_ICON_IN_5, m_iconIN_5);
	DDX_Control(pDX, IDS_ICON_IN_4, m_iconIN_4);
	DDX_Control(pDX, IDS_ICON_IN_3, m_iconIN_3);
	DDX_Control(pDX, IDS_ICON_IN_2, m_iconIN_2);
	DDX_Control(pDX, IDS_ICON_IN_16, m_iconIN_16);
	DDX_Control(pDX, IDS_ICON_IN_15, m_iconIN_15);
	DDX_Control(pDX, IDS_ICON_IN_14, m_iconIN_14);
	DDX_Control(pDX, IDS_ICON_IN_13, m_iconIN_13);
	DDX_Control(pDX, IDS_ICON_IN_12, m_iconIN_12);
	DDX_Control(pDX, IDS_ICON_IN_11, m_iconIN_11);
	DDX_Control(pDX, IDS_ICON_IN_10, m_iconIN_10);
	DDX_Control(pDX, IDS_ICON_IN_1, m_iconIN_1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIOTest, CDialog)
	//{{AFX_MSG_MAP(CDlgIOTest)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_MAIN_NEG_DIR, OnMainNegDir)
	ON_BN_CLICKED(IDB_MAIN_POS_DIR, OnMainPosDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIOTest message handlers

BOOL CDlgIOTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;
    byte tempShort = this->m_IOout&MAIN_AXE_POS_DIR;

	if (tempShort!=0)
	{
		this->m_BtnMainAxePosDir.SetBkColor(RGB(255,0,0));
	}
	else
	{
		this->m_BtnMainAxePosDir.SetBkColor(RGB(34,189,17));
	}
	tempShort = this->m_IOout&MAIN_AXE_NEG_DIR;
	if (tempShort!=0)
	{
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(255,0,0));
	}
	else
	{
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(34,189,17));
	}
	
    for (i=0;i<16;i++)
    {
		CheckIO_IN(i+1);
    }
    

	SetTimer(37,500,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




/*
  检查IO输入端口，第 num 个 IO
  会更新按钮颜色
  部分 限位开关 有IO复用的能力，使用 enable_el 设为0 可作为 通用IO口 
  这时候 IO状态 可以 用check_sfr_bit查询   

*/
void CDlgIOTest::CheckIO_IN(int num)
{
	CStatic *local;
	
	int ret = check_sfr_bit(1,num);
	
	switch (num)
	{
	case 1:
		local = &m_iconIN_1;
		break;
	case 2:
		local = &m_iconIN_2;
		break;
	case 3:
		local = &m_iconIN_3;
		break;
	case 4:
		local = &m_iconIN_4;
		break;
	case 5:
		local = &m_iconIN_5;
		break;
	case 6:
		local = &m_iconIN_6;
		break;
	case 7:
		local = &m_iconIN_7;
		break;
	case 8:
		local = &m_iconIN_8;
		break;
	case 9:
		local = &m_iconIN_9;
		break;
	case 10:
		local = &m_iconIN_10;
		break;
	case 11:
		local = &m_iconIN_11;
		break;
	case 12:
		local = &m_iconIN_12;
		break;
	case 13:
		local = &m_iconIN_13;
		break;
	case 14:
		local = &m_iconIN_14;
		break;
	case 15:
		local = &m_iconIN_15;
		break;
	case 16:
		local = &m_iconIN_16;
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
	
	/**/ //奇怪 这后面两句应该是设置 中断的 ，没用，，原程序没有注释掉，这里注释掉 
    //enable_isr(1,1);
	//set_isr_factor(1,0x01);
    //	set_isr_routine(this->MyIsr);
}

void CDlgIOTest::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
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
		MessageBox(L"default: KillTimer");
		KillTimer(nIDEvent);
		break;
    }
	CDialog::OnTimer(nIDEvent);
}

void CDlgIOTest::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(37);	
	// TODO: Add your message handler code here
	
}

void CDlgIOTest::OnMainNegDir() 
{
	// TODO: Add your control notification handler code here
	byte tempbyte = this->m_IOout&MAIN_AXE_NEG_DIR;
	if (tempbyte!=0)
	{
		
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(34,189,17));
		this->m_IOout&=(~MAIN_AXE_NEG_DIR);
		outport_bit(1,IO_FOR_MAINAXE_NEGETIVE_DIR,0);
	}
	else
	{
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(255,0,0));
		this->m_IOout|=MAIN_AXE_NEG_DIR;
		outport_bit(1,IO_FOR_MAINAXE_NEGETIVE_DIR,1);
	}
}

void CDlgIOTest::OnMainPosDir() 
{
	// TODO: Add your control notification handler code here
	   byte tempbyte = this->m_IOout&MAIN_AXE_POS_DIR;
	   if (tempbyte!=0)
	   {
		   
		   this->m_BtnMainAxePosDir.SetBkColor(RGB(34,189,17));
		   this->m_IOout&=(~MAIN_AXE_POS_DIR);
		   outport_bit(1,IO_FOR_MAINAXE_POSITIVE_DIR,0);
	   }
	   else
	   {
		   this->m_BtnMainAxePosDir.SetBkColor(RGB(255,0,0));
		   this->m_IOout|=MAIN_AXE_POS_DIR;
		   outport_bit(1,IO_FOR_MAINAXE_POSITIVE_DIR,1);
	   }
}
