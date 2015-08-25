#ifndef __GLOBAL__H__
#define __GLOBAL__H__

#include "Mmsystem.h"
#include "Mpc2810.h"

extern long g_iMMTimerID;
extern long g_iAccuracy;
extern int nCtrl;

extern void InitMMTimer();
extern void KillMMTimer(UINT nID);

#endif