// ZhongTWind.h : main header file for the ZHONGTWIND application
//

#if !defined(AFX_ZHONGTWIND_H__DF3C6317_1B69_40EE_90EB_3A51EB8E3B2D__INCLUDED_)
#define AFX_ZHONGTWIND_H__DF3C6317_1B69_40EE_90EB_3A51EB8E3B2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "GenParam.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CZhongTWindApp:
// See ZhongTWind.cpp for the implementation of this class
//

class CZhongTWindApp : public CWinApp
{
public:
	void ProgramInitial(void);
	GenParam GlobalParam;
	CZhongTWindApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZhongTWindApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZhongTWindApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZHONGTWIND_H__DF3C6317_1B69_40EE_90EB_3A51EB8E3B2D__INCLUDED_)
