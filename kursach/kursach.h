
// kursach.h : main header file for the kursach application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CkursachApp:
// See kursach.cpp for the implementation of this class
//

class CkursachApp : public CWinApp
{
public:
	CkursachApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CkursachApp theApp;
