
// Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CustomRP.h"
#include "Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Dlg dialog



Dlg::Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSTOMRP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_TabMain);
}

BEGIN_MESSAGE_MAP(Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &Dlg::OnTabSelChange)
END_MESSAGE_MAP()


// Dlg message handlers

BOOL Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LONG style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	style |= WS_SYSMENU | WS_MINIMIZEBOX;
	::SetWindowLong(this->m_hWnd, GWL_STYLE, style);
	::SetWindowPos(this->m_hWnd, nullptr, 0, 0, 0, 0,
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	m_TabMain.InsertItem(0, _T("General"));
	m_TabMain.InsertItem(1, _T("Advanced"));
	m_TabMain.InsertItem(2, _T("About"));

	m_tabGeneral.Create(IDD_TAB_GENERAL, &m_TabMain);
	m_tabAdvanced.Create(IDD_TAB_ADVANCED, &m_TabMain);
	m_tabAbout.Create(IDD_TAB_ABOUT, &m_TabMain);

	CRect rc;
	m_TabMain.GetClientRect(&rc);
	m_TabMain.AdjustRect(FALSE, &rc);

	m_tabGeneral.MoveWindow(&rc);
	m_tabAdvanced.MoveWindow(&rc);
	m_tabAbout.MoveWindow(&rc);

	m_tabGeneral.ShowWindow(SW_SHOW);
	m_tabAdvanced.ShowWindow(SW_HIDE);
	m_tabAbout.ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	switch (nID)
	{
	case SC_CLOSE: EndDialog(IDOK); break;
	case SC_MINIMIZE: ShowWindow(SW_MINIMIZE); break;
	case SC_MAXIMIZE: ShowWindow(SW_MAXIMIZE); break;
	default: CDialogEx::OnSysCommand(nID, lParam);
	}
}

void Dlg::OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	int sel = m_TabMain.GetCurSel();

	m_tabGeneral.ShowWindow(sel == 0 ? SW_SHOW : SW_HIDE);
	m_tabAdvanced.ShowWindow(sel == 1 ? SW_SHOW : SW_HIDE);
	m_tabAbout.ShowWindow(sel == 2 ? SW_SHOW : SW_HIDE);

	*pResult = 0;
}