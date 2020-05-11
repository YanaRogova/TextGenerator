#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MarkupTextGenerator.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMarkupTextGeneratorApp

BEGIN_MESSAGE_MAP(CMarkupTextGeneratorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMarkupTextGeneratorApp::OnAppAbout)
END_MESSAGE_MAP()


CMarkupTextGeneratorApp::CMarkupTextGeneratorApp() noexcept
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
	SetAppID(_T("MarkupTextGenerator.AppID.NoVersion"));
}


CMarkupTextGeneratorApp theApp;


BOOL CMarkupTextGeneratorApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));

	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);

	CMFCToolBar::m_bExtCharTranslation = TRUE;

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CMarkupTextGeneratorApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


void CMarkupTextGeneratorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

