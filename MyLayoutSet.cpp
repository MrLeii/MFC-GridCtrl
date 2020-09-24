// MyLayoutSet.cpp : 实现文件
//

#include "stdafx.h"
#include "MyLayoutControl.h"
#include "MyLayoutSet.h"
#include "afxdialogex.h"


// CMyLayoutSet 对话框

IMPLEMENT_DYNAMIC(CMyLayoutSet, CDialogEx)

CMyLayoutSet::CMyLayoutSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyLayoutSet::IDD, pParent)
{

}

CMyLayoutSet::~CMyLayoutSet()
{
}

void CMyLayoutSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyLayoutSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMyLayoutSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyLayoutSet 消息处理程序

CString strRow,strCol;

void CMyLayoutSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_SETROW)->GetWindowText(strRow);
	GetDlgItem(IDC_EDIT_SETCOLUMN)->GetWindowText(strCol);
	CDialogEx::OnOK();
}
