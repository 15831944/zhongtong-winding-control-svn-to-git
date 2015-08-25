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

	double	m_PipeTotalLen;             //�ܵ��ܳ�
	double	m_BandageWidth;             //ɴ��
	double	m_SandWidth;                //ɰ��
	double	m_CrossAngle;               //���ƽ�
	double	m_BuffLength;               //����������
	double	m_PipeDiameter;             //�ܵ�ֱ��
	double	m_SandRate;                 //��ɰ�ٱ�
	double	m_StartStopAngle;           //��ͣ��
	double	m_StopStopAngle;            //��ͣ��
	int		m_RadioMainAxeSpeedFactor;  //���ᵵλ
	double  m_MainAxeSpeedFactor;       //���ᵵλ�ٶ�
	int		m_RadioWindRule;            //���ƹ���
	int		m_RadioCutOffPoints;        //�е㷽ʽ
//////////////////////////////////////////////////////////////////////////
// require info
    int     m_WindMethod;               //���Ʒ�ʽ ���� ��ɰ ����
	double  m_startPos;                 //��ʼλ��
	double  m_endPos;                   //��ֹλ��
	int     m_windLayerNum;             //���Ʋ���
	int     m_WorkMethod;               //������ʽ ���� �ֶ�
//////////////////////////////////////////////////////////////////////////

    double  m_CResultBandageWidth;
	double  m_CResultCrossAngle;
	double  m_CResultStartAngle;
	double  m_CResultEndAngle;
	int  m_CResultWindNum;



};

#endif // !defined(AFX_TASKCOMPUTEPARAM_H__C68447D3_A0DC_4774_8CE8_5622CC42CD6C__INCLUDED_)
