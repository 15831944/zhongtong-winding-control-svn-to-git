// ComboBoxExt.cpp : implementation file
//

#include "stdafx.h"
#include "ZhongTWind.h"
#include "ComboBoxExt.h"
#include "ListCtrlEx.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt

/**
* Default constructor
*
* @param       Nil
* @return      Nil
* @exception   Nil
* @see         Nil
* @since        1.0
* @serial      Nil
* @deprecated  Nil
*/


CComboBoxExt::CComboBoxExt()
{
}



/**
* Destructor
*
* @param       Nil
* @return      Nil
* @exception   Nil
* @see         Nil
* @since        1.0
* @serial      Nil
* @deprecated  Nil
 */
CComboBoxExt::~CComboBoxExt()
{
}


BEGIN_MESSAGE_MAP(CComboBoxExt, CComboBox)
    //{{AFX_MSG_MAP(CComboBoxExt)
    ON_CONTROL_REFLECT( CBN_KILLFOCUS, OnKillFocusCombo )
    ON_CONTROL_REFLECT( CBN_SELCHANGE, OnSelChangeCombo )
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxExt message handlers

/**
* This function will be invoked when the focus of the combobox is lost
* This function will read the current string in the combo box and will set as
* the list control string.
*
* @param       Nil
* @return      void
* @exception   Nil
* @see         Nil
* @since       1.0
* @serial      Nil
* @deprecated  Nil
*/
void CComboBoxExt::OnKillFocusCombo()
{
    CString csText = _T("");
    // Get the text
    GetWindowText(csText);
	// Set the text into the current  cell of the List Ctrl.
    CListCtrlEx* pList = static_cast<CListCtrlEx*>(GetParent());
    int nRow = -1;
    int nCol = -1;
    pList->GetCellInfo(nRow, nCol);
	// Set the text into the current editable cell of the List Ctrl.
    pList->SetItemText(nRow, nCol, csText);
    ShowWindow(SW_HIDE);
    PostMessage(WM_DESTROY);
    return;
}


void CComboBoxExt::OnSelChangeCombo()
{
    CString csText = _T("");
    // Get the text
    GetWindowText(csText);
	// Set the text into the current  cell of the List Ctrl.
    CListCtrlEx* pList = static_cast<CListCtrlEx*>(GetParent());
    int nRow = -1;
    int nCol = -1;
    pList->GetCellInfo(nRow, nCol);
	// Set the text into the current editable cell of the List Ctrl.
    pList->SetItemText(nRow, nCol, csText);
    ShowWindow(SW_HIDE);
    PostMessage(WM_DESTROY);
    return;
}