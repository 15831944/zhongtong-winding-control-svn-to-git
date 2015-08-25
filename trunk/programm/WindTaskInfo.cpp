// WindTaskInfo.cpp: implementation of the CWindTaskInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MPC2810Ctrl.h"
#include "WindTaskInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWindTaskInfo::CWindTaskInfo()
{
  lp_next = NULL;
  lp_last = NULL;
}

CWindTaskInfo::~CWindTaskInfo()
{

}
