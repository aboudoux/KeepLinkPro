// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// GeneralDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "GeneralDlg.h"
#include "ProprietiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralDlg dialog


CGeneralDlg::CGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneralDlg)
	m_OperatorName = _T("");
	m_PanneauName = _T("");
	m_nTime = 0;
	m_bCheckAlerte = FALSE;
	//}}AFX_DATA_INIT

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild  = (CMDIChildWnd *) pFrame->GetActiveFrame();
	
	pDoc  = (CKeepLink2Doc *) pChild->GetActiveDocument();
	pView = (CKeepLink2View *) pChild->GetActiveView();
}


void CGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralDlg)
	DDX_Control(pDX, IDC_CHECK_ALERTE, m_ctlCheckAlerte);
	DDX_Control(pDX, IDC_SPIN_TIME, m_spinTime);
	DDX_Text(pDX, IDC_EDIT_OPERATOR_NAME, m_OperatorName);
	DDX_Text(pDX, IDC_EDIT_PANNEAU_NAME, m_PanneauName);
	DDX_Text(pDX, IDC_EDIT_TIME, m_nTime);
	DDX_Check(pDX, IDC_CHECK_ALERTE, m_bCheckAlerte);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralDlg, CDialog)
	//{{AFX_MSG_MAP(CGeneralDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TIME, OnDeltaposSpinTime)
	ON_BN_CLICKED(IDC_CHECK_ALERTE, OnCheckClick)
	ON_EN_CHANGE(IDC_EDIT_PANNEAU_NAME, OnChange)
	ON_EN_CHANGE(IDC_EDIT_OPERATOR_NAME, OnChange)
	ON_EN_CHANGE(IDC_EDIT_TIME, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralDlg message handlers

BOOL CGeneralDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_PanneauName  = pView->Panneau->m_NomDuPanneau;
	m_OperatorName = pView->Panneau->m_NomDuResponsable;
	m_nTime        = pView->Panneau->m_nTemps / 1000;
	m_bCheckAlerte = pView->Panneau->m_bAlerte;
	pPropDlg = ((CProprietiesDlg *)GetParent()->GetParent());

	m_imageList.Create( IDB_LED_ALERTE, 16, 1, (COLORREF)-1 );
	pPropDlg->m_tab.SetImageList( &m_imageList);

	m_ctlCheckAlerte.SetIcon( IDI_ICON_GREEN, IDI_ICON_RED );

	if( m_bCheckAlerte && pPropDlg->m_tab.GetItemCount() == 1 )
	{
		pPropDlg->m_tab.InsertItem(1, "Alerte SON", pView->Panneau->m_bAlerteSon );
		pPropDlg->m_tab.InsertItem(2, "Alerte MAIL", pView->Panneau->m_bAlerteMail );
		pPropDlg->m_tab.InsertItem(3, "Alerte SMS", pView->Panneau->m_bAlerteSms );
		pPropDlg->m_tab.InsertItem(4, "Alerte SYSLOG", pView->Panneau->m_bAlerteSyslog );	
	}

	UpdateData( FALSE );

	return TRUE;  
}

void CGeneralDlg::OnDeltaposSpinTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData( TRUE );
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if( pNMUpDown->iDelta < 0 )
		m_nTime++;
	else if( m_nTime != 0 )
		m_nTime--;

	UpdateData( FALSE );
	pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );

	*pResult = 0;
}


void CGeneralDlg::OnChange() 
{
	UpdateData( TRUE );
	
	int i;
	pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
	
	if( !m_bCheckAlerte )
	{
		for( i = 1; i < pPropDlg->m_tab.GetItemCount(); i )
			pPropDlg->m_tab.DeleteItem( i );
	}
	else if( pPropDlg->m_tab.GetItemCount() == 1 )
	{
	//	m_imageList.Create( IDB_LED_ALERTE, 16, 1, (COLORREF)-1 );
	//	pPropDlg->m_tab.SetImageList( &m_imageList);
	
		pPropDlg->m_tab.InsertItem(1, "Alerte SON", pView->Panneau->m_bAlerteSon );
		pPropDlg->m_tab.InsertItem(2, "Alerte MAIL", pView->Panneau->m_bAlerteMail );
		pPropDlg->m_tab.InsertItem(3, "Alerte SMS", pView->Panneau->m_bAlerteSms );
		pPropDlg->m_tab.InsertItem(4, "Alerte SYSLOG", pView->Panneau->m_bAlerteSyslog );
	}

	Invalidate();
}


BOOL CGeneralDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
    {
		if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
			pMsg->wParam=NULL ;
    }	
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CGeneralDlg::OnCheckClick()
{
	m_bCheckAlerte = !m_bCheckAlerte;
	m_ctlCheckAlerte.SetCheck( m_bCheckAlerte );
	OnChange();
}
