// TabGeneral.cpp : implementation file
//

#include "pch/pch.h"
#include "app/CustomRP.h"
#include "afxdialogex.h"
#include "ui/TabGeneral.h"
#include "res/resource.h"


// TabGeneral dialog

IMPLEMENT_DYNAMIC(TabGeneral, CDialogEx)

TabGeneral::TabGeneral(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_GENERAL, pParent)
{
    m_brBackground.CreateSolidBrush(RGB(249, 249, 249));
}

TabGeneral::~TabGeneral()
{
}

void TabGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_DISCORD_ID_INPUT, m_discordClientId);
}


BEGIN_MESSAGE_MAP(TabGeneral, CDialogEx)
	ON_WM_ERASEBKGND()
    ON_STN_CLICKED(IDC_ID_INPUT_LABEL, &TabGeneral::OnStnClickedIdInputLabel)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL TabGeneral::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
    pDC->FillSolidRect(&rect, RGB(249, 249, 249));
    return TRUE;
}

void TabGeneral::OnStnClickedIdInputLabel()
{
    // TODO: Add your control notification handler code here
}

std::string TabGeneral::GetDiscordClientId() const
{
    CString text;
    m_discordClientId.GetWindowText(text);

    CT2A ascii(text);  // convert CString (wchar_t) to char*
    return std::string(ascii);
}

void TabGeneral::SetDiscordClientId(std::string id)
{
    CString csId(id.c_str());

    if (m_discordClientId.GetSafeHwnd())
    {
        m_discordClientId.SetWindowText(csId);
    }
}

HBRUSH TabGeneral::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    switch (nCtlColor)
    {
    case CTLCOLOR_DLG:
        return m_brBackground;
    case CTLCOLOR_STATIC:
        // Set static text to same background
        pDC->SetBkColor(RGB(249, 249, 249));
        return m_brBackground;
    case CTLCOLOR_EDIT:
        // Optional: set edit background too
        pDC->SetBkColor(RGB(255, 255, 255));
        return (HBRUSH)GetStockObject(WHITE_BRUSH);
    default:
        return hbr;
    }
}
