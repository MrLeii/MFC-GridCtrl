#pragma once


// CMyLayoutSet 对话框

class CMyLayoutSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMyLayoutSet)

public:
	CMyLayoutSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyLayoutSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
