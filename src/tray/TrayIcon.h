#pragma once
#include <afxwin.h>
#include <shellapi.h>

#define WM_TRAYICON (WM_USER + 1)
#define ID_TRAY_EXIT     60001
#define ID_TRAY_SETTINGS 60002

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

    DECLARE_MESSAGE_MAP()

private:
    CTrayIcon m_trayIcon;
};
