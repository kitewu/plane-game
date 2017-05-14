// SETLEVEL.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "SETLEVEL.h"
#include "afxdialogex.h"

int SETLEVEL::level = 0;
// SETLEVEL 对话框

IMPLEMENT_DYNAMIC(SETLEVEL, CDialog)

SETLEVEL::SETLEVEL(CWnd* pParent /*=NULL*/)
	: CDialog(SETLEVEL::IDD, pParent)
{

}

SETLEVEL::~SETLEVEL()
{
}

void SETLEVEL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SETLEVEL, CDialog)
END_MESSAGE_MAP()


// SETLEVEL 消息处理程序
