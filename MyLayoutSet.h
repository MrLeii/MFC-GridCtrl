#pragma once


// CMyLayoutSet �Ի���

class CMyLayoutSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMyLayoutSet)

public:
	CMyLayoutSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyLayoutSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
