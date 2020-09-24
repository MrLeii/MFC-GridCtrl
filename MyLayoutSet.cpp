// MyLayoutSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyLayoutControl.h"
#include "MyLayoutSet.h"
#include "afxdialogex.h"


// CMyLayoutSet �Ի���

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


// CMyLayoutSet ��Ϣ�������

CString strRow,strCol;

void CMyLayoutSet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_SETROW)->GetWindowText(strRow);
	GetDlgItem(IDC_EDIT_SETCOLUMN)->GetWindowText(strCol);
	CDialogEx::OnOK();
}
