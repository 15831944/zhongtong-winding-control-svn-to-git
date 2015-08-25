// TaskComputeParam.h: interface for the TaskComputeParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKCOMPUTEPARAM_H__C68447D3_A0DC_4774_8CE8_5622CC42CD6C__INCLUDED_)
#define AFX_TASKCOMPUTEPARAM_H__C68447D3_A0DC_4774_8CE8_5622CC42CD6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TaskComputeParam  
{
public:
	TaskComputeParam();
	virtual ~TaskComputeParam();
//////////////////////////////////////////////////////////////////////////
//	Basic info

	double	m_PipeTotalLen;             //管道总长
	double	m_BandageWidth;             //纱宽
	double	m_SandWidth;                //砂宽
	double	m_CrossAngle;               //缠绕角
	double	m_BuffLength;               //缓冲区长度
	double	m_PipeDiameter;             //管道直径
	double	m_SandRate;                 //加砂速比
	double	m_StartStopAngle;           //起停角
	double	m_StopStopAngle;            //终停角
	int		m_RadioMainAxeSpeedFactor;  //主轴档位
	double  m_MainAxeSpeedFactor;       //主轴档位速度
	int		m_RadioWindRule;            //缠绕规则
	int		m_RadioCutOffPoints;        //切点方式
//////////////////////////////////////////////////////////////////////////
// require info
    int     m_WindMethod;               //缠绕方式 环向 加砂 交叉
	double  m_startPos;                 //起始位置
	double  m_endPos;                   //终止位置
	int     m_windLayerNum;             //缠绕层数
	int     m_WorkMethod;               //工作方式 连续 手动
//////////////////////////////////////////////////////////////////////////

    double  m_CResultBandageWidth;
	double  m_CResultCrossAngle;
	double  m_CResultStartAngle;
	double  m_CResultEndAngle;
	int  m_CResultWindNum;



};

#endif // !defined(AFX_TASKCOMPUTEPARAM_H__C68447D3_A0DC_4774_8CE8_5622CC42CD6C__INCLUDED_)
