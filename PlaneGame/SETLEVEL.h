#pragma once


// SETLEVEL �Ի���

class SETLEVEL : public CDialog
{
	DECLARE_DYNAMIC(SETLEVEL)

public:
	SETLEVEL(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SETLEVEL();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	static int level;
};
