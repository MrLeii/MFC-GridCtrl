
// MyLayoutControlView.h : CMyLayoutControlView 类的接口
//

#pragma once

#include "resource.h"
#include "d:\vs2010\mylayoutcontrol\gridctrl_src\gridctrl.h"
#include "afxcmn.h"


class CMyLayoutControlView : public CFormView
{
protected: // 仅从序列化创建
	CMyLayoutControlView();
	DECLARE_DYNCREATE(CMyLayoutControlView)

public:
	enum{ IDD = IDD_MYLAYOUTCONTROL_FORM };

// 特性
public:
	CMyLayoutControlDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMyLayoutControlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	//afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnSet();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnVirtualMode();
	

	CGridCtrl m_Grids;
public:
	BOOL	m_bVirtualMode;
	int		m_nFixCols;
	int		m_nFixRows;
	int		m_nCols;
	int		m_nRows;
	BOOL	m_bEditable;
	BOOL	m_bHeaderSort;

	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDelRow();
	afx_msg void OnDelcol();
	afx_msg void OnMerge();
	afx_msg void OnDiv();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
};

#ifndef _DEBUG  // MyLayoutControlView.cpp 中的调试版本
inline CMyLayoutControlDoc* CMyLayoutControlView::GetDocument() const
   { return reinterpret_cast<CMyLayoutControlDoc*>(m_pDocument); }
#endif

