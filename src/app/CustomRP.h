#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "res/resource.h"

// Forward declare
class CTrayWnd;

// CCustomRPApp
class CCustomRPApp : public CWinApp
{
public:
    CCustomRPApp();

    virtual BOOL InitInstance();
    virtual int ExitInstance();

    afx_msg void OnAppExit();
    afx_msg void OnAppSettings();

    DECLARE_MESSAGE_MAP()

private:
    CTrayWnd* m_pTrayWnd; // hidden window for tray icon
};

extern CCustomRPApp theApp;
