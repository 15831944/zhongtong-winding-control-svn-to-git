// AxeCtrl.cpp: implementation of the CAxeCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "AxeCtrl.h"
#include "mpc2810.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAxeCtrl::CAxeCtrl()
{

}

CAxeCtrl::~CAxeCtrl()
{

}

int CAxeCtrl::Axe_Initial()
{
   if (this->m_AxeNum<1)
   {
	   return -1;
   }
   set_outmode(this->m_AxeNum,this->m_OutMode,0);
   set_dir(m_AxeNum,m_moveDirect);
   enable_sd(m_AxeNum,0);
   enable_el(m_AxeNum,0);
   enable_org(m_AxeNum,0);
   enable_alm(m_AxeNum,0);
   set_encoder_mode(m_AxeNum,1,1,0); //±àÂëÆ÷ABÏà²î90 1±¶Æµ
   return 0;
}
