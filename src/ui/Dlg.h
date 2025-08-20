// Dlg.h : header file
//

#pragma once
#include <afxtabctrl.h>

#include "ui/TabGeneral.h"
#include "ui/TabAdvanced.h"
#include "ui/TabAbout.h"

// Dlg dialog
class Dlg : public CDialogEx
{
// Construction
public:
	Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSTOMRP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CMFCButton m_btnOK;
	CMFCButton m_btnCancel;

	CTabCtrl m_TabMain;
	TabGeneral   m_tabGeneral;
	TabAdvanced  m_tabAdvanced;
	TabAbout     m_tabAbout;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()
};
