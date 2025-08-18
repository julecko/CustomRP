// TabAbout.cpp : implementation file
//

#include "pch/pch.h"
#include "app/CustomRP.h"
#include "afxdialogex.h"
#include "ui/TabAbout.h"


// TabAbout dialog

IMPLEMENT_DYNAMIC(TabAbout, CDialogEx)

TabAbout::TabAbout(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_ABOUT, pParent)
{

}

TabAbout::~TabAbout()
{
}

void TabAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabAbout, CDialogEx)
END_MESSAGE_MAP()


// TabAbout message handlers
