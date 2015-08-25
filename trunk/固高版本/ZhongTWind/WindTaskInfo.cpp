// WindTaskInfo.cpp: implementation of the CWindTaskInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZhongTWind.h"
#include "WindTaskInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWindTaskInfo::CWindTaskInfo()
{

}

CWindTaskInfo::~CWindTaskInfo()
{

}

void CWindTaskInfo::TaskInfoCpyFrom(CWindTaskInfo src)
{
	 m_MainAxeSpeedFactor = src.m_MainAxeSpeedFactor;  //主轴档位速度
	 m_WindMethod = src.m_WindMethod;              //缠绕方式
	 m_LayerNum = src.m_LayerNum;                //缠绕层数	
	 m_EndStopAngle = src.m_EndStopAngle;         //终停角
	 m_StartStopAngle = src.m_StartStopAngle;       //起停角
	 m_EndPos = src.m_EndPos;               //终止位置
	 m_StartPos = src.m_StartPos;             //起始位置
	 m_BuffLen = src.m_BuffLen;              //缓冲区长度 
	 m_crossAngle = src.m_crossAngle;           //缠绕角
	 m_shaWidth = src.m_shaWidth;             //纱/砂宽
	 m_PipeDiam = src.m_PipeDiam;             //管道直径

}
