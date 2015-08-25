// AxeCtrl.h: interface for the CAxeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXECTRL_H__5DAE7935_9DE5_4B7D_8F1F_1FAA37C2B950__INCLUDED_)
#define AFX_AXECTRL_H__5DAE7935_9DE5_4B7D_8F1F_1FAA37C2B950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define OUTMODE_PULSE_DIRECTION 0x000001
#define OUTMODE_PULSE_DUE       0x000000

#define DIR_POS         1
#define DIR_NEG        -1

class CAxeCtrl  
{
public:
	int m_runningStatus;
	int m_SpeedMax;
	int m_moveDirect;
	int m_AxeNum;
	int Axe_Initial(void);
	int m_SpeedHigh;
	int m_SpeedLow;
	int m_SpeedUpDownStyle;
	int m_constSpeed;
	int m_OutMode;
	CAxeCtrl();
	virtual ~CAxeCtrl();

};

#endif // !defined(AFX_AXECTRL_H__5DAE7935_9DE5_4B7D_8F1F_1FAA37C2B950__INCLUDED_)
