#if !defined(AFX_MYBUTTON_H__0F4E3C57_D09F_42BA_93A6_C887FDBA1AC3__INCLUDED_)
#define AFX_MYBUTTON_H__0F4E3C57_D09F_42BA_93A6_C887FDBA1AC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyButton window

class CMyButton : public CButton
{
// Construction
public:
	CMyButton();

// Attributes
public:

// Operations
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG


private:
    int         m_Style;    //��ť��״��0-������1-��ǰ��2-���£�3-������
    BOOL        b_InRect;           //�������־
    CString     m_strText;          //��ť����
    COLORREF    m_ForeColor;        //�ı���ɫ
    COLORREF    m_BackColor;        //����ɫ
    COLORREF    m_LockForeColor;    //������ť��������ɫ
    CRect       m_ButRect;          //��ť�ߴ�
    CFont*      p_Font;             //����
	
    void  DrawButton(CDC *pDC);     //�������İ�ť
	// �ӿں���
public:
    void SetText(CString str);
    void SetForeColor(COLORREF color);      //�����ı���ɫ
    void SetBkColor(COLORREF color);        //���ñ�����ɫ
    void SetTextFont(int FontHight,LPCTSTR FontName);   //��������

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__0F4E3C57_D09F_42BA_93A6_C887FDBA1AC3__INCLUDED_)
