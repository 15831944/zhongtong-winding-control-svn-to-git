// MainOperationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "MainOperationDlg.h"
#include <math.h>
#include "WorkMonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LAYER_NUM_INITIAL 16
#define PI_VALUE   3.1415926535897
#define LAYER_METHOD_CIRCLE   0
#define LAYER_METHOD_JIASHA   1
#define LAYER_METHOD_CROSS    2


#define COMPUTE_METHOD_FIRM_WIDTH 0
#define COMPUTE_METHOD_FIRM_ANGLE 1
#define COMPUTE_METHOD_FIRM_STOPA 2


typedef struct tagREPORT_ITEM
{
	LPCTSTR name;
	int     width;
} REPORT_ITEM, *LPREPORT_ITEM;

const REPORT_ITEM s_reportItems[] = 
{
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

/////////////////////////////////////////////////////////////////////////////
// CMainOperationDlg dialog


CMainOperationDlg::CMainOperationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainOperationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainOperationDlg)
	m_BandageWidth    = 100;
	m_CrossAngle      = 45;
	m_LeftBuffLength  = 360;
	m_RightBuffLength = 360;
    m_PipeDiameter    = 480;
	m_PipeTotalLen = 9000.0;
	m_RadioWindRule = 0;
	m_RadioMainAxeSpeedFactor = 0;
	m_WindMethod_Layer1 = -1;
	m_WindMethod_Layer2 = -1;
	m_RadioContinueOrManual = -1;
	m_StartStopAngle  = 200;
	m_EndStopAngle    = 200;
	m_StartPosLayer1 = 0.0;
	m_EndPosLayer1 = 0.0;
	m_TaskLayerNum_L1 = 0;
	m_CheckLayer1 = FALSE;
	m_CheckLayer2 = FALSE;
	m_CheckLayer3 = FALSE;
	m_CheckLayer4 = FALSE;
	m_CheckLayer5 = FALSE;
	m_CheckLayer6 = FALSE;
	m_ShowCishuLayer1 = 0;
	m_ShowCishuLayer2 = 0;
	m_ShowCishuLayer3 = 0;
	m_ShowCishuLayer4 = 0;
	m_ShowCishuLayer5 = 0;
	m_ShowCishuLayer6 = 0;
	m_EndPosLayer2 = 0.0;
	m_EndPosLayer3 = 0.0;
	m_EndPosLayer4 = 0.0;
	m_EndPosLayer5 = 0.0;
	m_EndPosLayer6 = 0.0;
	m_CrossShowLayer1 = 0.0;
	m_CrossShowLayer2 = 0.0;
	m_CrossShowLayer3 = 0.0;
	m_CrossShowLayer4 = 0.0;
	m_CrossShowLayer5 = 0.0;
	m_CrossShowLayer6 = 0.0;
	m_WindMethod_Layer3 = -1;
	m_WindMethod_Layer4 = -1;
	m_WindMethod_Layer5 = -1;
	m_WindMethod_Layer6 = -1;
	m_TaskLayerNum_L2 = 0;
	m_TaskLayerNum_L3 = 0;
	m_TaskLayerNum_L4 = 0;
	m_TaskLayerNum_L5 = 0;
	m_TaskLayerNum_L6 = 0;
	m_StartPosLayer2 = 0.0;
	m_StartPosLayer3 = 0.0;
	m_StartPosLayer4 = 0.0;
	m_StartPosLayer5 = 0.0;
	m_StartPosLayer6 = 0.0;
	m_QiTingJiaoShow_Layer1 = 0.0;
	m_QiTingJiaoShow_Layer2 = 0.0;
	m_QiTingJiaoShow_Layer3 = 0.0;
	m_QiTingJiaoShow_Layer4 = 0.0;
	m_QiTingJiaoShow_Layer5 = 0.0;
	m_QiTingJiaoShow_Layer6 = 0.0;
	m_ZhongTingJiaoShowLayer1 = 0.0;
	m_ZhongTingJiaoShowLayer2 = 0.0;
	m_ZhongTingJiaoShowLayer3 = 0.0;
	m_ZhongTingJiaoShowLayer4 = 0.0;
	m_ZhongTingJiaoShowLayer5 = 0.0;
	m_ZhongTingJiaoShowLayer6 = 0.0;
	m_DataSetNum = 0;
	m_PipeTotalLen    = 5000;
	m_ShaWidthShow_Layer1 = 0.0;
	m_ShaWidthShow_Layer2 = 0.0;
	m_ShaWidthShow_Layer3 = 0.0;
	m_ShaWidthShow_Layer4 = 0.0;
	m_ShaWidthShow_Layer5 = 0.0;
	m_ShaWidthShow_Layer6 = 0.0;
	//}}AFX_DATA_INIT
}


void CMainOperationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainOperationDlg)
	DDX_Control(pDX, IDLIST_SHOW_LAYER, m_LayerShowList);
	DDX_Text(pDX, IDE_BANDI_WIDTH, m_BandageWidth);
	DDX_Text(pDX, IDE_CROSS_ANGLE, m_CrossAngle);
	DDX_Text(pDX, IDE_LEFT_BUFFLENGTH, m_LeftBuffLength);
	DDX_Text(pDX, IDE_RIGHT_BUFFLENGTH, m_RightBuffLength);
	DDX_Text(pDX, IDE_PIPEDIAMETER, m_PipeDiameter);
	DDX_Text(pDX, IDE_PIPE_TOTALLENGTH, m_PipeTotalLen);
	DDX_Radio(pDX, IDR_FIRM_SHA_WIDTH, m_RadioWindRule);
	DDX_Radio(pDX, IDC_RADIO_MAINAXE_SPEED_1, m_RadioMainAxeSpeedFactor);
	DDX_Radio(pDX, IDC_RADIO_L_LAYER_1, m_WindMethod_Layer1);
	DDX_Radio(pDX, IDC_RADIO_L_LAYER_2, m_WindMethod_Layer2);
	DDX_Radio(pDX, IDC_RADIO_CONTINUE_LAYER1, m_RadioContinueOrManual);
	DDX_Text(pDX, IDE_START_STOPANGLE, m_StartStopAngle);
	DDX_Text(pDX, IDE_STOP_STOPANGLE, m_EndStopAngle);
	DDX_Text(pDX, IDE_START_POS_LAYER1, m_StartPosLayer1);
	DDX_Text(pDX, IDE_END_POS_LAYER1, m_EndPosLayer1);
	DDX_Text(pDX, IDE_LAYER_NUM_LAYER1, m_TaskLayerNum_L1);
	DDX_Check(pDX, IDC_CHECK_LAYER1, m_CheckLayer1);
	DDX_Check(pDX, IDC_CHECK_LAYER2, m_CheckLayer2);
	DDX_Check(pDX, IDC_CHECK_LAYER3, m_CheckLayer3);
	DDX_Check(pDX, IDC_CHECK_LAYER4, m_CheckLayer4);
	DDX_Check(pDX, IDC_CHECK_LAYER5, m_CheckLayer5);
	DDX_Check(pDX, IDC_CHECK_LAYER6, m_CheckLayer6);
	DDX_Text(pDX, IDE_CISHU_SHOW_LAYER1, m_ShowCishuLayer1);
	DDX_Text(pDX, IDE_CISHU_SHOW_LAYER2, m_ShowCishuLayer2);
	DDX_Text(pDX, IDE_CISHU_SHOW_LAYER3, m_ShowCishuLayer3);
	DDX_Text(pDX, IDE_CISHU_SHOW_LAYER4, m_ShowCishuLayer4);
	DDX_Text(pDX, IDE_CISHU_SHOW_LAYER5, m_ShowCishuLayer5);
	DDX_Text(pDX, IDE_CISHU_SHOW_LAYER6, m_ShowCishuLayer6);
	DDX_Text(pDX, IDE_END_POS_LAYER2, m_EndPosLayer2);
	DDX_Text(pDX, IDE_END_POS_LAYER3, m_EndPosLayer3);
	DDX_Text(pDX, IDE_END_POS_LAYER4, m_EndPosLayer4);
	DDX_Text(pDX, IDE_END_POS_LAYER5, m_EndPosLayer5);
	DDX_Text(pDX, IDE_END_POS_LAYER6, m_EndPosLayer6);
	DDX_Text(pDX, IDE_JIAODU_SHOW_LAYER1, m_CrossShowLayer1);
	DDX_Text(pDX, IDE_JIAODU_SHOW_LAYER2, m_CrossShowLayer2);
	DDX_Text(pDX, IDE_JIAODU_SHOW_LAYER3, m_CrossShowLayer3);
	DDX_Text(pDX, IDE_JIAODU_SHOW_LAYER4, m_CrossShowLayer4);
	DDX_Text(pDX, IDE_JIAODU_SHOW_LAYER5, m_CrossShowLayer5);
	DDX_Text(pDX, IDE_JIAODU_SHOW_LAYER6, m_CrossShowLayer6);
	DDX_Radio(pDX, IDC_RADIO_L_LAYER_3, m_WindMethod_Layer3);
	DDX_Radio(pDX, IDC_RADIO_L_LAYER_4, m_WindMethod_Layer4);
	DDX_Radio(pDX, IDC_RADIO_L_LAYER_5, m_WindMethod_Layer5);
	DDX_Radio(pDX, IDC_RADIO_L_LAYER_6, m_WindMethod_Layer6);
	DDX_Text(pDX, IDE_LAYER_NUM_LAYER2, m_TaskLayerNum_L2);
	DDX_Text(pDX, IDE_LAYER_NUM_LAYER3, m_TaskLayerNum_L3);
	DDX_Text(pDX, IDE_LAYER_NUM_LAYER4, m_TaskLayerNum_L4);
	DDX_Text(pDX, IDE_LAYER_NUM_LAYER5, m_TaskLayerNum_L5);
	DDX_Text(pDX, IDE_LAYER_NUM_LAYER6, m_TaskLayerNum_L6);
	DDX_Text(pDX, IDE_START_POS_LAYER2, m_StartPosLayer2);
	DDX_Text(pDX, IDE_START_POS_LAYER3, m_StartPosLayer3);
	DDX_Text(pDX, IDE_START_POS_LAYER4, m_StartPosLayer4);
	DDX_Text(pDX, IDE_START_POS_LAYER5, m_StartPosLayer5);
	DDX_Text(pDX, IDE_START_POS_LAYER6, m_StartPosLayer6);
	DDX_Text(pDX, IDE_QITINGJIAO_SHOW_LAYER1, m_QiTingJiaoShow_Layer1);
	DDX_Text(pDX, IDE_QITINGJIAO_SHOW_LAYER2, m_QiTingJiaoShow_Layer2);
	DDX_Text(pDX, IDE_QITINGJIAO_SHOW_LAYER3, m_QiTingJiaoShow_Layer3);
	DDX_Text(pDX, IDE_QITINGJIAO_SHOW_LAYER4, m_QiTingJiaoShow_Layer4);
	DDX_Text(pDX, IDE_QITINGJIAO_SHOW_LAYER5, m_QiTingJiaoShow_Layer5);
	DDX_Text(pDX, IDE_QITINGJIAO_SHOW_LAYER6, m_QiTingJiaoShow_Layer6);
	DDX_Text(pDX, IDE_ZHONGTINGJIAO_SHOW_LAYER1, m_ZhongTingJiaoShowLayer1);
	DDX_Text(pDX, IDE_ZHONGTINGJIAO_SHOW_LAYER2, m_ZhongTingJiaoShowLayer2);
	DDX_Text(pDX, IDE_ZHONGTINGJIAO_SHOW_LAYER3, m_ZhongTingJiaoShowLayer3);
	DDX_Text(pDX, IDE_ZHONGTINGJIAO_SHOW_LAYER4, m_ZhongTingJiaoShowLayer4);
	DDX_Text(pDX, IDE_ZHONGTINGJIAO_SHOW_LAYER5, m_ZhongTingJiaoShowLayer5);
	DDX_Text(pDX, IDE_ZHONGTINGJIAO_SHOW_LAYER6, m_ZhongTingJiaoShowLayer6);
	DDX_Text(pDX, IDE_SHAKUAN_SHOW_LAYER1, m_ShaWidthShow_Layer1);
	DDX_Text(pDX, IDE_SHAKUAN_SHOW_LAYER2, m_ShaWidthShow_Layer2);
	DDX_Text(pDX, IDE_SHAKUAN_SHOW_LAYER3, m_ShaWidthShow_Layer3);
	DDX_Text(pDX, IDE_SHAKUAN_SHOW_LAYER4, m_ShaWidthShow_Layer4);
	DDX_Text(pDX, IDE_SHAKUAN_SHOW_LAYER5, m_ShaWidthShow_Layer5);
	DDX_Text(pDX, IDE_SHAKUAN_SHOW_LAYER6, m_ShaWidthShow_Layer6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainOperationDlg, CDialog)
	//{{AFX_MSG_MAP(CMainOperationDlg)
	ON_BN_CLICKED(IDB_COMPUTE, OnCompute)
	ON_BN_CLICKED(IDR_FIRM_SHA_WIDTH, OnFirmShaWidth)
	ON_BN_CLICKED(IDR_FIRM_CROSSANGLE, OnFirmCrossangle)
	ON_BN_CLICKED(IDB_ALTER, OnAlter)
	ON_BN_CLICKED(IDB_RUN, OnRun)
	ON_BN_CLICKED(IDB_ADDWORKTASK, OnAddworktask)
	ON_BN_CLICKED(IDC_CHECK_LAYER1, OnCheckLayer1)
	ON_BN_CLICKED(IDC_CHECK_LAYER2, OnCheckLayer2)
	ON_BN_CLICKED(IDC_CHECK_LAYER3, OnCheckLayer3)
	ON_BN_CLICKED(IDC_CHECK_LAYER4, OnCheckLayer4)
	ON_BN_CLICKED(IDC_CHECK_LAYER5, OnCheckLayer5)
	ON_BN_CLICKED(IDC_CHECK_LAYER6, OnCheckLayer6)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainOperationDlg message handlers

BOOL CMainOperationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i;
	CString showstr;
	// TODO: Add extra initialization here
	ShowWindow(SW_MAXIMIZE);
	this->m_LayerShowList.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	m_LayerShowList.SetExtendedStyle(m_LayerShowList.GetExtendedStyle()|LVS_EX_FLATSB|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	/*CImageList imgList;
	imgList.Create(1, 14, ILC_COLOR, 0, 0);
	
	list.SetImageList(&imgList, LVSIL_STATE);
	
	imgList.Detach();
	*/
	for (i=0; i<sizeof(s_reportItems)/sizeof(REPORT_ITEM); ++i)
	{
		m_LayerShowList.InsertColumn(i, s_reportItems[i].name, LVCFMT_LEFT, s_reportItems[i].width);
	}

	m_LayerShowList.SetRedraw(false);
    m_ListNum = 0;	
	for (i=0;i<LAYER_NUM_INITIAL;i++)
	{
		showstr.Format("%d",i+1);
		m_LayerShowList.InsertItem(i, showstr);
		showstr.Format("%.2f",0);		
		m_LayerShowList.SetItemText(i, INDEX_SHAKUAN, showstr);
		m_LayerShowList.SetItemText(i, INDEX_JIAODU, showstr);
		m_LayerShowList.SetItemText(i, INDEX_QITINGJIAO, showstr);
		m_LayerShowList.SetItemText(i, INDEX_ZHONGTINGJIAO, showstr);
		m_LayerShowList.SetItemText(i, INDEX_CISHU, showstr);
		m_LayerShowList.SetItemText(i, INDEX_WEIZHI, showstr);
	}
	m_LayerShowList.SetRedraw(TRUE);

//	showstr.Format("%.2f",1.2);		
//	m_LayerShowList.SetItemText(1, INDEX_QITINGJIAO, showstr);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainOperationDlg::OnCompute() 
{
	// TODO: Add your control notification handler code here
	
	int i;
	CString tempstr;
	UpdateLayerComputeData();

	for (i=0;i<6;i++)
	{
       if (m_intLayerCheck[i]==TRUE)
       {
		   switch (m_intLayerMethodSel[i])
		   {
		    case LAYER_METHOD_CIRCLE:
			   ComputeCircle(i,m_RadioMainAxeSpeedFactor,m_RadioWindRule);
			   break;
			case LAYER_METHOD_JIASHA:
			   break;
			case LAYER_METHOD_CROSS:
			   Compute_Cross(i,m_RadioMainAxeSpeedFactor,m_RadioWindRule);
			   break;
			default:
			   break;
		   }
       }
	}
}

void CMainOperationDlg::OnFirmShaWidth() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}

void CMainOperationDlg::OnFirmCrossangle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
}



void CMainOperationDlg::test()
{
	double daimeter = 500;
	double AxeLength = 5000;
	double angle     = 43.3;
	double stopangle = 344.3;
	double PI_value  = 3.1415926535;
	double sha_width = 100;
	double buff_len  = 360 ;
	int N;
	double ret ;
	CString tempstr;

    double temp ;
	temp = tan(PI_value*angle/180);
    ret = 2*AxeLength*temp+4*buff_len*temp+(PI_value*stopangle/180)*daimeter;

    N = (int)(ret/(PI_value*daimeter));

    double resultval = ret - ((double)N)*(PI_value*daimeter);
	tempstr.Format("%.3f",resultval);
	MessageBox(tempstr);
    resultval = sha_width/cos(PI_value*angle/180);
	//resultval = (daimeter*PI_value)/resultval;
	tempstr.Format("%.3f",resultval);
	//tempstr.Format("%d",(int)resultval);
	MessageBox(tempstr);
}

void CMainOperationDlg::OnAlter() 
{
	// TODO: Add your control notification handler code here
	m_DataSetNum++;

	if (m_DataSetNum>4)
	{
		m_DataSetNum = 0;
	}

	switch (m_DataSetNum)
	{
	   case 0:
         m_PipeDiameter    = 500;
		 m_BandageWidth    = 152;
		 m_CrossAngle      = 60;
		 m_LeftBuffLength  = 360;
		 m_RightBuffLength = 360;
		 m_PipeTotalLen    = 5000;
		 m_StartStopAngle  = 200;
		 m_EndStopAngle    = 200;
		 break;
	   case 1:
		 m_PipeDiameter    = 900;
		 m_BandageWidth    = 150;
		 m_CrossAngle      = 58;
		 m_LeftBuffLength  = 360;
		 m_RightBuffLength = 360;
		 m_PipeTotalLen    = 12000;
		 m_StartStopAngle  = 200;
		 m_EndStopAngle    = 200;
         break;
	   case 2:
		 m_PipeDiameter    = 800;
		 m_BandageWidth    = 200;
		 m_CrossAngle      = 60;
		 m_LeftBuffLength  = 360;
		 m_RightBuffLength = 360;
		 m_PipeTotalLen    = 12000;
		 m_StartStopAngle  = 200;
		 m_EndStopAngle    = 200;
		 break;
        case 3:
		 m_PipeDiameter    = 1200;
		 m_BandageWidth    = 200;
		 m_CrossAngle      = 65;
		 m_LeftBuffLength  = 0;
		 m_RightBuffLength = 0;
		 m_PipeTotalLen    = 12000;
		 m_StartStopAngle  = 200;
		 m_EndStopAngle    = 200;
		 break;
	   default:
		 break;
	}
	UpdateData(false);
}

void CMainOperationDlg::OnRun() 
{
	// TODO: Add your control notification handler code here
	if (m_ListNum<1)
	{
		MessageBox(_T("请添加缠绕任务"));
	}
	else
	{
		CWorkMonitorDlg dlg;
		dlg.m_lpOpDlg = this;
	    dlg.DoModal();
	}

}



void CMainOperationDlg::Compute_Cross(int index,int MainAxeSpeedFactor,int ComputeMethod)
{
	double temp_double;
	double arc_angle,tempTingAngle;
	double ret;
	double circleLen,Vertical_Len;
	int N,Ntemp;
	CString tempstr;
	double tt;

    UpdateLayerComputeData();
	arc_angle = PI_VALUE*m_CrossAngle/180;
    circleLen = PI_VALUE*m_PipeDiameter; 
	//Vertical_Len = m_BandageWidth/sin(arc_angle);
	Vertical_Len = m_BandageWidth;
	switch (ComputeMethod)
	{
	   case COMPUTE_METHOD_FIRM_ANGLE:
           temp_double = circleLen/(tan(PI_VALUE*m_CrossAngle/180)*(Vertical_Len));
           N = (int)temp_double;
           Vertical_Len = circleLen/(tan(PI_VALUE*m_CrossAngle/180)*((double)N));
		   tt = m_CrossAngle;
		   arc_angle = PI_VALUE*m_CrossAngle/180;
		   break;
	   case COMPUTE_METHOD_FIRM_WIDTH:
	   default:
		   temp_double = circleLen/(tan(PI_VALUE*m_CrossAngle/180));
		   temp_double = temp_double/Vertical_Len;
		   N = (int)temp_double;
           N = N+1;
		   temp_double = circleLen/(((double)N)*Vertical_Len);
		   ret = atan(temp_double);
	       tt = ret*180/PI_VALUE;
		   arc_angle = ret;
		   break;
	}



	double totalLen = m_fLayerEndPos[index] - m_fLayerStartPos[index];
	if (totalLen<0)
	{
		totalLen = totalLen*(-1);
	}
    
  //  totalLen -= m_LeftBuffLength;
  //  totalLen -= m_RightBuffLength;

    temp_double = 2*tan(arc_angle)*totalLen + 2*tan(arc_angle)*2*m_LeftBuffLength + 
		2*tan(arc_angle)*2*m_RightBuffLength + m_BandageWidth/cos(arc_angle);
    

	temp_double = 2*tan(arc_angle)*totalLen + 2*tan(arc_angle)*2*m_LeftBuffLength + 
		2*tan(arc_angle)*2*m_LeftBuffLength - m_BandageWidth*tan(arc_angle);
   // temp_double = 2*tan(arc_angle)*totalLen + 2*tan(arc_angle)*2*m_LeftBuffLength + 
   //		                                              m_BandageWidth/cos(arc_angle);



    temp_double = 2*totalLen*tan(arc_angle) + 4*m_LeftBuffLength*tan(arc_angle) 
		                                    + m_BandageWidth*tan(arc_angle);

    Ntemp = (int)(temp_double/circleLen);
    
    
	if (m_StartStopAngle<180)
	{
		tempTingAngle =(((double)(Ntemp+1)*circleLen)-temp_double)/(m_PipeDiameter);
        tempTingAngle= tempTingAngle*180/PI_VALUE;
	}
	else
	{
        tempTingAngle =(((double)(Ntemp+2)*circleLen)-temp_double)/(m_PipeDiameter);
		tempTingAngle= tempTingAngle*180/PI_VALUE;
	}




	m_fResultBandWidth[index] = Vertical_Len;
	m_fResultAngle[index] = tt;
	m_fResultStartAngle[index] = tempTingAngle;
	m_fResultStopAngle[index] = tempTingAngle;
	m_iResultLayerNum[index] = N*m_intLayerNumLayer[index];
    UpdateResultData(index);

}


void CMainOperationDlg::OnAddworktask() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(true);
	int i;
	UpdateLayerComputeData();
	CString tmpstr;
    m_LayerShowList.SetRedraw(false);
	for (i=0;i<6;i++)
	{

       if (m_intLayerCheck[i]==TRUE)
       {		   
		   if (m_ListNum>=LAYER_NUM_INITIAL)
		   {			   
			   m_ListNum = 0;
			   tmpstr.Format("%d",m_ListNum+1);
			   m_LayerShowList.InsertItem(m_ListNum, tmpstr);	           
		   }
		   switch (m_intLayerMethodSel[i])
		   {
		   case LAYER_METHOD_CIRCLE:
			   m_LayerShowList.SetItemText(m_ListNum, INDEX_WINDMETHOD, _T("环向"));
			   break;
		   case LAYER_METHOD_JIASHA:
			   m_LayerShowList.SetItemText(m_ListNum, INDEX_WINDMETHOD, _T("加沙"));
			   break;
		   case LAYER_METHOD_CROSS:
			   m_LayerShowList.SetItemText(m_ListNum, INDEX_WINDMETHOD, _T("交叉"));
			   break;
		   default:
			   break;
		   }
      
	       tmpstr.Format("%d",m_iResultLayerNum[i]);
	       m_LayerShowList.SetItemText(m_ListNum,INDEX_CISHU,tmpstr);
	       tmpstr.Format("%.2f",m_fResultStopAngle[i]);
	       m_LayerShowList.SetItemText(m_ListNum,INDEX_ZHONGTINGJIAO,tmpstr);
	       tmpstr.Format("%.2f",m_fResultStartAngle[i]);
	       m_LayerShowList.SetItemText(m_ListNum,INDEX_QITINGJIAO,tmpstr);
	       tmpstr.Format("%.2f",m_fResultAngle[i]);
	       m_LayerShowList.SetItemText(m_ListNum,INDEX_JIAODU,tmpstr);
	       tmpstr.Format("%.2f",m_fResultBandWidth[i]);
	       m_LayerShowList.SetItemText(m_ListNum,INDEX_SHAKUAN,tmpstr); 
	       m_WindTask[m_ListNum].m_crossAngle     = m_fResultAngle[i];
	       m_WindTask[m_ListNum].m_EndStopAngle   = m_fResultStopAngle[i];
	       m_WindTask[m_ListNum].m_LayerNum       = m_iResultLayerNum[i];
	       m_WindTask[m_ListNum].m_LayerTaskIndex = m_ListNum;
	       m_WindTask[m_ListNum].m_leftBuffLen    = m_LeftBuffLength;
	       m_WindTask[m_ListNum].m_PipeDiam       = m_PipeDiameter;
	       m_WindTask[m_ListNum].m_rightBuffLen   = m_RightBuffLength;
	       m_WindTask[m_ListNum].m_shaWidth       = m_fResultBandWidth[i];
	       m_WindTask[m_ListNum].m_StartPos       = m_fLayerStartPos[i];
	       m_WindTask[m_ListNum].m_StopPos        = m_fLayerEndPos[i];
	       m_WindTask[m_ListNum].m_StartStopAngle = m_fResultStartAngle[i];
	       m_WindTask[m_ListNum].m_WorkType       = m_intLayerMethodSel[i];

           switch (m_RadioMainAxeSpeedFactor)
           {
		     case 0:
				 m_WindTask[m_ListNum].m_mainAxeRatio   =  this->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_1;
			   break;
             case 1:
				 m_WindTask[m_ListNum].m_mainAxeRatio   =  this->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_2;
			   break;
			 case 2:
				 m_WindTask[m_ListNum].m_mainAxeRatio   =  this->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_3;
			   break;
			 case 3:
				 m_WindTask[m_ListNum].m_mainAxeRatio   =  this->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_4;
			   break;
			 case 4:
				 m_WindTask[m_ListNum].m_mainAxeRatio   =  this->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_5;
			   break;
			 case 5:
				 m_WindTask[m_ListNum].m_mainAxeRatio   =  this->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_6;
			   break;
			 default:
				 m_WindTask[m_ListNum].m_mainAxeRatio   =  this->m_lpMainDlg->m_Gsysparam.m_fMainAxeLevelFactor_1;
			   break;
           }  
	       m_ListNum++;
	   }

	}
    m_LayerShowList.SetRedraw(TRUE);
	m_WindTaskNum = m_ListNum;
}


/*****************************************************
1：
tga = 主轴周长/纱宽

2：
1/cosa = 主轴周长/纱宽  
*****************************************************/

void CMainOperationDlg::ComputeCircle(int index,int MainAxeSpeedFactor,int ComputeMethod)
{
	double arc_angle;
	double circleLen,Vertical_Len;
	int N;
	CString tempstr;
	
	circleLen = PI_VALUE*m_PipeDiameter; 
	//Vertical_Len = m_BandageWidth/sin(arc_angle);
	Vertical_Len = m_BandageWidth;  // 纱片宽度	
	N = 1;
	switch (ComputeMethod)
	{
	   case COMPUTE_METHOD_FIRM_WIDTH:
		   arc_angle = acos(m_BandageWidth/circleLen);
	       arc_angle = atan(circleLen/m_BandageWidth);
		   Vertical_Len = m_BandageWidth;
		   break;
	   case COMPUTE_METHOD_FIRM_ANGLE:
		   arc_angle = m_CrossAngle*PI_VALUE/180;
           Vertical_Len = cos(arc_angle)*circleLen;
           Vertical_Len = circleLen/tan(arc_angle);
		   break;
	   default:
		   arc_angle = acos(m_BandageWidth/circleLen);
		   arc_angle = atan(circleLen/m_BandageWidth);
		   Vertical_Len = m_BandageWidth;
		   break;
	}

	double tt = arc_angle*180/PI_VALUE;
	tempstr.Format("%.3f",tt);
	m_fResultBandWidth[index] = Vertical_Len;
	m_fResultAngle[index] = tt;
	m_fResultStartAngle[index] = m_StartStopAngle;
	m_fResultStopAngle[index] = m_EndStopAngle;
	m_iResultLayerNum[index] = N*m_intLayerNumLayer[index];
    UpdateResultData(index);
}

void CMainOperationDlg::OnCheckLayer1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_CheckLayer1)
	{
		if (m_WindMethod_Layer1==-1)
		{
			m_WindMethod_Layer1 = 0;
		}
		
	}
	
	UpdateData(false);
}

void CMainOperationDlg::OnCheckLayer2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_CheckLayer2)
	{
		if (m_WindMethod_Layer2==-1)
		{
			m_WindMethod_Layer2 = 0;
		}
		
	}
	UpdateData(false);
}

void CMainOperationDlg::OnCheckLayer3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_CheckLayer3)
	{
		if (m_WindMethod_Layer3==-1)
		{
			m_WindMethod_Layer3 = 0;
		}
		
	}	
	UpdateData(false);
}

void CMainOperationDlg::OnCheckLayer4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_CheckLayer4)
	{
		if (m_WindMethod_Layer4==-1)
		{
			m_WindMethod_Layer4 = 0;
		}
		
	}
	UpdateData(false);
}

void CMainOperationDlg::OnCheckLayer5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_CheckLayer5)
	{
		if (m_WindMethod_Layer5==-1)
		{
			m_WindMethod_Layer5 = 0;
		}
		
	}	
	UpdateData(false);	
}

void CMainOperationDlg::OnCheckLayer6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_CheckLayer6)
	{
		if (m_WindMethod_Layer6==-1)
		{
			m_WindMethod_Layer6 = 0;
		}
	}
	UpdateData(false);
}

void CMainOperationDlg::UpdateLayerComputeData()
{
     UpdateData(true);
	/*
	 int m_intLayerNumLayer[6];
	 double m_fLayerEndPos[6];
	 double m_fLayerStartPos[6];
	 int m_intLayerMethodSel[6];
	 int m_intLayerCheck[6];
    */

     m_intLayerCheck[0] = m_CheckLayer1;
     m_intLayerCheck[1] = m_CheckLayer2;
	 m_intLayerCheck[2] = m_CheckLayer3;
	 m_intLayerCheck[3] = m_CheckLayer4;
	 m_intLayerCheck[4] = m_CheckLayer5;
	 m_intLayerCheck[5] = m_CheckLayer6;


     m_intLayerMethodSel[0] = m_WindMethod_Layer1;
     m_intLayerMethodSel[1] = m_WindMethod_Layer2;
     m_intLayerMethodSel[2] = m_WindMethod_Layer3;
     m_intLayerMethodSel[3] = m_WindMethod_Layer4;
     m_intLayerMethodSel[4] = m_WindMethod_Layer5;
     m_intLayerMethodSel[5] = m_WindMethod_Layer6;

     m_fLayerStartPos[0] = m_StartPosLayer1;
     m_fLayerStartPos[1] = m_StartPosLayer2;
     m_fLayerStartPos[2] = m_StartPosLayer3;
     m_fLayerStartPos[3] = m_StartPosLayer4;
     m_fLayerStartPos[4] = m_StartPosLayer5;
     m_fLayerStartPos[5] = m_StartPosLayer6;

     m_fLayerEndPos[0] = m_EndPosLayer1;
     m_fLayerEndPos[1] = m_EndPosLayer2;
     m_fLayerEndPos[2] = m_EndPosLayer3;
     m_fLayerEndPos[3] = m_EndPosLayer4;
     m_fLayerEndPos[4] = m_EndPosLayer5;
     m_fLayerEndPos[5] = m_EndPosLayer6;

     m_intLayerNumLayer[0] = m_TaskLayerNum_L1;
     m_intLayerNumLayer[1] = m_TaskLayerNum_L2;
	 m_intLayerNumLayer[2] = m_TaskLayerNum_L3;
	 m_intLayerNumLayer[3] = m_TaskLayerNum_L4;
	 m_intLayerNumLayer[4] = m_TaskLayerNum_L5;
	 m_intLayerNumLayer[5] = m_TaskLayerNum_L6;

}

void CMainOperationDlg::UpdateResultData(int index)
{
	switch (index)
	{
	case 0:
		m_ShaWidthShow_Layer1     = m_fResultBandWidth[index];
		m_CrossShowLayer1         = m_fResultAngle[index];
		m_QiTingJiaoShow_Layer1   = m_fResultStartAngle[index];
		m_ZhongTingJiaoShowLayer1 = m_fResultStopAngle[index];
		m_ShowCishuLayer1         = m_iResultLayerNum[index];
		break;
	case 1:
		m_ShaWidthShow_Layer2     = m_fResultBandWidth[index];
		m_CrossShowLayer2         = m_fResultAngle[index];
		m_QiTingJiaoShow_Layer2   = m_fResultStartAngle[index];
		m_ZhongTingJiaoShowLayer2 = m_fResultStopAngle[index];
		m_ShowCishuLayer2         = m_iResultLayerNum[index];
		break;
	case 2:
		m_ShaWidthShow_Layer3     = m_fResultBandWidth[index];
		m_CrossShowLayer3         = m_fResultAngle[index];
		m_QiTingJiaoShow_Layer3   = m_fResultStartAngle[index];
		m_ZhongTingJiaoShowLayer3 = m_fResultStopAngle[index];
		m_ShowCishuLayer3         = m_iResultLayerNum[index];
		break;
	case 3:
		m_ShaWidthShow_Layer4     = m_fResultBandWidth[index];
		m_CrossShowLayer4         = m_fResultAngle[index];
		m_QiTingJiaoShow_Layer4   = m_fResultStartAngle[index];
		m_ZhongTingJiaoShowLayer4 = m_fResultStopAngle[index];
		m_ShowCishuLayer4         = m_iResultLayerNum[index];
		break;
	case 4:
		m_ShaWidthShow_Layer5     = m_fResultBandWidth[index];
		m_CrossShowLayer5         = m_fResultAngle[index];
		m_QiTingJiaoShow_Layer5   = m_fResultStartAngle[index];
		m_ZhongTingJiaoShowLayer5 = m_fResultStopAngle[index];
		m_ShowCishuLayer5         = m_iResultLayerNum[index];
		break;
	case 5:
		m_ShaWidthShow_Layer6     = m_fResultBandWidth[index];
		m_CrossShowLayer6         = m_fResultAngle[index];
		m_QiTingJiaoShow_Layer6   = m_fResultStartAngle[index];
		m_ZhongTingJiaoShowLayer6 = m_fResultStopAngle[index];
		m_ShowCishuLayer6         = m_iResultLayerNum[index];
		break;
	default:
		break;
	}
    UpdateData(false);

}

void CMainOperationDlg::AddOneTask(int index)
{
   ;
}

void CMainOperationDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	MessageBox("aa");
}
