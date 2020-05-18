#pragma once
#include <afxwin.h>

struct TextAttributes
{
	COLORREF      m_clrForeground;
	COLORREF      m_clrBackground;
	CString       m_strText;
	CString       m_strSize;
	CString       m_strFontFamily;
	int           m_nLineState;
	bool          m_bItalic;
	bool          m_bBold;
};

enum TextStates
{
	TEXT_NOLINE,
	TEXT_STRIKE_THROUGH,
	TEXT_UNDERLINE
};

class COutputWindow : public CStatic
{
public:

	COutputWindow();
	void SetTextAttributes(TextAttributes* textAttributes);
	void AttributesChanged();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);

	void ChangeFont();

protected:
	CFont           m_font;
	TextAttributes* m_pTextAttributes;
};