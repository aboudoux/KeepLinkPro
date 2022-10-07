// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// MyTab.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "MyTab.h"
#include "AjoutRegle.h"
#include "AlerteSonDlg.h"
#include "AlerteSMSDlg.h"
#include "AlerteMailDlg.h"
#include "AlerteSyslogDlg.h"
#include "GeneralDlg.h"
#include "ProprietiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTab

CMyTab::CMyTab()
{
	m_tabPages[0] = new CGeneralDlg;
	m_tabPages[1] = new CAlerteSonDlg;
	m_tabPages[2] = new CAlerteMailDlg;
	m_tabPages[3] = new CAlerteSMSDlg;
	m_tabPages[4] = new CAlerteSyslogDlg;
	
	m_nNumberOfPages = 5;

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	
//	pDoc  = (CKeepLink2Doc *) pChild->GetActiveDocument();
	pView = (CKeepLink2View *) pChild->GetActiveView();
	
}

CMyTab::~CMyTab()
{
	for( UINT nCount=0; nCount < m_nNumberOfPages; nCount++ )
	{
		delete m_tabPages[nCount];
		m_tabPages[nCount]=NULL;
	}
}


BEGIN_MESSAGE_MAP(CMyTab, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTab)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTab message handlers

void CMyTab::SetRectangle()
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

void CMyTab::Init()
{
	m_tabCurrent=0;
	
	m_tabPages[0]->Create( IDD_GENERAL,     this);
	m_tabPages[1]->Create( IDD_ALERTE_SON,  this );
	m_tabPages[2]->Create( IDD_ALERTE_MAIL, this );
	m_tabPages[3]->Create( IDD_ALERTE_SMS,  this );
	m_tabPages[4]->Create( IDD_ALERTE_SYSLOG, this );

	
	for( UINT nCount=1; nCount < m_nNumberOfPages; nCount++ )
	{
		m_tabPages[nCount]->ShowWindow(SW_HIDE);	
	}
	
	SetRectangle();
	SetTitle( m_tabCurrent );
	GetParent()->GetDlgItem( IDC_BUTTON_TEST )->ShowWindow( SW_HIDE );

}

void CMyTab::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CTabCtrl::OnLButtonDown(nFlags, point);

	if( m_tabCurrent != (UINT)GetCurFocus() )
	{
		m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent=GetCurFocus();		
		m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_tabPages[m_tabCurrent]->SetFocus();

		SetTitle( m_tabCurrent );

		if( !m_tabCurrent )
			GetParent()->GetDlgItem( IDC_BUTTON_TEST )->ShowWindow( SW_HIDE );
		else
			GetParent()->GetDlgItem( IDC_BUTTON_TEST )->ShowWindow( SW_SHOW );
		
		switch( m_tabCurrent )
		{
		case ALERTE_SON_TAB :
			((CAlerteSonDlg *)m_tabPages[m_tabCurrent])->ButtonTest();
			break;

		case ALERTE_MAIL_TAB :
			((CAlerteMailDlg *)m_tabPages[m_tabCurrent])->ButtonTest();
			break;

		case ALERTE_SMS_TAB :
			((CAlerteSMSDlg *)m_tabPages[m_tabCurrent])->ButtonTest();
			break;

		case ALERTE_SYSLOG_TAB :			
			((CAlerteSyslogDlg *)m_tabPages[m_tabCurrent])->ButtonTest();
			break;
		}
		//m_tabPages[m_tabCurrent]->ButtonTest();
	
	}
}

void CMyTab::SetTitle(UINT nItem)
{
	TCITEM *pTabItem = new TCITEM;
	CString strTmp;
	CString Title;

	pTabItem->mask       = TCIF_TEXT;
	pTabItem->cchTextMax = 29;
	pTabItem->pszText    = Title.GetBuffer( 30 );
	GetItem( m_tabCurrent, pTabItem );
	
	strTmp = Title;
	Title.Format("%s - %s", pView->Panneau->m_NomDuPanneau, strTmp );
	
	GetParent()->SetWindowText( Title );	

	delete pTabItem;
	pTabItem=NULL;
}

