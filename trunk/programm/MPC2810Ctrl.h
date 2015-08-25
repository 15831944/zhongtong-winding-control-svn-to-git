// MPC2810Ctrl.h : main header file for the MPC2810CTRL application
//

#if !defined(AFX_MPC2810CTRL_H__F42C692F_312C_4B85_9207_B629ACB4849D__INCLUDED_)
#define AFX_MPC2810CTRL_H__F42C692F_312C_4B85_9207_B629ACB4849D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMPC2810CtrlApp:
// See MPC2810Ctrl.cpp for the implementation of this class
//

class CMPC2810CtrlApp : public CWinApp
{
public:
	CMPC2810CtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMPC2810CtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMPC2810CtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPC2810CTRL_H__F42C692F_312C_4B85_9207_B629ACB4849D__INCLUDED_)
