// SysSetParam.h: interface for the SysSetParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSSETPARAM_H__80FD9BCA_813B_4AEA_981D_021972216BB2__INCLUDED_)
#define AFX_SYSSETPARAM_H__80FD9BCA_813B_4AEA_981D_021972216BB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SysSetParam  
{
public:
	
	double m_fASpeedFactor;
	double m_fAspeed;
	double m_fZeroLuoju;
	double m_fCarDistancePerRound;
	double m_fCarSpeedDownP;
	double m_fMainAxeLevelFactor_6;
	double m_fMainAxeLevelFactor_5;
	double m_fMainAxeLevelFactor_4;
	double m_fMainAxeLevelFactor_3;
	double m_fMainAxeLevelFactor_2;
	double m_fMainAxeLevelFactor_1;
	double m_fCarMaxSpeed;
	double m_fMainAxeMaxSpeed;
	int m_iCarPulses;
	int m_iMainAxePulses;
	SysSetParam();
	virtual ~SysSetParam();

};

#endif // !defined(AFX_SYSSETPARAM_H__80FD9BCA_813B_4AEA_981D_021972216BB2__INCLUDED_)
