#if !defined(AFX_LISTCTRLEX_H__6D6A30E4_36B5_4B0D_91E7_E8CBAB0E363C__INCLUDED_)
#define AFX_LISTCTRLEX_H__6D6A30E4_36B5_4B0D_91E7_E8CBAB0E363C__INCLUDED_

#ifndef _LISTCTRLEX_H_
#define _LISTCTRLEX_H_

#include "stdafx.h"
#include <afxtempl.h>
#include "ListCtrlCommon.h"

class CEditEx;
class CComboBoxExt;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window

class CListCtrlEx : public CListCtrl
{
// Construction
public:
	CListCtrlEx();
	void RemoveAllColoredRows();
    // Sets  editable
    void SetEditBox(int nItemIndex_i,
		int nSubItemIndex_i);
    // This function will set combo box in a particular row with values
    void SetComboBox(int nRow_i,
		int nCol_i,
		CStringArray& csarValues_i);
    void Clear(int nCoulmn_i);
    // Adding colored row
    void AddColoredRow(int nItemIndex,
		COLORREF colTextColor = RGB(0, 0, 0),
		COLORREF colBkColor =   RGB(255, 255, 255));
    void GetCellInfo(int& nRow_o, int& nCol_o);

private: 
    bool SearchForColoredItem(int nItem, int& nItemIndex);
	// To keep track the value of the selected row for editing
    int mnCurrentRowNo;
    // To keep track the value of the selected column for editing
    int  mnCurrentColumnNo;
    // The edit box to be displayed
    CEditEx* mpeditListEdit;
    // The combo box to de displayed
    CComboBoxExt* mpcomboListCombo;
    // This variable will containing the editable columns
    CArray<SEditableCell, SEditableCell> mastEditableItems;
    // This variable is used to add the rows those should be
    // colored.
    CArray<SColoredRow, SColoredRow> masColoredRows;
    // This variable will have the rows which have combo boxes.
    CArray<SComboCell, SComboCell> mastComboItems;
	
    int OnToolHitTest(CPoint ptToolPoint, TOOLINFO* pToolInfo) const;
	int CellRectFromPoint(CPoint& point,
		RECT* cellrect,
		int* col) const;
    void PreSubclassWindow();
	BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	
    void AddComboStrings(CString& csValues_o,
		CStringArray& csarValues_i);
    void Tokenize(const CString& csToken_i,
		WCHAR* pwcDelimit_i,
		CStringArray& csarData_o);
    // Hides edit box or combo box while scrolling
    void OnVScroll(UINT nSBCode_i,
		UINT nPos_i,
		CScrollBar* pScrollBar_i);
    // Hides edit box or combo box while scrolling
    void OnHScroll(UINT nSBCode_i,
		UINT nPos_i,
		CScrollBar* pScrollBar_i);
    // Show edit box / combo box while double clicking on a cell
    void OnLButtonDown(UINT nFlags_i, CPoint Point_i);
    // Show edit box if the selected column is set for combo box
    void OnRButtonDown(UINT nFlags_i, CPoint Point_i);
    // To show the text color for individual rows
    void OnCustomDraw(NMHDR* pNMHDR_i, LRESULT* pResult_i);
    // Hides the edit box
    void HideEditBox();
    // Adds column Names
    // This function will Display a combo box in the Value column of the List
    void DisplayComboBox(CRect& crRect_i, CString csValues_i);
    // This function will Display an edit box in the Value column of the List
    void DisplayEditBox(CRect& crRect_i);
    // Check whether a column is editable
    bool IsEditable(int nItemIndex_i, int nSubItemIndex_i);
    // This function will check whether a combo box is to be displayed in the
    // selected row
    bool IsComboSet(int nRow_i, int nCol_i, CString& csValue_o);


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // #ifndef _LISTCTRLEX_H_

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLEX_H__6D6A30E4_36B5_4B0D_91E7_E8CBAB0E363C__INCLUDED_)
