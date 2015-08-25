#if !defined(AFX_EDITEX_H__60A28AC7_70C6_4EEC_8A10_DF443B022371__INCLUDED_)
#define AFX_EDITEX_H__60A28AC7_70C6_4EEC_8A10_DF443B022371__INCLUDED_


#ifndef _EDITEX_H_
#define _EDITEX_H_

#include "StdAfx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditEx window

class CEditEx : public CEdit
{
// Construction
public:
	CEditEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG


	// This function is invoked when the edit box is lost its focus.
    // When the focus is lost the Text in this edit box is placed as the List
    // control text of class CListCtrlEx
    void OnKillFocus( CWnd* pNewWnd_i );


	DECLARE_MESSAGE_MAP()
};



#endif // #ifndef _EDITEX_H_


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITEX_H__60A28AC7_70C6_4EEC_8A10_DF443B022371__INCLUDED_)
