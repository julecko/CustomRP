#include "pch/pch.h"
#include "app/CustomRP.h"
#include "tray/TrayIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CCustomRPApp, CWinApp)
END_MESSAGE_MAP()

CCustomRPApp theApp;

CCustomRPApp::CCustomRPApp()
    : m_pTrayWnd(nullptr)
{
}

BOOL CCustomRPApp::InitInstance()
{
    CWinApp::InitInstance();

    m_pTrayWnd = new CTrayWnd();
    if (!m_pTrayWnd->CreateWnd())
        return FALSE;

    m_pMainWnd = m_pTrayWnd; // app lifetime = tray lifetime
    return TRUE;
}

int CCustomRPApp::ExitInstance()
{
    if (m_pTrayWnd)
    {
        m_pTrayWnd->DestroyWindow();
        delete m_pTrayWnd;
        m_pTrayWnd = nullptr;
    }

    return CWinApp::ExitInstance();
}
