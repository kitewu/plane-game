#pragma once


// SETLEVEL 对话框

class SETLEVEL : public CDialog
{
	DECLARE_DYNAMIC(SETLEVEL)

public:
	SETLEVEL(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SETLEVEL();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	static int level;
};
