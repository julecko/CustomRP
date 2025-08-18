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
END_MESSAGE_MAP()


// TabGeneral message handlers
