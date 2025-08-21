#pragma once
#include <afxwin.h>
#include <shellapi.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include "rpc/DiscordPresence.h"
#include "app/CustomRP.h"

#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAY_EXIT     60001
#define ID_TRAY_SETTINGS 60002
#define ID_TRAY_PROFILES 60003

#define ID_TRAY_PROFILE_START   61000
#define ID_TRAY_PROFILE_END     62000
#define ID_TRAY_DISCONNECT      63000

#define ID_PROFILE_CONNECT      63001
#define ID_PROFILE_REFRESH      63002


class CTrayIcon
{
public:
    CTrayIcon() { ZeroMemory(&m_nid, sizeof(m_nid)); }

    BOOL Create(CWnd* pWnd, UINT uID, HICON hIcon, CString tooltip)
    {
        m_nid.cbSize = sizeof(NOTIFYICONDATA);
        m_nid.hWnd = pWnd->GetSafeHwnd();
        m_nid.uID = uID;
        m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        m_nid.uCallbackMessage = WM_TRAYICON;
        m_nid.hIcon = hIcon;
        _tcsncpy_s(m_nid.szTip, tooltip, _TRUNCATE);
        return Shell_NotifyIcon(NIM_ADD, &m_nid);
    }

    void Remove()
    {
        Shell_NotifyIcon(NIM_DELETE, &m_nid);
    }

private:
    NOTIFYICONDATA m_nid;
};

class CTrayWnd : public CWnd
{
public:
    BOOL CreateWnd();

protected:
    afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
    afx_msg void OnTrayExit();
    afx_msg void OnTraySettings();
    afx_msg void OnTrayProfileSelected(UINT nID);
    afx_msg void OnTrayProfileAction(UINT nID);

    DECLARE_MESSAGE_MAP()

private:
    void BuildProfileMenu(CMenu& menu);
    bool TryInitDiscord(uint64_t clientId);
    void ConnectProfile(const std::string& profileName);
    void DisconnectProfile();

    CTrayIcon m_trayIcon;
    std::unordered_map<UINT, std::pair<std::string, int>> m_profileActionMap; 
    std::unordered_map<UINT, std::string> m_profileMenuMap;
    enum ProfileAction { Connect = 1, Refresh = 2 };
    UINT m_nextProfileCmdId = ID_TRAY_PROFILE_START;
    std::string m_currentProfile;
};
