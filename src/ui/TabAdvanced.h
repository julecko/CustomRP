#pragma once
#include "afxdialogex.h"


// TabAdvanced dialog

class TabAdvanced : public CDialogEx
{
	DECLARE_DYNAMIC(TabAdvanced)

public:
	TabAdvanced(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TabAdvanced();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_ADVANCED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};
