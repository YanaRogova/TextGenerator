#include "pch.h"
#include "OutputWindow.h"

BEGIN_MESSAGE_MAP(COutputWindow, CStatic)
	ON_WM_SIZE()
END_MESSAGE_MAP()

COutputWindow::COutputWindow()
{
	m_pTextAttributes = nullptr;
}

void COutputWindow::AttributesChanged()
{
	ChangeFont();
	CDC* pDC = GetDC();
	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(rect);
	rect.DeflateRect(1, 1, 1, 1);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));
	pDC->SelectObject(m_font);
	pDC->SetTextColor(m_pTextAttributes->m_clrForeground);
	pDC->SetBkColor(m_pTextAttributes->m_clrBackground);
	pDC->DrawText(m_pTextAttributes->m_strText, rect, DT_CENTER | DT_WORDBREAK);
}

void COutputWindow::ChangeFont()
{
	LOGFONT lf{
		_wtoi(m_pTextAttributes->m_strSize) * 3 / 2,
		0,
		0,
		0,
		m_pTextAttributes->m_bBold ? FW_BOLD : FW_NORMAL,
		m_pTextAttributes->m_bItalic,
		m_pTextAttributes->m_nLineState == TEXT_UNDERLINE,
		m_pTextAttributes->m_nLineState == TEXT_STRIKE_THROUGH,
		ANSI_CHARSET,
		OUT_STROKE_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE
	};

	wcscpy_s(lf.lfFaceName, m_pTextAttributes->m_strFontFamily);

	m_font.DeleteObject();
	m_font.CreateFontIndirectW(&lf);
}

void COutputWindow::SetTextAttributes(TextAttributes* textAttributes)
{
	m_pTextAttributes = textAttributes;
}

void COutputWindow::OnSize(UINT nType, int cx, int cy)
{
	if(m_pTextAttributes != nullptr)
		AttributesChanged();
}