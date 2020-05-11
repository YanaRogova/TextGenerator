#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       




class CMarkupTextGeneratorApp : public CWinApp
{
public:
	CMarkupTextGeneratorApp() noexcept;
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMarkupTextGeneratorApp theApp;
