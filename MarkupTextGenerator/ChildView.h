#pragma once
#include "OutputWindow.h"

class CChildView : public CWnd
{
public:
	CChildView();
	virtual ~CChildView();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	COLORREF CChildView::GetColor();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnButtonForeground();
	afx_msg void OnButtonBackground();
	afx_msg void OnChangeText();
	afx_msg void OnChangeSize();
	afx_msg void OnChBoxItalic();
	afx_msg void OnChBoxBold();
	afx_msg void OnRadioButton(UINT nID);
	afx_msg void OnCBoxFFamily();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
	
protected:
	CBrush         m_brBackground;
	COutputWindow  m_wndOutputWindow;
	CStatic        m_wndStaticText;
	CStatic        m_wndStaticSize;
	CEdit          m_wndEditText;
	CEdit          m_wndEditSize;
	CButton        m_wndChBoxItalic;
	CButton        m_wndChBoxBold;
	CButton        m_wndRadUnderline;
	CButton        m_wndRadStrikeThrough;
	CButton        m_wndRadNoLine;
	CButton        m_wndButForeground;
	CButton        m_wndButBackground;
	CComboBox      m_wndCBoxFontFamily;

	TextAttributes* m_pTextAttributes;
};