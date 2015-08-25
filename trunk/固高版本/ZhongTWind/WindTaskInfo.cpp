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
	 m_MainAxeSpeedFactor = src.m_MainAxeSpeedFactor;  //���ᵵλ�ٶ�
	 m_WindMethod = src.m_WindMethod;              //���Ʒ�ʽ
	 m_LayerNum = src.m_LayerNum;                //���Ʋ���	
	 m_EndStopAngle = src.m_EndStopAngle;         //��ͣ��
	 m_StartStopAngle = src.m_StartStopAngle;       //��ͣ��
	 m_EndPos = src.m_EndPos;               //��ֹλ��
	 m_StartPos = src.m_StartPos;             //��ʼλ��
	 m_BuffLen = src.m_BuffLen;              //���������� 
	 m_crossAngle = src.m_crossAngle;           //���ƽ�
	 m_shaWidth = src.m_shaWidth;             //ɴ/ɰ��
	 m_PipeDiam = src.m_PipeDiam;             //�ܵ�ֱ��

}
