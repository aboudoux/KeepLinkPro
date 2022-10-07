// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// AlerteMailDlg.cpp : implementation file
//

/*********************************************
Gestion des évenements de la boite de dialogue d'alerte MAIL
**********************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "AlerteMailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlerteMailDlg dialog


CAlerteMailDlg::CAlerteMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlerteMailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlerteMailDlg)
	m_bCheckMail = FALSE;
	m_strDestAddr = _T("");
	m_nEchec = 0;
	m_strMessage = _T("");
	m_strSMTP = _T("");
	m_strSujet = _T("");
	m_strLogin = _T("");
	m_strPassword = _T("");
	m_bCheckAuth = FALSE;
	m_strSource = _T("");
	//}}AFX_DATA_INIT
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild  = (CMDIChildWnd *) pFrame->GetActiveFrame();
	
	pDoc  = (CKeepLink2Doc *) pChild->GetActiveDocument();
	pView = (CKeepLink2View *) pChild->GetActiveView();
}


void CAlerteMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlerteMailDlg)
	DDX_Control(pDX, IDC_EDIT_DEST_ADDR, m_EditDest);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_MessageCtrl);
	DDX_Control(pDX, IDC_EDIT_SUJET, m_sujetCtrl);	
	DDX_Control(pDX, IDC_STATICMAIL2, m_helpMail);
	DDX_Control(pDX, IDC_CHECK_ACTIVE_MAIL, m_ctlCheckMail);
	DDX_Check(pDX, IDC_CHECK_ACTIVE_MAIL, m_bCheckMail);
	DDX_Text(pDX, IDC_EDIT_DEST_ADDR, m_strDestAddr);
	DDX_Text(pDX, IDC_EDIT_ECHECMAIL, m_nEchec);
	DDV_MinMaxUInt(pDX, m_nEchec, 1, 65000);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_strMessage);
	DDX_Text(pDX, IDC_EDIT_SMTP, m_strSMTP);
	DDX_Text(pDX, IDC_EDIT_SUJET, m_strSujet);
	DDX_Text(pDX, IDC_EDIT_MAIL_LOGIN, m_strLogin);
	DDX_Text(pDX, IDC_EDIT_MAIL_PASSWORD, m_strPassword);
	DDX_Check(pDX, IDC_CHECK_AUTH, m_bCheckAuth);
	DDX_Text(pDX, IDC_EDIT_SOURCE_ADRESSE, m_strSource);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlerteMailDlg, CDialog)
	//{{AFX_MSG_MAP(CAlerteMailDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINMAIL, OnDeltaposSpinmail)
	ON_EN_CHANGE(IDC_EDIT_SMTP, OnChange)
	ON_BN_CLICKED(IDC_CHECK_AUTH, OnCheckAuth)
	ON_BN_CLICKED(IDC_CHECK_ACTIVE_MAIL, OnCheckClick)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE_EMETTEUR, OnChange)
	ON_EN_CHANGE(IDC_EDIT_SUJET, OnChange)
	ON_EN_CHANGE(IDC_EDIT_MESSAGE, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ECHECMAIL, OnChange)
	ON_EN_CHANGE(IDC_EDIT_DEST_ADDR, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlerteMailDlg message handlers


/*********************************************
Active/désactive tous les contrôles de la feuille selon
que l'utilisateur active ou désactive l'alerte
**********************************************/
void CAlerteMailDlg::OnCheckActiveMail() 
{
	UpdateData( TRUE );
	
	UINT control[] = {
		IDC_STATICMAIL1,
		IDC_STATICMAIL2,
		IDC_STATICMAIL3,
		IDC_STATICMAIL4,
		IDC_STATICMAIL5,
		IDC_STATICMAIL6,
		IDC_STATICMAIL7,
		IDC_STATICMAIL8,
		IDC_EDIT_ADRESSE,	
		IDC_EDIT_MAIL_LOGIN,
		IDC_EDIT_MAIL_PASSWORD,	
		IDC_EDIT_NOM_EMETEUR,
		IDC_EDIT_SUJET,
		IDC_EDIT_MESSAGE,
		IDC_EDIT_SMTP,
		IDC_EDIT_ECHECMAIL,
		IDC_SPINMAIL,
		IDC_STATIC_GBAUTH,
		IDC_CHECK_AUTH,
		IDC_EDIT_SOURCE_ADRESSE,
		IDC_STATIC_SOURCE_ADDR,
		0
	};

	for( int i = 0; control[i]; i++ )
	{
		GetDlgItem( control[i] )->EnableWindow( m_bCheckMail );
	}

	GetDlgItem( IDC_ICON_MAIL_ENABLE )->ShowWindow( m_bCheckMail );
	GetDlgItem( IDC_ICON_MAIL_DISABLE )->ShowWindow( !m_bCheckMail );

	if( !m_bCheckMail )
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
		
	OnChange();
	OnCheckAuth();
	
}


/*********************************************
initialisation de la boite de dialogue
**********************************************/
BOOL CAlerteMailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bCheckMail  = pView->Panneau->m_bAlerteMail;
	m_nEchec      = pView->Panneau->m_nAlerteMail;
	m_strSMTP     = pView->Panneau->m_AlerteMail_Serveur;
	m_strMessage  = pView->Panneau->m_AlerteMail_Message;
	m_strDestAddr = pView->Panneau->m_AlerteMail_Adresses;
	m_strSujet    = pView->Panneau->m_AlerteMail_Sujet;
	m_strLogin    = pView->Panneau->m_AlerteMail_Login;
	m_strPassword = pView->Panneau->m_AlerteMail_Password;
	m_bCheckAuth  = pView->Panneau->m_bMailAuth;
	m_strSource   = pView->Panneau->m_AlerteMail_AdrEmetteur;
	
	UpdateData( FALSE );

	m_ctlCheckMail.SetIcon( IDI_ICON_GREEN, IDI_ICON_RED);

	pPropDlg = ((CProprietiesDlg *)GetParent()->GetParent());
	OnCheckActiveMail();
	ButtonTest();

	pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( FALSE );

	CString m_help;
	m_help.LoadString( IDS_AIDE );
	
	m_ToolTip.Create(this);
	
	m_ToolTip.AddTool( &m_sujetCtrl, m_help );
	m_ToolTip.AddTool( &m_MessageCtrl, m_help );
	m_ToolTip.AddTool( &m_EditDest, "Pour définir plusieurs adresses, séparez les par des points virgules\r\n"
									"Exemple : keeplink@tech.com;operator@essai.fr;responsable@test.net");
	
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, SHRT_MAX );
	m_ToolTip.Activate( TRUE );	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*********************************************
Incrémente/décremente le nombre d'echec de connexion
grace à la spin BOX
**********************************************/
void CAlerteMailDlg::OnDeltaposSpinmail(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData( TRUE );

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if( pNMUpDown->iDelta < 1 )
		m_nEchec++;
	else if( m_nEchec != 1 )
		m_nEchec--;

	UpdateData( FALSE );
	OnChange();

	*pResult = 0;
}


/*********************************************
Active/désactive les boutons TEST & Appliqué celon
l'état des controles de saisies
**********************************************/
void CAlerteMailDlg::OnChange() 
{
	UpdateData( TRUE );
	
	if( !m_bCheckMail )
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );

	if( m_bCheckMail && !m_strSMTP.IsEmpty() && !m_strDestAddr.IsEmpty() && !m_strSujet.IsEmpty() && !m_strMessage.IsEmpty() )
	{
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
	}
	else	
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
}


/*********************************************
Empéche l'utilisateur d'utiliser les touches Entrée et échapes, sauf
si le focus est dans la boite d'édition de message
**********************************************/
BOOL CAlerteMailDlg::PreTranslateMessage(MSG* pMsg) 
{

	if(pMsg->message==WM_KEYDOWN)
    {
		if( pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE )
		{
			if( !(GetFocus()->GetDlgCtrlID() == IDC_EDIT_MESSAGE && pMsg->wParam == VK_RETURN) )
				pMsg->wParam=NULL ;		
		}
    }

	m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}


/*********************************************
Méthode publique, pour que le parrent puisse activer
ou désactiver le bouton test lors du load des fichiers
**********************************************/
void CAlerteMailDlg::ButtonTest()
{
	UpdateData( TRUE );
	pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->ShowWindow( SW_SHOW );

	if( m_bCheckMail && !m_strSMTP.IsEmpty() &&  !m_strDestAddr.IsEmpty() && !m_strSujet.IsEmpty() && !m_strMessage.IsEmpty() )
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );		
	else
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );		
}


/*********************************************
Tips & hack - chope l'evenement de la check box 
d'activation/désactivation d'alerte
**********************************************/
void CAlerteMailDlg::OnCheckClick()
{
	m_bCheckMail = !m_bCheckMail;
	m_ctlCheckMail.SetCheck( m_bCheckMail );
	OnCheckActiveMail();
}


/*********************************************
Active / désactive les controles de l'authentification SMTP
**********************************************/
void CAlerteMailDlg::OnCheckAuth() 
{
	UpdateData( TRUE );

	if( !m_bCheckMail )
		return;

	GetDlgItem( IDC_EDIT_MAIL_LOGIN )->EnableWindow( m_bCheckAuth );
	GetDlgItem( IDC_EDIT_MAIL_PASSWORD )->EnableWindow( m_bCheckAuth );
	GetDlgItem( IDC_STATICMAIL3 )->EnableWindow( m_bCheckAuth );
	GetDlgItem( IDC_STATICMAIL4 )->EnableWindow( m_bCheckAuth );
}
