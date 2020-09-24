
// MyLayoutControlView.cpp : CMyLayoutControlView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyLayoutControl.h"
#endif

#include "MyLayoutControlDoc.h"
#include "MyLayoutControlView.h"

#include "MyLayoutSet.h"
#include "d:\vs2010\mylayoutcontrol\gridctrl_src\gridctrl.h"

CMyLayoutSet *mylayoutset;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyLayoutControlView

IMPLEMENT_DYNCREATE(CMyLayoutControlView, CFormView)

BEGIN_MESSAGE_MAP(CMyLayoutControlView, CFormView)
	ON_WM_CONTEXTMENU()
ON_COMMAND(ID_SET, &CMyLayoutControlView::OnSet)
ON_WM_SIZE()
ON_WM_RBUTTONUP()
ON_COMMAND(ID_DelRow, &CMyLayoutControlView::OnDelRow)
ON_COMMAND(ID_DelCol, &CMyLayoutControlView::OnDelcol)
ON_COMMAND(ID_Merge, &CMyLayoutControlView::OnMerge)
ON_COMMAND(ID_Div, &CMyLayoutControlView::OnDiv)
ON_BN_CLICKED(IDOK, &CMyLayoutControlView::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON2, &CMyLayoutControlView::OnBnClickedButton2)
END_MESSAGE_MAP()

// CMyLayoutControlView 构造/析构

CMyLayoutControlView::CMyLayoutControlView()
	: CFormView(CMyLayoutControlView::IDD)
{
	// TODO: 在此处添加构造代码
}

CMyLayoutControlView::~CMyLayoutControlView()
{

}

void CMyLayoutControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_SET, m_Grids);
}

BOOL CMyLayoutControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMyLayoutControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//m_Grids.EnableDragAndDrop(TRUE);

	OnVirtualMode();

 }




void CMyLayoutControlView::OnVirtualMode()
{
	
    UpdateData(TRUE);
    m_bVirtualMode = !m_bVirtualMode;
	m_Grids.SetVirtualMode(m_bVirtualMode);
    m_Grids.SetEditable(m_bEditable);

    m_bHeaderSort = m_Grids.GetHeaderSort();

	//m_Grid->SetTextBkColor(RGB(0xFF, 0xFF, 0xE0)); //黄色背景

    if (m_bVirtualMode)
    {

        m_nFixCols = 1;
	    m_nFixRows = 1;

	    TRY {
		    m_Grids.SetRowCount(m_nRows);
		    m_Grids.SetColumnCount(m_nCols);
		    m_Grids.SetFixedRowCount(m_nFixRows);
		    m_Grids.SetFixedColumnCount(m_nFixCols);

			m_Grids.SetColumnWidth(0,20);
			m_Grids.SetRowHeight(0,20);
			m_Grids.SetEditable(TRUE);

			for(int i = 1,j = 1;i < m_nRows,j < m_nCols;i++,j++)
			{
				m_Grids.SetRowHeight(i,200);
				m_Grids.SetColumnWidth(j,200);
			}
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH
    }
    else
    {
        m_nFixCols = 1;
	    m_nFixRows = 1;
	    m_nCols = 4;
	    m_nRows = 4;

        m_Grids.SetAutoSizeStyle();

	    TRY {
		    m_Grids.SetRowCount(m_nRows);
		    m_Grids.SetColumnCount(m_nCols);
		    m_Grids.SetFixedRowCount(m_nFixRows);
		    m_Grids.SetFixedColumnCount(m_nFixCols);
			m_Grids.SetColumnWidth(0,15);
			m_Grids.SetRowHeight(0,15);
			m_Grids.SetEditable(TRUE);

			for(int i = 1,j = 1;i < m_nRows,j < m_nCols;i++,j++)
			{
				m_Grids.SetRowHeight(i,600/m_nRows);
				m_Grids.SetColumnWidth(j,600/m_nCols);
				
			}
			//填充整个控件
			//m_Grids.ExpandToFit();
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH
}
	UpdateData(FALSE);
}



void CMyLayoutControlView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyLayoutControlView 诊断

#ifdef _DEBUG
void CMyLayoutControlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyLayoutControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyLayoutControlDoc* CMyLayoutControlView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyLayoutControlDoc)));
	return (CMyLayoutControlDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyLayoutControlView 消息处理程序



void CMyLayoutControlView::OnSet()
{
	// TODO: 在此添加命令处理程序代码
	if (NULL == mylayoutset)  
	{  
		// 创建非模态对话框实例  
		mylayoutset = new CMyLayoutSet();  
		mylayoutset->Create(IDD_DIALOG_SET,this);  
	}  
	// 若对话框已打开，则显示非模态对话框  
	mylayoutset->ShowWindow(SW_SHOW);

	//CMyLayoutSet dlg;
	//dlg.DoModal();
}


void CMyLayoutControlView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


/*void CMyLayoutControlView::OnUpdateEditRows()
{
	// TODO:  在此添加控件通知处理程序代码
	//CString strRow;
	//
	//GetDlgItem(IDC_EDITROW)->GetWindowText(strRow);
	//m_nRows = _ttoi(strRow);
	//UpdateData(FALSE);
	//TRY {
 //       m_Grids.SetRowCount(m_nRows); 
	//	for(int i = 0;i < m_nRows;i++)
	//	{
	//		m_Grids.SetRowHeight(i,600/m_nRows);
	//		
	//	}
 //   }
	//CATCH (CMemoryException, e)
	//{
	//	e->ReportError();
	//	return;
	//}
 //   END_CATCH
}*/

/*void CMyLayoutControlView::OnUpdateEditCols()
{

	// TODO:  在此添加控件通知处理程序代码

	//CString strCol;
	//GetDlgItem(IDC_EDITCOL)->GetWindowText(strCol);
	//m_nCols = _ttoi(strCol);
	//UpdateData(FALSE);
	//TRY {
 //       m_Grids.SetColumnCount(m_nCols); 
	//	for(int i = 0;i < m_nCols;i++)
	//	{
	//		m_Grids.SetColumnWidth(i,600/m_nCols);
	//		
	//	}
 //   }
	//CATCH (CMemoryException, e)
	//{
	//	e->ReportError();
	//	return;
	//}
 //   END_CATCH
}*/

void CMyLayoutControlView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	GetCursorPos(&point);
	ASSERT(menu.GetSafeHmenu());
	CMenu* pSubMenu = menu.GetSubMenu(0);
	ASSERT(pSubMenu);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,this);
	menu.Detach();
	//CFormView::OnRButtonUp(nFlags, point);
}


void CMyLayoutControlView::OnDelRow()
{
	// TODO: 在此添加命令处理程序代码
	CCellRange Selection = m_Grids.GetSelectedCellRange(); 
	if(!m_Grids.IsValid(Selection)) 
    return   ; 
	CGridCellBase *pCell; 
	int row;
	for(row = Selection.GetMinRow();row <= Selection.GetMaxRow();row++) 
	{ 
		pCell = m_Grids.GetCell(row,1);
		m_Grids.DeleteRow(row);
		m_nRows--;
	}
		//限制只能删除一行
		//if(pCell &&(pCell-> GetState() & GVIS_SELECTED)) 
		//	{
		//		m_Grids.DeleteRow(row);
		//		m_nRows--;
		//		
		//    } 
	m_Grids.SetColumnWidth(0,15);
	m_Grids.SetRowHeight(0,15);
	for(int i = 1;i < m_nRows;i++)
	{
		m_Grids.SetRowHeight(i,600/m_nRows);
			
	}
	//填充整个控件
	//m_Grids.ExpandToFit();

	m_Grids.Invalidate();
	
}


void CMyLayoutControlView::OnDelcol()
{
	// TODO: 在此添加命令处理程序代码
	CCellRange Selection = m_Grids.GetSelectedCellRange(); 
	if(!m_Grids.IsValid(Selection)) 
    return   ; 
	CGridCellBase *pCell; 

	for(int col = Selection.GetMinCol();col <= Selection.GetMaxCol();col++) 
	{ 
		pCell = m_Grids.GetCell(1,col); 
		m_Grids.DeleteColumn(col);
		m_nCols--;
	} 
	m_Grids.SetColumnWidth(0,15);
	m_Grids.SetRowHeight(0,15);
	for(int i = 1;i < m_nCols;i++)
	{
		m_Grids.SetColumnWidth(i,600/m_nCols);
			
	}
	//填充整个控件
	//m_Grids.ExpandToFit();

	m_Grids.Invalidate();
}

//合并
void CMyLayoutControlView::OnMerge()
{
	// TODO: 在此添加命令处理程序代码
	m_Grids.MergeSelectedCells();
}


//拆分
void CMyLayoutControlView::OnDiv()
{
	// TODO: 在此添加命令处理程序代码
	m_Grids.UnMergeSelectedCells();
}



void CMyLayoutControlView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	extern CString strRow,strCol;
	
	m_nRows = _ttoi(strRow);
	m_nCols = _ttoi(strCol);
	UpdateData(FALSE);
	TRY {
        m_Grids.SetRowCount(m_nRows);
		m_Grids.SetColumnCount(m_nCols);
		for(int i = 1,j = 1;i < m_nRows,j < m_nCols;i++,j++)
		{
			m_Grids.SetRowHeight(i,600/m_nRows);
			m_Grids.SetColumnWidth(j,600/m_nCols);
			
		}
		//填充整个控件
		m_Grids.ExpandToFit();
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	UpdateData(FALSE);

}


void CMyLayoutControlView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData();
	extern CString strRow,strCol;

	m_nRows = _ttoi(strRow);
	m_nCols = _ttoi(strCol);
	UpdateData(FALSE);
	TRY {
        m_Grids.SetRowCount(m_nRows);
		m_Grids.SetColumnCount(m_nCols);
		m_Grids.SetColumnWidth(0,15);
		m_Grids.SetRowHeight(0,15);
		for(int i = 1,j = 1;i < m_nRows,j < m_nCols;i++,j++)
		{
			m_Grids.SetRowHeight(i,600/m_nRows);
			m_Grids.SetColumnWidth(j,600/m_nCols);
			
		}
		//填充整个控件
		//m_Grids.ExpandToFit();
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	UpdateData(FALSE);
}
