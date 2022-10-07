// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// AlerteSyslogDlg.cpp : implementation file
//

/*********************************************
Gestion des évenements de la boite de dialogue SYSLOG
**********************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "AlerteSyslogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlerteSyslogDlg dialog


CAlerteSyslogDlg::CAlerteSyslogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlerteSyslogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlerteSyslogDlg)
	m_bCheckSyslog = FALSE;
	m_strMessageSyslog = _T("");
	m_strServeurSyslog = _T("");
	m_nEchecSyslog = 0;
	m_level = -1;
	m_service = -1;
	//}}AFX_DATA_INIT

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild  = (CMDIChildWnd *) pFrame->GetActiveFrame();
	
	pView = (CKeepLink2View *) pChild->GetActiveView();

}


void CAlerteSyslogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlerteSyslogDlg)
	DDX_Control(pDX, IDC_EDIT_MESSAGE_SYSLOG, m_MessageCtrl);
	DDX_Control(pDX, IDC_CHECK_SYSLOG, m_ctlCheckSyslog);
	DDX_Check(pDX, IDC_CHECK_SYSLOG, m_bCheckSyslog);
	DDX_Text(pDX, IDC_EDIT_MESSAGE_SYSLOG, m_strMessageSyslog);
	DDX_Text(pDX, IDC_EDIT_SERVEUR_SYSLOG, m_strServeurSyslog);
	DDX_Text(pDX, IDC_EDIT_ECHEC_SYSLOG, m_nEchecSyslog);
	DDV_MinMaxUInt(pDX, m_nEchecSyslog, 1, 65000);
	DDX_CBIndex(pDX, IDC_COMBO_LEVEL_SYSLOG, m_level);
	DDX_CBIndex(pDX, IDC_COMBO_SERVICE_SYSLOG, m_service);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlerteSyslogDlg, CDialog)
	//{{AFX_MSG_MAP(CAlerteSyslogDlg)
	ON_BN_CLICKED(IDC_CHECK_SYSLOG, OnCheckClick)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SYSLOG, OnDeltaposSpinSyslog)
	ON_CBN_SELCHANGE(IDC_COMBO_LEVEL_SYSLOG, OnChange)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVICE_SYSLOG, OnChange)
	ON_EN_CHANGE(IDC_EDIT_SERVEUR_SYSLOG, OnChange)
	ON_EN_CHANGE(IDC_EDIT_MESSAGE_SYSLOG, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ECHEC_SYSLOG, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlerteSyslogDlg message handlers



/*********************************************
initialisation de la boite de dialogue
**********************************************/
BOOL CAlerteSyslogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bCheckSyslog     = pView->Panneau->m_bAlerteSyslog;
	m_nEchecSyslog     = pView->Panneau->m_nAlerteSyslog;
	m_strServeurSyslog = pView->Panneau->m_AlerteSyslog_Serveur;
	m_strMessageSyslog = pView->Panneau->m_AlerteSyslog_Message;
	
	UpdateData( FALSE );

	m_ctlCheckSyslog.SetIcon( IDI_ICON_GREEN, IDI_ICON_RED );

	pPropDlg = ((CProprietiesDlg *)GetParent()->GetParent());
	OnCheckSyslog();
	GetPriority();
	pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( FALSE );

	CString m_help;
	m_help.LoadString( IDS_AIDE );

	m_ToolTip.Create(this);
	
	m_ToolTip.AddTool( &m_MessageCtrl, m_help );
	
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, SHRT_MAX );
	m_ToolTip.Activate( TRUE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*********************************************
Activation/désactivation des controles de la feuille
celon que l'alerte est active ou non
**********************************************/
void CAlerteSyslogDlg::OnCheckSyslog() 
{
	UpdateData( TRUE );
	
	UINT control[] = {
		IDC_STATIC_SYSLOG1,
		IDC_STATIC_SYSLOG2,
		IDC_STATIC_SYSLOG3,
		IDC_STATIC_SYSLOG4,
		IDC_STATIC_SYSLOG5,
		IDC_STATIC_SYSLOG6,
		IDC_EDIT_ECHEC_SYSLOG,
		IDC_EDIT_MESSAGE_SYSLOG,
		IDC_EDIT_MESSAGE_SYSLOG,
		IDC_COMBO_LEVEL_SYSLOG,
		IDC_COMBO_SERVICE_SYSLOG,
		IDC_EDIT_SERVEUR_SYSLOG,
		IDC_SPIN_SYSLOG,
		0
	};

	for( int i = 0; control[i]; i++ )
	{
		GetDlgItem( control[i] )->EnableWindow( m_bCheckSyslog );
	}		

	GetDlgItem( IDC_ICON_SYSLOG_ENABLE )->ShowWindow( m_bCheckSyslog );
	GetDlgItem( IDC_ICON_SYSLOG_DISABLE )->ShowWindow( !m_bCheckSyslog );
	
	if( !m_bCheckSyslog )
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
	
	OnChange();
}

void CAlerteSyslogDlg::OnDeltaposSpinSyslog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData( TRUE );

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if( pNMUpDown->iDelta < 1 )
		m_nEchecSyslog++;
	else if( m_nEchecSyslog != 1 )
		m_nEchecSyslog--;

	UpdateData( FALSE );
	OnChange();

	*pResult = 0;
}



void CAlerteSyslogDlg::SetPriority()
{
	int Service[15] = { LOG_AUTH, LOG_AUTHPRIV, LOG_CRON, LOG_DAEMON, LOG_FTP, 
		LOG_INSTALL, LOG_KERN, LOG_LPR, LOG_MAIL, 
		LOG_NETINFO, LOG_NEWS, LOG_REMOTEAUTH, LOG_SYSLOG, 
		LOG_USER, LOG_UUCP };

	int Level[8] = { LOG_ALERT, LOG_CRIT, LOG_DEBUG, LOG_EMERG, LOG_ERR, LOG_INFO, LOG_NOTICE, LOG_WARNING };

	UpdateData( TRUE );

	pView->Panneau->m_AlerteSyslog_nService = Service[m_service];
	pView->Panneau->m_AlerteSyslog_nLevel   = Level[m_level];
	
}

void CAlerteSyslogDlg::OnChange() 
{
	ButtonTest();

	if( !m_bCheckSyslog )
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
	
	if( m_bCheckSyslog && !m_strMessageSyslog.IsEmpty() && !m_strServeurSyslog.IsEmpty() )
		pPropDlg->GetDlgItem( IDC_APPLIQUER )->EnableWindow( TRUE );
}

void CAlerteSyslogDlg::GetPriority()
{
	int Service[15] = { LOG_AUTH, LOG_AUTHPRIV, LOG_CRON, LOG_DAEMON, LOG_FTP, 
		LOG_INSTALL, LOG_KERN, LOG_LPR, LOG_MAIL, 
		LOG_NETINFO, LOG_NEWS, LOG_REMOTEAUTH, LOG_SYSLOG, 
		LOG_USER, LOG_UUCP };

	int Level[8] = { LOG_ALERT, LOG_CRIT, LOG_DEBUG, LOG_EMERG, LOG_ERR, LOG_INFO, LOG_NOTICE, LOG_WARNING };

	UINT i;

	UpdateData( TRUE );

	for( i = 0; i < 15 ; i++ )
	{
		if( Service[i] == pView->Panneau->m_AlerteSyslog_nService )
		{
			m_service = i;
			break;
		}
	}

	for( i = 0; i < 8 ; i++ )
	{
		if( Level[i] == pView->Panneau->m_AlerteSyslog_nLevel )
		{
			m_level = i;
			break;
		}
	}

	UpdateData( FALSE );
}

void CAlerteSyslogDlg::ButtonTest()
{
	UpdateData( TRUE );

	if( m_bCheckSyslog && !m_strMessageSyslog.IsEmpty() && !m_strServeurSyslog.IsEmpty() )
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( TRUE );
	else
		pPropDlg->GetDlgItem( IDC_BUTTON_TEST )->EnableWindow( FALSE );
}

BOOL CAlerteSyslogDlg::PreTranslateMessage(MSG* pMsg) 
{
	
	if(pMsg->message==WM_KEYDOWN)
    {
		if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
			pMsg->wParam=NULL ;
    }		
	
	m_ToolTip.RelayEvent( pMsg );
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CAlerteSyslogDlg::OnCheckClick()
{
	m_bCheckSyslog = !m_bCheckSyslog;
	m_ctlCheckSyslog.SetCheck( m_bCheckSyslog );
	OnCheckSyslog();
}
