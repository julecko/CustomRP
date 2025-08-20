// TabGeneral.cpp : implementation file
//

#include "pch/pch.h"
#include "app/CustomRP.h"
#include "afxdialogex.h"
#include "ui/TabGeneral.h"


// TabGeneral dialog

IMPLEMENT_DYNAMIC(TabGeneral, CDialogEx)

TabGeneral::TabGeneral(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_GENERAL, pParent)
{

}

TabGeneral::~TabGeneral()
{
}

void TabGeneral::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabGeneral, CDialogEx)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


BOOL TabGeneral::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
    pDC->FillSolidRect(&rect, RGB(249, 249, 249));
    return TRUE;
}
