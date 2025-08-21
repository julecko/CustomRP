#include "pch/pch.h"
#include "TrayIcon.h"
#include "app/CustomRP.h"
#include "ui/Dlg.h"
#include "util/Config.h"

#include <stdexcept>


BEGIN_MESSAGE_MAP(CTrayWnd, CWnd)
    ON_MESSAGE(WM_TRAYICON, &CTrayWnd::OnTrayNotify)
    ON_COMMAND(ID_TRAY_EXIT, &CTrayWnd::OnTrayExit)
    ON_COMMAND(ID_TRAY_SETTINGS, &CTrayWnd::OnTraySettings)
    ON_COMMAND_RANGE(ID_TRAY_PROFILE_START, 62000, &CTrayWnd::OnTrayProfileSelected)
END_MESSAGE_MAP()

BOOL CTrayWnd::CreateWnd()
{
    CString clsName = AfxRegisterWndClass(0);
    if (!CreateEx(0, clsName, _T("HiddenTrayWnd"),
        WS_OVERLAPPED, CRect(0, 0, 0, 0),
        nullptr, 0))
    {
        return FALSE;
    }

    HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_trayIcon.Create(this, 1, hIcon, _T("CustomRP Running"));
    return TRUE;
}

void CTrayWnd::BuildProfileMenu(CMenu& menu)
{
    m_profileActionMap.clear();
    m_nextProfileCmdId = ID_TRAY_PROFILE_START;

    // Add all profiles with Connect / Reconnect options directly in the main menu
    for (const auto& profile : theApp.pManager->GetAllProfiles())
    {
        std::string profileName = profile.GetName();
        bool isConnected = (profileName == m_currentProfile);

        // Prefix * for active profile
        std::string displayName = profileName;
        if (isConnected)
            displayName = "*" + profileName;

        // Profile name as submenu
        CMenu profileSubMenu;
        profileSubMenu.CreatePopupMenu();

        // Connect option
        UINT connectId = m_nextProfileCmdId++;
        profileSubMenu.AppendMenu(isConnected ? MF_GRAYED : MF_STRING, connectId, _T("Connect"));
        m_profileActionMap[connectId] = { profileName, ProfileAction::Connect };

        // Reconnect option
        UINT reconnectId = m_nextProfileCmdId++;
        profileSubMenu.AppendMenu(MF_STRING, reconnectId, _T("Reconnect"));
        m_profileActionMap[reconnectId] = { profileName, ProfileAction::Refresh };

        // Add profile submenu to main menu
        menu.AppendMenu(MF_POPUP, (UINT_PTR)profileSubMenu.Detach(), CA2T(displayName.c_str()));
    }

    // Separator line
    menu.AppendMenu(MF_SEPARATOR);

    // Single Disconnect button (applies to current profile)
    menu.AppendMenu(MF_STRING | (m_currentProfile.empty() ? MF_GRAYED : 0),
        ID_TRAY_DISCONNECT, _T("Disconnect"));

    // Settings and Exit
    menu.AppendMenu(MF_STRING, ID_TRAY_SETTINGS, _T("Settings..."));
    menu.AppendMenu(MF_STRING, ID_TRAY_EXIT, _T("Exit"));
}



LRESULT CTrayWnd::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
    if (lParam == WM_RBUTTONUP)
    {
        CMenu menu;
        menu.CreatePopupMenu();

        BuildProfileMenu(menu);

        CPoint pt;
        GetCursorPos(&pt);
        SetForegroundWindow();

        UINT cmd = menu.TrackPopupMenu(TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x, pt.y, this);

        if (cmd >= ID_TRAY_PROFILE_START && cmd < ID_TRAY_PROFILE_END)
        {
            OnTrayProfileAction(cmd);
        }
        else if (cmd == ID_TRAY_SETTINGS)
        {
            OnTraySettings();
        }
        else if (cmd == ID_TRAY_EXIT)
        {
            OnTrayExit();
        }
        else if (cmd == ID_TRAY_DISCONNECT)
        {
            DisconnectProfile();
        }
    }

    return 0;
}

void CTrayWnd::OnTrayProfileAction(UINT nID)
{
    auto it = m_profileActionMap.find(nID);
    if (it == m_profileActionMap.end())
        return;

    std::string profileName = it->second.first;
    int action = it->second.second;

    switch (action)
    {
    case ProfileAction::Connect:    
        ConnectProfile(profileName);
        break;
    case ProfileAction::Refresh:
        ConnectProfile(profileName);
        break;
    }
}

void CTrayWnd::OnTrayExit() { PostQuitMessage(0); }

void CTrayWnd::OnTraySettings()
{
    static Dlg* pDlg = nullptr;

    if (!pDlg || !::IsWindow(pDlg->GetSafeHwnd()))
    {
        pDlg = new Dlg(this);
        pDlg->Create(IDD_CUSTOMRP_DIALOG, this);
    }

    pDlg->ShowWindow(SW_SHOW);
    pDlg->SetForegroundWindow();
}

void CTrayWnd::OnTrayProfileSelected(UINT nID)
{
    auto it = m_profileMenuMap.find(nID);
    if (it == m_profileMenuMap.end()) return;

    std::string selectedProfile = it->second;

    if (m_currentProfile != selectedProfile)
    {
        m_currentProfile = selectedProfile;
        theApp.pManager->SetCurrentProfile(m_currentProfile);

        // Manage Discord Presence
        if (!m_discord)
        {
            m_discord = std::make_unique<MyDiscordPresence>();

            std::string clientIdStr = config.get("DISCORD_CLIENT_ID");
            uint64_t discordClientId = 0;
            try
            {
                discordClientId = std::stoull(clientIdStr);
            }
            catch (const std::invalid_argument&)
            {
                AfxMessageBox(_T("DISCORD_CLIENT_ID is not a valid number."));
                m_discord.reset();
                return;
            }
            catch (const std::out_of_range&)
            {
                AfxMessageBox(_T("DISCORD_CLIENT_ID is too large."));
                m_discord.reset();
                return;
            }

            if(!TryInitDiscord(discordClientId))
            {
                return; // Stop connecting if Discord failed
            }
        }
        else
        {
            // Refresh presence for new profile
            m_discord->UpdatePresence(
                theApp.pManager->GetCurrentProfile()->GetState(),
                theApp.pManager->GetCurrentProfile()->GetDetails()
            );
        }
    }
    else
    {
        // Disconnect
        DisconnectProfile();
    }
}

bool CTrayWnd::TryInitDiscord(uint64_t clientId)
{
    if (!m_discord->Initialize(clientId))
    {
        m_discord.reset();
        AfxMessageBox(_T("Discord initialization failed. Invalid client ID or Discord not running."));
        return false;
    }

    m_discordThread = std::thread([this]() { m_discord->RunCallbacks(); });
    
    return true;
}

void CTrayWnd::ConnectProfile(const std::string& profileName)
{
    if (!m_discord)
    {
        m_discord = std::make_unique<MyDiscordPresence>();

        std::string clientIdStr = config.get("DISCORD_CLIENT_ID");
        uint64_t discordClientId = 0;
        try
        {
            discordClientId = std::stoull(clientIdStr);
        }
        catch (const std::invalid_argument&)
        {
            AfxMessageBox(_T("DISCORD_CLIENT_ID is not a valid number."));
            m_discord.reset();
            return;
        }
        catch (const std::out_of_range&)
        {
            AfxMessageBox(_T("DISCORD_CLIENT_ID is too large."));
            m_discord.reset();
            return;
        }

        if(!TryInitDiscord(discordClientId))
        {
            return; // Stop connecting if Discord failed
        }
    }

    m_discord->UpdatePresence(
        theApp.pManager->GetProfile(profileName)->GetState(),
        theApp.pManager->GetProfile(profileName)->GetDetails()
    );

    m_currentProfile = profileName;
    theApp.pManager->SetCurrentProfile(profileName);
}

void CTrayWnd::DisconnectProfile()
{
    if (m_discord)
    {
        m_discord->Shutdown();
        if (m_discordThread.joinable())
            m_discordThread.join();
        m_discord.reset();
    }
    m_currentProfile.clear();
}
