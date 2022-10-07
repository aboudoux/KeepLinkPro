// myedit.cpp : implementation file
// this class is to catch the messages sent to the edit box,
// so that we may use the arrow or tab keys to move to the 
// next item and begin editing

#include "stdafx.h"
#include "listview.h"
#include "myedit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if !defined(LISTCTL_H)
    #include "listctl.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
:   x (0), 
    y (0)
{
} // CMyEdit

CMyEdit::~CMyEdit()
{
} // ~CMyEdit


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
    //{{AFX_MSG_MAP(CMyEdit)
    ON_WM_GETDLGCODE()
    ON_WM_KEYDOWN()
    ON_WM_WINDOWPOSCHANGING()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

// tell the parent control that we do want to recieve arrow keys
// and tab key messages
UINT 
CMyEdit::OnGetDlgCode () 
{
    UINT Code = CEdit::OnGetDlgCode () | DLGC_WANTARROWS | DLGC_WANTTAB;
    return Code;
} // OnGetDlgCode


// catch the keys we want and forward them to the list control
void 
CMyEdit::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    CMyListCtl* pParent = (CMyListCtl*)GetParent ();
    switch (nChar)
    {
		case VK_TAB:
		{
			::SendMessage (pParent->m_hWnd, WM_KEYDOWN, VK_TAB, 0L);
			break;
		}
		case VK_UP :
		{
			::SendMessage (pParent->m_hWnd, WM_KEYDOWN, VK_UP, 0L);
			break;
		}
		case VK_DOWN :
		{
			::SendMessage (pParent->m_hWnd, WM_KEYDOWN, VK_DOWN, 0L);
			break;
		}
		case VK_F2 :
		{
			::SendMessage (pParent->m_hWnd, WM_KEYDOWN, VK_F2, 0L);
			break;
		}
		default :
		{
			CEdit::OnKeyDown (nChar, nRepCnt, nFlags);
			break;
		}
    }
} // OnKeyDown

void 
CMyEdit::OnWindowPosChanging (WINDOWPOS FAR* pwndpos) 
{
    pwndpos->x = x;
    pwndpos->y = y;
    CEdit::OnWindowPosChanging(pwndpos);	
} // OnWindowPosChanging
