// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// ProprietiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "ProprietiesDlg.h"
#include "GeneralDlg.h"
#include "AlerteSonDlg.h"
#include "AlerteMailDlg.h"
#include "AlerteSyslogDlg.h"
#include "AlerteSMSDlg.h"
#include "cSound.h"
#include "B64crypt.h"

#pragma comment( lib, ".\\res\\WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProprietiesDlg dialog


CProprietiesDlg::CProprietiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProprietiesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProprietiesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProprietiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProprietiesDlg)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProprietiesDlg, CDialog)
	//{{AFX_MSG_MAP(CProprietiesDlg)
	ON_BN_CLICKED(IDC_QUITTER, OnQuitter)
	ON_BN_CLICKED(IDC_APPLIQUER, OnAppliquer)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProprietiesDlg message handlers

BOOL CProprietiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_imageList.Create( IDB_LED_ALERTE, 16, 1, (COLORREF)-1 );
	m_tab.SetImageList( &m_imageList);
	
	m_tab.InsertItem(0, "Général", 2 );
	m_tab.Init( );
	

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	
	pDoc  = (CKeepLink2Doc *) pChild->GetActiveDocument();
	pView = (CKeepLink2View *) pChild->GetActiveView();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProprietiesDlg::OnQuitter() 
{
	CDialog::OnOK()	;
}

void CProprietiesDlg::OnAppliquer() 
{
	CGeneralDlg      *   pGeneralDlg    = ((CGeneralDlg *)m_tab.m_tabPages[GENERAL_TAB]);
	CAlerteSonDlg    * pAlerteSonDlg    = ((CAlerteSonDlg *)m_tab.m_tabPages[ALERTE_SON_TAB]);
	CAlerteMailDlg   * pAlerteMailDlg   = ((CAlerteMailDlg *)m_tab.m_tabPages[ALERTE_MAIL_TAB]);
	CAlerteSMSDlg    * pAlerteSmsDlg    = ((CAlerteSMSDlg *)m_tab.m_tabPages[ALERTE_SMS_TAB]);
	CAlerteSyslogDlg * pAlerteSyslogDlg = ((CAlerteSyslogDlg *)m_tab.m_tabPages[ALERTE_SYSLOG_TAB]);

//	switch( m_tab.GetCurSel() )
//	{
//	case GENERAL_TAB :
	BOOL IconState[10];
	RtlZeroMemory( &IconState, m_tab.m_nNumberOfPages * sizeof( BOOL ) );

			// raffraichi l'état des variables
			pGeneralDlg->UpdateData( TRUE );

			// enregistre dans l'objet CPanneau les variables de la fenêtre
			pView->Panneau->m_NomDuPanneau     = pGeneralDlg->m_PanneauName;
			pView->Panneau->m_NomDuResponsable = pGeneralDlg->m_OperatorName;
			pView->Panneau->m_nTemps           = pGeneralDlg->m_nTime * 1000;
			pView->Panneau->m_bAlerte          = pGeneralDlg->m_bCheckAlerte;

			// réacualise la vision du document
			pDoc->SetTitle( pView->Panneau->m_NomDuPanneau );
			m_tab.SetTitle( GENERAL_TAB );


//	case ALERTE_SON_TAB :

			pAlerteSonDlg->UpdateData( TRUE );

			pView->Panneau->m_bAlerteSon        = IconState[ALERTE_SON_TAB] = pAlerteSonDlg->m_bCheckSon;
			pView->Panneau->m_AlerteSon_Fichier = pAlerteSonDlg->m_strSound;
			pView->Panneau->m_nAlerteSon        = pAlerteSonDlg->m_nEchecSon;			

//	case ALERTE_MAIL_TAB :

			pAlerteMailDlg->UpdateData( TRUE );		

			if( (pAlerteMailDlg->m_strSMTP.IsEmpty() || 
				// login
				// password


				pAlerteMailDlg->m_strDestAddr.IsEmpty() || 
				pAlerteMailDlg->m_strSujet.IsEmpty() || 
				pAlerteMailDlg->m_strMessage.IsEmpty()) &&  pAlerteMailDlg->m_bCheckMail )
			{
				MessageBox( "Les paramètres de l'alerte Mail ne seront pas appliqués, car un ou plusieurs champs de saisie sont vides.\r\n\r\n"
							"Veuillez renseigner tous les paramètres concernant cette alerte de façon à ce qu'elle puisse être activée.", "KeepLink PRO - Alerte Email", MB_ICONERROR );

				IconState[ALERTE_MAIL_TAB] = pView->Panneau->m_bAlerteMail = FALSE;
				pAlerteMailDlg->OnCheckClick();

			}
			else
			{
				pView->Panneau->m_bAlerteMail            = IconState[ALERTE_MAIL_TAB] = pAlerteMailDlg->m_bCheckMail;
				pView->Panneau->m_nAlerteMail            = pAlerteMailDlg->m_nEchec;
				pView->Panneau->m_AlerteMail_Serveur     = pAlerteMailDlg->m_strSMTP;
				pView->Panneau->m_AlerteMail_Message     = pAlerteMailDlg->m_strMessage;
				pView->Panneau->m_AlerteMail_Adresses    = pAlerteMailDlg->m_strDestAddr;
				pView->Panneau->m_AlerteMail_Sujet       = pAlerteMailDlg->m_strSujet;
				pView->Panneau->m_bMailAuth              = pAlerteMailDlg->m_bCheckAuth;
				pView->Panneau->m_AlerteMail_Login       = pAlerteMailDlg->m_strLogin;
				pView->Panneau->m_AlerteMail_AdrEmetteur = pAlerteMailDlg->m_strSource;

				CString tmp;
				tmp = pAlerteMailDlg->m_strPassword;
				
				CB64crypt obj64Crypt;
				if( !obj64Crypt.DeCrypt( tmp.GetBuffer( 0 )))
				{
					obj64Crypt.Crypt( tmp.GetBuffer(0) );
					pView->Panneau->m_AlerteMail_Password    = obj64Crypt.pCrypt;
				}				
				
			}			
			
			if( m_tab.GetCurSel() == ALERTE_MAIL_TAB )
			{
				if( !pAlerteMailDlg->m_strSMTP.IsEmpty() &&  !pAlerteMailDlg->m_strDestAddr.IsEmpty() && 
					!pAlerteMailDlg->m_strSujet.IsEmpty() && !pAlerteMailDlg->m_strMessage.IsEmpty() && 
					pAlerteMailDlg->m_bCheckMail )
				{
					GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );
				}
			}

//  case ALERTE_SMS_TAB :

			pAlerteSmsDlg->UpdateData( TRUE );
			pView->Panneau->m_bAlerteSms        = IconState[ALERTE_SMS_TAB] = pAlerteSmsDlg->m_CheckSMS;
			pView->Panneau->m_AlerteSms_Numero  = pAlerteSmsDlg->m_strNumeroSMS;
			pView->Panneau->m_AlerteSms_Message = pAlerteSmsDlg->m_strMessageSMS;
			pView->Panneau->m_AlerteSms_Modem   = pAlerteSmsDlg->m_strComboModem;
			pView->Panneau->m_nAlerteSms        = pAlerteSmsDlg->m_nEchecSMS;
			
			int nIndex;

			if( !pAlerteSmsDlg->m_strComboModem.IsEmpty() )
			{
				
				pView->Panneau->m_strComPort.Format("COM%u", pAlerteSmsDlg->m_ModemInfo.GetModemComPort( pAlerteSmsDlg->m_strComboModem ) );
				pView->Panneau->m_strInitString = pAlerteSmsDlg->m_ModemInfo.GetModemInitString( pAlerteSmsDlg->m_strComboModem );
				
				if( (nIndex = pView->Panneau->m_strInitString.Find("<cr>") ) )
					pView->Panneau->m_strInitString.Delete( nIndex, 4 );
			}
			
			//	case ALERTE_SYSLOG_TAB :
			
			pAlerteSyslogDlg->SetPriority();
			pView->Panneau->m_AlerteSyslog_Serveur = pAlerteSyslogDlg->m_strServeurSyslog;
			pView->Panneau->m_AlerteSyslog_Message = pAlerteSyslogDlg->m_strMessageSyslog;
			pView->Panneau->m_nAlerteSyslog        = pAlerteSyslogDlg->m_nEchecSyslog;
			pView->Panneau->m_bAlerteSyslog        = IconState[ALERTE_SYSLOG_TAB] = pAlerteSyslogDlg->m_bCheckSyslog;
//	}	

	if( m_tab.GetItemCount() > 1 )
	{
		TC_ITEM item;
		item.mask = TCIF_IMAGE;

		for( UINT i = 1; i < m_tab.m_nNumberOfPages; i ++ )
		{
			item.iImage = IconState[i];
			m_tab.SetItem( i, &item );
		}		
	}

	GetDlgItem( IDC_APPLIQUER )->EnableWindow( FALSE );
	pDoc->SetModifiedFlag( TRUE );
}


void CProprietiesDlg::OnButtonTest() 
{

	switch( m_tab.GetCurSel() )
	{
	case ALERTE_SON_TAB :
		{
			cSound sound;
			if( sound.PlaySoundFile( ((CAlerteSonDlg *)m_tab.m_tabPages[1])->m_strSound.GetBuffer(0) ) )
				MessageBox("Impossible de jouer le son\n\n"
						   "Vérifiez que le chemin sélectionné correspond à un son existant",				
				"Erreur", MB_ICONERROR );

			break;
		}
	case ALERTE_MAIL_TAB :
		{				
			OnAppliquer();
			switch( pView->SendMail( -1 ) )
			{
			case 0 : MessageBox("Votre message de test vient d'être envoyé !", "Test d'alerte MAIL", MB_ICONINFORMATION );
				break;
			case 1 : MessageBox("Impossible de se connecter au serveur SMTP", "Test d'alerte MAIL", MB_ICONERROR );
				break;
			case 2 : MessageBox("L'authentification au serveur SMTP a échoué.", "Test d'alerte MAIL", MB_ICONERROR );
				break;
			}
			
			break;
		}
	case ALERTE_SMS_TAB :
		{
			OnAppliquer();
			pView->SendSMS( -1 );
			
			break;
		}
	case ALERTE_SYSLOG_TAB :
		{
			OnAppliquer();
			if( pView->SendSyslogMessage( -1 ) )
				MessageBox("Votre message de test vient d'être envoyé !", "Test d'alerte SYSLOG", MB_ICONINFORMATION );
			else
				MessageBox("Impossible de se connecter au serveur SYSLOG", "Erreur", MB_ICONERROR );
				
			break;
		}
	}	
}

void CProprietiesDlg::OnOK() 
{
	OnAppliquer();	
	CDialog::OnOK();
}
