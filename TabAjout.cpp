// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// TabAjout.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "TabAjout.h"
#include "AjoutSimple.h"
#include "AjoutMultiple.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabAjout

CTabAjout::CTabAjout()
{
	m_tabPages[0] = new CAjoutSimple;
	m_tabPages[1] = new CAjoutMultiple;

	m_nNumberOfPages = 2;
}

CTabAjout::~CTabAjout()
{
	for( UINT nCount=0; nCount < m_nNumberOfPages; nCount++ )
	{
		delete m_tabPages[nCount];
		m_tabPages[nCount] = NULL;
	}
}


BEGIN_MESSAGE_MAP(CTabAjout, CTabCtrl)
	//{{AFX_MSG_MAP(CTabAjout)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabAjout message handlers

void CTabAjout::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	
	GetClientRect( &tabRect );
	GetItemRect( 0, &itemRect );
	
	nX  = itemRect.left;
	nY  = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom-nY - 1;
	
	m_tabPages[0]->SetWindowPos( &wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW );

	for( UINT nCount=1; nCount < m_nNumberOfPages; nCount++ )
	{
		m_tabPages[nCount]->SetWindowPos( &wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW );
	}
}

void CTabAjout::Init()
{
	m_tabCurrent=0;
	
	m_tabPages[0]->Create( IDD_AJOUT_SIMPLE, this);
	m_tabPages[1]->Create( IDD_AJOUT_MULTIPLE, this );
	
	
	for( UINT nCount=1; nCount < m_nNumberOfPages; nCount++ )
	{
		m_tabPages[nCount]->ShowWindow(SW_HIDE);	
	}
	
	SetRectangle();	
}

void CTabAjout::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CTabCtrl::OnLButtonDown(nFlags, point);

	m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
	m_tabCurrent=GetCurFocus();		
	m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
	m_tabPages[m_tabCurrent]->SetFocus();
}
