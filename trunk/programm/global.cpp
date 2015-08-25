#include "StdAfx.h"
#include "global.h"

long g_iMMTimerID = 0;
long g_iAccuracy;
int nCtrl=0;
int flag=0;

int TestFunction()
{
    /*
	switch(flag) {
	case 0:
       set_maxspeed(1,10000);
	   set_maxspeed(2,10000);
	   set_maxspeed(3,10000);
	   set_maxspeed(4,10000);
       fast_pmove(1,10000);
		flag = 1;
		return 1;
	case 1:
		if((check_done(1)==1))
			return 1;
		flag = 2;
	case 2:
    	fast_pmove(2,10000);
		flag =3;
		return 1;
	case 3:
		if(check_done(2)==1)
			return 1;
		flag = 4;
		   	return 0;
	}
	*/
	return 1;
}

void PASCAL MMCallbackProc(UINT wTimerID, UINT msg,DWORD dwUser,DWORD dwl,DWORD dw2)
{
	
	if (nCtrl==1)
	{   
		if(TestFunction()!=0)
		{
		}
		else
		{
			   TestFunction();
			   flag = 0;
		}	
	}
}


void InitMMTimer()
{
	TIMECAPS tc;
	CString str;

	if(timeGetDevCaps(&tc,sizeof(TIMECAPS))==TIMERR_NOERROR)
	{
		g_iAccuracy=min(max(tc.wPeriodMin,1),tc.wPeriodMax);
		if(g_iAccuracy>1)
		{
			str.Format("系统多媒体定时器分辨率为%d",g_iAccuracy);
			AfxMessageBox(str);
			return;
		}
	}
	g_iMMTimerID = timeSetEvent(5,g_iAccuracy,(LPTIMECALLBACK)MMCallbackProc,NULL,TIME_PERIODIC);//参数1为定时精度单位毫秒
	if(g_iMMTimerID==0)
	{
		AfxMessageBox("系统多媒体定时器安装失败！");
		return;
	}
}

void KillMMTimer(UINT nID)
{
	if(nID!=0)
	{
		timeKillEvent(nID);
		timeEndPeriod(g_iAccuracy);
	}
	g_iMMTimerID=0;
}