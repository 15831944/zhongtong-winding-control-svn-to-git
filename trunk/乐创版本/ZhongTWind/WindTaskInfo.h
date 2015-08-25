// WindTaskInfo.h: interface for the CWindTaskInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDTASKINFO_H__E9FBFA7A_E26D_4157_96AA_CE3CD0A68D84__INCLUDED_)
#define AFX_WINDTASKINFO_H__E9FBFA7A_E26D_4157_96AA_CE3CD0A68D84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWindTaskInfo  
{
public:
	void TaskInfoCpyFrom(CWindTaskInfo src);
	CWindTaskInfo();
	virtual ~CWindTaskInfo();

	double  m_MainAxeSpeedFactor;  //主轴档位速度
	int m_WindMethod;              //缠绕方式  环向加砂交叉
	int m_LayerNum;                //缠绕层数
	int m_LayerTaskIndex;          //
	double m_EndStopAngle;         //终停角
	double m_StartStopAngle;       //起停角
	double m_EndPos;               //终止位置
	double m_StartPos;             //起始位置
	double m_BuffLen;              //缓冲区长度 
	double m_crossAngle;           //缠绕角
	double m_shaWidth;             //纱/砂宽
	double m_PipeDiam;             //管道直径
	CWindTaskInfo* lp_next;
	CWindTaskInfo* lp_last;
};

#endif // !defined(AFX_WINDTASKINFO_H__E9FBFA7A_E26D_4157_96AA_CE3CD0A68D84__INCLUDED_)
