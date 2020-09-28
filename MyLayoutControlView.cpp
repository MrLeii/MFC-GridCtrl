
// MyLayoutControlView.cpp : CMyLayoutControlView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyLayoutControl.h"
#endif

#include "MyLayoutControlDoc.h"
#include "MyLayoutControlView.h"

#include "MyLayoutSet.h"
#include "GridCtrl_src\GridCtrl.h"

#include "NewCellTypes/GridURLCell.h"
#include "NewCellTypes/GridCellCombo.h"
#include "NewCellTypes/GridCellCheck.h"
#include "NewCellTypes/GridCellNumeric.h"
#include "NewCellTypes/GridCellDateTime.h"
#include "NewCellTypes\GridCellButton.h"


CMyLayoutSet *mylayoutset;
extern CString strRow,strCol;
BOOL bnSet;
extern BOOL m_Button;
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
ON_COMMAND(ID_CtrlBtn, &CMyLayoutControlView::OnInsertCtrlbtn)
END_MESSAGE_MAP()

// CMyLayoutControlView ����/����

CMyLayoutControlView::CMyLayoutControlView()
	: CFormView(CMyLayoutControlView::IDD)
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CMyLayoutControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	
	OnVirtualMode();

 }




void CMyLayoutControlView::OnVirtualMode()
{
	
    UpdateData(TRUE);
    m_bVirtualMode = !m_bVirtualMode;
	m_Grids.SetVirtualMode(m_bVirtualMode);
    m_Grids.SetEditable(m_bEditable);

    m_bHeaderSort = m_Grids.GetHeaderSort();

	//m_Grid->SetTextBkColor(RGB(0xFF, 0xFF, 0xE0)); //��ɫ����

    if (m_bVirtualMode)
    {
	
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
				m_Grids.SetRowHeight(i,600/(m_nRows-1));
				m_Grids.SetColumnWidth(j,600/(m_nCols-1));
				
			}
			//��������ؼ�
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
	CPoint ptCursor;
	GetCursorPos(&ptCursor);//��ȡ���λ��
	CRect rc;

	GetDlgItem(IDC_CUSTOM_SET)->GetWindowRect(&rc);
	if (rc.PtInRect(ptCursor))
	{
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	GetCursorPos(&point);
	ASSERT(menu.GetSafeHmenu());
	CMenu* pSubMenu = menu.GetSubMenu(0);
	ASSERT(pSubMenu);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,point.x,point.y,this);
	menu.Detach();
	}
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyLayoutControlView ���

#ifdef _DEBUG
void CMyLayoutControlView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyLayoutControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyLayoutControlDoc* CMyLayoutControlView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyLayoutControlDoc)));
	return (CMyLayoutControlDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyLayoutControlView ��Ϣ�������



void CMyLayoutControlView::OnSet()
{
	// TODO: �ڴ���������������
	if (NULL == mylayoutset)  
	{  
		// ������ģ̬�Ի���ʵ��  
		mylayoutset = new CMyLayoutSet();  
		mylayoutset->Create(IDD_DIALOG_SET,this);  
	}  
	// ���Ի����Ѵ򿪣�����ʾ��ģ̬�Ի���  
	mylayoutset->ShowWindow(SW_SHOW);

	//CMyLayoutSet dlg;
	//dlg.DoModal();
}


void CMyLayoutControlView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


/*void CMyLayoutControlView::OnUpdateEditRows()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CFormView::OnRButtonUp(nFlags, point);
}



void CMyLayoutControlView::OnDelRow()
{
	// TODO: �ڴ���������������
	CCellRange Selection = m_Grids.GetSelectedCellRange(); 
	if(!m_Grids.IsValid(Selection)) 
    return   ; 
	CGridCellBase *pCell; 
	int row;
	for(row = Selection.GetMinRow();row <= Selection.GetMaxRow();row++) 
	{ 
		//����ѡ������ʱɾ��
		if(Selection.GetMaxCol() == (m_nCols-1))
		{
			pCell = m_Grids.GetCell(row,1);
			m_Grids.DeleteRow(row);
			m_nRows--;
		}
	}
		//����ֻ��ɾ��һ��
		//if(pCell &&(pCell-> GetState() & GVIS_SELECTED)) 
		//	{
		//		m_Grids.DeleteRow(row);	
		//    } 
	m_Grids.SetColumnWidth(0,15);
	m_Grids.SetRowHeight(0,15);
	for(int i = 1;i < m_nRows;i++)
	{
		m_Grids.SetRowHeight(i,600/(m_nRows-1));
			
	}
	//��������ؼ�
	//m_Grids.ExpandToFit();
	//m_Grids.Invalidate();
	//bSet = FALSE;
	bnSet = FALSE;
	m_Grids.Refresh();
	
}


void CMyLayoutControlView::OnDelcol()
{
	// TODO: �ڴ���������������
	CCellRange Selection = m_Grids.GetSelectedCellRange(); 
	if(!m_Grids.IsValid(Selection)) 
    return   ; 
	CGridCellBase *pCell; 

	for(int col = Selection.GetMinCol();col <= Selection.GetMaxCol();col++) 
	{ 
		if(Selection.GetMaxRow() == (m_nRows-1))
		{
			pCell = m_Grids.GetCell(1,col); 
			m_Grids.DeleteColumn(col);
			m_nCols--;
		}
	} 
	m_Grids.SetRowCount(m_nRows);
	m_Grids.SetColumnCount(m_nCols);
	m_Grids.SetColumnWidth(0,15);
	m_Grids.SetRowHeight(0,15);
	for(int i = 1;i < m_nCols;i++)
	{
		m_Grids.SetColumnWidth(i,600/(m_nCols-1));
			
	}
	bnSet = FALSE;
	m_Grids.Refresh();
}

//�ϲ�
void CMyLayoutControlView::OnMerge()
{
	// TODO: �ڴ���������������
	m_Grids.MergeSelectedCells();
}


//���
void CMyLayoutControlView::OnDiv()
{
	// TODO: �ڴ���������������
	m_Grids.UnMergeSelectedCells();
}

/*void CMyLayoutControlView::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData();
	
	//��ͷ������
	m_nRows = _ttoi(strRow) + 1;
	m_nCols = _ttoi(strCol) + 1;
	UpdateData(FALSE);
	TRY {
        m_Grids.SetRowCount(m_nRows);
		m_Grids.SetColumnCount(m_nCols);
		m_Grids.SetColumnWidth(0,15);
		m_Grids.SetRowHeight(0,15);
		for(int i = 1,j = 1;i < m_nRows,j < m_nCols;i++,j++)
		{
			m_Grids.SetRowHeight(i,600/(m_nRows-1));
			m_Grids.SetColumnWidth(j,600/(m_nCols-1));
			
		}
		//��������ؼ�
		//m_Grids.ExpandToFit();
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	UpdateData(FALSE);
}*/


BOOL CMyLayoutControlView::PreTranslateMessage(MSG* pMsg)
{
	//���õ�Ԫ�񲻿ɱ༭
	m_Grids.EnableDragAndDrop(FALSE);
	m_Grids.SetEditable(FALSE);

	if(bnSet)
	{
		m_nRows = _ttoi(strRow) + 1;
		m_nCols = _ttoi(strCol) + 1;
		m_Grids.SetRowCount(m_nRows);
		m_Grids.SetColumnCount(m_nCols);
		m_Grids.SetColumnWidth(0,15);
		m_Grids.SetRowHeight(0,15);
		for(int i = 1,j = 1;i < m_nRows,j < m_nCols;i++,j++)
		{
			m_Grids.SetRowHeight(i,600/(m_nRows-1));
			m_Grids.SetColumnWidth(j,600/(m_nCols-1));
			
		}
		m_Grids.Refresh();
	}
	/*��������ؼ�
	m_Grids.ExpandToFit();*/
	
	return CView::PreTranslateMessage(pMsg);
}




void CMyLayoutControlView::OnInsertCtrlbtn()
{
	// TODO: �ڴ���������������
	//CCellRange Selection = m_Grids.GetSelectedCellRange(); 
	//if(!m_Grids.IsValid(Selection)) 
 //   return   ; 
	int n;

	//CRect  rect_button(50,50,100,100);//���ư�ťλ�á���С ;
	//m_button.Create(_T("hello"),WS_CHILD|WS_VISIBLE|WS_BORDER,rect_button,this,IDC_BUTTON1);
	//GetDlgItem(IDC_BUTTON1)->SetWindowPos(GetDlgItem(IDC_CUSTOM_SET), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	//m_button.ShowWindow(SW_SHOW);

/*
	switch(n)
	{
	}*/
	m_Grids.SetCellType(1,1, RUNTIME_CLASS(CGridCellButton));

	CGridCellButton* pCell11 = (CGridCellButton*) m_Grids.GetCell(1,1);
	m_Grids.RedrawCell(1,1);

	m_Grids.SetCellType(2,1, RUNTIME_CLASS(CGridCellButton));

	CGridCellButton* pCell21 = (CGridCellButton*) m_Grids.GetCell(2,1);
	m_Grids.RedrawCell(2,1);

	
}
