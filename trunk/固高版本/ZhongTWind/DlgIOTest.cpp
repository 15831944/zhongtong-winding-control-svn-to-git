// DlgIOTest.cpp : implementation file
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "DlgIOTest.h"
#include "gep.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIOTest dialog


#define  MAIN_AXE_POS_DIR  ((unsigned short)(0x0002))
#define  MAIN_AXE_NEG_DIR  ((unsigned short)(0x0001))








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
	DDX_Control(pDX, IDB_MAIN_NEG_DIR, m_BtnMainAxeNegDir);
	DDX_Control(pDX, IDB_MAIN_POS_DIR, m_BtnMainAxePosDir);
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
    unsigned short tempbyte = this->m_IOout&MAIN_AXE_POS_DIR;
	
	if (tempbyte!=0)
	{
		this->m_BtnMainAxePosDir.SetBkColor(RGB(255,0,0));
	}
	else
	{
		this->m_BtnMainAxePosDir.SetBkColor(RGB(34,189,17));
	}
	tempbyte = this->m_IOout&MAIN_AXE_NEG_DIR;
	if (tempbyte!=0)
	{
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(255,0,0));
	}
	else
	{
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(34,189,17));
	}
	
    //GT_ExOpt();
    unsigned short ButtonStatus;
	GT_ExInpt(&ButtonStatus);
    CheckIO_IN(ButtonStatus);
	SetTimer(37,500,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIOTest::CheckIO_IN(unsigned short num)
{
   int i = 0;
   CStatic *local;
  // unsigned short ButtonStatus;
  // GT_ExInpt(&ButtonStatus);

   unsigned short tempShort = 0x0001;

   for (i=0;i<16;i++)
   {
	   switch (i)
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
		   local = &m_iconIN_1;
	   }
	   if ((num&tempShort)!=0)
	   {
		   local->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_REDLIGHT));
	   }
	   else
	   {
		   local->SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_GREENLIGHT));
	   }
	   tempShort = tempShort <<1;
   }

}

void CDlgIOTest::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
    {
    case 37:
		unsigned short ButtonStatus;
		GT_ExInpt(&ButtonStatus);
        CheckIO_IN(ButtonStatus);
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
	unsigned short tempbyte = this->m_IOout&MAIN_AXE_NEG_DIR;
	if (tempbyte!=0)
	{		
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(34,189,17));
		this->m_IOout&=(~MAIN_AXE_NEG_DIR);
		GT_ExOpt(this->m_IOout);
		//outport_bit(1,IO_FOR_MAINAXE_NEGETIVE_DIR,0);
	}
	else
	{
		this->m_BtnMainAxeNegDir.SetBkColor(RGB(255,0,0));
		this->m_IOout|=MAIN_AXE_NEG_DIR;
		GT_ExOpt(this->m_IOout);
		//outport_bit(1,IO_FOR_MAINAXE_NEGETIVE_DIR,1);
	}
}

void CDlgIOTest::OnMainPosDir() 
{
	unsigned short tempbyte = this->m_IOout&MAIN_AXE_POS_DIR;
	if (tempbyte!=0)
	{
	    this->m_BtnMainAxePosDir.SetBkColor(RGB(34,189,17));
	    this->m_IOout&=(~MAIN_AXE_POS_DIR);
	    GT_ExOpt(this->m_IOout);
		//outport_bit(1,IO_FOR_MAINAXE_POSITIVE_DIR,0);
	}
	else
	{
	    this->m_BtnMainAxePosDir.SetBkColor(RGB(255,0,0));
	    this->m_IOout|=MAIN_AXE_POS_DIR;
        GT_ExOpt(this->m_IOout);
	    //outport_bit(1,IO_FOR_MAINAXE_POSITIVE_DIR,1);
    }	
}
