// SETLEVEL.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "SETLEVEL.h"
#include "afxdialogex.h"

int SETLEVEL::level = 0;
// SETLEVEL �Ի���

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


// SETLEVEL ��Ϣ�������
