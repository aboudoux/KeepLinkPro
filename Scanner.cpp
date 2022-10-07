// Scanner.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "Scanner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanner dialog


CScanner::CScanner(CWnd* pParent /*=NULL*/)
	: CDialog(CScanner::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanner)
	m_pDest = 0;
	m_pSource = 0;
	m_max_thread = 0;
	m_lThread = 0;
	m_tThread = 0;
	m_strAdresse = _T("");
	m_description = _T("");
	//}}AFX_DATA_INIT

	pScanList = NULL;
}


void CScanner::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanner)
	DDX_Control(pDX, ID_COMBO_SCAN, m_combo);
	DDX_Control(pDX, IDC_EDIT_SCAN_LIST, m_list);
	DDX_Control(pDX, IDC_EDIT_SCAN_PROGRESS, m_progress);
	DDX_Text(pDX, IDC_EDIT_SCAN_PORT_DEST, m_pDest);
	DDV_MinMaxDWord(pDX, m_pDest, 0, 65534);
	DDX_Text(pDX, IDC_EDIT_SCAN_PORT_SOURCE, m_pSource);
	DDV_MinMaxDWord(pDX, m_pSource, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_SCAN_MAX_THREAD, m_max_thread);
	DDX_Text(pDX, IDC_EDIT_SCAN_LTHREAD, m_lThread);
	DDX_Text(pDX, IDC_EDIT_SCAN_TTHREAD, m_tThread);
	DDX_Text(pDX, IDC_EDIT_SCAN_ADRESSE, m_strAdresse);
	DDX_Text(pDX, IDC_DESCRIPT, m_description);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanner, CDialog)
	//{{AFX_MSG_MAP(CScanner)
	ON_BN_CLICKED(IDC_EDIT_SCAN_RADIO1, OnRadioButton)
	ON_BN_CLICKED(ID_SCAN_START, OnButtonStart)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_SCAN_ADRESSE, OnChangeEditScanAdresse)
	ON_CBN_SELCHANGE(ID_COMBO_SCAN, OnSelchangeComboScan)
	ON_BN_CLICKED(IDC_EDIT_SCAN_RADIO2, OnRadioButton)
	ON_BN_CLICKED(IDC_OK, OnButtonOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanner message handlers

BOOL CScanner::OnInitDialog() 
{
	CDialog::OnInitDialog();

	OnChangeEditScanAdresse();

	m_pSource = 1;
	m_pDest   = 1024;
	m_max_thread = 500;

	CheckDlgButton( IDC_EDIT_SCAN_RADIO1, TRUE );
	
	UpdateData( FALSE );
	

	return TRUE; 
}

void CScanner::OnOK() 
{
	CString title;
	GetDlgItem( ID_SCAN_START )->GetWindowText( title );
	
	if( title == "A&rrêter"  )
	{
		GetDlgItem( IDOK )->SetWindowText( "Wait...");
		GetDlgItem( IDOK )->EnableWindow( FALSE );
		OnScanStop();
	}

	EndDialog( -1 );
}

void CScanner::OnRadioButton() 
{
	UpdateData( TRUE );

	if( IsDlgButtonChecked( IDC_EDIT_SCAN_RADIO1 ) )
		m_max_thread = 500;
	else
		m_max_thread = 255;
	
	UpdateData( FALSE);
}
//
// Clique sur le bouton démarrer
//
void CScanner::OnButtonStart() 
{	
	CString title;
	GetDlgItem( ID_SCAN_START )->GetWindowText( title );

	if( title == "&Démarrer" )
		OnScanStart();
	else
		OnScanStop();
}

/******************************
Fonction de démarrage
*******************************/
void CScanner::OnScanStart() 
{
	UpdateData( TRUE );

	if( m_strAdresse.IsEmpty() )
	{
		MessageBox("Veuillez entrer une adresse", NULL, MB_ICONERROR );
		return;
	}

	thisThread = new MYTHREAD[m_max_thread];	
	m_bStack   = new BOOL[m_max_thread];
	RtlZeroMemory( m_bStack, m_max_thread * sizeof(BOOL) );

	dwPort = m_pSource;
	m_lThread = 0;
	m_tThread = 0;
	m_list.ResetContent();

	GetDlgItem( IDC_STATIC_QUESTION )->EnableWindow( FALSE );
	GetDlgItem( ID_COMBO_SCAN )->EnableWindow( FALSE );
	GetDlgItem( IDC_OK )->EnableWindow( FALSE );
	GetDlgItem( ID_SCAN_START )->SetWindowText( "A&rrêter" );

	GetDlgItem( IDC_DESCRIPT )->EnableWindow( FALSE );
	m_combo.SetCurSel( -1 );	
	OnSelchangeComboScan();
	
	m_progress.SetRange32( m_pSource, m_pDest );
	m_progress.SetStep( 1 );
	m_progress.SetPos( 0 );

	SetTimer( 1, 1000, NULL );
}

void CScanner::OnScanStop()
{
	KillTimer( 1 );
	GetDlgItem( ID_SCAN_START )->EnableWindow( FALSE );
	GetDlgItem( ID_SCAN_START )->SetWindowText("Wait...");
	
	while( TRUE )
	{
		for( DWORD i = 0; i < m_max_thread; i++ )
		{
			if( m_bStack[i] )
			{
				Sleep( 100 );
				i = 0;
				continue;
			}				
		}
		
		if( i == m_max_thread  )
			break;	
	}
	
	GetDlgItem( ID_SCAN_START )->SetWindowText("&Démarrer");
	GetDlgItem( ID_SCAN_START )->EnableWindow( TRUE );

	int nPort = m_list.GetCount();
	if(  nPort )
	{
		// Si des ports on été trouvé, enable les controles
		// à la fin du scan
		GetDlgItem( IDC_STATIC_QUESTION )->EnableWindow( TRUE );
		GetDlgItem( ID_COMBO_SCAN )->EnableWindow( TRUE );
		GetDlgItem( IDC_OK )->EnableWindow( TRUE );
		GetDlgItem( IDC_DESCRIPT )->EnableWindow( TRUE );

		// création de la liste des ports en mémoire
		CString * pTmpString;
		pTmpString = new CString[nPort + 1];

		int i,j;
		for( i=0; i < nPort; i++ )
		{
			m_list.GetText( i, pTmpString[i]);
		}			
		pTmpString[i].Empty();

		// compare à la liste principale pour obteni la corréspondance
		// port -> nom
		for( i=0; !pTmpString[i].IsEmpty(); i++ )
		{
			for( j=0; !m_pAjout->m_strPortList[j].IsEmpty(); j++ )
			{
				if( atoi( pTmpString[i].GetBuffer(0)) == atoi( m_pAjout->m_strPortList[j]) )
				{
					pTmpString[i] = m_pAjout->m_strPortList[j];
					break;
				}
			}
		}
		
		// si plus de 2 ports Procède au rangement de la liste
		if( nPort > 1 )
		{						
			m_pAjout->Tribule( pTmpString );						
		}

		// Affiche la nouvelle liste de port
		m_list.ResetContent();
		
		for( i=0; i < nPort; i++ )
		{
			m_list.AddString( pTmpString[i] );
		}			

		delete[] pTmpString;

		// Set la comboBox de choix
		m_combo.SetCurSel( 0 );
		OnSelchangeComboScan();
	}
	else
	{
		GetDlgItem( IDC_STATIC_QUESTION )->EnableWindow( FALSE );
		GetDlgItem( ID_COMBO_SCAN )->EnableWindow( FALSE );
		GetDlgItem( IDC_OK )->EnableWindow( FALSE );
		GetDlgItem( IDC_DESCRIPT )->EnableWindow( FALSE );
		m_combo.SetCurSel( -1 );
		OnSelchangeComboScan();
	}


	delete[] thisThread;
	delete[] m_bStack;
	thisThread=NULL;
	m_bStack=NULL;
}



void CScanner::OnTimer(UINT nIDEvent) 
{
	if( dwPort >= m_pDest )
	{
		OnScanStop();		
	}
	else
	{			
		for( DWORD i = 0; i < m_max_thread; i++ )
		{
			if( !m_bStack[i] && (dwPort < m_pDest) )
			{
				thisThread[i]._this  = this;
				thisThread[i].bMutex = &m_bStack[i];
				thisThread[i].port   = dwPort;
				
				AfxBeginThread( ConnectThread, &thisThread[i] );
				dwPort++;							
			}
		}
		
	}

	m_lThread = dwPort - m_pSource;	
	UpdateData( FALSE );
	
	CDialog::OnTimer(nIDEvent);
}

UINT CScanner::ConnectThread(LPVOID pParam)
{
	MYTHREAD * Localparam = (MYTHREAD *)pParam;
	CSocket tSocket;
	CString tmpStr;		

	*Localparam->bMutex = TRUE;
	tSocket.Create();

	if( tSocket.Connect( Localparam->_this->m_strAdresse, Localparam->port ) )
	{
		tmpStr.Format("%u", Localparam->port );
		Localparam->_this->m_list.AddString( tmpStr );		
	}

	tSocket.Close();
	*Localparam->bMutex = FALSE;
	Localparam->_this->m_tThread++;
	Localparam->_this->m_progress.StepIt();
	
	AfxEndThread( 0 );

	return 0;
}


void CScanner::OnChangeEditScanAdresse() 
{
	UpdateData( TRUE );

	GetDlgItem( ID_SCAN_START )->EnableWindow( !m_strAdresse.IsEmpty() );
}

void CScanner::OnSelchangeComboScan() 
{	
	CString Descript[4] = {
	"Ajoute seulement les ports sélectionnés de la liste ci dessus à la liste générale de sélection.",
	"Ajoute tous les ports de la liste ci dessus à la liste générale de sélection.",
	"Remplace seulement les ports sélectionnés de la liste ci dessus à la liste générale de sélection.",
	"Remplace la liste générale de sélection par tous les ports de la liste ci dessus.",	
	};	
	
	int cursel = m_combo.GetCurSel();
	
	if( cursel >= 0 && cursel < 4 )
		m_description = Descript[cursel];
	else
		m_description.Empty();

	UpdateData( FALSE );	
}


void CScanner::OnButtonOk() 
{
	int nPort, i, j;
	int cursel = m_combo.GetCurSel();
	
	if( cursel == APPEND_ALL || cursel == REPLACE_ALL )
		nPort = m_list.GetCount();		
	else
		nPort = m_list.GetSelCount();
	
	if( nPort )
	{
		pScanList = new CString[nPort + 1];
		
		for( i=0, j=0; i < m_list.GetCount(); i++ )
		{
			if( cursel == APPEND_ALL || cursel == REPLACE_ALL )
				m_list.SetSel( i );
			
			if( m_list.GetSel(i) )
			{
				m_list.GetText( i, pScanList[j] );
				pScanList[j] += " [SCAN]";				
				j++;
			}						
		}

		pScanList[j].Empty();
	}
	else pScanList = NULL;
	
	
	EndDialog( cursel );		
}

void CScanner::SetParent(CAjout *pAjout)
{
	m_pAjout = pAjout;
}
