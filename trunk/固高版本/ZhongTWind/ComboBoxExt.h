#if !defined(AFX_COMBOBOXEXT_H__725E02C9_6C15_4438_86E7_D0B87AB71454__INCLUDED_)
#define AFX_COMBOBOXEXT_H__725E02C9_6C15_4438_86E7_D0B87AB71454__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxExt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt window

#ifndef _COMBOBOXEXT_H_
#define _COMBOBOXEXT_H_


class CComboBoxExt : public CComboBox
{
// Construction
public:
	CComboBoxExt();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxExt)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboBoxExt();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxExt)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

    // Used for setting the text in the combo
    // as the text in the list control when
    //focus is lost
    void OnKillFocusCombo();
    // Used for setting the text in the combo
    // as the text in the list control when
    //selection is changed is lost
    void OnSelChangeCombo();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // ifndef _COMBOBOXEXT_H_


#endif // !defined(AFX_COMBOBOXEXT_H__725E02C9_6C15_4438_86E7_D0B87AB71454__INCLUDED_)


