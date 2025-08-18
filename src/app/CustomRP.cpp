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

    m_discord = std::make_unique<MyDiscordPresence>();
    if (m_discord->Initialize(NULL))
    {
        m_discord->UpdatePresence("In Main Menu", "Playing CustomRP");

        m_discordThread = std::thread([this]() {
            if (m_discord)
                m_discord->RunCallbacks();
            });
    }

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

    if(m_discord)
    {
        m_discord->Shutdown();
    }

    if (m_discordThread.joinable())
        m_discordThread.join();

    m_discord.reset();

    return CWinApp::ExitInstance();
}
