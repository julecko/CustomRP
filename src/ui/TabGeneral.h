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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};
