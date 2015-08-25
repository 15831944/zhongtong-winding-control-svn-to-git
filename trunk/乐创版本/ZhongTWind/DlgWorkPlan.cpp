// DlgWorkPlan.cpp : implementation file
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "DlgWorkPlan.h"
#include <math.h>
#include "WorkMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CZhongTWindApp theApp;

typedef struct tagREPORT_ITEM
{
	LPCTSTR name;
	int     width;
} REPORT_ITEM, *LPREPORT_ITEM;

const REPORT_ITEM s_reportItems[] = 
{
//	{_T("选择"),          50},
	{_T("铺层"),          50},
	{_T("纱宽"),          50},
	{_T("角度"),          50},
	{_T("起停角"),        70},
	{_T("终停角"),        70},
	{_T("次数"),          50},
	{_T("位置"),          50},
	{_T("缠绕方式"),      80},
} ;

#define INDEX_LAYER            0
#define INDEX_SHAKUAN          1
#define INDEX_JIAODU           2
#define INDEX_QITINGJIAO       3
#define INDEX_ZHONGTINGJIAO    4
#define INDEX_CISHU            5
#define INDEX_WEIZHI           6
#define INDEX_WINDMETHOD       7

#define PI_VALUE   (3.1415926535897)

#define WIND_METHOD_CIRCLE     1
#define WIND_METHOD_ADDSAND    2
#define WIND_METHOD_CROSS      3

/*
enum WindMethod {WIND_METHOD_CIRCLE=1,
                 WIND_METHOD_ADDSAND=2,
                 WIND_METHOD_CROSS=3};
*/

#define WIND_RULE_CONFIRM_WIDTH       0
#define WIND_RULE_CONFIRM_ANGLE       1
#define WIND_RULE_CONFIRM_STOPANGLE   2

/*
enum WindRULE   {WIND_RULE_CONFIRM_WIDTH,
                 WIND_RULE_CONFIRM_ANGLE,
                 WIND_RULE_CONFIRM_STOPANGLE};
*/

#define WORK_METHOD_MANUAL     1
#define WORK_METHOD_AUTO       2



static int CutOffPoints[] = 
{
	1,2,3,4,5,
};
/////////////////////////////////////////////////////////////////////////////
// CDlgWorkPlan dialog


CDlgWorkPlan::CDlgWorkPlan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWorkPlan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWorkPlan)
	m_PipeTotalLen = 0.0;
	m_BandageWidth = 0.0;
	m_SandWidth = 0.0;
	m_CrossAngle = 0.0;
	m_BuffLength = 0.0;
	m_PipeDiameter = 0.0;
	m_SandRate = 0.0;
	m_StartStopAngle = 0.0;
	m_StopStopAngle = 0.0;
	m_RadioMainAxeSpeedFactor = -1;
	m_RadioWindRule = -1;
	m_RadioCutOffPoints = -1;
	//}}AFX_DATA_INIT
}


void CDlgWorkPlan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWorkPlan)
	DDX_Control(pDX, IDB_RUN, m_BtnRun);
	DDX_Control(pDX, IDB_ADDTASK, m_BtnAddTask);
	DDX_Control(pDX, IDB_DELTASK, m_BtnDelTask);
	DDX_Control(pDX, IDB_COMPUTE, m_BtnCompute);
	DDX_Control(pDX, IDL_CREATETASK, mListCreateTaskList);
	DDX_Control(pDX, IDLIST_SHOW_LAYER, m_LayerShowList);
	DDX_Text(pDX, IDE_PIPE_TOTALLENGTH, m_PipeTotalLen);
	DDV_MinMaxDouble(pDX, m_PipeTotalLen, 0., 1000000.);
	DDX_Text(pDX, IDE_BANDI_WIDTH, m_BandageWidth);
	DDV_MinMaxDouble(pDX, m_BandageWidth, 0., 1000000.);
	DDX_Text(pDX, IDE_SANDWIDTH, m_SandWidth);
	DDV_MinMaxDouble(pDX, m_SandWidth, 0., 1000000.);
	DDX_Text(pDX, IDE_CROSS_ANGLE, m_CrossAngle);
	DDV_MinMaxDouble(pDX, m_CrossAngle, 0., 1000000.);
	DDX_Text(pDX, IDE_BUFFLENGTH, m_BuffLength);
	DDV_MinMaxDouble(pDX, m_BuffLength, 0., 1000000.);
	DDX_Text(pDX, IDE_PIPEDIAMETER, m_PipeDiameter);
	DDV_MinMaxDouble(pDX, m_PipeDiameter, 0., 1000000.);
	DDX_Text(pDX, IDE_SANDRATE, m_SandRate);
	DDV_MinMaxDouble(pDX, m_SandRate, 0., 1000000.);
	DDX_Text(pDX, IDE_START_STOPANGLE, m_StartStopAngle);
	DDV_MinMaxDouble(pDX, m_StartStopAngle, 0., 1000000.);
	DDX_Text(pDX, IDE_STOP_STOPANGLE, m_StopStopAngle);
	DDV_MinMaxDouble(pDX, m_StopStopAngle, 0., 1000000.);
	DDX_Radio(pDX, IDC_RADIO_MAINAXE_SPEED_1, m_RadioMainAxeSpeedFactor);
	DDX_Radio(pDX, IDR_FIRM_SHA_WIDTH, m_RadioWindRule);
	DDX_Radio(pDX, IDC_RADIO_CUTOFF_POINTS, m_RadioCutOffPoints);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWorkPlan, CDialog)
	//{{AFX_MSG_MAP(CDlgWorkPlan)
	ON_NOTIFY(NM_RCLICK, IDLIST_SHOW_LAYER, OnRclickShowLayer)
	ON_BN_CLICKED(IDB_COMPUTE, OnCompute)
	ON_BN_CLICKED(IDB_ADDTASK, OnAddtask)
	ON_BN_CLICKED(IDB_DELTASK, OnBtnDeltask)
	ON_COMMAND(IDM_DELETE, OnMenuDeleteTask)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDL_CREATETASK, OnItemchangedCreatetask)
	ON_BN_CLICKED(IDB_RUN, OnBtnRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWorkPlan message handlers

BOOL CDlgWorkPlan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i;
	CString showstr;
	// TODO: Add extra initialization here
	ShowWindow(SW_MAXIMIZE);

    SetDataInitial();

    m_TaskNum = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////
    this->m_LayerShowList.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	m_LayerShowList.SetExtendedStyle(m_LayerShowList.GetExtendedStyle()|LVS_EX_FLATSB|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
     //   m_LayerShowList.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i=0; i<sizeof(s_reportItems)/sizeof(REPORT_ITEM); ++i)
	{
		m_LayerShowList.InsertColumn(i, s_reportItems[i].name, LVCFMT_LEFT, s_reportItems[i].width);
	}
	
	m_LayerShowList.SetRedraw(false);
    m_ListReportNum = 0;	
    
	/*
	for (i=0;i<6;i++)
	{
		showstr.Format(_T("%d"),i+1);
		m_LayerShowList.InsertItem(i, showstr);
		showstr.Format(_T("%.2f"),0);		
		m_LayerShowList.SetItemText(i, INDEX_SHAKUAN, showstr);
		m_LayerShowList.SetItemText(i, INDEX_JIAODU, showstr);
		m_LayerShowList.SetItemText(i, INDEX_QITINGJIAO, showstr);
		m_LayerShowList.SetItemText(i, INDEX_ZHONGTINGJIAO, showstr);
		m_LayerShowList.SetItemText(i, INDEX_CISHU, showstr);
		m_LayerShowList.SetItemText(i, INDEX_WEIZHI, showstr);
	}
	*/
	m_LayerShowList.SetRedraw(TRUE);
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	mListCreateTaskList.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	mListCreateTaskList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
    // InsertColumns
	mListCreateTaskList.InsertColumn(0, _T("选择"), LVCFMT_LEFT, 50);
    mListCreateTaskList.InsertColumn(1, _T("环向/加砂/交叉"), LVCFMT_LEFT, 120);
    mListCreateTaskList.InsertColumn(2, _T("起始位置"), LVCFMT_LEFT, 80);
    mListCreateTaskList.InsertColumn(3, _T("终止位置"), LVCFMT_LEFT, 80);
    mListCreateTaskList.InsertColumn(4, _T("层数"), LVCFMT_LEFT, 60);
	mListCreateTaskList.InsertColumn(5, _T("连续/手动"), LVCFMT_LEFT, 80);
    mListCreateTaskList.InsertColumn(6, _T("沙宽"), LVCFMT_LEFT, 60);
    mListCreateTaskList.InsertColumn(7, _T("缠绕角"), LVCFMT_LEFT, 60);
	mListCreateTaskList.InsertColumn(8, _T("两端停角"), LVCFMT_LEFT, 80);
	mListCreateTaskList.InsertColumn(9, _T("次数"), LVCFMT_LEFT, 60);

    mListCreateTaskList.InsertItem(0, NULL);
    mListCreateTaskList.InsertItem(2, NULL);
    mListCreateTaskList.InsertItem(3, NULL);

    mListCreateTaskList.InsertItem(4, NULL);
    mListCreateTaskList.InsertItem(5, NULL);
    mListCreateTaskList.InsertItem(6, NULL);


	CStringArray acsComboStrings;   
    acsComboStrings.Add(_T("环向"));
    acsComboStrings.Add(_T("加砂"));
    acsComboStrings.Add(_T("交叉"));

	CStringArray acsComboStrings2;   
    acsComboStrings2.Add(_T("连续"));
    acsComboStrings2.Add(_T("手动"));
	
	for (i=0;i<6;i++)
	{
		mListCreateTaskList.SetComboBox(i,
			1,
		acsComboStrings);
        mListCreateTaskList.SetItemText(i, 1, _T("环向"));
		mListCreateTaskList.SetComboBox(i,
			5,
		acsComboStrings2);
		mListCreateTaskList.SetItemText(i, 5, _T("手动"));
	}
    
	for (i=0;i<6;i++)
	{
		CString strContent;

        mListCreateTaskList.SetEditBox(i, 2);
		mListCreateTaskList.SetItemText(i, 2, _T("0"));
		mListCreateTaskList.SetEditBox(i, 3);
		strContent.Format(_T("%.2f"),m_PipeTotalLen);
		mListCreateTaskList.SetItemText(i, 3,strContent);
        
        mListCreateTaskList.SetEditBox(i, 4);
		mListCreateTaskList.SetItemText(i, 4,_T("1"));

		mListCreateTaskList.AddColoredRow(i,
			RGB(230,34,55),
		    RGB(156,253,145));
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWorkPlan::OnRclickShowLayer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

   
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_LSTR_MENU ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
    }

	*pResult = 0;
}

void CDlgWorkPlan::SetDataInitial()
{
   	m_PipeTotalLen            = 5000;
	m_BandageWidth            = 100;
	m_SandWidth               = 100;
	m_CrossAngle              = 65;
	m_BuffLength              = 360;
	m_PipeDiameter            = 480;
	m_SandRate                = 0.5;
	m_StartStopAngle          = 200;
	m_StopStopAngle           = 200;
	m_RadioMainAxeSpeedFactor = 0;
	m_RadioWindRule           = 0;
	m_RadioCutOffPoints       = 0;
	UpdateData(false);
}

void CDlgWorkPlan::OnCompute() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	CString str;
	for(int i=0; i<mListCreateTaskList.GetItemCount(); i++)
	{
		if( mListCreateTaskList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || mListCreateTaskList.GetCheck(i))
		{
			GetComputeParam(&m_TaskParamForCreate[i],i);
			if (m_TaskParamForCreate[i].m_WindMethod == WIND_METHOD_CIRCLE 
			    || m_TaskParamForCreate[i].m_WindMethod == WIND_METHOD_ADDSAND )
			{
                 ComputeCircle(i);
			}
			else if (m_TaskParamForCreate[i].m_WindMethod == WIND_METHOD_CROSS )
			{
                 Compute_Cross(i);
			}
		}
    }
}

void CDlgWorkPlan::GetComputeParam(TaskComputeParam *param,int listIndex)
{
	TCHAR tcText[MAX_CHAR_COUNT];
    UpdateData(true);
	param->m_BandageWidth            = this->m_BandageWidth;
	param->m_BuffLength              = this->m_BuffLength;
	param->m_CrossAngle              = this->m_CrossAngle;
	param->m_PipeDiameter            = this->m_PipeDiameter;
	param->m_PipeTotalLen            = this->m_PipeTotalLen;
	param->m_SandRate                = this->m_SandRate;
	param->m_SandWidth               = this->m_SandWidth;
	param->m_StartStopAngle          = this->m_StartStopAngle;
	param->m_StopStopAngle           = this->m_StopStopAngle;

	
    mListCreateTaskList.GetItemText(listIndex,4,tcText,MAX_CHAR_COUNT);
    param->m_windLayerNum = wcstoul(tcText,NULL,0);
    
    wmemset(tcText,0x00,MAX_CHAR_COUNT);
    mListCreateTaskList.GetItemText(listIndex,1,tcText,MAX_CHAR_COUNT);
    if (wcscoll(tcText,_T("环向"))==0)
    {
		param->m_WindMethod = WIND_METHOD_CIRCLE;
    }
	else if (wcscoll(tcText,_T("加砂"))==0)
	{
		param->m_WindMethod = WIND_METHOD_ADDSAND;
	}
	else if (wcscoll(tcText,_T("交叉"))==0)
	{
		param->m_WindMethod = WIND_METHOD_CROSS;
	}
    else
	{
        param->m_WindMethod = -1;
	}


	wmemset(tcText,0x00,MAX_CHAR_COUNT);
    mListCreateTaskList.GetItemText(listIndex,5,tcText,MAX_CHAR_COUNT);
    if (wcscoll(tcText,_T("手动"))==0)
    {
		param->m_WorkMethod = WORK_METHOD_MANUAL;
    }
	else if (wcscoll(tcText,_T("连续"))==0)
	{
		param->m_WorkMethod = WORK_METHOD_AUTO;
	}
	else 
	{
		param->m_WorkMethod = -1;
	}
	
	wmemset(tcText,0x00,MAX_CHAR_COUNT);
    mListCreateTaskList.GetItemText(listIndex,2,tcText,MAX_CHAR_COUNT);
    param->m_startPos = wcstod(tcText,NULL);

	wmemset(tcText,0x00,MAX_CHAR_COUNT);
    mListCreateTaskList.GetItemText(listIndex,3,tcText,MAX_CHAR_COUNT);
    param->m_endPos  = wcstod(tcText,NULL);

	param->m_RadioMainAxeSpeedFactor = this->m_RadioMainAxeSpeedFactor;
    param->m_MainAxeSpeedFactor      =  theApp.GlobalParam.m_fMainAxeLevelFactor[param->m_RadioMainAxeSpeedFactor];

	param->m_RadioWindRule           = this->m_RadioWindRule;
    param->m_RadioCutOffPoints       = CutOffPoints[this->m_RadioCutOffPoints];

}


/*****************************************************
1：
tga = 主轴周长/纱宽

  2：
  1/cosa = 主轴周长/纱宽  
*****************************************************/

void CDlgWorkPlan::ComputeCircle(int Listindex)
{
	double arc_angle;
	double circleLen,Horizon_Len;
	int N;
	CString tempstr;
	
	circleLen = PI_VALUE*m_TaskParamForCreate[Listindex].m_PipeDiameter;
	Horizon_Len = m_TaskParamForCreate[Listindex].m_BandageWidth;  //纱片宽度
    if (m_TaskParamForCreate[Listindex].m_WindMethod == WIND_METHOD_ADDSAND)
    {
       Horizon_Len = m_TaskParamForCreate[Listindex].m_SandWidth; 
    }
    
	N = 1;
	switch (m_TaskParamForCreate[Listindex].m_RadioWindRule)
	{
	   case WIND_RULE_CONFIRM_WIDTH:
		   //arc_angle = acos(m_BandageWidth/circleLen);
		   arc_angle = atan(circleLen/Horizon_Len);
		   //Vertical_Len = m_BandageWidth;
		   break;
	   case WIND_RULE_CONFIRM_ANGLE:
		   arc_angle = m_TaskParamForCreate[Listindex].m_CrossAngle*PI_VALUE/180;  //角度制 化为 弧度制
           Horizon_Len = cos(arc_angle)*circleLen;
           Horizon_Len = circleLen/tan(arc_angle);
		   break;
	   default:
		   //arc_angle = acos(m_BandageWidth/circleLen);
		   arc_angle = atan(circleLen/Horizon_Len);
		   //Vertical_Len = m_BandageWidth;
		   break;
	}
	
	double tt = arc_angle*180/PI_VALUE;   //化为角度制
	tempstr.Format(L"%.3f",tt);

	m_TaskParamForCreate[Listindex].m_CResultBandageWidth = Horizon_Len;
	m_TaskParamForCreate[Listindex].m_CResultCrossAngle   = tt;
	m_TaskParamForCreate[Listindex].m_CResultStartAngle   = m_TaskParamForCreate[Listindex].m_StartStopAngle;
	m_TaskParamForCreate[Listindex].m_CResultEndAngle     = m_TaskParamForCreate[Listindex].m_StopStopAngle;
	m_TaskParamForCreate[Listindex].m_CResultWindNum      = 1*m_TaskParamForCreate[Listindex].m_windLayerNum;

    tempstr.Format(L"%.2f",m_TaskParamForCreate[Listindex].m_CResultBandageWidth);
    mListCreateTaskList.SetItemText(Listindex, 6, tempstr);   //纱宽

    tempstr.Format(L"%.2f",m_TaskParamForCreate[Listindex].m_CResultCrossAngle);
    mListCreateTaskList.SetItemText(Listindex, 7, tempstr);   //缠绕角

    tempstr.Format(L"%.2f",m_TaskParamForCreate[Listindex].m_CResultStartAngle);
    mListCreateTaskList.SetItemText(Listindex, 8, tempstr);   //两端停角

	tempstr.Format(L"%d",m_TaskParamForCreate[Listindex].m_CResultWindNum);
    mListCreateTaskList.SetItemText(Listindex, 9, tempstr);   //
	UpdateData(false);
}

void CDlgWorkPlan::Compute_Cross(int ListIndex)
{
	double temp_double;
	double arc_angle,tempTingAngle;
	double ret;
	double circleLen,Horizon_Len;
	int N,Ntemp;
	CString tempstr;
	double tt;	
    
	arc_angle = PI_VALUE*(m_TaskParamForCreate[ListIndex].m_CrossAngle)/180;
    circleLen = PI_VALUE*m_TaskParamForCreate[ListIndex].m_PipeDiameter; 	
	Horizon_Len = m_TaskParamForCreate[ListIndex].m_BandageWidth;

	switch (m_TaskParamForCreate[ListIndex].m_RadioWindRule)
	{
	   case WIND_RULE_CONFIRM_ANGLE:
           temp_double = circleLen/(tan(PI_VALUE*m_TaskParamForCreate[ListIndex].m_CrossAngle/180)*(Horizon_Len));
           N = (int)temp_double;
           Horizon_Len = circleLen/(tan(PI_VALUE*m_TaskParamForCreate[ListIndex].m_CrossAngle/180)*((double)N));
		   tt = m_TaskParamForCreate[ListIndex].m_CrossAngle;
		   arc_angle = PI_VALUE*m_TaskParamForCreate[ListIndex].m_CrossAngle/180;
		   break;
	   case WIND_RULE_CONFIRM_WIDTH:
	   default:
		   temp_double = circleLen/(tan(PI_VALUE*m_TaskParamForCreate[ListIndex].m_CrossAngle/180));
		   temp_double = temp_double/Horizon_Len;
		   N = (int)temp_double;
           N = N+1;
		   temp_double = circleLen/(((double)N)*Horizon_Len);
		   ret = atan(temp_double);
		   tt = ret*180/PI_VALUE;
		   arc_angle = ret;
		   break;
	}
	
	
	
	double totalLen = m_TaskParamForCreate[ListIndex].m_endPos - m_TaskParamForCreate[ListIndex].m_startPos;
	if (totalLen<0)
	{
		totalLen = totalLen*(-1);
	}
    

	
    temp_double = 2*tan(arc_angle)*totalLen + 2*tan(arc_angle)*2*m_TaskParamForCreate[ListIndex].m_BuffLength + 
		2*tan(arc_angle)*2*m_TaskParamForCreate[ListIndex].m_BuffLength + m_TaskParamForCreate[ListIndex].m_BandageWidth/cos(arc_angle);
    
	
	temp_double = 2*tan(arc_angle)*totalLen + 2*tan(arc_angle)*2*m_TaskParamForCreate[ListIndex].m_BuffLength + 
		2*tan(arc_angle)*2*m_TaskParamForCreate[ListIndex].m_BuffLength - m_TaskParamForCreate[ListIndex].m_BandageWidth*tan(arc_angle);
	// temp_double = 2*tan(arc_angle)*totalLen + 2*tan(arc_angle)*2*m_LeftBuffLength + 
	//		                                              m_BandageWidth/cos(arc_angle);
	
	
	
    temp_double = 2*totalLen*tan(arc_angle) + 4*m_TaskParamForCreate[ListIndex].m_BuffLength*tan(arc_angle) 
		+ m_TaskParamForCreate[ListIndex].m_BandageWidth*tan(arc_angle);
	
    Ntemp = (int)(temp_double/circleLen);
    
    
	if (m_TaskParamForCreate[ListIndex].m_StartStopAngle<180)
	{
		tempTingAngle =(((double)(Ntemp+1)*circleLen)-temp_double)/(m_TaskParamForCreate[ListIndex].m_PipeDiameter);
        tempTingAngle= tempTingAngle*180/PI_VALUE;
	}
	else
	{
        tempTingAngle =(((double)(Ntemp+2)*circleLen)-temp_double)/(m_TaskParamForCreate[ListIndex].m_PipeDiameter);
		tempTingAngle= tempTingAngle*180/PI_VALUE;
	}
	

	m_TaskParamForCreate[ListIndex].m_CResultBandageWidth = Horizon_Len;
	m_TaskParamForCreate[ListIndex].m_CResultCrossAngle   = tt;
	m_TaskParamForCreate[ListIndex].m_CResultStartAngle   = tempTingAngle;
	m_TaskParamForCreate[ListIndex].m_CResultEndAngle     = tempTingAngle;
	m_TaskParamForCreate[ListIndex].m_CResultWindNum      = N*m_TaskParamForCreate[ListIndex].m_windLayerNum;
	
    tempstr.Format(L"%.2f",m_TaskParamForCreate[ListIndex].m_CResultBandageWidth);
    mListCreateTaskList.SetItemText(ListIndex, 6, tempstr);   //纱宽
	
    tempstr.Format(L"%.2f",m_TaskParamForCreate[ListIndex].m_CResultCrossAngle);
    mListCreateTaskList.SetItemText(ListIndex, 7, tempstr);   //缠绕角
	
    tempstr.Format(L"%.2f",m_TaskParamForCreate[ListIndex].m_CResultStartAngle);
    mListCreateTaskList.SetItemText(ListIndex, 8, tempstr);   //两端停角
	
	tempstr.Format(L"%d",m_TaskParamForCreate[ListIndex].m_CResultWindNum);
    mListCreateTaskList.SetItemText(ListIndex, 9, tempstr);   //
	UpdateData(false);

}

void CDlgWorkPlan::OnAddtask() 
{
	// TODO: Add your control notification handler code here
	CString tmpstr;
	UpdateData(true);

    m_LayerShowList.SetRedraw(false);
	for(int i=0; i<mListCreateTaskList.GetItemCount(); i++)
	{
		if( mListCreateTaskList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || mListCreateTaskList.GetCheck(i))
		{
			if(m_ListReportNum>=64)
			{
				MessageBox(L"到达最大任务上限64，无法添加任务！");
				return;
			}

			 //tmpstr.Format(L"%d",m_ListReportNum+1);
			 m_LayerShowList.InsertItem(m_ListReportNum, tmpstr);
			 switch (m_TaskParamForCreate[i].m_WindMethod)
			 {
			   case WIND_METHOD_CIRCLE:
				 m_LayerShowList.SetItemText(m_ListReportNum, INDEX_WINDMETHOD, _T("环向"));
				 break;
		   	   case WIND_METHOD_ADDSAND:
				 m_LayerShowList.SetItemText(m_ListReportNum, INDEX_WINDMETHOD, _T("加沙"));
				 break;
			   case WIND_METHOD_CROSS:
				 m_LayerShowList.SetItemText(m_ListReportNum, INDEX_WINDMETHOD, _T("交叉"));
				 break;
			   default:
				 break;
			 }

			 tmpstr.Format(L"%d",m_TaskParamForCreate[i].m_CResultWindNum);
			 m_LayerShowList.SetItemText(m_ListReportNum,INDEX_CISHU,tmpstr);
			 tmpstr.Format(L"%.2f",m_TaskParamForCreate[i].m_CResultEndAngle);
			 m_LayerShowList.SetItemText(m_ListReportNum,INDEX_ZHONGTINGJIAO,tmpstr);
			 tmpstr.Format(L"%.2f",m_TaskParamForCreate[i].m_CResultStartAngle);
			 m_LayerShowList.SetItemText(m_ListReportNum,INDEX_QITINGJIAO,tmpstr);
			 tmpstr.Format(L"%.2f",m_TaskParamForCreate[i].m_CResultCrossAngle);
			 m_LayerShowList.SetItemText(m_ListReportNum,INDEX_JIAODU,tmpstr);
			 tmpstr.Format(L"%.2f",m_TaskParamForCreate[i].m_CResultBandageWidth);
	         m_LayerShowList.SetItemText(m_ListReportNum,INDEX_SHAKUAN,tmpstr); 
             
			 tmpstr.Format(L"%d",m_ListReportNum+1);
             m_LayerShowList.SetItemText(m_ListReportNum,0,tmpstr); 

			 m_WindTask[m_ListReportNum].m_crossAngle     = m_TaskParamForCreate[i].m_CResultCrossAngle;
			 m_WindTask[m_ListReportNum].m_EndStopAngle   = m_TaskParamForCreate[i].m_CResultStartAngle;
			 m_WindTask[m_ListReportNum].m_LayerNum       = m_TaskParamForCreate[i].m_CResultWindNum;
			// m_WindTask[m_ListReportNum].m_LayerTaskIndex = m_ListNum;
			 m_WindTask[m_ListReportNum].m_BuffLen        = m_TaskParamForCreate[i].m_BuffLength;
			 m_WindTask[m_ListReportNum].m_PipeDiam       = m_TaskParamForCreate[i].m_PipeDiameter;
			 //m_WindTask[m_ListReportNum].m_rightBuffLen   = m_TaskParamForCreate[i].m_BuffLength;
			 m_WindTask[m_ListReportNum].m_shaWidth       = m_TaskParamForCreate[i].m_CResultBandageWidth;
			 m_WindTask[m_ListReportNum].m_StartPos       = m_TaskParamForCreate[i].m_startPos;
			 m_WindTask[m_ListReportNum].m_EndPos        = m_TaskParamForCreate[i].m_endPos;
			 m_WindTask[m_ListReportNum].m_StartStopAngle = m_TaskParamForCreate[i].m_CResultStartAngle;
	         m_WindTask[m_ListReportNum].m_WindMethod     = m_TaskParamForCreate[i].m_WindMethod;
			 m_WindTask[m_ListReportNum].m_MainAxeSpeedFactor   = m_TaskParamForCreate[i].m_MainAxeSpeedFactor;
             m_ListReportNum++;
			 m_TaskNum++;
		}//if

	}//for
    m_LayerShowList.SetRedraw(true);
}

void CDlgWorkPlan::OnBtnDeltask() 
{
	// TODO: Add your control notification handler code here
	DelTask();

}

void CDlgWorkPlan::DelTask(void)
{

	POSITION   pos   =   m_LayerShowList.GetFirstSelectedItemPosition();
	int   nItem , i;
	CString tmpstr;
	m_LayerShowList.SetRedraw(false);
	if   (pos   !=   NULL)
    {
        nItem  =   m_LayerShowList.GetNextSelectedItem(pos);
		m_LayerShowList.DeleteItem(nItem);
		
        for (i = nItem;i<m_ListReportNum-1;i++)
        {
            m_WindTask[i].TaskInfoCpyFrom(m_WindTask[i+1]);
        }
        m_ListReportNum--;
        m_TaskNum--;
		for (i=0;i<m_ListReportNum;i++)
		{
			tmpstr.Format(L"%d",i+1);
			m_LayerShowList.SetItemText(i,0,tmpstr); 

		}


    }
	UpdateData(true);
    m_LayerShowList.SetRedraw(true);
}

void CDlgWorkPlan::OnMenuDeleteTask() 
{
	// TODO: Add your command handler code here
	DelTask();
}

/*
void CDlgWorkPlan::OnItemchangedCreatetask(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	MessageBox(L"go on!");
	*pResult = 0;
}
*/


void CDlgWorkPlan::OnBtnRun() 
{
	// TODO: Add your control notification handler code here
	if (m_ListReportNum<1)
	{
		MessageBox(_T("请添加缠绕任务"));
	}
	else
	{
		CWorkMonitorDlg dlg;
		dlg.m_lpWorkPlanDlg = this;
		dlg.DoModal();
	}
}
