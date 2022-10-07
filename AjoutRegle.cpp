// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// AjoutRegle.cpp : implementation file
//
/******************************************
Au début, ce fichier gérait la boite de dialogue
D'ajout et de modification des règles de surveillance.
Celle ci ne gère plus maintenant que la bdl de modification,
car celle d'ajout à complétement été refaite
*******************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "AjoutRegle.h"
#include "ScanDlg.h"
#include "ScanViewDlg.h"
//#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NUMBER_OF_STRING 51	


/////////////////////////////////////////////////////////////////////////////
// CAjoutRegle dialog


CAjoutRegle::CAjoutRegle(CWnd* pParent /*=NULL*/)
	: CDialog(CAjoutRegle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjoutRegle)
	m_strAdresse = _T("");
	m_strNom = _T("");
	m_strPort = _T("");
	//}}AFX_DATA_INIT

		CString List[NUMBER_OF_STRING] = {
			"21 (FTP)",
			"25 (SMTP)",
			"110 (POP3)",
			"80 (HTTP)",
			"443 (HTTPS)",
			"143 (IMAP)",
			"135 (NETBIOS)",
			"139 (NETBIOS-SSN)",
			"53 (DNS)",
			"23 (TELNET)",
			"22 (SSH)",
			"37 (TIME)",
			"69 (TFTP)",
			"79 (FINGER)",
			"119 (NNTP)",
			"445 (MICROSOFT-SMB)",
			"515 (PRINTER)",
			"1433 (MS-SQL)",
			"1512 (WINS)",
			"5900 (VNC)",
			"3306 (MYSQL)",
			"389 (LDAP)",
			"520 (EFS)",
			"1723 (PPTP)",
			"543 (KERBEROS)",
			"111 (RPC)",
			"113 (AUTH)",
			"69 (GOPHER)",
			"179 (BGP)",
			"6667 (IRC)",
			"464 (KERBEROS-PASS)",
			"513 (LOGIN)",
			"666 (DOOM)",
			"4662 (EMULE)",
			"3389 (TSE)",
			"5679 (SYNC)",
			"222 (AUS)",			
			"1494 (CITRIX)",
			"106 (EUDORA)",
			"3000 (HBCI)",			
			"1352 (LOTUS NOTES)",
			"8080 (SQUID)",
			"1498 (SYBASE-SQL)",
			"43 (WHOIS)",
			"63 (WHOIS PP)",
			"177 (XDMCP)",
			"1529 (ORACLE)",
			"593 (MS-RPC)",
			"636 (SLDAP)",
			"88 (KERBEROS)",
			"",
	};
	
	m_strPortList = new CString[NUMBER_OF_STRING];

	for( int i = 0; i < NUMBER_OF_STRING; i++ )
	{
		m_strPortList[i] = List[i];
	}

	Tribule( m_strPortList );
}


void CAjoutRegle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjoutRegle)
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_STATIC_SURVEILLE, m_staticSurveille);
	DDX_Control(pDX, IDC_STATIC_RULENAME, m_staticRuleName);
	DDX_Control(pDX, IDC_STATIC_IP, m_staticIP);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_title);
	DDX_Text(pDX, IDC_EDIT_ADRESSE, m_strAdresse);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strNom);
	DDX_CBString(pDX, IDC_COMBO1, m_strPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjoutRegle, CDialog)
	//{{AFX_MSG_MAP(CAjoutRegle)
	ON_BN_CLICKED(IDQUIT, OnQuit)
	ON_BN_CLICKED(ID_AJOUT, OnAjout)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_ADRESSE, OnChangeEditAdresse)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditAdresse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjoutRegle message handlers

BOOL CAjoutRegle::OnInitDialog() 
{
	CDialog::OnInitDialog();

	/*m_link.SetURL( "http://www.techandfeel.net/keeplink/port.htm");
	m_link.SetUnderline( TRUE );
	m_link.SetAutoSize();
	m_link.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	*/

	m_title.SetURL( "http://www.techandfeel.net/keeplink/index.html" );
	m_title.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	if( !m_bitmap.LoadBitmap( IDB_VBANNER2 ) )	
		return FALSE;

	
	for( int i = 0; !m_strPortList[i].IsEmpty(); i++ )
	{
		m_Combo.AddString( m_strPortList[i] );		
	}


	OnChangeEditAdresse();
		
	return TRUE;  
}

void CAjoutRegle::OnQuit() 
{
	OnOK();
}

/**********************************************************
Modifie une règle de surveillance
***********************************************************/
void CAjoutRegle::OnAjout() 
{
	int nItem;
	
	UpdateData( TRUE );	
	GetDlgItem( ID_AJOUT )->EnableWindow( FALSE );

	m_Panneau->m_SockThread.pView   = m_pWnd;
	m_Panneau->m_SockThread.Adresse = m_strAdresse;
	m_Panneau->m_SockThread.port    = atoi( m_strPort );
	m_Panneau->m_SockThread.Nom     = m_strNom;	
	m_Panneau->m_SockThread._this   = m_Panneau;

	
	nItem = m_Panneau->m_SockThread.nItem;
	m_Panneau->m_CurrentListPosition = m_Panneau->m_ListSockThread.FindIndex( nItem );
	m_Panneau->m_ListSockThread.SetAt( m_Panneau->m_CurrentListPosition, m_Panneau->m_SockThread );
	
	
	m_pWnd->m_tableau.SetItemText( nItem, 1, m_strNom );
	m_pWnd->m_tableau.SetItemText( nItem, 2, m_strAdresse );
	m_pWnd->m_tableau.SetItemText( nItem, 3, m_strPort );	

	m_pWnd->GetDocument()->SetModifiedFlag( TRUE );
	CDialog::OnOK();
	
}

/**********************************************************
Passage des pointeurs entre les La view, et la bdl
***********************************************************/
void CAjoutRegle::SetParent( CKeepLink2View *pWnd, CPanneau *Panneau )
{
	m_pWnd    = pWnd;
	m_Panneau = Panneau;
}

/**********************************************************
crée l'effet de transparence pour le logo Tech&Feel
***********************************************************/
void CAjoutRegle::OnPaint() 
{
	CPaintDC dc(this);	
	m_bitmap.DrawTransparent( &dc, 0, 0, RGB( 0xFB, 0xFC, 0xFC) );
}

/**********************************************************
Active/Desactive le bouton modifier
***********************************************************/
void CAjoutRegle::OnChangeEditAdresse() 
{
	UpdateData( TRUE );	
	
	if( !m_strAdresse.IsEmpty() && !m_strNom.IsEmpty() )
		GetDlgItem( ID_AJOUT )->EnableWindow( TRUE );
	else
		GetDlgItem( ID_AJOUT )->EnableWindow( FALSE );
}

void CAjoutRegle::SwitchString(CString &source, CString &dest)
{
	CString tmp = source;
	source      = dest;
	dest        = tmp;
}

void CAjoutRegle::Tribule(CString *List)
{
	for( int i = 1; !List[i].IsEmpty(); i++ )
	{
		if( atoi( List[i].GetBuffer(0) ) < atoi( List[i - 1].GetBuffer(0) ) )
		{
			SwitchString( List[i], List[i - 1] );
			i=1;
			continue;
		}
	}
}
