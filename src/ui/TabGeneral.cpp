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
    SaveAllProfiles();
}

void TabGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_DISCORD_ID_INPUT, m_discordClientId);

    DDX_Control(pDX, IDC_PROFILE_LIST_BOX, m_profileList);
    DDX_Control(pDX, IDC_ADD_PROFILE, m_btnAdd);
    DDX_Control(pDX, IDC_REMOVE_PROFILE, m_btnRemove);
    DDX_Control(pDX, IDC_NAME_INPUT, m_editName);
    DDX_Control(pDX, IDC_STATE_INPUT, m_editState);
    DDX_Control(pDX, IDC_DETAILS_INPUT, m_editDetails);
}


BEGIN_MESSAGE_MAP(TabGeneral, CDialogEx)
	ON_WM_ERASEBKGND()
    ON_STN_CLICKED(IDC_ID_INPUT_LABEL, &TabGeneral::OnStnClickedIdInputLabel)
    ON_WM_CTLCOLOR()
    ON_LBN_SELCHANGE(IDC_PROFILE_LIST_BOX, &TabGeneral::OnProfileSelected)
    ON_BN_CLICKED(IDC_ADD_PROFILE, &TabGeneral::OnAddProfile)
    ON_BN_CLICKED(IDC_REMOVE_PROFILE, & TabGeneral::OnRemoveProfile)

    ON_EN_KILLFOCUS(IDC_NAME_INPUT, &TabGeneral::OnNameEditKillFocus)
    ON_EN_KILLFOCUS(IDC_STATE_INPUT, &TabGeneral::OnStateEditKillFocus)
    ON_EN_KILLFOCUS(IDC_DETAILS_INPUT, &TabGeneral::OnDetailsEditKillFocus)
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

void TabGeneral::OnProfileSelected()
{
    ClearProfileInputs();

    int sel = m_profileList.GetCurSel();
    if (sel != LB_ERR) {
        CString name;
        m_profileList.GetText(sel, name);

        Profile* p = theApp.pManager->GetProfile(std::string(CT2A(name)));
        if (p) {
            m_editName.SetWindowText(CA2T(p->GetName().c_str()));
            m_editState.SetWindowText(CA2T(p->GetState().c_str()));
            m_editDetails.SetWindowText(CA2T(p->GetDetails().c_str()));
        }
    }
}

void TabGeneral::OnAddProfile()
{
    std::string uniqueName = theApp.pManager->GetUniqueName("NewProfile");
    Profile newProfile(uniqueName);
    theApp.pManager->AddProfile(newProfile);

    m_profileList.AddString(CA2T(uniqueName.c_str()));
    int index = m_profileList.FindStringExact(-1, CA2T(uniqueName.c_str()));
    if (index != LB_ERR) m_profileList.SetCurSel(index);

    // Clear inputs for new profile
    ClearProfileInputs();
    m_editName.SetWindowText(CA2T(uniqueName.c_str()));
}

void TabGeneral::OnRemoveProfile()
{
    int sel = m_profileList.GetCurSel();
    if (sel == LB_ERR) return;

    CString name;
    m_profileList.GetText(sel, name);

    theApp.pManager->RemoveProfile(std::string(CT2A(name)));
    m_profileList.DeleteString(sel);
    
    ClearProfileInputs();
}

void TabGeneral::OnNameEditKillFocus()
{
    int sel = m_profileList.GetCurSel();
    if (sel == LB_ERR) return;

    CString csNewName;
    m_editName.GetWindowText(csNewName);

    CString csOldName;
    m_profileList.GetText(sel, csOldName);

    std::string oldNameStr = CT2A(csOldName);
    std::string newNameStr = CT2A(csNewName);

    Profile* p = theApp.pManager->GetProfile(oldNameStr);
    if (p) {
        if (oldNameStr != newNameStr && theApp.pManager->GetProfile(newNameStr)) {
            newNameStr = theApp.pManager->GetUniqueName(newNameStr);
            m_editName.SetWindowText(CA2T(newNameStr.c_str()));
        }

        p->SetName(newNameStr);

        m_profileList.DeleteString(sel);
        m_profileList.InsertString(sel, CA2T(newNameStr.c_str()));
        m_profileList.SetCurSel(sel);
    }
}

void TabGeneral::OnStateEditKillFocus()
{
    int sel = m_profileList.GetCurSel();
    if (sel == LB_ERR) return;

    CString csState;
    m_editState.GetWindowText(csState);

    CString csName;
    m_profileList.GetText(sel, csName);

    Profile* p = theApp.pManager->GetProfile(std::string(CT2A(csName)));
    if (p) p->SetState(std::string(CT2A(csState)));
}

void TabGeneral::OnDetailsEditKillFocus()
{
    int sel = m_profileList.GetCurSel();
    if (sel == LB_ERR) return;

    CString csDetails;
    m_editDetails.GetWindowText(csDetails);

    CString csName;
    m_profileList.GetText(sel, csName);

    Profile* p = theApp.pManager->GetProfile(std::string(CT2A(csName)));
    if (p) p->SetDetails(std::string(CT2A(csDetails)));
}

void TabGeneral::ClearProfileInputs()
{
    m_editName.SetWindowText(_T(""));
    m_editState.SetWindowText(_T(""));
    m_editDetails.SetWindowText(_T(""));
}

void TabGeneral::SaveAllProfiles()
{
    OnNameEditKillFocus();
    OnDetailsEditKillFocus();
    OnStateEditKillFocus();
}
