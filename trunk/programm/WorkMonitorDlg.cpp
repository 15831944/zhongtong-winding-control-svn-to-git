// WorkMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "WorkMonitorDlg.h"
#include "Mpc2810.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define LAYER_METHOD_CIRCLE   0
#define LAYER_METHOD_JIASHA   1
#define LAYER_METHOD_CROSS    2


#define BUTTON_JIASHA          6
#define BUTTON_HUANXIANG       7
#define BUTTON_QINGLING        8
#define BUTTON_ZIDONG          9
#define BUTTON_SHOUDONG       10
#define BUTTON_CARSPEEDDOWN   11
#define BUTTON_CARSPEEDUP     12 
#define BUTTON_CARREVDIR      13
#define BUTTON_CARPOSDIR      14 
#define BUTTON_MAINREVDIR     15
#define BUTTON_MAINPOSDIR     16

#define BUTTON_JIASHA_BIT          (1<<5)
#define BUTTON_HUANXIANG_BIT       (1<<6)
#define BUTTON_QINGLING_BIT        (1<<7)
#define BUTTON_ZIDONG_BIT          (1<<8)
#define BUTTON_SHOUDONG_BIT        (1<<9)
#define BUTTON_CARSPEEDDOWN_BIT   (1<<10)
#define BUTTON_CARSPEEDUP_BIT     (1<<11) 
#define BUTTON_CARREVDIR_BIT      (1<<12)
#define BUTTON_CARPOSDIR_BIT      (1<<13) 
#define BUTTON_MAINREVDIR_BIT     (1<<14)
#define BUTTON_MAINPOSDIR_BIT     (1<<15) 


#define  CONTROL_STATUS_INITIAL        0
#define  CONTROL_STATUS_AUTO           1
#define  CONTROL_STATUS_MANUAL         2

#define  MPC2810_MAX_SPEED        2000000
#define  MPC2810_MIN_INITIAL_SPEED    100


#define  PI_VALUE        3.14159265359



/////////////////////////////////////////////////////////////////////////////
// CWorkMonitorDlg dialog


CWorkMonitorDlg::CWorkMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkMonitorDlg)
	m_WorkingProg1 = _T("");
	m_WorkingProg2 = _T("");
	m_WorkingProg3 = _T("");
	m_WorkingOutput = _T("");
	m_WindNum = 0;
	m_Already_WindNum = 0;
	m_CarDir = _T("");
	m_CarPos = 0.0;
	m_CarSpeed = 0.0;
	m_CrossAngle = 0.0;
	m_EndPos = 0.0;
	m_EndStopAngle = 0.0;
	m_MainAxeDir = _T("");
	m_MainAxePos = 0.0;
	m_MainAxeSpeed = 0.0;
	m_PipeDiam = 0.0;
	m_PucengStartLayer = 0;
	m_ShaPianWidth = 0.0;
	m_StartPos = 0.0;
	m_StartStopAngle = 0.0;
	m_test1 = 0;
	m_test2 = 0;
	m_record1 = 0;
	m_record2 = 0;
	m_DebugOutEdit = _T("");
	m_MonitorMainAxe = 0.0;
	m_queryThread    = NULL;
	m_WindProcThread = NULL;
	m_ControlStatus  = 0;
	m_AdjMainAxeAngle = 0.0;
	//}}AFX_DATA_INIT
}


void CWorkMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkMonitorDlg)
	DDX_Control(pDX, IDB_TEST, m_ButtonTest);
	DDX_Control(pDX, IDB_SET_ZEROPOT, m_ButtonZeroSet);
	DDX_Control(pDX, IDB_INITIAL, m_ButtonInitial);
	DDX_Control(pDX, IDB_STARTWORK, m_ButtonStartWork);
	DDX_Text(pDX, IDE_WORKING_PROGRESS_1, m_WorkingProg1);
	DDX_Text(pDX, IDE_WORKING_PROGRESS_2, m_WorkingProg2);
	DDX_Text(pDX, IDE_WORKING_PROGRESS_3, m_WorkingProg3);
	DDX_Text(pDX, IDE_WORKING_OUTPUT, m_WorkingOutput);
	DDX_Text(pDX, IDE_WIND_NUM, m_WindNum);
	DDX_Text(pDX, IDE_ALREADY_WINDNUM, m_Already_WindNum);
	DDX_Text(pDX, IDE_CAR_DIR, m_CarDir);
	DDX_Text(pDX, IDE_CAR_POS, m_CarPos);
	DDX_Text(pDX, IDE_CAR_SPEED, m_CarSpeed);
	DDX_Text(pDX, IDE_CROSS_ANGLE, m_CrossAngle);
	DDX_Text(pDX, IDE_END_POS, m_EndPos);
	DDX_Text(pDX, IDE_END_STOPANGLE, m_EndStopAngle);
	DDX_Text(pDX, IDE_MAINAXE_DIR, m_MainAxeDir);
	DDX_Text(pDX, IDE_MAINAXE_POS, m_MainAxePos);
	DDX_Text(pDX, IDE_MAINAXE_SPEED, m_MainAxeSpeed);
	DDX_Text(pDX, IDE_PIPE_DIAM, m_PipeDiam);
	DDX_Text(pDX, IDE_PUCENG_START, m_PucengStartLayer);
	DDX_Text(pDX, IDE_SHAPIAN_WIDTH, m_ShaPianWidth);
	DDX_Text(pDX, IDE_START_POS, m_StartPos);
	DDX_Text(pDX, IDE_START_STOPANGLE, m_StartStopAngle);
	DDX_Text(pDX, IDC_EDIT1, m_test1);
	DDX_Text(pDX, IDC_EDIT2, m_test2);
	DDX_Text(pDX, IDC_EDIT3, m_record1);
	DDX_Text(pDX, IDC_EDIT4, m_record2);
	DDX_Text(pDX, IDE_DEBUG_OUT, m_DebugOutEdit);
	DDX_Text(pDX, IDC_MAIN_AXE_ANGLE_M, m_MonitorMainAxe);
	DDX_Text(pDX, IDC_MONITOR_ADJ_ANGLE, m_AdjMainAxeAngle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CWorkMonitorDlg)
	ON_BN_CLICKED(IDB_INITIAL, OnInitial)
	ON_BN_CLICKED(IDB_STARTWORK, OnStartwork)
	ON_BN_CLICKED(IDB_SET_ZEROPOT, OnSetZeropot)
	ON_MESSAGE(WM_MMTIMER_MEASURE_SPEED, OnMMTimerMeasureSpeed)
	ON_MESSAGE(WM_THREAD_BUTTON_CHANGE,OnButtonChanged)
	ON_MESSAGE(WM_THREAD_POS_UPDATE,OnUpdateCarPos)
	ON_MESSAGE(WM_DEBUGOUTPUT,OnUpdateDebugOut)   
	ON_MESSAGE(WM_DEBUGOUTPUTMM,OnUpdateDebugOutMM)	
	ON_MESSAGE(WM_WIND_NUM_UPDATE,OnUpdateWindNum)
	ON_BN_CLICKED(IDB_TEST, OnTest)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkMonitorDlg message handlers

BOOL CWorkMonitorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_QueryThreadRunningFlag = 0;
	m_queryThread = AfxBeginThread(QueryPressButton, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	
    m_QueryThreadRunningFlag = 1;
   
	ShowWindow(SW_MAXIMIZE);
    m_CurrentWindTaskIndex = 0;
/*    
	CString tempstr;
	tempstr.Format("%d",m_lpOpDlg->m_ListNum);
*/
	m_CurTaskIndex = 0;
	m_PipeDiam       = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_PipeDiam;
	m_ShaPianWidth   = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_shaWidth;
	m_StartPos       = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_StartPos;
	m_EndPos         = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_StopPos;
	m_StartStopAngle = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_StartStopAngle;
    m_EndStopAngle   = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_EndStopAngle;
	m_CrossAngle     = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_crossAngle;
	m_WindNum        = m_lpOpDlg->m_WindTask[m_CurTaskIndex].m_LayerNum;

    

	m_MainAxeDir     = "<<+>>";
	m_MainAxePos     = 0;
	m_MainAxeSpeed   = 0;

	m_CarDir         = "<<+>>";
    m_CarPos         = 0;
	m_Already_WindNum= 0;
	m_PucengStartLayer  = 1;
	UpdateData(false);

    m_iMeasureInterval = 100;
	m_iUpdateInterval  = 200;
    int intCheck;	
	intCheck = check_sfr(1);
    ButtonProcess(intCheck);
    m_ThisEncoder_Show = 0;
	m_LastEncoder_Show = 0;  
	
    m_queryThread->ResumeThread();
    this->m_iUpdateCount = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



UINT QueryPressButton(LPVOID pParam)   /// 线程函数
{   
    CWorkMonitorDlg* workingDlg = (CWorkMonitorDlg*)pParam;
    int intCheck;
	int LastIntCheck;
	LastIntCheck = 0;
	intCheck = 0;
	int firstflag=0;
	double pos;
	CString  pos_str;
	while (workingDlg->m_QueryThreadRunningFlag==1)
    {
       intCheck = check_sfr(1);

	   if (LastIntCheck!=intCheck)
	   {
		   if (firstflag!=0)
		   {
			   SendMessage(workingDlg->GetSafeHwnd(),WM_THREAD_BUTTON_CHANGE,LastIntCheck,intCheck);
		   }		   
		   firstflag = 1;
	   }
	   LastIntCheck = intCheck;
       get_abs_pos(1,&pos);
       SendMessage(workingDlg->GetSafeHwnd(),WM_THREAD_POS_UPDATE,(WPARAM)(&pos),(LPARAM)(&pos));
       Sleep(200);
    }
	//ExitThread(0);
    firstflag = 1;
	return 0;
}

void CWorkMonitorDlg::OnInitial() 
{
	// TODO: Add your control notification handler code here
	m_ButtonInitial.SetText(_T("初始化OK!"));
	m_ButtonInitial.EnableWindow(false);
//	set_outmode(1,1,0);
	set_maxspeed(1,MPC2810_MAX_SPEED);
//	set_profile(1,MPC2810_MIN_INITIAL_SPEED,20000,500000);
	//set_dir(1,-1);
   // set_conspeed(1,2000);
	m_CarCurSpeed = 2000;
	//con_vmove(1,1);
	double distancev = (20/424.115001)*11*10000;
    //fast_pmove(1,distancev);
	//Sleep(1000);
	int status = check_status(1);
	set_encoder_mode(1,1,1,0);//set_encoder_mode(1,1,1,0);
    set_encoder_mode(2,0,1,0);

    get_encoder(2,&m_iniCarEncoderVal);
	set_maxspeed(2,1000000);
	set_conspeed(2,1000000);
	con_vmove(2,1);

}

BOOL CWorkMonitorDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_QueryThreadRunningFlag = 0;
	DestroyTimer();
	sudden_stop(2);
	return CDialog::DestroyWindow();
}



void CWorkMonitorDlg::ButtonProcess(int buttonStatus)
{
    UINT AndTemp1; 
	UINT AndTemp2; 
	if (buttonStatus&BUTTON_QINGLING_BIT==0)  //清零按钮
     {
		 MessageBox("aa");
		 m_CarPos = 0;
		 m_WorkingOutput = "标定零点成功111";
		 set_abs_pos(1,0); 
		 get_encoder(2,&m_iniCarEncoderVal);
     }


	 AndTemp1     = buttonStatus&BUTTON_CARREVDIR_BIT;
	 AndTemp2     = buttonStatus&BUTTON_CARPOSDIR_BIT;

	 if ((AndTemp1)&&(AndTemp2))   //3档中间
	 {
        ;
	 }
	 else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
	 {
         m_CarDir         = ">>>>>>>";
	 }
	 else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
	 {
         m_CarDir         = "<<<<<<<";
	 } 
	 else
	 {
		 MessageBox(_T("小车方向按钮出错!"));
	 }
	 AndTemp1     = buttonStatus&BUTTON_MAINREVDIR_BIT;
	 AndTemp2     = buttonStatus&BUTTON_MAINPOSDIR_BIT;
	 if ((AndTemp1)&&(AndTemp2))   //3档中间
	 {
		 outport_bit(1,3,1);
         outport_bit(1,4,1);;
	 }
	 else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
	 {
         m_MainAxeDir         = ">>>>>>>";
		 outport_bit(1,3,1);
         outport_bit(1,4,0);
	 }
	 else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
	 {
         m_MainAxeDir         = "<<<<<<<";
		 outport_bit(1,4,1);
         outport_bit(1,3,0);
	 } 
	 else
	 {
		 MessageBox(_T("主轴方向按钮出错!"));
	 }

	 AndTemp1     = buttonStatus&BUTTON_JIASHA_BIT;
	 AndTemp2     = buttonStatus&BUTTON_HUANXIANG_BIT;
	 
	 if ((AndTemp1)&&(AndTemp2))   //3档中间
	 {
		 ;
	 }
	 else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
	 {
         ;
	 }
	 else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
	 {
         ;
	 } 
	 else
	 {
		 MessageBox(_T("加沙按钮出错!"));
	 }


	 AndTemp1     = buttonStatus&BUTTON_ZIDONG_BIT;
	 AndTemp2     = buttonStatus&BUTTON_SHOUDONG_BIT;
	 
	 if ((AndTemp1)&&(AndTemp2))   //3档中间
	 {
		 ;
	 }
	 else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
	 {
         ;
	 }
	 else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
	 {
         ;
	 } 
	 else
	 {
		 MessageBox(_T("自动手动按钮出错!"));
	 }


	 UpdateData(false);
}

void CWorkMonitorDlg::OnStartwork() 
{
	// TODO: Add your control notification handler code here
    if (myAbs(m_CarPos)<0.0001)
    {
		m_ButtonStartWork.EnableWindow(false);
		m_WindProcThread = AfxBeginThread(WindingProcessThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	    this->m_WindProcessRunningFlag = 1;
		m_WindProcThread->ResumeThread();
    }
    else
	{
		MessageBox("请先归零");
	}

}

void CWorkMonitorDlg::OnSetZeropot() 
{
	// TODO: Add your control notification handler code here
	
}



void  PASCAL MeasureMainAxeSpeedWork(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	CWorkMonitorDlg* localThisdlg = (CWorkMonitorDlg *)dwUser;
	double tempDelta;
	localThisdlg->m_iUpdateCount++;
    localThisdlg->m_iLastEncoderValue = localThisdlg->m_iThisEncoderValue;
    localThisdlg->m_2LastEncoderValue = localThisdlg->m_2ThisEncoderValue;
	get_encoder(2,&(localThisdlg->m_2ThisEncoderValue));
	get_encoder(1,&(localThisdlg->m_iThisEncoderValue)); 
	localThisdlg->m_MainAxeDeltaEncoderCount[localThisdlg->m_iUpdateCount-1] = 
		                      localThisdlg->m_iThisEncoderValue - localThisdlg->m_iLastEncoderValue;

	tempDelta = (double)(localThisdlg->m_2ThisEncoderValue - localThisdlg->m_2LastEncoderValue);
    localThisdlg->m_TickEncoderDelta = localThisdlg->myAbs(tempDelta);
	if (localThisdlg->m_iUpdateCount>=(localThisdlg->m_iUpdateInterval/localThisdlg->m_iMeasureInterval))
	{
		PostMessage(localThisdlg->GetSafeHwnd(),WM_MMTIMER_MEASURE_SPEED,0,0);
		localThisdlg->m_iUpdateCount = 0;
	}
	
}

bool CWorkMonitorDlg::CreateTimer()
{
	TIMECAPS tc;
	
	if (timeGetDevCaps(&tc,sizeof(TIMECAPS))!=TIMERR_NOERROR)
	{
		return FALSE;
	}
	
	wTimerRes = min(max(tc.wPeriodMin,1),tc.wPeriodMax);
	
	timeBeginPeriod(wTimerRes);
	m_wTimerID = timeSetEvent(m_iMeasureInterval,wTimerRes,(LPTIMECALLBACK)MeasureMainAxeSpeedWork,(DWORD)this,TIME_PERIODIC);
	
	if (m_wTimerID==0)
	{
		return FALSE;
	}	
    return TRUE;
}

void CWorkMonitorDlg::DestroyTimer()
{
	if (m_wTimerID)
	{
		timeKillEvent(m_wTimerID);	  
		timeEndPeriod(wTimerRes);
		m_wTimerID = 0;
		MessageBox("Destroy OK!");
	}
}


LRESULT CWorkMonitorDlg::OnMMTimerMeasureSpeed(WPARAM wparam, LPARAM lparam)
{

	CString showStr;
    this->m_LastEncoder_Show = m_iLastEncoderValue;
	this->m_ThisEncoder_Show = m_iThisEncoderValue;
	double tempdouble;
	double MainAxeEncoder_resolution;
	double MainAxeRatio;
	double RealV;
	m_test1 = m_iLastEncoderValue;
    m_test2 = m_iThisEncoderValue;
    MainAxeEncoder_resolution = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iMainAxePulses);
	if (m_iThisEncoderValue<0)
	{
		;
	}
    int i,num;
	long MeanDelta;
	MeanDelta = 0;

	num = (this->m_iUpdateInterval/this->m_iMeasureInterval);
    for (i =0 ;i<num;i++)
    {
       MeanDelta += m_MainAxeDeltaEncoderCount[i];
    }

     

	// 编码器差值除以时间，时间单位是毫秒，所以乘以1000，编码器分辨率是2000，所以除以2000 得到转速
	tempdouble = ((double)(m_iThisEncoderValue - m_iLastEncoderValue))*1000/
		         ((double)m_iMeasureInterval*MainAxeEncoder_resolution);
	showStr.Format("%.5f",tempdouble);

	MainAxeRatio = GetMainAxeSpeedRatio(m_lpOpDlg->m_RadioMainAxeSpeedFactor);
    this->m_MainAxeSpeed = tempdouble*60/MainAxeRatio; //得到每分钟多少转
    
	RealV = (double)(m_iThisEncoderValue - m_iLastEncoderValue)*(PI_VALUE)*(m_lpOpDlg->m_WindTask[0].m_PipeDiam)*1000/
		              (((double)m_iMeasureInterval)*MainAxeEncoder_resolution*MainAxeRatio);
    RealV = ((double)(MeanDelta))*(PI_VALUE)*(m_lpOpDlg->m_WindTask[0].m_PipeDiam)*1000/
		              (((double)m_iMeasureInterval)*MainAxeEncoder_resolution*MainAxeRatio*(double)num);
    
	//RealV = (double)(m_iThisEncoderValue - m_iLastEncoderValue)*(PI_VALUE)*(m_lpOpDlg->m_WindTask[0].m_PipeDiam)*1000/
	//	              ((m_TickEncoderDelta/1000)*MainAxeEncoder_resolution*MainAxeRatio);

  //  m_MainAxeRealV = m_MainAxeRealV/1000;
    
	if (RealV<0)
	{
		m_MainAxeRealV=RealV*(-1);
	} 
    else
	{
        m_MainAxeRealV = RealV;
	}
 
    UpdateData(false);

	return 0;
}


LRESULT CWorkMonitorDlg::OnUpdateCarPos(WPARAM wparam, LPARAM lparam)
{

	 double Car_RoundRatio;
	 double Car_DistancePerRound;
	 double Car_CyclePulse;
	 double *pos;

	 Car_RoundRatio = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP;
	 Car_DistancePerRound = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound;
     Car_CyclePulse = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iCarPulses);	

	 pos = (double *)wparam; 
	 long endcoderVal;
	 get_encoder(2,&endcoderVal);
     endcoderVal -= m_iniCarEncoderVal;

	 m_CarPos = ((*pos)*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
	// m_CarPos = *pos;
	 UpdateData(false);
    
	 return 0;
}

LRESULT CWorkMonitorDlg::OnButtonChanged(WPARAM wparam, LPARAM lparam)
{
	UINT lastButton;
	UINT thisButton;
    UINT changed;
    UINT AndTemp1, AndTemp2;
    UINT AndTempLast1, AndTempLast2;
	lastButton = ((UINT)wparam)&0xFFFFFFFF;
    thisButton = ((UINT)lparam)&0xFFFFFFFF;
    
    changed = lastButton^thisButton;

    if (changed&BUTTON_QINGLING_BIT)
    {
		AndTemp1 = thisButton&BUTTON_QINGLING_BIT;
		if (AndTemp1)
		{
			m_CarPos = 0;
			m_WorkingOutput = "标定零点成功";
		    set_abs_pos(1,0); 
			get_encoder(2,&m_iniCarEncoderVal);
			CString aa;
			aa.Format("%.2f",(double)m_iniCarEncoderVal);
		    MessageBox(aa);
		}
		else
		{

		}
    }
////////////////////////////////////////////小车加减速3档 按钮///////////////////////////////////////////////
	if ((changed&BUTTON_CARSPEEDUP_BIT)||(changed&BUTTON_CARSPEEDDOWN_BIT))
    {
		AndTemp1     = thisButton&BUTTON_CARSPEEDUP_BIT;
        AndTemp2     = thisButton&BUTTON_CARSPEEDDOWN_BIT;
		AndTempLast1 = lastButton&BUTTON_CARSPEEDUP_BIT;
        AndTempLast2 = lastButton&BUTTON_CARSPEEDDOWN_BIT;
		UINT andtemp11,andtemp12;
		andtemp11     = thisButton&BUTTON_CARREVDIR_BIT;
		andtemp12     = thisButton&BUTTON_CARPOSDIR_BIT;
		if ((AndTemp1)&&(AndTemp2))   //3档中间
		{
			KillTimer(7);			  
 			/*
          if ((AndTempLast1==0)&&(AndTempLast2))
		  {
			  KillTimer(7);			  
		  }
		  else
		  {
              KillTimer(8);
		  }
		  */
		}
		else if((AndTemp1)&&(AndTemp2==0))//小车加速
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				SetTimer(7,500,0);
				m_flagTimerSpeed = 1;
                int checkstatus = check_status(1);
                checkstatus = checkstatus&0x0001;
                if (checkstatus!=0)
                {					
					set_profile(1,100,4000,500000);
					m_CarCurSpeed = 4000;
					if (andtemp12==0)
					{
						fast_vmove(1,1);
					}
					else
					{
                        fast_vmove(1,-1);
					}
                }
				else
				{
					m_CarCurSpeed += 4000;
					if (m_CarCurSpeed>160000)
					{
						m_CarCurSpeed = 160000;
					}
					else
					{
                       change_speed(1,m_CarCurSpeed);
					}
					
				}
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//小车小车减速
		{
			if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				SetTimer(7,500,0);
				m_flagTimerSpeed = 2;
                int checkstatus = check_status(1);
                checkstatus = checkstatus&0x0001;
                if (checkstatus!=0)
                {					
                    ;
                }
				else
				{
					m_CarCurSpeed -= 4000;
					if (m_CarCurSpeed<=0)
					{
						m_CarCurSpeed = 0;
						sudden_stop(1);
					}
					else
					{
                      change_speed(1,m_CarCurSpeed);
					}
					
				}
            }
		} 
		else
		{
			MessageBox(_T("减速按钮出错!"));
		}
    }
/////////////////////////////////////////小车加减速3档 按钮/////////////////////////////////////////////


////////////////////////////////////////////小车正反向3档 按钮///////////////////////////////////////////////
	if ((changed&BUTTON_CARREVDIR_BIT)||(changed&BUTTON_CARPOSDIR_BIT))
    {
		AndTemp1     = thisButton&BUTTON_CARREVDIR_BIT;
        AndTemp2     = thisButton&BUTTON_CARPOSDIR_BIT;
		AndTempLast1 = lastButton&BUTTON_CARREVDIR_BIT;
        AndTempLast2 = lastButton&BUTTON_CARPOSDIR_BIT;
		if ((AndTemp1)&&(AndTemp2))   //3档中间
		{
            if ((AndTempLast1)&&(AndTempLast2==0))//原先正向被按下
            {
				m_CarDir = "<<<+>>>";		
				set_profile(1,100,2000,500000);
				decel_stop(1);
				m_CarCurSpeed =0;
				//MessageBox("小车正向归位");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//原先反向被按下
			{
				m_CarDir = "<<<+>>>";
				set_profile(1,100,2000,500000);
				decel_stop(1);
				m_CarCurSpeed =0;
				//MessageBox("小车反向归位");
			}
		}
		else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				set_dir(1,1);//MessageBox("小车正向");
				m_CarDir = ">>>>>>>";
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				set_dir(1,-1);//MessageBox("小车反向");
				m_CarDir = "<<<<<<<";
            }
		} 
		else
		{
			MessageBox(_T("小车方向按钮出错!"));
		}
    }
/////////////////////////////////////////小车正反向3档 按钮/////////////////////////////////////////////
////////////////////////////////////////////主轴正反向3档 按钮//////////////////////////////////////////
	if ((changed&BUTTON_MAINREVDIR_BIT)||(changed&BUTTON_MAINPOSDIR_BIT))
    {
		AndTemp1     = thisButton&BUTTON_MAINREVDIR_BIT;
        AndTemp2     = thisButton&BUTTON_MAINPOSDIR_BIT;
		AndTempLast1 = lastButton&BUTTON_MAINREVDIR_BIT;
        AndTempLast2 = lastButton&BUTTON_MAINPOSDIR_BIT;

		if ((AndTemp1)&&(AndTemp2))   //3档中间
		{

            if ((AndTempLast1)&&(AndTempLast2==0))//原先正向被按下
            {
				outport_bit(1,3,1);
                outport_bit(1,4,1);
				m_MainAxeDir = "<<<+>>>";
				//MessageBox("主轴正向归位");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//原先反向被按下
			{
				outport_bit(1,3,1);
                outport_bit(1,4,1);
				m_MainAxeDir = "<<<+>>>";
				//MessageBox("主轴反向归位");
			}
		}
		else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				outport_bit(1,3,1);
                outport_bit(1,4,0);
				//outport_byte(1,16);
				m_MainAxeDir = ">>>>>>>";
				//MessageBox("主轴正向");
            }
			/*
			else if ((AndTempLast1==0)&&(AndTempLast2))//原先反向被按下
			{
				outport_bit(1,3,0);
                outport_bit(1,4,1);
				MessageBox("16");
				m_MainAxeDir = ">>>>>>>";
			}*/
		}
		else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				outport_bit(1,4,1);
				outport_bit(1,3,0);
                
				//MessageBox("主轴反向");
				//outport_byte(1,16);
				m_MainAxeDir = "<<<<<<<";
            }
		} 
		else
		{
			MessageBox(_T("主轴方向按钮出错!"));
		}
    }
/////////////////////////////////////////主轴正反向3档 按钮/////////////////////////////////////////////
////////////////////////////////////////////手动自动3档 按钮////////////////////////////////////////////
	if ((changed&BUTTON_ZIDONG_BIT)||(changed&BUTTON_SHOUDONG_BIT))
    {
		AndTemp1     = thisButton&BUTTON_ZIDONG_BIT;
        AndTemp2     = thisButton&BUTTON_SHOUDONG_BIT;
		AndTempLast1 = lastButton&BUTTON_ZIDONG_BIT;
        AndTempLast2 = lastButton&BUTTON_SHOUDONG_BIT;

		if ((AndTemp1)&&(AndTemp2))   //3档中间
		{

            if ((AndTempLast1)&&(AndTempLast2==0))//原先正向被按下
            {
				MessageBox("自动归位");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//原先反向被按下
			{
				MessageBox("手动归位");
			}
		}
		else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
		        ;
				MessageBox("自动");
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				MessageBox("手动");
            }
		} 
		else
		{
			MessageBox(_T("自动手动按钮出错!"));
		}
    }
/////////////////////////////////////////手动自动3档 按钮/////////////////////////////////////////////
////////////////////////////////////////////环向加沙按钮//////////////////////////////////////////////
	if ((changed&BUTTON_JIASHA_BIT)||(changed&BUTTON_HUANXIANG_BIT))
    {
		AndTemp1     = thisButton&BUTTON_JIASHA_BIT;
        AndTemp2     = thisButton&BUTTON_HUANXIANG_BIT;
		AndTempLast1 = lastButton&BUTTON_JIASHA_BIT;
        AndTempLast2 = lastButton&BUTTON_HUANXIANG_BIT;
		
		if ((AndTemp1)&&(AndTemp2))   //3档中间
		{
			
            if ((AndTempLast1)&&(AndTempLast2==0))//原先正向被按下
            {
				MessageBox("加沙归位");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//原先反向被按下
			{
				MessageBox("环向归位");
			}
		}
		else if((AndTemp1)&&(AndTemp2==0))//小车正向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				;
				MessageBox("加沙");
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//小车反向被按下
		{
            if ((AndTempLast1)&&(AndTempLast2))//原先在中间
            {
				MessageBox("环向");
            }
		} 
		else
		{
			MessageBox(_T("环向加沙按钮出错!"));
		}
    }
///////////////////////////////////////////环向加沙按钮///////////////////////////////////////////////
    UpdateData(false);
    return 0;
}

void CWorkMonitorDlg::OnTest() 
{
	// TODO: Add your control notification handler code here
	if (CreateTimer()==true)
	{
		MessageBox("MMTimer Set OK!");
		m_iLastEncoderValue = 0;
		m_iThisEncoderValue = 0;
		m_iUpdateCount = 0;

		m_ButtonTest.EnableWindow(false);
	}
    
}

void CWorkMonitorDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	decel_stop(1);

	double pos;
	get_abs_pos(1,&pos);
    this->m_WindProcessRunningFlag = 0;
    sudden_stop(1);
}

void CWorkMonitorDlg::OnButton2() 
{
	double pos;
    long encoderCar;
	get_abs_pos(1,&pos);
    get_encoder(2,&encoderCar);

	set_profile(1,100,20000,20000);
	/*
    CString aa;
	aa.Format("%.2f",(double)(m_iniCarEncoderVal - encoderCar));
	MessageBox(aa);
    aa.Format("%.2f",(double)(m_iniCarEncoderVal));
	MessageBox(aa);
    */
    get_abs_pos(1,&pos);
    //pos = (pos/Car_DistancePerRound)*(Car_RoundRatio*Car_CyclePulse);
    //fast_pmove(1,(double)(encoderCar - m_iniCarEncoderVal));
    fast_pmove(1,0-pos);
}


void CWorkMonitorDlg::OnTimer(UINT nIDEvent) 
{
	int checkstatus;
	switch (nIDEvent)
    {
    case 7:
		if (m_flagTimerSpeed == 1)
		{
			m_CarCurSpeed += 4000;
			if (m_CarCurSpeed>160000)
			{
				m_CarCurSpeed = 160000;
			}
			else
			{
				change_speed(1,m_CarCurSpeed); 
			}
		}
	    else
		{
			checkstatus = check_status(1);
			checkstatus = checkstatus&0x00001;
			if (checkstatus!=0)
			{					
				;
			}
			else
			{
				m_CarCurSpeed -= 4000;
				if (m_CarCurSpeed<=0)
				{
					m_CarCurSpeed = 0;
					sudden_stop(1);
				}
				else
				{
					change_speed(1,m_CarCurSpeed);
				}
			}		
		}
		break;
	case 8:		
		break;
    default:
		//	MessageBox("default: KillTimer");
		//KillTimer(nIDEvent);
		break;
    }	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CWorkMonitorDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	long temp;
	get_encoder(1,&(temp)); 
	m_record1 = temp;
	UpdateData(false);
}

void CWorkMonitorDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	long temp;
	get_encoder(1,&(temp)); 
	m_record2 = temp;
	UpdateData(false);
}


UINT WindingProcessThread(LPVOID pParam)   /// 线程函数
{   
    CWorkMonitorDlg* workingDlg = (CWorkMonitorDlg*)pParam;
	CarControlParam CarParam,CarNewParam;

	double MainAxeSpeed;
	double buffLen;
	double TotalLen;
	double StopPos;
	double startpos;
	double qitingjiao;
    int TaskIndex;
	int runningflag;
	double EncoderResolution;

	int N;
    int i;

	TaskIndex = workingDlg->m_CurTaskIndex;
    N = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_LayerNum;
	workingDlg->ComputeCarMoveParam(TaskIndex,&CarParam);

	EncoderResolution = workingDlg->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iMainAxePulses;
    qitingjiao = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_StartStopAngle;
	MainAxeSpeed = workingDlg->m_MainAxeRealV;

	buffLen = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_leftBuffLen;
	TotalLen = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos - workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos;
	StopPos = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos;
	startpos = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos;
    
	int ret ;

	 runningflag = 1;
     ret = -1;
   for (i =TaskIndex;i< workingDlg->m_lpOpDlg->m_WindTaskNum;i++)
   {
      if (workingDlg->m_lpOpDlg->m_WindTask[i].m_WorkType == LAYER_METHOD_CIRCLE)
      {
          ret = workingDlg->CircleWindProcessq(i,&(workingDlg->m_WindProcessRunningFlag));
      }
	  else if (workingDlg->m_lpOpDlg->m_WindTask[i].m_WorkType == LAYER_METHOD_CROSS)
	  {   //CrossWindProcess
          ret = workingDlg->CrossWindProcessq(i,&(workingDlg->m_WindProcessRunningFlag));
		  //ret = workingDlg->CrossWindProcess(i,&(workingDlg->m_WindProcessRunningFlag));
	  }

	  if ( ret == 0)
	  {
		  workingDlg->m_ButtonStartWork.EnableWindow(TRUE);
	      return 0;
	  }
	  else if (ret == 1)
	  {
		  ret = -1;
	  }
   }

    //workingDlg->CrossWindProcess(TaskIndex,&(workingDlg->m_WindProcessRunningFlag));

	/*
	Angle = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_crossAngle;
	Angle = Angle*PI_VALUE/180;
	Car_RoundRatio = workingDlg->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP;
	Car_DistancePerRound = workingDlg->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(workingDlg->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iCarPulses);
    Car_ObjSpeed = MainAxeSpeed/tan(Angle);
    V0 = 100*Car_DistancePerRound/(Car_RoundRatio*Car_CyclePulse);
	buffLen = workingDlg->m_lpOpDlg->m_WindTask[TaskIndex].m_leftBuffLen;
    Car_a = (Car_ObjSpeed*Car_ObjSpeed - V0*V0)/2*buffLen;  //单位都是毫米
    Car_a = (Car_a/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
	Car_ObjSpeed = (Car_ObjSpeed/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
	*/



	workingDlg->m_ButtonStartWork.EnableWindow(TRUE);
	return 0;
}




double CWorkMonitorDlg::GetMainAxeSpeedRatio(int index)
{

   double ret;
   switch (index)
   {
     case 0:
		ret = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_1);
	   break;
     case 1:
		ret = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_2);
	   break;
	 case 2:
		ret = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_3);
	   break;
	 case 3:
		ret = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_4);
	   break;
     case 4:
        ret = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_5);
		 break;
	 case 5:
        ret = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_6);
		 break;
	 default:
		ret = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_1);
	   break;
   }
   
   return ret ;
   
}

double CWorkMonitorDlg::myAbs(double a)
{
   double ret;
   ret = a * a;
   ret = sqrt(ret);
   return ret;
}

void CWorkMonitorDlg::ComputeCarMoveParam(int index, CarControlParam* lpparam)
{
	double Car_a;
	double Car_ObjSpeed;
	double MainAxeSpeed;
	double Angle;
	double Car_RoundRatio;
	double Car_DistancePerRound;
    double Car_CyclePulse;
	double V0;
	double buffLen;
    int TaskIndex;
	index = index;
    MainAxeSpeed = this->m_MainAxeRealV;
	TaskIndex = index ;//this->m_CurTaskIndex;
	Angle = this->m_lpOpDlg->m_WindTask[TaskIndex].m_crossAngle;
	Angle = Angle*PI_VALUE/180;
	
	Car_RoundRatio = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP;
	Car_DistancePerRound = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iCarPulses);

    Car_ObjSpeed = MainAxeSpeed/tan(Angle);

    V0 = 100*Car_DistancePerRound/(Car_RoundRatio*Car_CyclePulse);

	buffLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_leftBuffLen;

    Car_a = (Car_ObjSpeed*Car_ObjSpeed - V0*V0)/(2*buffLen);  //单位都是毫米
	Car_a = (Car_ObjSpeed*Car_ObjSpeed - 0*0)/(2*buffLen);  //单位都是毫米
    
	Car_a = (Car_a/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
	Car_ObjSpeed = (Car_ObjSpeed/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;


    lpparam->m_a = Car_a;
    lpparam->m_ObjSpeed = Car_ObjSpeed; 

}




int CWorkMonitorDlg::CrossWindProcess(int index, int *runningflag)
{
   int iWindLayerNum;
   CarControlParam CarParam,CarNewParam;
   double Car_a;
   double Car_ObjSpeed;
   double Car_CurPos;
   double MainAxeSpeed;
   double Car_RoundRatio;
   double Car_DistancePerRound;
   double Car_CyclePulse;
   double buffLen;
   double TotalLen;
   double StopPos;
   double startpos;
   double qitingjiao;
   int TaskIndex;
   long iniMainAxeEncoder;
   long CurMainAxeEncoder;
   double EncoderResolution;
   int Car_dir;
   int i;
   int condition;
   int localrunningflag;
   double Car_CurPosInmm;
   long StartPosEncoder;
   long EndPosEncoder;

   TaskIndex = index;
   iWindLayerNum = this->m_lpOpDlg->m_WindTask[index].m_LayerNum;
   ComputeCarMoveParam(index,&CarParam);
   EncoderResolution = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iMainAxePulses;   //主轴编码器分辨率
   qitingjiao = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartStopAngle;     // 起停角
   MainAxeSpeed = this->m_MainAxeRealV;  //主轴速度
   

   Car_RoundRatio = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP;
   Car_DistancePerRound = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound;
   Car_CyclePulse = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iCarPulses);	
	
   buffLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_leftBuffLen;  //缓冲长度
   TotalLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos - 
	                      this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos;  //起点减去终点
   if (TotalLen>0)
   {
	   Car_dir = 1;
   }
   else	
   {
       Car_dir = -1;
   }
   StopPos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos;   //终点
   startpos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos; //起点



   for (i = 0;i<iWindLayerNum;i++)
   {
	   this->ComputeCarMoveParam(TaskIndex,&CarParam);
	   Car_a = CarParam.m_a;
	   Car_ObjSpeed = CarParam.m_ObjSpeed;
	   
	   set_profile(1,100,Car_ObjSpeed,Car_a);
	   fast_vmove(1,Car_dir);
	   get_encoder(1,&StartPosEncoder);
	   localrunningflag = 1;
	   while ((*runningflag)&&(localrunningflag))
	   {
		   get_abs_pos(1,&Car_CurPos);
           Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
           condition = 0;
		   if (Car_dir>0)
		   {
			   condition = 0;
			   if (Car_CurPosInmm>=StopPos - ((double)Car_dir)*buffLen)
			   {
                  condition = 1;
			   }			   
		   }
		   else
		   {
			   condition = 0;
			   if (Car_CurPosInmm<=StopPos - ((double)Car_dir)*buffLen)
			   {
				   condition = 1;
			   }
		   }
		   if (condition==1) //如果划过主区域，进入第二个缓冲区
		   {
			   set_profile(1,100,Car_ObjSpeed,Car_a);
			   change_speed(1,100);
			   get_abs_pos(1,&Car_CurPos);
			   Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
			   localrunningflag = 0;
		   }
		   else
		   {
			   this->ComputeCarMoveParam(TaskIndex,&CarNewParam);
			   if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.1*this->myAbs(CarParam.m_ObjSpeed)) //变化量大于10%就变速
			   {
				   CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				   CarParam.m_a = CarNewParam.m_a;
				   set_profile(1,100,CarParam.m_ObjSpeed,Car_a);
				   change_speed(1,CarParam.m_ObjSpeed);
			   }
			   Sleep(100);
		   }
	   }
	   if ((*runningflag)==0)
	   {
		   return 0;
	   }
       
       if (Car_dir>0)
       {
           condition = 0;
		   if (Car_CurPosInmm<StopPos)
		   {
			   condition = 1;
		   }
       }
	   else
	   {
	       condition = 0;
		   if (Car_CurPosInmm>StopPos)
		   {
			   condition = 1;
		   }
	   }

	   while ((condition)&&((*runningflag)))  // 是否到达指定位置
	   {
		   condition = 0;
		   get_abs_pos(1,&Car_CurPos);
		   Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
		   Sleep(100);
		   if (Car_dir>0)
		   {
			   condition = 0;
			   if (Car_CurPosInmm<StopPos)
			   {
				   condition = 1;
			   }
		   }
		   else
		   {
			   condition = 0;
			   if (Car_CurPosInmm>StopPos)
			   {
				   condition = 1;
			   }
		   }
	   }
	   if ((*runningflag)==0)
	   {
		   return 0;
	   }
	   sudden_stop(1);
	    int angleflag = 1;
	   get_encoder(1,&iniMainAxeEncoder); 
	   double ObjdeltaEncoder  = qitingjiao*EncoderResolution/(360*m_lpOpDlg->m_WindTask[index].m_mainAxeRatio);

	   while((angleflag)&&((*runningflag))) //等待起停角
	   {
		   Sleep(1);
		   get_encoder(1,&CurMainAxeEncoder); 
		   if (this->myAbs(CurMainAxeEncoder-iniMainAxeEncoder) >= ObjdeltaEncoder)
		   {
			   angleflag = 0;
		   }		   
	   }
	   if ((*runningflag)==0)
	   {
		   return 0;
	   }

       //this->ComputeCarMoveParam(0,&CarParam);
	   set_profile(1,100,Car_ObjSpeed,Car_a);
	   fast_vmove(1,-1*Car_dir);  //开始反向走了。
	   localrunningflag = 1;
	   while  ((*runningflag)&&(localrunningflag))
	   {
		   get_abs_pos(1,&Car_CurPos);
		   Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
		   condition = 0;
		   if (Car_dir>0)
		   {
			   condition = 0;
			   if (Car_CurPosInmm<= startpos+buffLen)
			   {
				   condition = 1;
			   }			   
		   }
		   else
		   {
			   condition = 0;
			   if (Car_CurPosInmm>=StopPos - buffLen)
			   {
				   condition = 1;
			   }
		   }

		   if (condition == 1)
		   {
			   //set_profile(1,CarParam.m_ObjSpeed,100,(-1)*Car_a); //?
			   change_speed(1,100);
			   get_abs_pos(1,&Car_CurPos);
			   Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
			   localrunningflag = 0;
		   }
		   else
		   {   
			   this->ComputeCarMoveParam(0,&CarNewParam);
			   if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.1*this->myAbs(CarParam.m_ObjSpeed)) //变化量大于10%就变速
			   {
				   CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				   CarParam.m_a = CarNewParam.m_a;
				   set_profile(1,100,CarParam.m_ObjSpeed,Car_a);
				   change_speed(1,CarParam.m_ObjSpeed);
			   }
			   Sleep(100);
		   }
	   }
       if ((*runningflag)==0)
	   {
		   return 0;
	   }


	   if (Car_dir>0)
       {
           condition = 0;
		   if (Car_CurPosInmm>startpos)
		   {
			   condition = 1;
		   }
       }
	   else
	   {
		   condition = 0;
		   if (Car_CurPosInmm<StopPos)
		   {
			   condition = 1;
		   }
	   }

	   while ((condition == 1)&&((*runningflag))) 
	   {
		   get_abs_pos(1,&Car_CurPos);
		   Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
		   Sleep(100);
		   if (Car_dir>0)
		   {
			   condition = 0;
			   if (Car_CurPosInmm>startpos)
			   {
				   condition = 1;
			   }
		   }
		   else
		   {
			   condition = 0;
			   if (Car_CurPosInmm<StopPos)
			   {
				   condition = 1;
			   }
		   }
	   }
	   if ((*runningflag)==0)
	   {
		   return 0 ;
	   }
	   sudden_stop(1);
	   angleflag = 1;
	   get_encoder(1,&iniMainAxeEncoder); 
	   ObjdeltaEncoder  = qitingjiao*EncoderResolution/(360*m_lpOpDlg->m_WindTask[index].m_mainAxeRatio);
	   while((angleflag)&&((*runningflag))) 
	   {
		   Sleep(1);
		   get_encoder(1,&CurMainAxeEncoder); 
		   if (this->myAbs(CurMainAxeEncoder-iniMainAxeEncoder) >= ObjdeltaEncoder)
		   {
			   angleflag = 0;
		   }
	   }
	   if ((*runningflag)==0)
	   {
		   return 0;
	   }
       get_encoder(1,&EndPosEncoder);

   }
   return 1;
}



int CWorkMonitorDlg::CircleWindProcessq(int index, int *runningflag)
{
	int iWindLayerNum;
	CarControlParam CarParam,CarNewParam;
	double Car_a;
	double Car_ObjSpeed;
	double Car_CurPos;
	double MainAxeSpeed;
	double Car_RoundRatio;
	double Car_DistancePerRound;
	double Car_CyclePulse;
	double buffLen;
	double TotalLen;
	double StopPos;
	double startpos;
	int TaskIndex;
//	double iniMainAxeEncoder;
//	double CurMainAxeEncoder;
	double EncoderResolution;
	int Car_dir;
	int i;
    double mainAxeRatio;
//	double Car_CurPosInmm;
    double distanceStartPos;

	iWindLayerNum = this->m_lpOpDlg->m_WindTask[index].m_LayerNum;
	ComputeCarMoveParam(0,&CarParam);
	mainAxeRatio = this->m_lpOpDlg->m_WindTask[index].m_mainAxeRatio;
	EncoderResolution = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iMainAxePulses;   //主轴编码器分辨率
	//	qitingjiao = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartStopAngle;     // 起停角
	MainAxeSpeed = this->m_MainAxeRealV;  //主轴速度
	TaskIndex = index;   
	Car_RoundRatio = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP;
	Car_DistancePerRound = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iCarPulses);	
	
	buffLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_leftBuffLen;  //缓冲长度
	TotalLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos - 
		this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos;  //起点减去终点
	if (TotalLen>0)
	{
		Car_dir = 1;
	}
	else	
	{
		Car_dir = -1;
	}
	StopPos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos;   //终点
	startpos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos; //起点


	for (i = 0;i<iWindLayerNum;i++)
	{
		get_abs_pos(1,&Car_CurPos);
		distanceStartPos = (startpos/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
		fast_pmove(1,distanceStartPos - Car_CurPos);  //到起点
		
		while(check_done(1))
		{
			Sleep(100); 
		}
		
		this->ComputeCarMoveParam(0,&CarParam);
		Car_a = CarParam.m_a;
		Car_ObjSpeed = CarParam.m_ObjSpeed;
		
		set_profile(1,100,Car_ObjSpeed,Car_a);
        distanceStartPos = ((StopPos - startpos)/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
        
		fast_pmove(1,distanceStartPos - Car_CurPos);
		while((check_done(1))&&(*runningflag))
		{
			this->ComputeCarMoveParam(0,&CarNewParam);
			if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.08*this->myAbs(CarParam.m_ObjSpeed)) //变化量大于05%就变速
			{
				CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				CarParam.m_a = CarNewParam.m_a;
				set_profile(1,100,CarParam.m_ObjSpeed,Car_a);
				change_speed(1,CarParam.m_ObjSpeed);
			}
			Sleep(100);
		}
		if ((*runningflag)==0)
		{
			return 0;
		}
        sudden_stop(1);

	}

    return 1;
}


int CWorkMonitorDlg::CircleWindProcess(int index, int *runningflag)
{
    int iWindLayerNum;
	CarControlParam CarParam,CarNewParam;
	double Car_a;
	double Car_ObjSpeed;
	double Car_CurPos;
	double MainAxeSpeed;
	double Car_RoundRatio;
	double Car_DistancePerRound;
	double Car_CyclePulse;
	double buffLen;
	double TotalLen;
	double StopPos;
	double startpos;
	int TaskIndex;
//	double iniMainAxeEncoder;
//	double CurMainAxeEncoder;
	double EncoderResolution;
	int Car_dir;
	int i;
	int condition;
    int localrunningflag;
    double mainAxeRatio;
	double Car_CurPosInmm;

	iWindLayerNum = this->m_lpOpDlg->m_WindTask[index].m_LayerNum;
	ComputeCarMoveParam(0,&CarParam);
	mainAxeRatio = this->m_lpOpDlg->m_WindTask[index].m_mainAxeRatio;
	EncoderResolution = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iMainAxePulses;   //主轴编码器分辨率
//	qitingjiao = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartStopAngle;     // 起停角
	MainAxeSpeed = this->m_MainAxeRealV;  //主轴速度
	TaskIndex = index;   
	Car_RoundRatio = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP;
	Car_DistancePerRound = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iCarPulses);	
	
	buffLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_leftBuffLen;  //缓冲长度
	TotalLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos - 
		this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos;  //起点减去终点


	if (TotalLen>0)
	{
		Car_dir = 1;
	}
	else	
	{
		Car_dir = -1;
	}
	StopPos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos;   //终点
	startpos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos; //起点
/*
    get_abs_pos(1,&Car_CurPos);
	double distanceStartPos = (startpos/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
    fast_pmove(1,distanceStartPos - Car_CurPos);  //到起点

	while(check_done(1))
	{
	 Sleep(100); 
	}
 */   

	for (i = 0;i<iWindLayerNum;i++)
	{
		get_abs_pos(1,&Car_CurPos);
		double distanceStartPos = (startpos/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
		fast_pmove(1,distanceStartPos - Car_CurPos);  //到起点
		
		while(check_done(1))
		{
			Sleep(100); 
		}

		this->ComputeCarMoveParam(0,&CarParam);
		Car_a = CarParam.m_a;
		Car_ObjSpeed = CarParam.m_ObjSpeed;
		
		set_profile(1,100,Car_ObjSpeed,Car_a);
		fast_vmove(1,Car_dir);
	    localrunningflag = 1;
		while ((*runningflag)&&(localrunningflag))
		{
			get_abs_pos(1,&Car_CurPos);
			Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
			condition = 0;
			if (Car_dir>0)
			{
				condition = 0;
				if (Car_CurPosInmm>=StopPos - ((double)Car_dir)*buffLen)
				{
					condition = 1;
				}			   
			}
			else
			{
				condition = 0;
				if (Car_CurPosInmm<=StopPos - ((double)Car_dir)*buffLen)
				{
					condition = 1;
				}
			}
			if (condition==1) //如果划过主区域，进入第二个缓冲区
			{
				//set_profile(1,CarParam.m_ObjSpeed,100,(-1)*Car_a); //?
				change_speed(1,100);
				get_abs_pos(1,&Car_CurPos);
				Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
				localrunningflag = 0;
			}
			else
			{
				this->ComputeCarMoveParam(0,&CarNewParam);
				if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.1*this->myAbs(CarParam.m_ObjSpeed)) //变化量大于10%就变速
				{
					CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
					CarParam.m_a = CarNewParam.m_a;
					set_profile(1,100,CarParam.m_ObjSpeed,Car_a);
					change_speed(1,CarParam.m_ObjSpeed);
				}
				Sleep(100);
			}
		}
		if ((*runningflag)==0)
		{
			return 0;
		}

		if (Car_dir>0)
		{
			condition = 0;
			if (Car_CurPosInmm<StopPos)
			{
				condition = 1;
			}
		}
		else
		{
			condition = 0;
			if (Car_CurPosInmm>StopPos)
			{
				condition = 1;
			}
		}
		
		while ((condition)&&((*runningflag)))  // 是否到达指定位置
		{
			condition = 0;
			get_abs_pos(1,&Car_CurPos);
			Car_CurPosInmm = (Car_CurPos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
			Sleep(100);
			if (Car_dir>0)
			{
				condition = 0;
				if (Car_CurPosInmm<StopPos)
				{
					condition = 1;
				}
			}
			else
			{
				condition = 0;
				if (Car_CurPosInmm>StopPos)
				{
					condition = 1;
				}
			}
		}
		if ((*runningflag)==0)
		{
			return 0;
		}
	    sudden_stop(1);


	}

    return 1;
}


int CWorkMonitorDlg::CrossWindProcessq(int index, int *runningflag)
{
	int iWindLayerNum;
	CarControlParam CarParam,CarNewParam;
	double Car_a;
	double Car_ObjSpeed;
	double Car_CurPos;
	double MainAxeSpeed;
	double Car_RoundRatio;
	double Car_DistancePerRound;
	double Car_CyclePulse;
	double buffLen;
	double TotalLen;
	double StopPos;
	double startpos;
	double qitingjiao;
	int TaskIndex;
	long iniMainAxeEncoder;
	long CurMainAxeEncoder;
	double EncoderResolution;
	int Car_dir;
	int i;
//	int condition;
//  double Car_CurPosInmm;
    double distanceStartPos;
	long StartPosEncoder;
    long EndPosEncoder;
	long lastEncoderV;
    long midPosEncoder;
	double MainAxePos_Y;
    double MainAxeRatio;
    double deltaMainCircle;
    double MainAxeCircleLen;
    double adjustangle;
    double halfEncoderlen;
    CString debugOutstr;
    double temp_CurSpeed;

	TaskIndex = index;
	iWindLayerNum = this->m_lpOpDlg->m_WindTask[index].m_LayerNum;
	ComputeCarMoveParam(index,&CarParam);
	EncoderResolution = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iMainAxePulses;   //主轴编码器分辨率
	MainAxeRatio = m_lpOpDlg->m_WindTask[index].m_mainAxeRatio;
	qitingjiao = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartStopAngle;     // 起停角
	MainAxeSpeed = this->m_MainAxeRealV;  //主轴速度	   
    
	MainAxeCircleLen = this->m_lpOpDlg->m_WindTask[index].m_PipeDiam*PI_VALUE;
	Car_RoundRatio = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarSpeedDownP;
	Car_DistancePerRound = this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(this->m_lpOpDlg->m_lpMainDlg->m_Gsysparam.m_iCarPulses);	
	   
	buffLen  = this->m_lpOpDlg->m_WindTask[TaskIndex].m_leftBuffLen;  //缓冲长度
	TotalLen = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos - 
	                            this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos;  //起点减去终点
	if (TotalLen>0)
	{
	  Car_dir = 1;
	}
	else	
	{
	  Car_dir = -1;
	}
	StopPos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StopPos;   //终点
	startpos = this->m_lpOpDlg->m_WindTask[TaskIndex].m_StartPos; //起点
	 
	MainAxePos_Y = 0;
	
	this->ComputeCarMoveParam(TaskIndex,&CarParam);
	Car_a = CarParam.m_a;
	Car_ObjSpeed = CarParam.m_ObjSpeed;
	set_profile(1,20,Car_ObjSpeed,Car_a);
	set_maxspeed(1,Car_ObjSpeed);
	//////////////////////////////////////////////////////////////////
	CString astr;
	astr.Format("%.2f",Car_a);
	astr+="\r\n";
	SendMessage(WM_DEBUGOUTPUT,(WPARAM)(&astr),astr.GetLength());
/////////////////////////////////////////////////////////////////////////
    

	get_encoder(1,&StartPosEncoder);
	lastEncoderV = StartPosEncoder;
    for (i = 0;i<iWindLayerNum;i++)
	{
		/*
		get_abs_pos(1,&Car_CurPos);
		distanceStartPos = (startpos/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
		fast_pmove(1,distanceStartPos - Car_CurPos);  //到起点
        while(check_done(1))
		{
			Sleep(100); 
		}
		*/
		
		
        distanceStartPos = ((StopPos - startpos)/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
       // get_abs_pos(1,&Car_CurPos);
	   //double curTorch = Car_CurPos;
		fast_pmove(1,distanceStartPos );
		//fast_pmove(1,distanceStartPos - Car_CurPos);
	
		int monitorFlag = 0;
		while((check_done(1))&&(*runningflag))
		{
			this->ComputeCarMoveParam(TaskIndex,&CarNewParam);
			if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.1*this->myAbs(CarParam.m_ObjSpeed)) //变化量大于10%就变速
			{
			    /*
				CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				CarParam.m_a = CarNewParam.m_a;
				set_profile(1,20,CarParam.m_ObjSpeed,Car_a);
				change_speed(1,CarParam.m_ObjSpeed);
				*/
				;
			}
			/*
			temp_CurSpeed = get_rate(1);
            if ((monitorFlag==0)&&(temp_CurSpeed>=Car_ObjSpeed))
            {
                double curPos;
				get_abs_pos(1,&curPos);
				curPos = (curPos-curTorch)*Car_DistancePerRound/(Car_RoundRatio*Car_CyclePulse);
				debugOutstr.Format("%f",curPos);
                debugOutstr = "1: up speed at:" + debugOutstr + "\r\n";
				SendMessage(WM_DEBUGOUTPUT,(WPARAM)(&debugOutstr),debugOutstr.GetLength());
				monitorFlag = 1;
            }
            if ((monitorFlag==1)&&(temp_CurSpeed<Car_ObjSpeed))
            {
                double curPos;
				get_abs_pos(1,&curPos);
				curPos = (curPos-curTorch)*Car_DistancePerRound/(Car_RoundRatio*Car_CyclePulse);
				debugOutstr.Format("%f",curPos);
                debugOutstr = "2: down speed at:" + debugOutstr + "\r\n";
				SendMessage(WM_DEBUGOUTPUT,(WPARAM)(&debugOutstr),debugOutstr.GetLength());
				monitorFlag = 2;
            }
            */

			//Sleep(10);
            get_encoder(1,&midPosEncoder);
            deltaMainCircle = myAbs((double)(midPosEncoder - lastEncoderV))/(MainAxeRatio*(double)EncoderResolution);
            lastEncoderV = midPosEncoder;
            deltaMainCircle = deltaMainCircle * MainAxeCircleLen;
            MainAxePos_Y += deltaMainCircle;
		}
        if (*runningflag==0)
        {
			return 0;
        }




        //sudden_stop(1);
		int angleflag = 1;
		get_encoder(1,&iniMainAxeEncoder); 
		double ObjdeltaEncoder  =  (qitingjiao)*EncoderResolution*(m_lpOpDlg->m_WindTask[index].m_mainAxeRatio)/(360);
		 ObjdeltaEncoder  =  (360)*EncoderResolution*(m_lpOpDlg->m_WindTask[index].m_mainAxeRatio)/(360);
		while((angleflag)&&((*runningflag))) //等待起停角
		{
			//Sleep(1);
			get_encoder(1,&CurMainAxeEncoder); 
			midPosEncoder = CurMainAxeEncoder;
            deltaMainCircle = myAbs((double)(midPosEncoder - lastEncoderV))/(MainAxeRatio*(double)EncoderResolution);
            lastEncoderV = midPosEncoder;
            deltaMainCircle = deltaMainCircle * MainAxeCircleLen;
            MainAxePos_Y += deltaMainCircle;
			if (this->myAbs(CurMainAxeEncoder-iniMainAxeEncoder)
				                               >= ObjdeltaEncoder)
			{
				angleflag = 0;
			}

		}
		if ((*runningflag)==0)
		{
			return 0;
		}

		set_profile(1,20,Car_ObjSpeed,Car_a);
        distanceStartPos = ((startpos - StopPos)/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
        get_abs_pos(1,&Car_CurPos);

        fast_pmove(1,distanceStartPos);
        while((check_done(1))&&(*runningflag))
		{
			this->ComputeCarMoveParam(TaskIndex,&CarNewParam);
			if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.1*this->myAbs(CarParam.m_ObjSpeed)) //变化量大于10%就变速
			{
				/*
				CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				CarParam.m_a = CarNewParam.m_a;
				set_profile(1,0,CarParam.m_ObjSpeed,Car_a);
				change_speed(1,CarParam.m_ObjSpeed);
                */
            }
			//Sleep(10);
			get_encoder(1,&midPosEncoder);
            deltaMainCircle = myAbs((double)(midPosEncoder - lastEncoderV))/(MainAxeRatio*(double)EncoderResolution);
            lastEncoderV = midPosEncoder;
            deltaMainCircle = deltaMainCircle * MainAxeCircleLen;
            MainAxePos_Y += deltaMainCircle;
		}
		if (*runningflag==0)
        {
			return 0;
        }
		
       // sudden_stop(1);
		get_encoder(1,&midPosEncoder);
		deltaMainCircle = myAbs((double)(midPosEncoder - lastEncoderV))/(MainAxeRatio*(double)EncoderResolution);
		lastEncoderV = midPosEncoder;
		deltaMainCircle = deltaMainCircle * MainAxeCircleLen;
        MainAxePos_Y += deltaMainCircle;        
		adjustangle = AdjustAngle(MainAxePos_Y+MainAxeCircleLen*qitingjiao/360,MainAxeCircleLen,TaskIndex);

        double tempout = 360*MainAxePos_Y/MainAxeCircleLen;
        SendMessage(WM_DEBUGOUTPUTMM,(WPARAM)(&tempout),(LPARAM)(&adjustangle));

		angleflag = 1;
		get_encoder(1,&iniMainAxeEncoder); 

        tempout = qitingjiao+adjustangle;
        if (tempout>180+360)
        {
           tempout-=360;
        }
		ObjdeltaEncoder  = (tempout)*EncoderResolution*(m_lpOpDlg->m_WindTask[index].m_mainAxeRatio)/(360);
	//	ObjdeltaEncoder  = 360*EncoderResolution*(m_lpOpDlg->m_WindTask[index].m_mainAxeRatio)/(360);
		while((angleflag)&&((*runningflag))) //等待起停角
		{
		//	Sleep(1);
			get_encoder(1,&CurMainAxeEncoder); 
			if (this->myAbs(CurMainAxeEncoder-iniMainAxeEncoder) 
				>= ObjdeltaEncoder)
			{
				angleflag = 0;
			}		   
		}
		if ((*runningflag)==0)
		{
			return 0;
		}
		/*
        get_encoder(1,&EndPosEncoder);
        CString deltaAStr;
		CString outStr;
		outStr = "delta Angle : ";
        deltaAStr.Format("%f",(double)(EndPosEncoder - StartPosEncoder));
        outStr+=deltaAStr;
        outStr+="\r\n";
		SendMessage(WM_DEBUGOUTPUT,(WPARAM)(&outStr),outStr.GetLength());
		SendMessage(WM_WIND_NUM_UPDATE,i+1,i+1);
		*/
		MainAxePos_Y = 0;
		get_encoder(1,&StartPosEncoder);
    	lastEncoderV = StartPosEncoder;
	}

return 1;
}


LRESULT CWorkMonitorDlg::OnUpdateWindNum(WPARAM wparam, LPARAM lparam)
{
	m_Already_WindNum = (int)lparam;
	UpdateData(false);
	return 0;
}

LRESULT CWorkMonitorDlg::OnUpdateDebugOutMM(WPARAM wparam, LPARAM lparam)
{
    double Y;
	double adjA;

	Y = *((double *)wparam);
	adjA = *((double *)lparam);

    this->m_MonitorMainAxe = Y;
	this->m_AdjMainAxeAngle = adjA;

   	UpdateData(false);
	
	return 0;
}


LRESULT CWorkMonitorDlg::OnUpdateDebugOut(WPARAM wparam, LPARAM lparam)
{
	int debugstrNum = (int)lparam;
	int i;
	CString outbuff;
	char *debugoutT;
	CString *dOut;
	outbuff = "";
	debugoutT = (char *)wparam;
	dOut = (CString *)wparam;
	for (i=0;i<debugstrNum;i++)
	{
		outbuff+= *debugoutT++;
	}
	
	//  m_DebugOutEdit += outbuff;
	m_DebugOutEdit += *dOut;
	UpdateData(false);
	
	return 0;
}



double CWorkMonitorDlg::AdjustAngle(double nowlength, double circlelen,int i)
{
	int N;
	double a;
    double angle;
    double width;
	double ret;

	angle = this->m_lpOpDlg->m_WindTask[i].m_crossAngle;
	angle = angle*PI_VALUE/180;

	width = this->m_lpOpDlg->m_WindTask[i].m_shaWidth;
    N = (int)(nowlength/circlelen);

	a = nowlength - ((double)N)*circlelen;

	if (a <= width*tan(angle))
	{
		ret = width*tan(angle) - a;
	}
	else	
	{
	    ret = circlelen - a + width*tan(angle);
	}
    ret = ret/circlelen;
	ret = ret * 360;
    return ret ;
   

}
