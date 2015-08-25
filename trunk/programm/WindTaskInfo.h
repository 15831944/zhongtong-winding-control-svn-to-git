// WindTaskInfo.h: interface for the CWindTaskInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDTASKINFO_H__7EBB4EF3_6CFA_4039_AE13_178E2042D6C7__INCLUDED_)
#define AFX_WINDTASKINFO_H__7EBB4EF3_6CFA_4039_AE13_178E2042D6C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWindTaskInfo  
{
public:
	double m_mainAxeRatio;
	int m_WorkType;
	int m_LayerNum;
	int m_LayerTaskIndex;
	double m_EndStopAngle;
	double m_StartStopAngle;
	double m_StopPos;
	double m_StartPos;
	double m_rightBuffLen;
	double m_leftBuffLen;
	double m_crossAngle;
	double m_shaWidth;
	double m_PipeDiam;
	CWindTaskInfo* lp_next;
	CWindTaskInfo* lp_last;
	CWindTaskInfo();
	virtual ~CWindTaskInfo();

};

#endif // !defined(AFX_WINDTASKINFO_H__7EBB4EF3_6CFA_4039_AE13_178E2042D6C7__INCLUDED_)
