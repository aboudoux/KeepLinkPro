// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// AlerteSonDlg.cpp : implementation file
//

/*********************************************
Gestion des évenements de la boite de dialogue
d'alerte SON
**********************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "AlerteSonDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlerteSonDlg dialog


CAlerteSonDlg::CAlerteSonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlerteSonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlerteSonDlg)
	m_nEchecSon = 0;
	m_strSound = _T("");
	m_bCheckSon = FALSE;
	//}}AFX_DATA_INIT
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild  = (CMDIChildWnd *) pFrame->GetActiveFrame();
	
	pDoc  = (CKeepLink2Doc *) pChild->GetActiveDocument();
	pView = (CKeepLink2View *) pChild->GetActiveView();
}


void CAlerteSonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlerteSonDlg)
	DDX_Control(pDX, IDC_CHECK_SONENABLE, m_ctlCheckSon);
	DDX_Text(pDX, IDC_EDIT_ECHECSON, m_nEchecSon);
	DDV_MinMaxUInt(pDX, m_nEchecSon, 1, 65000);
	DDX_Text(pDX, IDC_EDIT_FICHIERSON, m_strSound);
	DDX_Check(pDX, IDC_CHECK_SONENABLE, m_bCheckSon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlerteSonDlg, CDialog)
	//{{AFX_MSG_MAP(CAlerteSonDlg)
	ON_BN_CLICKED(IDC_CHECK_SONENABLE, OnCheckClick)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINSON, OnDeltaposSpinson)
	ON_EN_CHANGE(IDC_EDIT_FICHIERSON, OnChangeEditFichierson)
	ON_BN_CLICKED(IDC_BUTTON_PARCOURIRSON, OnButtonParcourir)
	ON_EN_CHANGE(IDC_EDIT_ECHECSON, OnChangeEditEchecson)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlerteSonDlg message handlers


/*********************************************
Activation/Désactivation de tout les controles de
la feuille en fonction de l'état du bouton D'activation de l'alerte
**********************************************/
void CAlerteSonDlg::OnCheckSonenable() 
{
	UpdateData(TRUE);

	UINT control[] = {
		IDC_BUTTON_PARCOURIRSON,
		IDC_EDIT_ECHECSON,
		IDC_EDIT_FICHIERSON,
		IDC_SPINSON,
		IDC_STATIC_SON1,
		IDC_STATIC_SON2,
		IDC_STATIC_SON3,
		0
	};

	for( int i = 0; control[i]; i++ )
	{
		GetDlgItem( control[i] )->EnableWindow( m_bCheckSon );
	}	


	GetDlgItem( IDC_ICON_SON_ENABLE )->ShowWindow( m_bCheckSon );
	GetDlgItem( IDC_ICON_SON_DISABLE )->ShowWindow( !m_bCheckSon );

	if( m_bCheckSon )
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( !m_strSound.IsEmpty() );				
	else
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
	
	OnChangeEditFichierson();

}


/*********************************************
Empeche l'utilisateur de presser les touches Echap et Entrée
**********************************************/
BOOL CAlerteSonDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
    {
		if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
			pMsg->wParam=NULL ;
    }	
	
	return CDialog::PreTranslateMessage(pMsg);
}



/*********************************************
IncrémentationDécrementation du nombre d'echec
via la SpinBox
**********************************************/
void CAlerteSonDlg::OnDeltaposSpinson(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData( TRUE );

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if( pNMUpDown->iDelta < 1 )
		m_nEchecSon++;
	else if( m_nEchecSon != 1 )
		m_nEchecSon--;

	UpdateData( FALSE );
	OnChangeEditFichierson();

	*pResult = 0;
}


/*********************************************
initialisation de la boite de dialogue
**********************************************/
BOOL CAlerteSonDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_nEchecSon = pView->Panneau->m_nAlerteSon;
	m_strSound  = pView->Panneau->m_AlerteSon_Fichier;
	m_bCheckSon = pView->Panneau->m_bAlerteSon;

	m_ctlCheckSon.SetIcon( IDI_ICON_GREEN, IDI_ICON_RED );
	UpdateData( FALSE );

	pPropDlg = ((CProprietiesDlg *)GetParent()->GetParent());
	OnCheckSonenable();
	pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( FALSE );

	return TRUE;  
}


/*********************************************
Activation des boutons TEST & Appliquer
**********************************************/
void CAlerteSonDlg::OnChangeEditFichierson() 
{
	UpdateData( TRUE );
	
	if( !m_bCheckSon || !m_strSound.IsEmpty() )
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );	
	
	ButtonTest();
}


/*********************************************
ouvre le boite de dialogue permettant de parcourir le disque
à la recherche d'un fichier son
**********************************************/
void CAlerteSonDlg::OnButtonParcourir() 
{
	static char szFilter[] = "WAV Files (*.wav)|*.wav|MIDI Files (*.mid)|*.mid|All Files (*.*)|*.*|";
	CFileDialog fdialog( TRUE, "wav" , "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter );

	if( fdialog.DoModal() == IDOK )
	{
		m_strSound = fdialog.GetPathName();
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
	}	
	
	UpdateData( FALSE );	
}


/*********************************************
Si l'editBox du chemin de son est changer, active le bouton appliquer
**********************************************/
void CAlerteSonDlg::OnChangeEditEchecson() 
{
	pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
}


/*********************************************
Fonction publique pour l'activation du bouton test via une fenetre parent
**********************************************/
void CAlerteSonDlg::ButtonTest()
{
	pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->ShowWindow( SW_SHOW );

	if( m_bCheckSon && !m_strSound.IsEmpty() )
	{
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );
	//	pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
	}
	else
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
}


/*********************************************
Tips & Hack - chope l'evenement sur le bouton d'activation de l'alerte
**********************************************/
void CAlerteSonDlg::OnCheckClick()
{
	m_bCheckSon = !m_bCheckSon;
	m_ctlCheckSon.SetCheck( m_bCheckSon );
	OnCheckSonenable();
}
