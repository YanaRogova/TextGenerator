#include "pch.h"
#include "framework.h"
#include "MarkupTextGenerator.h"
#include "ChildView.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_OUTPUT_WINDOW     1300
#define ID_STATIC            1301
#define ID_EDIT_TEXT         1302
#define ID_EDIT_SIZE         1303
#define ID_CHBOX_ITALIC      1304
#define ID_CHBOX_BOLD        1305
#define ID_RADBUT_NOLINE     1306
#define ID_RADBUT_STRIKE     1307
#define ID_RADBUT_UND        1308
#define ID_BUT_FOREGROUND    1309
#define ID_BUT_BACKGROUND    1310
#define ID_CBOX_FFAMILY      1311
#define ID_EDIT_TEXTBLOCK    1312
#define ID_BUT_COPY          1313

CChildView::CChildView()
{
	m_brBackground.CreateSolidBrush(RGB(255, 255, 255));

	m_pTextAttributes = new TextAttributes();
	m_pTextAttributes->m_clrForeground = RGB(0, 0, 0);
	m_pTextAttributes->m_clrBackground = RGB(255, 255, 255);
	m_pTextAttributes->m_strText = L"";
	m_pTextAttributes->m_strSize = L"12";
	m_pTextAttributes->m_strFontFamily = L"Arial";
	m_pTextAttributes->m_nLineState = TEXT_NOLINE;
	m_pTextAttributes->m_bBold = false;
	m_pTextAttributes->m_bItalic = false;
}

CChildView::~CChildView()
{
	delete m_pTextAttributes;
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_COPY()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUT_FOREGROUND, OnButtonForeground)
	ON_COMMAND(ID_BUT_BACKGROUND, OnButtonBackground)
	ON_COMMAND(ID_CHBOX_ITALIC, OnChBoxItalic)
	ON_COMMAND(ID_CHBOX_BOLD, OnChBoxBold)
	ON_COMMAND(ID_BUT_COPY, OnButtonCopy)
	ON_EN_CHANGE(ID_EDIT_TEXT, OnChangeText)
	ON_EN_CHANGE(ID_EDIT_SIZE, OnChangeSize)
	ON_COMMAND_RANGE(ID_RADBUT_NOLINE, ID_RADBUT_UND, OnRadioButton)
	ON_CBN_SELENDOK(ID_CBOX_FFAMILY, OnCBoxFFamily)
END_MESSAGE_MAP()


BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	m_wndOutputWindow.Create(L"", WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER,
		CRect(10, 10, 600, 300), this, ID_OUTPUT_WINDOW);

	m_wndOutputWindow.SetTextAttributes(m_pTextAttributes);
	
	CString str;
	str.LoadString(IDS_STATIC_TEXT);
	m_wndStaticText.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(620, 0, 720, 20), this, ID_STATIC);

	m_wndEditText.Create(WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_TABSTOP | WS_BORDER,
		CRect(620, 20, 820, 100), this, ID_EDIT_TEXT);


	str.LoadString(IDS_STATIC_SIZE);
	m_wndStaticSize.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(620, 105, 720, 125), this, ID_STATIC);

	m_wndEditSize.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_TABSTOP | WS_BORDER,
		CRect(725, 102, 820, 122), this, ID_EDIT_SIZE);
	

	str.LoadString(IDS_CHBOX_ITALIC);
	m_wndChBoxItalic.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTOCHECKBOX,
		CRect(620, 130, 780, 150), this, ID_CHBOX_ITALIC);

	str.LoadString(IDS_CHBOX_BOLD);
	m_wndChBoxBold.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTOCHECKBOX,
		CRect(620, 155, 780, 175), this, ID_CHBOX_BOLD);


	str.LoadString(IDS_RADBUT_NOLINE);
	m_wndRadNoLine.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
		CRect(620, 180, 780, 200), this, ID_RADBUT_NOLINE);

	m_wndRadNoLine.SetCheck(true);

	str.LoadString(IDS_RADBUT_STRIKE);
	m_wndRadStrikeThrough.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
		CRect(620, 205, 780, 225), this, ID_RADBUT_STRIKE);

	str.LoadString(IDS_RADBUT_UND);
	m_wndRadUnderline.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
		CRect(620, 230, 780, 250), this, ID_RADBUT_UND);
	

	str.LoadString(IDS_BUT_FOREGROUND);
	m_wndButForeground.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(620, 255, 820, 275), this, ID_BUT_FOREGROUND);

	str.LoadString(IDS_BUT_BACKGROUND);
	m_wndButBackground.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(620, 280, 820, 300), this, ID_BUT_BACKGROUND);


	str.LoadString(IDS_CBOX_FFAMILY);
	m_wndCBoxFontFamily.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWNLIST,
		CRect(620, 305, 820, 450), this, ID_CBOX_FFAMILY);

	std::vector<CString> fontNames = { L"Arial",  L"Arial Black", L"Bahnschrift", L"Calibri", L"Cambria", L"Candara", 
		L"Comic Sans MS", L"Consolas", L"Constantia", L"Corbel", L"Courier New" , L"Ebrima", L"Franklin Gothic Medium" , 
		L"Gabriola", L"Gadugi" , L"Georgia", L"Impact" , L"Ink Free", L"Javanese Text" , L"Lucida Console", L"Lucida Sans Unicode" , 
		L"Malgun Gothic", L"Marlett" , L"Microsoft Himalaya", L"Microsoft JhengHei" , L"Microsoft JhengHei UI", 
		L"Microsoft New Tai Lue" , L"Microsoft PhagsPa", L"Microsoft Sans Serif" , L"Microsoft Tai Le", L"Microsoft YaHei", 
		L"Microsoft YaHei UI" , L"Microsoft Yi Baiti", L"Mongolian Baiti", L"MV Boli" , L"Myanmar Text", L"Nirmala UI", 
		L"Palatino Linotype" , L"Segoe Print" , L"Segoe Script", L"Segoe UI" , L"SimSun", L"NSimSun" , L"SimSun-ExtB", L"Sitka Small", 
		L"Sitka Text", L"Sitka Subheading" , L"Sitka Heading", L"Sitka Display" , L"Sitka Banner", L"Sylfaen" , L"Symbol", L"Tahoma",
		L"Times New Roman", L"Trebuchet MS" , L"Verdana", L"Webdings" , L"Wingdings", L"Yu Gothic" , L"Yu Gothic UI" };

	for (int i = 0; i < fontNames.size(); i++)
	{
		m_wndCBoxFontFamily.InsertString(i, fontNames[i]);
	}
	m_wndCBoxFontFamily.SetCurSel(0);

	m_wndEditTextBlock.Create(WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_TABSTOP | WS_BORDER | ES_READONLY,
		CRect(10, 340, 600, 450), this, ID_EDIT_TEXTBLOCK);

	str.LoadString(IDS_BUT_COPY);
	m_wndButCopy.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(620, 380, 820, 410), this, ID_BUT_COPY);

	return 0;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); 
}

HBRUSH CChildView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	const DWORD dwStyle = pWnd->GetStyle();

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brBackground;
	}

	if (dwStyle & BS_AUTOCHECKBOX)
		return m_brBackground;

	return hBrush;
}

void CChildView::OnButtonForeground()
{
	COLORREF foreground = GetColor();
	if (foreground != -1)
	{
		m_pTextAttributes->m_clrForeground = foreground;
		m_wndOutputWindow.AttributesChanged();
	}
	GenerateText();
}

void CChildView::OnButtonBackground()
{
	COLORREF background = GetColor();
	if (background != -1)
	{
		m_pTextAttributes->m_clrBackground = background;
		m_wndOutputWindow.AttributesChanged();
	}
	GenerateText();
}

COLORREF CChildView::GetColor()
{

	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
		return dlg.GetColor();
	return -1;
}

void CChildView::OnChangeText()
{
	m_wndEditText.GetWindowText(m_pTextAttributes->m_strText);
	m_wndOutputWindow.AttributesChanged();
	GenerateText();
}

void CChildView::OnChangeSize()
{
	m_wndEditSize.GetWindowText(m_pTextAttributes->m_strSize);
	m_wndOutputWindow.AttributesChanged();
	GenerateText();
}

void CChildView::OnChBoxItalic()
{
	m_pTextAttributes->m_bItalic = m_wndChBoxItalic.GetCheck();
	m_wndOutputWindow.AttributesChanged();
	GenerateText();
}

void CChildView::OnChBoxBold()
{
	m_pTextAttributes->m_bBold = m_wndChBoxBold.GetCheck();
	m_wndOutputWindow.AttributesChanged();
	GenerateText();
}

void CChildView::OnRadioButton(UINT nID)
{
	switch (nID)
	{
	case ID_RADBUT_NOLINE:
		m_pTextAttributes->m_nLineState = TEXT_NOLINE;
		break;
	case ID_RADBUT_STRIKE:
		m_pTextAttributes->m_nLineState = TEXT_STRIKE_THROUGH;
		break;
	case ID_RADBUT_UND:
		m_pTextAttributes->m_nLineState = TEXT_UNDERLINE;
		break;
	}
	m_wndOutputWindow.AttributesChanged();
	GenerateText();
}

void CChildView::OnCBoxFFamily()
{
	m_wndCBoxFontFamily.GetLBText(m_wndCBoxFontFamily.GetCurSel(), m_pTextAttributes->m_strFontFamily);
	m_wndOutputWindow.AttributesChanged();
	GenerateText();
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	if (m_pTextAttributes != nullptr)
		m_wndOutputWindow.AttributesChanged();
}

void CChildView::GenerateText()
{
	CString strFWeight = m_pTextAttributes->m_bBold ? L" FontWeight=\"Bold\"" : L"";
	CString strFStyle = m_pTextAttributes->m_bItalic ? L" FontStyle=\"Italic\"" : L"";
	CString strTextDecorations;
	if (m_pTextAttributes->m_nLineState == TEXT_STRIKE_THROUGH)
		strTextDecorations = L" TextDecorations=\"StrikeThrough\"";
	else if (m_pTextAttributes->m_nLineState == TEXT_UNDERLINE)
		strTextDecorations = L" TextDecorations=\"Underline\"";
	else 
		strTextDecorations = L"";

	CString TextBlock;
	TextBlock.Format(L"<TextBlock%s%s FontFamily=\"%s\" FontSize=\"%s\"%s Background=\"#%.2X%.2X%.2X\" Foreground=\"#%.2X%.2X%.2X\">%s</TextBlock>", 
		strFStyle, strFWeight, m_pTextAttributes->m_strFontFamily, m_pTextAttributes->m_strSize, strTextDecorations, 
		GetRValue(m_pTextAttributes->m_clrForeground), GetGValue(m_pTextAttributes->m_clrForeground), GetBValue(m_pTextAttributes->m_clrForeground),
		GetRValue(m_pTextAttributes->m_clrBackground), GetGValue(m_pTextAttributes->m_clrBackground), GetBValue(m_pTextAttributes->m_clrBackground),
		m_pTextAttributes->m_strText);
	m_wndEditTextBlock.SetWindowText(TextBlock);	
}

void CChildView::OnCopy()
{
	m_wndEditTextBlock.SetSel(0, -1);
	m_wndEditTextBlock.Copy();
}

void CChildView::OnButtonCopy()
{
	OnCopy();
}