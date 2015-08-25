// CarControlParam.h: interface for the CCarControlParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARCONTROLPARAM_H__F0D09CE9_89E5_4A8C_8839_1D273452FC4A__INCLUDED_)
#define AFX_CARCONTROLPARAM_H__F0D09CE9_89E5_4A8C_8839_1D273452FC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCarControlParam  
{
public:
	int m_dir;
	double m_pos;
	double m_a;
	double m_ObjSpeed;
	double m_CurSpeed;
	CCarControlParam();
	virtual ~CCarControlParam();

};

#endif // !defined(AFX_CARCONTROLPARAM_H__F0D09CE9_89E5_4A8C_8839_1D273452FC4A__INCLUDED_)
