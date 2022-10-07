// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// AlerteSMSDlg.cpp : implementation file
//

/*********************************************
Géestion des évenements de la boite de dialogue
Alerte SMS
**********************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "AlerteSMSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlerteSMSDlg dialog


CAlerteSMSDlg::CAlerteSMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlerteSMSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlerteSMSDlg)
	m_CheckSMS = FALSE;
	m_nEchecSMS = 0;
	m_strMessageSMS = _T("");
	m_strNumeroSMS = _T("");
	m_strComboModem = _T("");
	//}}AFX_DATA_INIT
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild  = (CMDIChildWnd *) pFrame->GetActiveFrame();
	
//	pDoc  = (CKeepLink2Doc *) pChild->GetActiveDocument();
	pView = (CKeepLink2View *) pChild->GetActiveView();
}


void CAlerteSMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlerteSMSDlg)
	DDX_Control(pDX, IDC_EDIT_MESSAGE_SMS, m_MessageCtrl);
	DDX_Control(pDX, IDC_CHECK_SMS, m_ctlCheckSMS);
	DDX_Control(pDX, IDC_COMBO_MODEM, m_ComboModem);
	DDX_Check(pDX, IDC_CHECK_SMS, m_CheckSMS);
	DDX_Text(pDX, IDC_EDIT_ECHECSMS, m_nEchecSMS);
	DDV_MinMaxUInt(pDX, m_nEchecSMS, 1, 65000);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_SMS, m_strMessageSMS);
	DDX_Text(pDX, IDC_EDIT_NUMERO_SMS, m_strNumeroSMS);
	DDX_CBString(pDX, IDC_COMBO_MODEM, m_strComboModem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlerteSMSDlg, CDialog)
	//{{AFX_MSG_MAP(CAlerteSMSDlg)
	ON_BN_CLICKED(IDC_CHECK_SMS, OnCheckClick)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINSMS, OnDeltaposSpinsms)
	ON_EN_CHANGE(IDC_EDIT_NUMERO_SMS, OnChange)
	ON_EN_CHANGE(IDC_EDIT_MESSAGE_SMS, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ECHECSMS, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_MODEM, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlerteSMSDlg message handlers


/*********************************************
Initialisation de la boite de dialogue
**********************************************/
BOOL CAlerteSMSDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_CheckSMS      = pView->Panneau->m_bAlerteSms;
	m_nEchecSMS     = pView->Panneau->m_nAlerteSms;
	m_strNumeroSMS  = pView->Panneau->m_AlerteSms_Numero;
	m_strComboModem = pView->Panneau->m_AlerteSms_Modem;
	m_strMessageSMS = pView->Panneau->m_AlerteSms_Message;

	pPropDlg = ((CProprietiesDlg *)GetParent()->GetParent());
	m_ModemInfo.FillComboBoxWithModemNames( &m_ComboModem );

	m_ctlCheckSMS.SetIcon( IDI_ICON_GREEN, IDI_ICON_RED );

	UpdateData( FALSE );
	OnCheckSmsEnable();

	CString m_help;
	m_help.LoadString( IDS_AIDE );

	m_ToolTip.Create(this);
	
	m_ToolTip.AddTool( &m_MessageCtrl, m_help );
	
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, SHRT_MAX );
	m_ToolTip.Activate( TRUE );
	
	return TRUE;
}


/*********************************************
Active/Désactive tout les controles de la feuilles
selon que l'utilisateur active/désactive l'alerte
**********************************************/
void CAlerteSMSDlg::OnCheckSmsEnable() 
{
	UpdateData( TRUE );
	
	UINT control[] = {
		IDC_STATIC_SMS1,
		IDC_STATIC_SMS2,
		IDC_STATIC_SMS3,
		IDC_STATIC_SMS4,
		IDC_STATIC_SMS5,
		IDC_EDIT_ECHECSMS,
		IDC_EDIT_MESSAGE_SMS,
		IDC_EDIT_NUMERO_SMS,
		IDC_COMBO_MODEM,
		IDC_SPINSMS,
		0
	};

	for( int i = 0; control[i]; i++ )
	{
		GetDlgItem( control[i] )->EnableWindow( m_CheckSMS );
	}

	GetDlgItem( IDC_ICON_SMS_ENABLE )->ShowWindow( m_CheckSMS );
	GetDlgItem( IDC_ICON_SMSDISABLE )->ShowWindow( !m_CheckSMS );
	
	OnChange();	
}


/*********************************************
Enpeche l'utilisateur de presser les touches Echap et entrée,
sauf dans le cas ou le focus ce trouve dans la saisie de message
**********************************************/
BOOL CAlerteSMSDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
    {
		if( pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE )
		{
			if( !(GetFocus()->GetDlgCtrlID() == IDC_EDIT_MESSAGE_SMS && pMsg->wParam == VK_RETURN) )
				pMsg->wParam=NULL ;		
		}
    }

	m_ToolTip.RelayEvent( pMsg );
	
	return CDialog::PreTranslateMessage(pMsg);
}


/*********************************************
incrémente ou décrémente le nombre d'echec via la SpinBox
**********************************************/
void CAlerteSMSDlg::OnDeltaposSpinsms(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData( TRUE );

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if( pNMUpDown->iDelta < 1 )
		m_nEchecSMS++;
	else if( m_nEchecSMS != 1 )
		m_nEchecSMS--;

	UpdateData( FALSE );
	OnCheckSmsEnable();

	*pResult = 0;
}


/*********************************************
Ativation/Desactivation des boutons Appliquer et TEST
**********************************************/
void CAlerteSMSDlg::OnChange() 
{
	UpdateData( TRUE );

	if( !m_CheckSMS )
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );

	if( m_CheckSMS && !m_strMessageSMS.IsEmpty() && !m_strNumeroSMS.IsEmpty() && !m_strComboModem.IsEmpty() )
	{
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
	}
	else
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
}


/*********************************************
Methode publique permettant à la fenetre parent de modifier
le bouton test en cas de load depuis un fichier
**********************************************/
void CAlerteSMSDlg::ButtonTest()
{
	if( m_CheckSMS && !m_strMessageSMS.IsEmpty() && !m_strNumeroSMS.IsEmpty() && !m_strComboModem.IsEmpty() )
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );
	else
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
	
}


/*********************************************
Tips & hack - chope l'evenement du clique sur l'activation de l'alerte
**********************************************/
void CAlerteSMSDlg::OnCheckClick()
{
	m_CheckSMS = !m_CheckSMS;
	m_ctlCheckSMS.SetCheck( m_CheckSMS );
	OnCheckSmsEnable();

}
