// GenParam.h: interface for the GenParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENPARAM_H__B85E2612_F6E6_4AE5_8717_2D5FF93B1360__INCLUDED_)
#define AFX_GENPARAM_H__B85E2612_F6E6_4AE5_8717_2D5FF93B1360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GenParam  
{
public:
	double m_fAccelerationFactor;
	double m_fAcceleration;
	double m_fZeroPitch;
	double m_fCarDistancePerRound;
	double m_fCarSpeedDownP;
	double m_fMainAxeLevelFactor[10];
	double m_fCarMaxSpeed;
	double m_fMainAxeMaxSpeed;
	int m_iCarPulses;
	int m_iMainAxePulses;
	GenParam();
	virtual ~GenParam();

};

#endif // !defined(AFX_GENPARAM_H__B85E2612_F6E6_4AE5_8717_2D5FF93B1360__INCLUDED_)
