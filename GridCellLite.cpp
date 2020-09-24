

#include "stdafx.h"
#include "GridCell.h"
#include "InPlaceEdit.h"
#include "GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef GRIDCTRL_MINSIZE
/////////////////////////////////////////////////////////////////////////////
// CGridCellAttr default static attributes

DWORD    CGridCellAttr::m_nDefFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX
#ifndef _WIN32_WCE
                                       | DT_END_ELLIPSIS
#endif
                                       ;
COLORREF CGridCellAttr::m_crDefBkClr = CLR_DEFAULT;     // Background colour (or CLR_DEFAULT)
COLORREF CGridCellAttr::m_crDefFgClr = CLR_DEFAULT;     // Forground colour (or CLR_DEFAULT)
LOGFONT  CGridCellAttr::m_lfDefFont;                    // Cell font
UINT     CGridCellAttr::m_nDefMargin = 3;               // Internal cell margin

#endif

IMPLEMENT_DYNCREATE(CGridCell, CGridCellBase)

/////////////////////////////////////////////////////////////////////////////
// GridCell

CGridCell::CGridCell()
{
    Reset();
}

CGridCell::~CGridCell()
{
#ifdef GRIDCTRL_MINSIZE
    delete m_pAttr;
#endif
}

/////////////////////////////////////////////////////////////////////////////
// GridCell Attributes

void CGridCell::Reset()
{
    CGridCellBase::Reset();

    m_strText.Empty();
    m_nImage   = -1;
    m_pGrid    = NULL;
    m_bEditing = FALSE;
    m_pEditWnd = NULL;

#ifdef GRIDCTRL_MINSIZE
    delete m_pAttr;
    m_pAttr    = NULL;
#else
#ifdef _WIN32_WCE
    m_nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX;
#else
    m_nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX | DT_END_ELLIPSIS;
#endif
    m_crBkClr = CLR_DEFAULT;     // Background colour (or CLR_DEFAULT)
    m_crFgClr = CLR_DEFAULT;     // Forground colour (or CLR_DEFAULT)
    m_lfFont;                    // Cell font
    m_nMargin = 3;               // Internal cell margin
#endif
}

/////////////////////////////////////////////////////////////////////////////
// GridCell Operations

BOOL CGridCell::Edit(int nRow, int nCol, CRect rect, CPoint /* point */, UINT nID, UINT nChar)
{
    DWORD dwStyle = ES_LEFT;
    if (GetFormat() & DT_RIGHT) 
        dwStyle = ES_RIGHT;
    else if (GetFormat() & DT_CENTER) 
        dwStyle = ES_CENTER;

    m_bEditing = TRUE;
    
    // InPlaceEdit auto-deletes itself
    CGridCtrl* pGrid = GetGrid();
    m_pEditWnd = new CInPlaceEdit(pGrid, rect, dwStyle, nID, nRow, nCol, GetText(), nChar);
    
    return TRUE;
}

void CGridCell::EndEdit()
{
    if (m_pEditWnd)
        ((CInPlaceEdit*)m_pEditWnd)->EndEdit();
}

void CGridCell::OnEndEdit()
{
    m_bEditing = FALSE;
    m_pEditWnd = NULL;
}

inline DWORD    CGridCell::GetFormat()                 { return m_nFormat; }
inline COLORREF CGridCell::GetTextClr()                { return m_crFgClr; }
inline COLORREF CGridCell::GetBackClr()                { return m_crBkClr; }
inline const LOGFONT* CGridCell::GetFont()             { return &m_lfFont; }
inline UINT     CGridCell::GetMargin()                 { return m_nMargin; }

inline void     CGridCell::SetFormat(DWORD nFormat)    { m_nFormat = nFormat; }                      
inline void     CGridCell::SetTextClr(COLORREF clr)    { m_crFgClr = clr; }                          
inline void     CGridCell::SetBackClr(COLORREF clr)    { m_crBkClr = clr; }                          
inline void     CGridCell::SetFont(const LOGFONT* plf) { memcpy(&(m_lfFont), plf, sizeof(LOGFONT)); }
inline void     CGridCell::SetMargin( UINT nMargin)    { m_nMargin = nMargin; }
