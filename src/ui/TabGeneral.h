#pragma once
#include "afxdialogex.h"


// TabGeneral dialog

class TabGeneral : public CDialogEx
{
	DECLARE_DYNAMIC(TabGeneral)

public:
	CListBox m_profileList;

	TabGeneral(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TabGeneral();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_GENERAL };
#endif

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	std::string GetDiscordClientId() const;
	void SetDiscordClientId(std::string);
	void ClearProfileInputs();

protected:
	CBrush m_brBackground;

	CEdit m_discordClientId;


	CButton m_btnAdd;
	CButton m_btnRemove;

	CEdit m_editName;
	CEdit m_editState;
	CEdit m_editDetails;

	CString m_strName;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnProfileSelected();
	afx_msg void OnAddProfile();
	afx_msg void OnRemoveProfile();

	afx_msg void OnNameEditKillFocus();
	afx_msg void OnStateEditKillFocus();
	afx_msg void OnDetailsEditKillFocus();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedIdInputLabel();
};
