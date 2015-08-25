// DlgTest.cpp : implementation file
//

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "DlgTest.h"
#include "Mpc2810.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTest dialog


CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTest)
	m_Axe1Position = _T("");
	m_Axe1SpeedShow = _T("");
	m_UpdateInterval = 10000;
	m_ThisEncoder_Show = 0;
	m_MeasureInterval = 2000;
	m_LastEncoder_Show = 0;
	//}}AFX_DATA_INIT
}


void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTest)
	DDX_Text(pDX, IDS_AXE1POSITION, m_Axe1Position);
	DDV_MaxChars(pDX, m_Axe1Position, 100);
	DDX_Text(pDX, IDS_AXE1_SHOW_SPEED, m_Axe1SpeedShow);
	DDX_Text(pDX, IDE_UPDATEINTERVAL, m_UpdateInterval);
	DDV_MinMaxInt(pDX, m_UpdateInterval, 0, 2147483647);
	DDX_Text(pDX, IDE_THIS_ENCODER, m_ThisEncoder_Show);
	DDX_Text(pDX, IDE_MEASURE_INTERVAL, m_MeasureInterval);
	DDV_MinMaxInt(pDX, m_MeasureInterval, 0, 2147483647);
	DDX_Text(pDX, IDE_LAST_ENCODER, m_LastEncoder_Show);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
	//{{AFX_MSG_MAP(CDlgTest)
	ON_BN_CLICKED(IDB_Axe2Setup, OnAxe2Setup)
	ON_BN_CLICKED(IDB_AXE2START, OnAxe2start)
	ON_BN_CLICKED(IDB_POS_RESET, OnPosReset)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_AXE1_SET, OnAxe1Set)
	ON_MESSAGE(WM_MMTIMER_MEASURE_SPEED, OnMMTimerMeasureSpeed)
	ON_BN_CLICKED(IDB_START_AXE1, OnStartAxe1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTest message handlers

void CDlgTest::OnAxe2Setup() 
{
	// TODO: Add your control notification handler code here
	set_maxspeed(2,2000000);
	set_profile(2,100,1000000,500000);
	//set_conspeed(2,1000000);
}

void CDlgTest::OnAxe2start() 
{
	// TODO: Add your control notification handler code here
	fast_vmove(2,1);  //启动1 轴正向连续运动 
    m_Axe2runningStatus = 1;
}

BOOL CDlgTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Axe2runningStatus = 0;
	m_Axe1runningStatus = 0;
    m_iMeasureInterval = 2000;	
	m_iMeasureInterval = 5;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTest::OnPosReset() 
{
	// TODO: Add your control notification handler code here
	if (m_Axe1runningStatus==0)
	{
		set_abs_pos(1,0); 
		//reset_pos(1);
		m_Axe1Position = "0";
		UpdateData(false);
	}
}

void CDlgTest::DestroyTimer()
{
  if (m_wTimerID)
  {
	  timeKillEvent(m_wTimerID);	  
	  timeEndPeriod(wTimerRes);
	  m_wTimerID = 0;
	  MessageBox("Destroy OK!");
  }
}



void  PASCAL MeasureMainAxeSpeed(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	CDlgTest* localThisdlg = (CDlgTest *)dwUser;
	localThisdlg->m_iUpdateCount++;
    localThisdlg->m_iLastEncoderValue = localThisdlg->m_iThisEncoderValue;
    get_encoder(1,&(localThisdlg->m_iThisEncoderValue)); 
	if (localThisdlg->m_iUpdateCount>=(localThisdlg->m_iUpdateInterval/localThisdlg->m_iMeasureInterval))
	{
		PostMessage(localThisdlg->GetSafeHwnd(),WM_MMTIMER_MEASURE_SPEED,0,0);
		localThisdlg->m_iUpdateCount = 0;
	}
	
}


bool CDlgTest::CreateTimer()
{
	TIMECAPS tc;
	
	if (timeGetDevCaps(&tc,sizeof(TIMECAPS))!=TIMERR_NOERROR)
	{
		return FALSE;
	}
	
	wTimerRes = min(max(tc.wPeriodMin,1),tc.wPeriodMax);
	
	timeBeginPeriod(wTimerRes);
	m_wTimerID = timeSetEvent(m_iMeasureInterval,wTimerRes,(LPTIMECALLBACK)MeasureMainAxeSpeed,(DWORD)this,TIME_PERIODIC);
	
	if (m_wTimerID==0)
	{
		return FALSE;
	}
	
	
	return TRUE;

}


void CDlgTest::OnDestroy() 
{
	CDialog::OnDestroy();
	DestroyTimer();
	// TODO: Add your message handler code here
	
}

LRESULT CDlgTest::OnMMTimerMeasureSpeed(WPARAM wparam, LPARAM lparam)
{
	// this->FunUpdateData(0,0);
	// SetTimer(2,1000,0);
	/*
	CString showStr;
    this->m_LastEncoder_Show = m_iLastEncoderValue;
	this->m_ThisEncoder_Show = m_iThisEncoderValue;
	double tempdouble;
	tempdouble = (m_iThisEncoderValue - m_iLastEncoderValue)*1000/m_iMeasureInterval;
	showStr.Format("%.3f",tempdouble);
    this->m_Axe1SpeedShow = showStr;
    UpdateData(false);
    */
	MessageBox("haha");
	return 0;
}

void CDlgTest::OnAxe1Set() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_iMeasureInterval = this->m_MeasureInterval;
	m_iUpdateInterval = this->m_UpdateInterval;
}

void CDlgTest::OnStartAxe1() 
{
	// TODO: Add your control notification handler code here
	if (CreateTimer()==true)
	{
		MessageBox("MMTimer Set OK!");
		m_iLastEncoderValue = 0;
		m_iThisEncoderValue = 0;
		m_iUpdateCount = 0;
	}
}
