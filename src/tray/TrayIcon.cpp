#include "pch/pch.h"
#include "TrayIcon.h"
#include "app/CustomRP.h"
#include "ui/Dlg.h"

BEGIN_MESSAGE_MAP(CTrayWnd, CWnd)
    ON_MESSAGE(WM_TRAYICON, &CTrayWnd::OnTrayNotify)
    ON_COMMAND(ID_TRAY_EXIT, &CTrayWnd::OnTrayExit)
    ON_COMMAND(ID_TRAY_SETTINGS, &CTrayWnd::OnTraySettings)
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

LRESULT CTrayWnd::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
    if (lParam == WM_RBUTTONUP)
    {
        CMenu menu;
        menu.CreatePopupMenu();
        menu.AppendMenu(MF_STRING, ID_TRAY_PROFILES, _T("Profiles"));
        menu.AppendMenu(MF_STRING, ID_TRAY_SETTINGS, _T("Settings..."));
        menu.AppendMenu(MF_STRING, ID_TRAY_EXIT, _T("Exit"));

        CPoint pt;
        GetCursorPos(&pt);
        SetForegroundWindow();
        menu.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
    }
    return 0;
}

void CTrayWnd::OnTrayExit()
{
    PostQuitMessage(0);
}

void CTrayWnd::OnTraySettings()
{
    static Dlg* pDlg = nullptr;

    if (!pDlg || !::IsWindow(pDlg->GetSafeHwnd()))
    {
        pDlg = new Dlg(this);        // parent = tray window
        pDlg->Create(IDD_CUSTOMRP_DIALOG, this);
    }

    pDlg->ShowWindow(SW_SHOW);
    pDlg->SetForegroundWindow();
}
