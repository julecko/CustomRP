#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "res/resource.h"
#include "rpc/DiscordPresence.h"
#include "profile/ProfileManager.h"
#include <thread>
#include <memory>

class CTrayWnd;

class CCustomRPApp : public CWinApp
{
public:
    CCustomRPApp();

    virtual BOOL InitInstance();
    virtual int ExitInstance();


    DECLARE_MESSAGE_MAP()

private:
    CTrayWnd* m_pTrayWnd; // hidden window for tray icon
    ProfileManager* pManager;

    std::unique_ptr<MyDiscordPresence> m_discord;
    std::thread m_discordThread;
};

extern CCustomRPApp theApp;
