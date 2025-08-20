#pragma once
#include "afxdialogex.h"


// TabAbout dialog

class TabAbout : public CDialogEx
{
	DECLARE_DYNAMIC(TabAbout)

public:
	TabAbout(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TabAbout();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_ABOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};
