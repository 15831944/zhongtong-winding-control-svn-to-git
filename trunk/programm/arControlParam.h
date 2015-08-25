// arControlParam.h: interface for the CarControlParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCONTROLPARAM_H__A55E390A_F94D_481E_BED1_824E6926DCD2__INCLUDED_)
#define AFX_ARCONTROLPARAM_H__A55E390A_F94D_481E_BED1_824E6926DCD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CarControlParam  
{
public:
	double m_MaxSpeed;
	double m_iniSpeed;
	double m_CurSpeed;
	double m_ObjSpeed;
	double m_a;
	double m_pos;
	int m_dir;
	CarControlParam();
	virtual ~CarControlParam();

};

#endif // !defined(AFX_ARCONTROLPARAM_H__A55E390A_F94D_481E_BED1_824E6926DCD2__INCLUDED_)
