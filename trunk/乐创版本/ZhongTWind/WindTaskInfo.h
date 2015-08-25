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

	double  m_MainAxeSpeedFactor;  //���ᵵλ�ٶ�
	int m_WindMethod;              //���Ʒ�ʽ  �����ɰ����
	int m_LayerNum;                //���Ʋ���
	int m_LayerTaskIndex;          //
	double m_EndStopAngle;         //��ͣ��
	double m_StartStopAngle;       //��ͣ��
	double m_EndPos;               //��ֹλ��
	double m_StartPos;             //��ʼλ��
	double m_BuffLen;              //���������� 
	double m_crossAngle;           //���ƽ�
	double m_shaWidth;             //ɴ/ɰ��
	double m_PipeDiam;             //�ܵ�ֱ��
	CWindTaskInfo* lp_next;
	CWindTaskInfo* lp_last;
};

#endif // !defined(AFX_WINDTASKINFO_H__E9FBFA7A_E26D_4157_96AA_CE3CD0A68D84__INCLUDED_)
