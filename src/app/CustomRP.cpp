#include "pch/pch.h"
#include "app/CustomRP.h"
#include "tray/TrayIcon.h"
#include "util/Logger.h"
#include "util/Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CCustomRPApp, CWinApp)
END_MESSAGE_MAP()

CCustomRPApp theApp;

CCustomRPApp::CCustomRPApp()
    : m_pTrayWnd(nullptr), pManager(nullptr)
{
}

BOOL CCustomRPApp::InitInstance()
{
    CWinApp::InitInstance();

    m_hMutex = CreateMutex(NULL, TRUE, L"Global\\CustomRP_SingleInstance");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return FALSE; // Exit this instance
    }

    // Modern look
    INITCOMMONCONTROLSEX icc = { sizeof(icc) };
    icc.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&icc);

    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

    // Logger initialization
    logger.init("logs/CustomRP.log", "logs/CustomRP-error.log");

    // Config initialiation
    config.init("config");
    config.load();

    // Initialize tray icon
    m_pTrayWnd = new CTrayWnd();
    if (!m_pTrayWnd->CreateWnd())
        return FALSE;

    m_pMainWnd = m_pTrayWnd; // app lifetime = tray lifetime

    // Profile manager initialization
    pManager = new ProfileManager();

    if (pManager->GetAllProfiles().empty()) {
        Profile defaultProfile("Default");
        defaultProfile.SetState("Hello world");
        defaultProfile.SetDetails("My first presence");

        pManager->AddProfile(defaultProfile);
    }

    /*m_discord = std::make_unique<MyDiscordPresence>();
    if (m_discord->Initialize(NULL))
    {
        m_discord->UpdatePresence("In Main Menu", "Playing CustomRP");

        m_discordThread = std::thread([this]() {
            if (m_discord)
                m_discord->RunCallbacks();
            });
    }*/

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

    if (pManager)
    {
        pManager->SaveProfiles();
        delete pManager;
        pManager = nullptr;
    }

    if(m_discord)
    {
        m_discord->Shutdown();
    }

    if (m_discordThread.joinable())
        m_discordThread.join();

    m_discord.reset();

    config.save();

    if (m_hMutex)
    {
        ReleaseMutex(m_hMutex);
        CloseHandle(m_hMutex);
        m_hMutex = nullptr;
    }

    return CWinApp::ExitInstance();
}
