// WorkMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "WorkMonitorDlg.h"
#include "gep.h"
#include <math.h>
#include "mmsystem.h"
#include "CarControlParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




#define WIND_METHOD_CIRCLE     1
#define WIND_METHOD_ADDSAND    2
#define WIND_METHOD_CROSS      3

#define BOARD_AXE_FOR_CAR      1
#define BOARD_AXE_FOR_ENCODER  2

#define  MAIN_AXE_POS_DIR  ((unsigned short)(0x0002))
#define  MAIN_AXE_NEG_DIR  ((unsigned short)(0x0001))


#define  MAINAXE_FREQ_INVERT_N_CLOSE()  m_CurIOOut|=MAIN_AXE_NEG_DIR; GT_ExOpt(m_CurIOOut)
#define  MAINAXE_FREQ_INVERT_N_OPEN()   m_CurIOOut&=(~MAIN_AXE_NEG_DIR); GT_ExOpt(m_CurIOOut) 

#define  MAINAXE_FREQ_INVERT_P_CLOSE()  m_CurIOOut|=MAIN_AXE_POS_DIR; GT_ExOpt(m_CurIOOut)
#define  MAINAXE_FREQ_INVERT_P_OPEN()   m_CurIOOut&=(~MAIN_AXE_POS_DIR); GT_ExOpt(m_CurIOOut)


#define BUTTON_ADDSAND_BIT          (1<<5)
#define BUTTON_CIRCLEWIND_BIT       (1<<6)
#define BUTTON_CLEARPOSZERO_BIT     (1<<7)
#define BUTTON_AUTO_BIT             (1<<8)
#define BUTTON_MANUAL_BIT           (1<<9)
#define BUTTON_CARSPEEDDOWN_BIT    (1<<10)
#define BUTTON_CARSPEEDUP_BIT      (1<<11) 
#define BUTTON_CARNEGDIR_BIT       (1<<12)
#define BUTTON_CARPOSDIR_BIT       (1<<13) 
#define BUTTON_MAINNEGDIR_BIT      (1<<14)
#define BUTTON_MAINPOSDIR_BIT      (1<<15) 

#define PI_VALUE   (3.1415926535897)

extern CZhongTWindApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWorkMonitorDlg dialog


CWorkMonitorDlg::CWorkMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkMonitorDlg)
	m_WorkingOutHint = _T("");
	m_WorkingProgress1 = _T("");
	m_WorkingProgress2 = _T("");
	m_WorkingProgress3 = _T("");
	m_MainAxeSpeed = 0.0;
	m_MainAxePos = 0.0;
	m_MainAxeDir = _T("");
	m_CarPos = 0.0;
	m_CarSpeed = 0.0;
	m_CarDir = _T("");
	m_AlreadyWindNum = 0;
	m_PipeDiam = 0.0;
	m_BandageWidth = 0.0;
	m_StartPos = 0.0;
	m_EndPos = 0.0;
	m_StartStopAngle = 0.0;
	m_StopStopAngle = 0.0;
	m_WindNum = 0;
	m_CrossAngle = 0.0;
	m_WindStartLayer = 0;
	m_WindMethod = _T("");
	//}}AFX_DATA_INIT
}


void CWorkMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkMonitorDlg)
	DDX_Control(pDX, IDB_STARTWORK, m_BtnStartWork);
	DDX_Control(pDX, IDB_MEASURESTART, m_BtnMeasureStart);
	DDX_Control(pDX, IDB_INITIAL, m_BtnInitial);
	DDX_Text(pDX, IDE_WORKING_OUTPUT, m_WorkingOutHint);
	DDX_Text(pDX, IDE_WORKING_PROGRESS_1, m_WorkingProgress1);
	DDX_Text(pDX, IDE_WORKING_PROGRESS_2, m_WorkingProgress2);
	DDX_Text(pDX, IDE_WORKING_PROGRESS_3, m_WorkingProgress3);
	DDX_Text(pDX, IDE_MAINAXE_SPEED, m_MainAxeSpeed);
	DDX_Text(pDX, IDE_MAINAXE_POS, m_MainAxePos);
	DDX_Text(pDX, IDE_MAINAXE_DIR, m_MainAxeDir);
	DDX_Text(pDX, IDE_CAR_POS, m_CarPos);
	DDX_Text(pDX, IDE_CAR_SPEED, m_CarSpeed);
	DDX_Text(pDX, IDE_CAR_DIR, m_CarDir);
	DDX_Text(pDX, IDE_ALREADY_WINDNUM, m_AlreadyWindNum);
	DDX_Text(pDX, IDE_PIPE_DIAM, m_PipeDiam);
	DDX_Text(pDX, IDE_SHAPIAN_WIDTH, m_BandageWidth);
	DDX_Text(pDX, IDE_START_POS, m_StartPos);
	DDX_Text(pDX, IDE_END_POS, m_EndPos);
	DDX_Text(pDX, IDE_START_STOPANGLE, m_StartStopAngle);
	DDX_Text(pDX, IDE_END_STOPANGLE, m_StopStopAngle);
	DDX_Text(pDX, IDE_WIND_NUM, m_WindNum);
	DDX_Text(pDX, IDE_CROSS_ANGLE, m_CrossAngle);
	DDX_Text(pDX, IDE_PUCENG_START, m_WindStartLayer);
	DDX_Text(pDX, IDE_WINDMETHOD, m_WindMethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CWorkMonitorDlg)
	ON_BN_CLICKED(IDB_INITIAL, OnInitial)
	ON_BN_CLICKED(IDB_SET_ZEROPOT, OnSetZeropot)
	ON_BN_CLICKED(IDB_MEASURESTART, OnMeasurestart)
	ON_BN_CLICKED(IDB_STOP, OnStop)
	ON_BN_CLICKED(IDB_SUDDEN_STOP, OnSuddenStop)
	ON_MESSAGE(WM_THREAD_BUTTON_CHANGE,OnButtonChanged)
	ON_MESSAGE(WM_MMTIMER_MEASURE_SPEED, OnMMTimerMeasureSpeed)
	ON_BN_CLICKED(IDB_STARTWORK, OnStartwork)
	ON_MESSAGE(WM_THREAD_POS_UPDATE,OnUpdateCarPos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkMonitorDlg message handlers

BOOL CWorkMonitorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ShowWindow(SW_MAXIMIZE);
    LoadTask(0);

	m_MainAxeDir     = "<<+>>";
	m_MainAxePos     = 0;
	m_MainAxeSpeed   = 0;
	
	m_CarDir         = "<<+>>";
    m_CarPos         = 0;
	m_AlreadyWindNum = 0;
	m_WindStartLayer  = 1;
    UpdateData(false);

   

	m_QueryThreadRunningFlag = 0;
	m_queryThread = AfxBeginThread(QueryPressButton, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
    m_QueryThreadRunningFlag = 1;

    m_CurIOOut = 0xFFFF;
    GT_ExOpt(m_CurIOOut);
    unsigned short intCheck;	
	GT_ExInpt(&intCheck);
    
    ButtonProcess(intCheck);
    m_queryThread->ResumeThread();
	
	m_CarCurSpeed = 0;
    m_CurrTaskIndex= 0;
    m_CurCarMoveDir = 1;


	m_iMeasureInterval = 100; //0.1ms
	m_iUpdateInterval  = 200; //0.2ms
    m_iUpdateCount = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWorkMonitorDlg::LoadTask(int TaskIndex)
{
     m_PipeDiam       = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_PipeDiam;
	 m_BandageWidth   = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_shaWidth;
	 m_StartPos       = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_StartPos;
	 m_EndPos         = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_EndPos;
     m_StartStopAngle = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_StartStopAngle;
	 m_StopStopAngle  = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_EndStopAngle;
	 m_WindNum        = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_LayerNum;
	 m_CrossAngle     = m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_crossAngle;
	 
	 if (m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_WindMethod==WIND_METHOD_CIRCLE)
	 {
		 m_WindMethod = L"����";		 
	 }
	 else if (m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_WindMethod==WIND_METHOD_ADDSAND)
	 {
		 m_WindMethod = L"��ɰ";
		 //m_BandageWidth = m_lpWorkPlanDlg->m_WindTask[TaskIndex].wi
	 }
	 else if (m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_WindMethod==WIND_METHOD_CROSS)
	 {
		 m_WindMethod = L"����";
	 }
	 UpdateData(false);
}

void CWorkMonitorDlg::OnInitial() 
{
	// TODO: Add your control notification handler code here
	short rtn;
    rtn=GT_StepDir(BOARD_AXE_FOR_CAR);//������������巽���ź�
	//rtn=GT_StepPulse(BOARD_AXE_FOR_CAR); //������������������ź�
	Ges_error(rtn);
	rtn=GT_AxisOn(BOARD_AXE_FOR_CAR); //����ʹ��
	Ges_error(rtn);
	rtn=GT_ClrSts(BOARD_AXE_FOR_CAR); //������״̬�Ĵ�����λ
	Ges_error(rtn);
		
}

void CWorkMonitorDlg::Ges_error(short rtn)
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

void CWorkMonitorDlg::OnSetZeropot() 
{
	// TODO: Add your control notification handler code here
	
}

void CWorkMonitorDlg::ButtonProcess(unsigned short buttonStatus)
{
	UINT AndTemp1; 
	UINT AndTemp2; 
	if (buttonStatus&BUTTON_CLEARPOSZERO_BIT==0)  //���㰴ť
	{
		MessageBox(L"�궨���");
		m_CarPos = 0;
		m_WorkingOutHint = L"�궨���ɹ�!!!";
		GT_ZeroPos(BOARD_AXE_FOR_CAR); //������ʵ��λ�ú�Ŀ��λ������
		//get_encoder(2,&m_iniCarEncoderVal);
	}
	
	
	AndTemp1     = buttonStatus&BUTTON_CARNEGDIR_BIT;
	AndTemp2     = buttonStatus&BUTTON_CARPOSDIR_BIT;
	
	if ((AndTemp1)&&(AndTemp2))   //3���м�
	{
        ;
	}
	else if((AndTemp1)&&(AndTemp2==0))//С�����򱻰���
	{
		m_CarDir         = ">>>>>>>";
		m_CurCarMoveDir = 1;
	}
	else if ((AndTemp1==0)&&(AndTemp2))//С�����򱻰���
	{
		m_CarDir         = "<<<<<<<";
		m_CurCarMoveDir = -1;
	} 
	else
	{
		MessageBox(_T("С������ť����!"));
	}




	AndTemp1     = buttonStatus&BUTTON_MAINNEGDIR_BIT;
	AndTemp2     = buttonStatus&BUTTON_MAINPOSDIR_BIT;

	if ((AndTemp1)&&(AndTemp2))   //3���м�
	{
		MAINAXE_FREQ_INVERT_N_CLOSE();
		MAINAXE_FREQ_INVERT_P_CLOSE();
	}
	else if((AndTemp1)&&(AndTemp2==0))//�������򱻰���
	{
		m_MainAxeDir         = ">>>>>>>";
		MAINAXE_FREQ_INVERT_N_CLOSE();
		MAINAXE_FREQ_INVERT_P_OPEN();
	}
	else if ((AndTemp1==0)&&(AndTemp2))//���ᷴ�򱻰���
	{
		m_MainAxeDir         = "<<<<<<<";
		MAINAXE_FREQ_INVERT_P_CLOSE();
		MAINAXE_FREQ_INVERT_N_OPEN();
	} 
	else
	{
		MessageBox(_T("���᷽��ť����!"));
	}



	
	AndTemp1     = buttonStatus&BUTTON_ADDSAND_BIT;
	AndTemp2     = buttonStatus&BUTTON_CIRCLEWIND_BIT;
	
	if ((AndTemp1)&&(AndTemp2))   //3���м�
	{
		;
	}
	else if((AndTemp1)&&(AndTemp2==0))//
	{
		;
	}
	else if ((AndTemp1==0)&&(AndTemp2))//
	{
		;
	} 
	else
	{
		MessageBox(_T("��ɳ����ť����!"));
	}
	


	
	AndTemp1     = buttonStatus&BUTTON_AUTO_BIT;
	AndTemp2     = buttonStatus&BUTTON_MANUAL_BIT;
	
	if ((AndTemp1)&&(AndTemp2))   //3���м�
	{
		;
	}
	else if((AndTemp1)&&(AndTemp2==0))//�Զ�������
	{
		;
	}
	else if ((AndTemp1==0)&&(AndTemp2))//�ֶ�������
	{
		;
	} 
	else
	{
		MessageBox(_T("�Զ��ֶ���ť����!"));
	}
	
	
	 UpdateData(false);
}


UINT QueryPressButton(LPVOID pParam)   /// �̺߳���
{   
    CWorkMonitorDlg* workingDlg = (CWorkMonitorDlg*)pParam;
    unsigned short intCheck;
	unsigned short LastIntCheck;

	LastIntCheck = 0;
	intCheck = 0;
	int firstflag=0;

    long pos;
	CString  pos_str;
	while (workingDlg->m_QueryThreadRunningFlag==1)
    {
		GT_ExInpt(&intCheck);

		if (LastIntCheck!=intCheck)
		{
			if (firstflag!=0)
			{
				SendMessage(workingDlg->GetSafeHwnd(),WM_THREAD_BUTTON_CHANGE,((UINT)LastIntCheck)&0x0000FFFF,((UINT)intCheck)&0x0000FFFF);
			}		   
			firstflag = 1;
		}
		LastIntCheck = intCheck;

		//get_abs_pos(1,&pos);
		GT_GetAtlPos(1,&pos); 
		SendMessage(workingDlg->GetSafeHwnd(),WM_THREAD_POS_UPDATE,(WPARAM)(&pos),(LPARAM)(&pos));
		Sleep(200);
    }
	//ExitThread(0);
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

    if (changed&BUTTON_CLEARPOSZERO_BIT)
    {
		AndTemp1 = thisButton&BUTTON_CLEARPOSZERO_BIT;
		if (AndTemp1) //��ť�ǰ��º���
		{
			m_CarPos = 0;
			m_WorkingOutHint = L"�궨���ɹ�";
		    GT_ZeroPos(BOARD_AXE_FOR_CAR);
			GT_SetAtlPos(BOARD_AXE_FOR_CAR,0);
		}
		else
		{
            ;
		}
    }
////////////////////////////////////////////С���Ӽ���3�� ��ť///////////////////////////////////////////////
	if ((changed&BUTTON_CARSPEEDUP_BIT)||(changed&BUTTON_CARSPEEDDOWN_BIT))
    {
		AndTemp1     = thisButton&BUTTON_CARSPEEDUP_BIT;
        AndTemp2     = thisButton&BUTTON_CARSPEEDDOWN_BIT;
		AndTempLast1 = lastButton&BUTTON_CARSPEEDUP_BIT;
        AndTempLast2 = lastButton&BUTTON_CARSPEEDDOWN_BIT;
		UINT andtemp11,andtemp12;
		andtemp11     = thisButton&BUTTON_CARNEGDIR_BIT;
		andtemp12     = thisButton&BUTTON_CARPOSDIR_BIT;
		if ((AndTemp1)&&(AndTemp2))   //3���м�
		{
			KillTimer(7);			  
		}
		else if((AndTemp1)&&(AndTemp2==0))//С������
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				SetTimer(7,500,0);
				m_flagTimerSpeed = 1;
				unsigned long checkstatus;
				GT_GetSts(BOARD_AXE_FOR_CAR,&checkstatus); //
                checkstatus = checkstatus&(0x0001<<10);    //Bit10 
                if (checkstatus==0)
                {						
					GT_PrflV(1); //�����ٶ�ģʽ
                    GT_SetVel(1,theApp.GlobalParam.m_fAcceleration); //��һ����Ժ���
                    GT_SetAcc(1,theApp.GlobalParam.m_fAccelerationFactor);
					//set_profile(1,100,theApp.GlobalParam.m_fAcceleration,); //m_fAcceleration = 8000
					m_CarCurSpeed = theApp.GlobalParam.m_fAcceleration;
					if (andtemp12==0)//ȷ��һ���߼�
					{   //����ť����
						GT_SetVel(1,theApp.GlobalParam.m_fAcceleration);
					}
					else
					{
                        GT_SetVel(1,-1.0*theApp.GlobalParam.m_fAcceleration);
					}
                    GT_Update(1);
                }
				else
				{
					m_CarCurSpeed += theApp.GlobalParam.m_fAcceleration;
					if (m_CarCurSpeed>160000)
					{
						m_CarCurSpeed = 160000;
					}
					else
					{
                       //change_speed(1,m_CarCurSpeed);
					   GT_SetVel(1,m_CarCurSpeed);
					   GT_Update(1);
					}
					
				}
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//С��С������
		{
			if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				SetTimer(7,500,0);
				m_flagTimerSpeed = 2;
                unsigned long checkstatus;
				GT_GetSts(BOARD_AXE_FOR_CAR,&checkstatus); //
                checkstatus = checkstatus&(0x0001<<10);    //Bit10 
                if (checkstatus!=0)//�Ѿ���ֹ�ˣ�ʲôҲ������
                {					
                    ;
                }
				else
				{
					m_CarCurSpeed -= theApp.GlobalParam.m_fAcceleration;
					if (m_CarCurSpeed<=0)
					{
						m_CarCurSpeed = 0;
						GT_SmthStp(1);
						//GT_AbptStp(1);  //��ͣ
					}
					else
					{
                      GT_SetVel(1,m_CarCurSpeed);
                      GT_Update(1);
					}
					
				}
            }
		} 
		else
		{
			MessageBox(_T("���ٰ�ť����!"));
		}
    }
/////////////////////////////////////////С���Ӽ���3�� ��ť/////////////////////////////////////////////


////////////////////////////////////////////С��������3�� ��ť///////////////////////////////////////////////
	if ((changed&BUTTON_CARNEGDIR_BIT)||(changed&BUTTON_CARPOSDIR_BIT))
    {
		AndTemp1     = thisButton&BUTTON_CARNEGDIR_BIT;
        AndTemp2     = thisButton&BUTTON_CARPOSDIR_BIT;
		AndTempLast1 = lastButton&BUTTON_CARNEGDIR_BIT;
        AndTempLast2 = lastButton&BUTTON_CARPOSDIR_BIT;
		if ((AndTemp1)&&(AndTemp2))   //3���м�
		{
            if ((AndTempLast1)&&(AndTempLast2==0))//ԭ�����򱻰���
            {
				m_CarDir = "<<<+>>>";		
				//set_profile(1,100,theApp.GlobalParam.m_fAcceleration/2,theApp.GlobalParam.m_fAccelerationFactor);  //4000 500000
				//GT_SetVel(1,m_CarCurSpeed);
				GT_SetAcc(1,theApp.GlobalParam.m_fAccelerationFactor);
				GT_Update(1);
				GT_SmthStp(1); ///��ͣ
				m_CarCurSpeed =0;
				//MessageBox("С�������λ");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//ԭ�ȷ��򱻰���
			{
				m_CarDir = "<<<+>>>";
				//set_profile(1,100,theApp.GlobalParam.m_fAcceleration/2,theApp.GlobalParam.m_fAccelerationFactor); 
				GT_SetAcc(1,theApp.GlobalParam.m_fAccelerationFactor);
				GT_Update(1);
				GT_SmthStp(1); ///��ͣ
				m_CarCurSpeed =0;
				//MessageBox("С�������λ");
			}
		}
		else if((AndTemp1)&&(AndTemp2==0))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				//MessageBox("С������");
				m_CarDir = ">>>>>>>";
                m_CurCarMoveDir = 1;
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				//MessageBox("С������");
				m_CurCarMoveDir = -1;
				m_CarDir = "<<<<<<<";
            }
		} 
		else
		{
			MessageBox(_T("С������ť����!"));
		}
    }
/////////////////////////////////////////С��������3�� ��ť/////////////////////////////////////////////





////////////////////////////////////////////����������3�� ��ť//////////////////////////////////////////
	if ((changed&BUTTON_MAINNEGDIR_BIT)||(changed&BUTTON_MAINPOSDIR_BIT))
    {
		AndTemp1     = thisButton&BUTTON_MAINNEGDIR_BIT;
        AndTemp2     = thisButton&BUTTON_MAINPOSDIR_BIT;
		AndTempLast1 = lastButton&BUTTON_MAINNEGDIR_BIT;
        AndTempLast2 = lastButton&BUTTON_MAINPOSDIR_BIT;

		if ((AndTemp1)&&(AndTemp2))   //3���м�
		{

            if ((AndTempLast1)&&(AndTempLast2==0))//ԭ�����򱻰���
            {
				MAINAXE_FREQ_INVERT_N_CLOSE();
                MAINAXE_FREQ_INVERT_P_CLOSE();
				m_MainAxeDir = "<<<+>>>";
				//MessageBox("���������λ");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//ԭ�ȷ��򱻰���
			{
				MAINAXE_FREQ_INVERT_N_CLOSE();
                MAINAXE_FREQ_INVERT_P_CLOSE();
				m_MainAxeDir = "<<<+>>>";
				//MessageBox("���ᷴ���λ");
			}
		}

		else if((AndTemp1)&&(AndTemp2==0))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				MAINAXE_FREQ_INVERT_N_CLOSE();
                MAINAXE_FREQ_INVERT_P_OPEN();
				m_MainAxeDir = ">>>>>>>";
				//MessageBox("��������");
            }
			
			else if ((AndTempLast1==0)&&(AndTempLast2))//ԭ�ȷ��򱻰���
			{
				MAINAXE_FREQ_INVERT_N_CLOSE();
                MAINAXE_FREQ_INVERT_P_OPEN();
				//MessageBox("16");
				m_MainAxeDir = ">>>>>>>";
			}
		}
		else if ((AndTemp1==0)&&(AndTemp2))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				MAINAXE_FREQ_INVERT_P_CLOSE();
				MAINAXE_FREQ_INVERT_N_OPEN();
                
				//MessageBox("���ᷴ��");
				//outport_byte(1,16);
				m_MainAxeDir = "<<<<<<<";
            }
		} 
		else
		{
			MessageBox(_T("���᷽��ť����!"));
		}
    }
/////////////////////////////////////////����������3�� ��ť/////////////////////////////////////////////
////////////////////////////////////////////�ֶ��Զ�3�� ��ť////////////////////////////////////////////
	if ((changed&BUTTON_AUTO_BIT)||(changed&BUTTON_MANUAL_BIT))
    {
		AndTemp1     = thisButton&BUTTON_AUTO_BIT;
        AndTemp2     = thisButton&BUTTON_MANUAL_BIT;
		AndTempLast1 = lastButton&BUTTON_AUTO_BIT;
        AndTempLast2 = lastButton&BUTTON_MANUAL_BIT;

		if ((AndTemp1)&&(AndTemp2))   //3���м�
		{

            if ((AndTempLast1)&&(AndTempLast2==0))//ԭ�����򱻰���
            {
				MessageBox(L"�Զ���λ");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//ԭ�ȷ��򱻰���
			{
				MessageBox(L"�ֶ���λ");
			}
		}
		else if((AndTemp1)&&(AndTemp2==0))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
		        ;
				MessageBox(L"�Զ�");
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				MessageBox(L"�ֶ�");
            }
		} 
		else
		{
			MessageBox(_T("�Զ��ֶ���ť����!"));
		}
    }
/////////////////////////////////////////�ֶ��Զ�3�� ��ť/////////////////////////////////////////////
////////////////////////////////////////////�����ɳ��ť//////////////////////////////////////////////
	if ((changed&BUTTON_ADDSAND_BIT)||(changed&BUTTON_CIRCLEWIND_BIT))
    {
		AndTemp1     = thisButton&BUTTON_ADDSAND_BIT;
        AndTemp2     = thisButton&BUTTON_CIRCLEWIND_BIT;
		AndTempLast1 = lastButton&BUTTON_ADDSAND_BIT;
        AndTempLast2 = lastButton&BUTTON_CIRCLEWIND_BIT;
		
		if ((AndTemp1)&&(AndTemp2))   //3���м�
		{
			
            if ((AndTempLast1)&&(AndTempLast2==0))//ԭ�����򱻰���
            {
				MessageBox(L"��ɳ��λ");
            }
			else if ((AndTempLast1==0)&&(AndTempLast2))//ԭ�ȷ��򱻰���
			{
				MessageBox(L"�����λ");
			}
		}
		else if((AndTemp1)&&(AndTemp2==0))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				;
				MessageBox(L"��ɳ");
            }
		}
		else if ((AndTemp1==0)&&(AndTemp2))//С�����򱻰���
		{
            if ((AndTempLast1)&&(AndTempLast2))//ԭ�����м�
            {
				MessageBox(L"����");
            }
		} 
		else
		{
			MessageBox(_T("�����ɳ��ť����!"));
		}
    }
///////////////////////////////////////////�����ɳ��ť///////////////////////////////////////////////
    UpdateData(false);
    return 0;
}

void CWorkMonitorDlg::OnMeasurestart() 
{
	// TODO: Add your control notification handler code here
	GT_EncSns(0x0000); //�������������ȡ��
	GT_EncOn(BOARD_AXE_FOR_ENCODER);
	GT_EncOn(BOARD_AXE_FOR_CAR);
    //GT_GetAtlPos
  
    if (CreateTimer()==true)
	{
		MessageBox(L"MMTimer Set OK!");
		m_iLastEncoderValueMainAxe = 0;
		m_iThisEncoderValueMainAxe = 0;
		m_iUpdateCount = 0;
		
		m_BtnMeasureStart.EnableWindow(false);
	}

}



void  PASCAL MeasureMainAxeSpeedWork(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	CWorkMonitorDlg* localThisdlg = (CWorkMonitorDlg *)dwUser;
	
	localThisdlg->m_iUpdateCount++;
    localThisdlg->m_iLastEncoderValueMainAxe = localThisdlg->m_iThisEncoderValueMainAxe;
	// localThisdlg->m_2LastEncoderValue = localThisdlg->m_2ThisEncoderValue;
	//	get_encoder(2,&(localThisdlg->m_2ThisEncoderValue));
	GT_GetAtlPos(2,&(localThisdlg->m_iThisEncoderValueMainAxe)); 
	
	localThisdlg->m_MainAxeDeltaEncoderCount[localThisdlg->m_iUpdateCount-1] = 
		localThisdlg->m_iThisEncoderValueMainAxe - localThisdlg->m_iLastEncoderValueMainAxe;
	
	//	tempDelta = (double)(localThisdlg->m_2ThisEncoderValue - localThisdlg->m_2LastEncoderValue);
	//    localThisdlg->m_TickEncoderDelta = localThisdlg->myAbs(tempDelta);
	
	
	
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

LRESULT CWorkMonitorDlg::OnMMTimerMeasureSpeed(WPARAM wparam, LPARAM lparam)
{
	CString showStr;
	double tempdouble;
	double MainAxeEncoder_resolution;
	double MainAxeRatio;
	double RealV;

    MainAxeEncoder_resolution = (double)(theApp.GlobalParam.m_iMainAxePulses);
	if (m_iThisEncoderValueMainAxe<0)
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
	
	
	
	// ��������ֵ����ʱ�䣬ʱ�䵥λ�Ǻ��룬���Գ���1000���������ֱ�����2000�����Գ���2000 �õ�ת��
	tempdouble = ((double)(m_iThisEncoderValueMainAxe - m_iLastEncoderValueMainAxe))*1000/
		((double)m_iMeasureInterval*MainAxeEncoder_resolution);
	showStr.Format(L"%.5f",tempdouble);
	
	MainAxeRatio = this->m_lpWorkPlanDlg->m_WindTask[m_CurrTaskIndex].m_MainAxeSpeedFactor;
    this->m_MainAxeSpeed = tempdouble*60/MainAxeRatio; //�õ�ÿ���Ӷ���ת
    
	RealV = (double)(m_iThisEncoderValueMainAxe - m_iLastEncoderValueMainAxe)*(PI_VALUE)*(m_lpWorkPlanDlg->m_WindTask[m_CurrTaskIndex].m_PipeDiam)*1000/
		(((double)m_iMeasureInterval)*MainAxeEncoder_resolution*MainAxeRatio);
    RealV = ((double)(MeanDelta))*(PI_VALUE)*(this->m_lpWorkPlanDlg->m_WindTask[m_CurrTaskIndex].m_PipeDiam)*1000/
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

void CWorkMonitorDlg::OnStop() 
{
    this->m_WindProcessRunningFlag = 0;
    GT_SmthStp(1);
	//GT_AbptStp(1);  //��ͣ
}

void CWorkMonitorDlg::OnSuddenStop() 
{
  GT_AbptStp(1);	
  long pos;
  GT_GetAtlPos(1,&pos); 
  GT_PrflT(1);//���������˶�
  GT_SetPos(1,0-pos); //����Ŀ��λ��
  GT_SetVel(1,5000);
  GT_SetAcc(1,5000);
  GT_Update(1);
}

void CWorkMonitorDlg::OnStartwork() 
{
	// TODO: Add your control notification handler code here
	if (myAbs(m_CarPos)<0.0001)
    {
		m_BtnStartWork.EnableWindow(false);
		m_WindProcThread = AfxBeginThread(WindingProcessThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
		this->m_WindProcessRunningFlag = 1;
		m_WindProcThread->ResumeThread();
    }
    else
	{
		MessageBox(L"���ȹ���");
	}

}

double CWorkMonitorDlg::myAbs(double a)
{
	double ret;
	ret = a * a;
	ret = sqrt(ret);
    return ret;
}



LRESULT CWorkMonitorDlg::OnUpdateCarPos(WPARAM wparam, LPARAM lparam)
{
	double Car_RoundRatio;
	double Car_DistancePerRound;
	double Car_CyclePulse;
	long *temp;
	double pos;
	
	Car_RoundRatio = theApp.GlobalParam.m_fCarSpeedDownP;  //m_fCarSpeedDownP;
	Car_DistancePerRound = theApp.GlobalParam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(theApp.GlobalParam.m_iCarPulses);	
	

	temp = (long *)wparam; 
	pos = (  double )(*temp); 
	
	m_CarPos = (pos*Car_DistancePerRound)/(Car_RoundRatio*Car_CyclePulse);
	
	UpdateData(false);
    
	return 0;
}



UINT WindingProcessThread(LPVOID pParam) 
{
	   CWorkMonitorDlg* workingDlg = (CWorkMonitorDlg*)pParam;
	   CCarControlParam CarParam,CarNewParam;
	   
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
	   
	   TaskIndex = workingDlg->m_CurrTaskIndex;
	   N = workingDlg->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_LayerNum;
	   
	   workingDlg->ComputeCarMoveParam(TaskIndex,&CarParam);
	   
	   EncoderResolution = theApp.GlobalParam.m_iMainAxePulses;
	   qitingjiao = workingDlg->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_StartStopAngle;
	   MainAxeSpeed = workingDlg->m_MainAxeRealV;
	   
	   buffLen = workingDlg->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_BuffLen;
	   TotalLen = workingDlg->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_EndPos - workingDlg->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_StartPos;
	   StopPos = workingDlg->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_EndPos;
	   startpos = workingDlg->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_StartPos;
	   
	   int ret ;
	   
	   runningflag = 1;
	   ret = -1;
	   for (i =TaskIndex;i< workingDlg->m_lpWorkPlanDlg->m_ListReportNum;i++)
	   {
		   if (workingDlg->m_lpWorkPlanDlg->m_WindTask[i].m_WindMethod == WIND_METHOD_CIRCLE)
		   {
			   ret = workingDlg->CircleWindProcess(i,&(workingDlg->m_WindProcessRunningFlag));
		   }
		   else if (workingDlg->m_lpWorkPlanDlg->m_WindTask[i].m_WindMethod == WIND_METHOD_CROSS)
		   {   //CrossWindProcess
			   ret = workingDlg->CrossWindProcessq(i,&(workingDlg->m_WindProcessRunningFlag));
			   //ret = workingDlg->CrossWindProcess(i,&(workingDlg->m_WindProcessRunningFlag));
		   }
		   
		   if ( ret == 0)
		   {
			   workingDlg->m_BtnStartWork.EnableWindow(TRUE);
			   return 0;
		   }
		   else if (ret == 1)
		   {
			   ret = -1;
		   }
	   }
	   
	   //workingDlg->CrossWindProcess(TaskIndex,&(workingDlg->m_WindProcessRunningFlag));
	   workingDlg->m_BtnStartWork.EnableWindow(TRUE);
    	return 0;
}

void CWorkMonitorDlg::ComputeCarMoveParam(int index, CCarControlParam *lpparam)
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
	Angle = this->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_crossAngle;
	Angle = Angle*PI_VALUE/180;
	
	Car_RoundRatio = theApp.GlobalParam.m_fCarSpeedDownP;
	Car_DistancePerRound = theApp.GlobalParam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)( theApp.GlobalParam.m_iCarPulses );
	
    Car_ObjSpeed = MainAxeSpeed/tan(Angle);
	
    V0 = 100*Car_DistancePerRound/(Car_RoundRatio*Car_CyclePulse);
	
	buffLen = this->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_BuffLen;
	
    Car_ObjSpeed = Car_ObjSpeed/1000.0;   ///   -> mm/ms

    Car_a = (Car_ObjSpeed*Car_ObjSpeed - V0*V0)/(2*buffLen);  //��λ���Ǻ���
    
	Car_a = (Car_ObjSpeed*Car_ObjSpeed - 0*0)/(2*buffLen);  //��λ���Ǻ���
    


	Car_a = (Car_a/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
	Car_ObjSpeed = (Car_ObjSpeed/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
	
	
    lpparam->m_a = Car_a;
    lpparam->m_ObjSpeed = Car_ObjSpeed; 

}

int CWorkMonitorDlg::CircleWindProcess(int index, int *runningflag)
{
	int iWindLayerNum;
	CCarControlParam CarParam,CarNewParam;
	double Car_a;
	double Car_ObjSpeed;
	long Car_CurPos;
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
    long distanceStartPos;
	
	iWindLayerNum = this->m_lpWorkPlanDlg->m_WindTask[index].m_LayerNum;////
	ComputeCarMoveParam(index,&CarParam);
	mainAxeRatio = this->m_lpWorkPlanDlg->m_WindTask[index].m_MainAxeSpeedFactor;
	EncoderResolution = theApp.GlobalParam.m_iMainAxePulses;
	MainAxeSpeed = this->m_MainAxeRealV;  //�����ٶ�
	TaskIndex = index;   
	Car_RoundRatio = theApp.GlobalParam.m_fCarSpeedDownP;
	Car_DistancePerRound = theApp.GlobalParam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(theApp.GlobalParam.m_iCarPulses);	
	
	buffLen = this->m_lpWorkPlanDlg->m_WindTask[index].m_BuffLen;//���峤��
	TotalLen = this->m_lpWorkPlanDlg->m_WindTask[index].m_EndPos - 
		this->m_lpWorkPlanDlg->m_WindTask[index].m_StartPos;  //����ȥ�յ�

	
	if (TotalLen>0)
	{
		Car_dir = 1;
	}
	else	
	{
		Car_dir = -1;
	}


	StopPos = this->m_lpWorkPlanDlg->m_WindTask[index].m_EndPos;   //�յ�
	startpos =this->m_lpWorkPlanDlg->m_WindTask[index].m_StartPos; //���
	
	
	for (i = 0;i<iWindLayerNum;i++)
	{
		GT_GetAtlPos(1,&Car_CurPos); 
		distanceStartPos = (startpos/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
		
		GT_PrflT(1);//���������˶�
		GT_SetPos(1,distanceStartPos - Car_CurPos); //����Ŀ��λ��
		GT_SetVel(1,5000);
		GT_SetAcc(1,5000);
        GT_Update(1);
//		unsigned long checkstatus;
//		GT_GetSts(BOARD_AXE_FOR_CAR,&checkstatus); //
//		checkstatus = checkstatus&(0x0001<<10);    //Bit10 
		while (check_done(BOARD_AXE_FOR_CAR)!=0)
		{
            Sleep(100); 
		}
		
		this->ComputeCarMoveParam(index,&CarParam);
		Car_a = CarParam.m_a;
		Car_ObjSpeed = CarParam.m_ObjSpeed;
		
		GT_PrflT(1);//���������˶�		
		GT_SetVel(1,Car_ObjSpeed);
		GT_SetAcc(1,Car_a);        
        distanceStartPos = ((StopPos - startpos)/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
        //GT_SetPos(1,distanceStartPos - Car_CurPos); //����Ŀ��λ��
        GT_SetPos(1,distanceStartPos);
		GT_Update(1);

		while((check_done(BOARD_AXE_FOR_CAR)!=0)&&(*runningflag))
		{
			this->ComputeCarMoveParam(index,&CarNewParam);
			if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>(0.08*this->myAbs(CarParam.m_ObjSpeed))) //�仯������05%�ͱ���
			{
				CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				CarParam.m_a = CarNewParam.m_a;
				GT_SetVel(1,CarParam.m_ObjSpeed);
				GT_SetAcc(1,CarParam.m_a);        
	        	GT_Update(1);
			}
			Sleep(100);
		}
		if ((*runningflag)==0)
		{
			return 0;
		}
        GT_AbptStp(1);
		
	}
	
    return 1;

}

int CWorkMonitorDlg::CrossWindProcessq(int index, int *runningflag)
{

	int iWindLayerNum;
	CCarControlParam CarParam,CarNewParam;
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
 
    CString debugOutstr;
    double temp_CurSpeed;

	TaskIndex = index;
	iWindLayerNum = this->m_lpWorkPlanDlg->m_WindTask[index].m_LayerNum;
	ComputeCarMoveParam(index,&CarParam);
	EncoderResolution = theApp.GlobalParam.m_iMainAxePulses;   //����������ֱ���

	MainAxeRatio = this->m_lpWorkPlanDlg->m_WindTask[index].m_MainAxeSpeedFactor;
	qitingjiao = this->m_lpWorkPlanDlg->m_WindTask[TaskIndex].m_StartStopAngle;     // ��ͣ��
	MainAxeSpeed = this->m_MainAxeRealV;  //�����ٶ�	   
    
	MainAxeCircleLen = this->m_lpWorkPlanDlg->m_WindTask[index].m_PipeDiam*PI_VALUE;
	Car_RoundRatio = theApp.GlobalParam.m_fCarSpeedDownP;
	Car_DistancePerRound = theApp.GlobalParam.m_fCarDistancePerRound;
	Car_CyclePulse = (double)(theApp.GlobalParam.m_iCarPulses);	
	   
	buffLen  = this->m_lpWorkPlanDlg->m_WindTask[index].m_BuffLen;//���峤��
	TotalLen = this->m_lpWorkPlanDlg->m_WindTask[index].m_EndPos -  
	                           this->m_lpWorkPlanDlg->m_WindTask[index].m_StartPos;  //����ȥ�յ�
	if (TotalLen>0)
	{
	  Car_dir = 1;
	}
	else	
	{
	  Car_dir = -1;
	}

	StopPos = this->m_lpWorkPlanDlg->m_WindTask[index].m_EndPos;   //�յ�
	startpos = this->m_lpWorkPlanDlg->m_WindTask[index].m_StartPos; //���
	 
	MainAxePos_Y = 0;
	
	this->ComputeCarMoveParam(TaskIndex,&CarParam);
	Car_a = CarParam.m_a;
	Car_ObjSpeed = CarParam.m_ObjSpeed;


	GT_PrflT(1);//���������˶�
//	GT_SetPos(1,distanceStartPos - Car_CurPos); //����Ŀ��λ��
	GT_SetVel(1,Car_ObjSpeed);
	GT_SetAcc(1,Car_a);
    
    GT_GetAtlPos(2,&StartPosEncoder); 
	lastEncoderV = StartPosEncoder;

    for (i = 0;i<iWindLayerNum;i++)
	{
		/*
		get_abs_pos(1,&Car_CurPos);
		distanceStartPos = (startpos/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
		fast_pmove(1,distanceStartPos - Car_CurPos);  //�����
        while(check_done(1))
		{
			Sleep(100); 
		}
		*/
        distanceStartPos = ((StopPos - startpos)/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;
       // get_abs_pos(1,&Car_CurPos);
	   //double curTorch = Car_CurPos;

		GT_SetPos(1,distanceStartPos); //����Ŀ��λ��
        GT_Update(1);
		//fast_pmove(1,distanceStartPos );
	
		int monitorFlag = 0;
		while((check_done(BOARD_AXE_FOR_CAR))&&(*runningflag))
		{
			this->ComputeCarMoveParam(TaskIndex,&CarNewParam);
			if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.1*this->myAbs(CarParam.m_ObjSpeed)) //�仯������10%�ͱ���
			{
				/*
				CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				CarParam.m_a = CarNewParam.m_a;
				GT_SetVel(1,CarParam.m_ObjSpeed);
            	GT_SetAcc(1,CarParam.m_a);
				GT_Update(1);
				*/
			}

			Sleep(10);

			GT_GetAtlPos(2,&midPosEncoder);  //get_encoder(1,&midPosEncoder);
            
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
		GT_GetAtlPos(2,&iniMainAxeEncoder); //get_encoder(1,&iniMainAxeEncoder); 
		double ObjdeltaEncoder  =  (qitingjiao)*EncoderResolution*(this->m_lpWorkPlanDlg->m_WindTask[index].m_MainAxeSpeedFactor)/(360);
		 ObjdeltaEncoder  =  (360)*EncoderResolution*(this->m_lpWorkPlanDlg->m_WindTask[index].m_MainAxeSpeedFactor)/(360);
		while((angleflag)&&((*runningflag))) //�ȴ���ͣ��
		{
			//Sleep(1);
			GT_GetAtlPos(2,&CurMainAxeEncoder); //get_encoder(1,&CurMainAxeEncoder); 

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

		this->ComputeCarMoveParam(TaskIndex,&CarNewParam);
		CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
		CarParam.m_a = CarNewParam.m_a;
		GT_PrflT(1);//���������˶�
		GT_SetVel(1,CarParam.m_ObjSpeed);
        GT_SetAcc(1,CarParam.m_a);
		//	GT_SetPos(1,distanceStartPos - Car_CurPos); //����Ŀ��λ��
        distanceStartPos = ((startpos - StopPos)/Car_DistancePerRound)*Car_RoundRatio*Car_CyclePulse;


        long cartemp;
        GT_GetAtlPos(1,&cartemp);  //		get_abs_pos(1,&Car_CurPos);
        Car_CurPos = (double)cartemp;
		GT_SetPos(1,distanceStartPos); //����Ŀ��λ��
        GT_Update(1);

        //fast_pmove(1,distanceStartPos);
        while((check_done(BOARD_AXE_FOR_CAR))&&(*runningflag))
		{
			this->ComputeCarMoveParam(TaskIndex,&CarNewParam);
			if (this->myAbs(CarNewParam.m_ObjSpeed - CarParam.m_ObjSpeed)>0.1*this->myAbs(CarParam.m_ObjSpeed)) //�仯������10%�ͱ���
			{
				/*
				CarParam.m_ObjSpeed = CarNewParam.m_ObjSpeed;
				CarParam.m_a = CarNewParam.m_a;
				set_profile(1,0,CarParam.m_ObjSpeed,Car_a);
				change_speed(1,CarParam.m_ObjSpeed);
                */
            }
			//Sleep(10);
			GT_GetAtlPos(2,&midPosEncoder); //get_encoder(1,&midPosEncoder);
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
		GT_GetAtlPos(2,&midPosEncoder); //get_encoder(1,&midPosEncoder);
		deltaMainCircle = myAbs((double)(midPosEncoder - lastEncoderV))/(MainAxeRatio*(double)EncoderResolution);
		lastEncoderV = midPosEncoder;
		deltaMainCircle = deltaMainCircle * MainAxeCircleLen;
        MainAxePos_Y += deltaMainCircle;        
		adjustangle = AdjustAngle(MainAxePos_Y+MainAxeCircleLen*qitingjiao/360,MainAxeCircleLen,TaskIndex);

        double tempout = 360*MainAxePos_Y/MainAxeCircleLen;
 //       SendMessage(WM_DEBUGOUTPUTMM,(WPARAM)(&tempout),(LPARAM)(&adjustangle));

		angleflag = 1;
		GT_GetAtlPos(2,&iniMainAxeEncoder); //get_encoder(1,&iniMainAxeEncoder); 

        tempout = qitingjiao+adjustangle;
        if (tempout>180+360)
        {
           tempout-=360;
        }
		ObjdeltaEncoder  = (tempout)*EncoderResolution*(this->m_lpWorkPlanDlg->m_WindTask[index].m_MainAxeSpeedFactor)/(360);
	//	ObjdeltaEncoder  = 360*EncoderResolution*(m_lpOpDlg->m_WindTask[index].m_mainAxeRatio)/(360);
		while((angleflag)&&((*runningflag))) //�ȴ���ͣ��
		{
		//	Sleep(1);
			GT_GetAtlPos(2,&CurMainAxeEncoder); // get_encoder(1,&CurMainAxeEncoder); 
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
		GT_GetAtlPos(2,&StartPosEncoder); //get_encoder(1,&StartPosEncoder);
    	lastEncoderV = StartPosEncoder;
	}

    return 1;

}

double CWorkMonitorDlg::AdjustAngle(double nowlength, double circlelen, int i)
{
	int N;
	double a;
    double angle;
    double width;
	double ret;
	
	angle = this->m_lpWorkPlanDlg->m_WindTask[i].m_crossAngle;
	angle = angle*PI_VALUE/180;
	
	width = this->m_lpWorkPlanDlg->m_WindTask[i].m_shaWidth;
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

unsigned long CWorkMonitorDlg::check_done(unsigned short axis)
{
	unsigned long checkstatus;
	GT_GetSts(axis,&checkstatus); //
	checkstatus = checkstatus&(0x0001<<10);    //Bit10 
    return checkstatus;
}
