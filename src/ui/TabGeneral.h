#pragma once
#include "afxdialogex.h"


// TabGeneral dialog

class TabGeneral : public CDialogEx
{
	DECLARE_DYNAMIC(TabGeneral)

public:
	TabGeneral(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TabGeneral();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_GENERAL };
#endif

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	std::string GetDiscordClientId() const;
	void SetDiscordClientId(std::string);

protected:
	CBrush m_brBackground;
	CEdit m_discordClientId;

	CString m_strName;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedIdInputLabel();
};
