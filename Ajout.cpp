// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// Ajout.cpp : implementation file
/******************************************************************
Traitement de la boite de dialogue Parent d'ajout de règle
Cette boite de dialogue contient une tab-sheet qui gère Ajout simple
et l'ajout multiple de règle.
Pour traiter les événements de l'ajout simple : ce reporter à CAjoutSimple
Pour traiter les événements d'ajout multiple : ce reporter à  CAjoutMultiple
*********************************************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "Ajout.h"
#include "AjoutSimple.h"
#include "AjoutMultiple.h"
#include "Scanner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NUMBER_OF_STRING   51
#define TAB_REGLE_SIMPLE   0
#define TAB_REGLE_MULTIPLE 1


/////////////////////////////////////////////////////////////////////////////
// CAjout dialog


CAjout::CAjout(CWnd* pParent /*=NULL*/)
	: CDialog(CAjout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// Liste général des ports.
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

CAjout::~CAjout()
{
	delete[] m_strPortList;
}


void CAjout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjout)
	DDX_Control(pDX, IDC_TAB_AJOUT, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjout, CDialog)
	//{{AFX_MSG_MAP(CAjout)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, OnAjouter)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, OnScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjout message handlers

BOOL CAjout::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_tab.InsertItem( 0, "Règle simple" );
	m_tab.InsertItem( 1, "Règles multiples" );
	m_tab.Init( );

	if( !m_bitmap.LoadBitmap( IDB_VBANNER ) )
		return FALSE;

		
	return TRUE; 
}

void CAjout::OnPaint() 
{
	CPaintDC dc(this);
	m_bitmap.DrawTransparent( &dc, 0, 0, RGB( 0xFB, 0xFC, 0xFC) );
			
}


/**************************************
Clique sur le bouton Ajouter
***************************************/
void CAjout::OnAjouter() 
{
	CString Nom, Adresse, port, strTmp;
	
	CAjoutSimple   *   pAjoutSimple = ((CAjoutSimple *)m_tab.m_tabPages[TAB_REGLE_SIMPLE]);
	CAjoutMultiple * pAjoutMultiple = ((CAjoutMultiple *)m_tab.m_tabPages[TAB_REGLE_MULTIPLE]);

	switch( m_tab.m_tabCurrent )
	{
	
	/* Gestion des règles simples */
	case TAB_REGLE_SIMPLE :
		{
			pAjoutSimple->UpdateData( TRUE );
			
			Nom     = pAjoutSimple->m_strNom;
			Adresse = pAjoutSimple->m_strAdresse;

			if( pAjoutSimple->IsDlgButtonChecked( IDC_RADIO_PORT_MULTIPLE ) )
			{
				CListBox *ListBox = &pAjoutSimple->m_ListBox;
				
				if( !ListBox->GetSelCount() )
				{
					MessageBox("Impossible de créer une règle de surveillance avec les paramètres fournis.\r\n\r\n"
					"Vérifiez que vous avez bien renseigné tout les champs (Nom de la règle, nom de la machine ainsi que le port)\r\n"
					"et que vous avez bien donné un \"nombre\" comme port de surveillance.", NULL, MB_ICONERROR );

					return;

				}
				for( int i = 0; i < ListBox->GetCount(); i++ )
				{
					if( ListBox->GetSel( i ) )
					{
						ListBox->GetText( i, port );
						strTmp = Nom + " port " + port;
						AddRule( strTmp, Adresse, port );
						ListBox->SetSel( i, FALSE );
					}
				}

			}
			else
			{
				port = pAjoutSimple->m_strPort;
				
				if( !AddRule( Nom, Adresse, port ) )
				{
					MessageBox("Impossible de créer une règle de surveillance avec les paramètres fournis.\r\n\r\n"
					"Vérifiez que vous avez bien renseigné tout les champs (Nom de la règle, nom de la machine ainsi que le port)\r\n"
					"et que vous avez bien donné un \"nombre\" comme port de surveillance.", NULL, MB_ICONERROR );

					return;
				}

				pAjoutSimple->m_strPort.Empty();			

			}

			pAjoutSimple->m_strNom.Empty();
			pAjoutSimple->m_strAdresse.Empty();
			(pAjoutSimple->GetDlgItem( IDC_EDIT_REGLE_NOM ))->SetFocus();
				
			GetDlgItem( IDOK )->EnableWindow( FALSE );

			pAjoutSimple->UpdateData( FALSE );
			

			break;
		}

	/* gestion des règles multiples */
	case TAB_REGLE_MULTIPLE :
		{
			pAjoutMultiple->UpdateData( TRUE );			

			RULES Rules[] = {
				{ &pAjoutMultiple->m_strNom1, &pAjoutMultiple->m_strAdresse1, &pAjoutMultiple->m_strPort1 },
				{ &pAjoutMultiple->m_strNom2, &pAjoutMultiple->m_strAdresse2, &pAjoutMultiple->m_strPort2 },
				{ &pAjoutMultiple->m_strNom3, &pAjoutMultiple->m_strAdresse3, &pAjoutMultiple->m_strPort3 },
				{ &pAjoutMultiple->m_strNom4, &pAjoutMultiple->m_strAdresse4, &pAjoutMultiple->m_strPort4 },
				{ &pAjoutMultiple->m_strNom5, &pAjoutMultiple->m_strAdresse5, &pAjoutMultiple->m_strPort5 },
				{ &pAjoutMultiple->m_strNom6, &pAjoutMultiple->m_strAdresse6, &pAjoutMultiple->m_strPort6 },
				{ &pAjoutMultiple->m_strNom7, &pAjoutMultiple->m_strAdresse7, &pAjoutMultiple->m_strPort7 },
				{ &pAjoutMultiple->m_strNom8, &pAjoutMultiple->m_strAdresse8, &pAjoutMultiple->m_strPort8 },
				{ &pAjoutMultiple->m_strNom9, &pAjoutMultiple->m_strAdresse9, &pAjoutMultiple->m_strPort9 },
				{ &pAjoutMultiple->m_strNom10, &pAjoutMultiple->m_strAdresse10, &pAjoutMultiple->m_strPort10 },
				{NULL, NULL, NULL},
			};

			for( int i = 0; Rules[i].Nom; i ++ )
			{
				if( !Rules[i].Nom->IsEmpty() && !Rules[i].Adresse->IsEmpty() && !Rules[i].port->IsEmpty() )
				{
					AddRule( *Rules[i].Nom, *Rules[i].Adresse, *Rules[i].port );
				}

				Rules[i].Nom->Empty();
				Rules[i].Adresse->Empty();
				Rules[i].port->Empty();
			}

			pAjoutMultiple->UpdateData( FALSE );
			GetDlgItem( IDOK )->EnableWindow( FALSE );
		}
	}
	
}

/************************************************
Rajoute un règle de surveillance au tableau courant
*************************************************/
BOOL CAjout::AddRule(CString m_strNom, CString m_strAdresse, CString m_strPort)
{
	
	int nItem, nPort;
	CString tmp;

	if( !(nPort = atoi( m_strPort )) )
		return FALSE;	
	
	m_Panneau->m_SockThread.pView   = m_pWnd;
	m_Panneau->m_SockThread.Adresse = m_strAdresse;
	m_Panneau->m_SockThread.port    = nPort;
	m_Panneau->m_SockThread.Nom     = m_strNom;	
	m_Panneau->m_SockThread._this   = m_Panneau;
	
	m_Panneau->m_SockThread.hThread = NULL;
	nItem = m_pWnd->m_tableau.GetItemCount();
	
	if( m_strNom.IsEmpty() || m_strAdresse.IsEmpty() || m_strPort.IsEmpty()  )
		return FALSE;

	
	m_Panneau->m_SockThread.nItem   = nItem;				
	m_Panneau->m_ListSockThread.AddTail( m_Panneau->m_SockThread );
	m_pWnd->m_tableau.InsertItem( LVIF_TEXT | LVIF_IMAGE, nItem, "Stopped", 0, 0, 3, NULL );		
	
	
	m_pWnd->m_tableau.SetItemText( nItem, 1, m_strNom );
	m_pWnd->m_tableau.SetItemText( nItem, 2, m_strAdresse );
	m_pWnd->m_tableau.SetItemText( nItem, 3, m_strPort );	
	
	m_pWnd->GetDocument()->SetModifiedFlag( TRUE );

	return TRUE;
	
}

/***************************************************
Passage de pointeur entre le panneau de surveillance courant
et la boite de dialogue
*****************************************************/
void CAjout::SetParent(CKeepLink2View *pView)
{
	m_pWnd    = pView;
	m_Panneau = m_pWnd->Panneau;
}

/*****************************************************
Lance la bdl du scanner multiThread, et traite
les options choisies par l'utilisateur
- Ajouter tout les ports à la liste général
- Ajouter les port sélsctionnés à la liste générale
- Remplacer tout les ports de la liste générale par les ports trouvé
- Remplacer tout les ports de la liste générales par les ports sélectionnés
******************************************************/
void CAjout::OnScan() 
{
	CString * ScanList;// pointeur sur la liste des ports trouvé par le scanner
	CScanner scanner;
	CAjoutSimple   *   pAjoutSimple = ((CAjoutSimple *)m_tab.m_tabPages[TAB_REGLE_SIMPLE]);
	CAjoutMultiple * pAjoutMultiple = ((CAjoutMultiple *)m_tab.m_tabPages[TAB_REGLE_MULTIPLE]);

	// passage de pointeur
	scanner.SetParent( this );

	// lance la boite de dialogue
	int index = scanner.DoModal();
	ScanList = scanner.pScanList;

	// si pas de pointeur, retour
	if( !ScanList )
		return;

	// si clique sur le bouton Quitter dans le scanner
	if( index == -1 )
	{
		if( ScanList )
		{
			delete[] ScanList;
			ScanList=NULL;
		}
		return;
	}

	// si le chois sélectionné dans le scanner est de type remplacer
	// Réinitialise les combos & listbox  de Regle simple
	if( index == REPLACE_ALL || index == REPLACE_SELECTED )
		{
			pAjoutSimple->m_ctlCombo.ResetContent();
			pAjoutSimple->m_ListBox.ResetContent();
		}

	// procède à l'ajout de ports
	for( int i = 0; !ScanList[i].IsEmpty(); i++ )
	{		
		pAjoutSimple->m_ctlCombo.AddString( ScanList[i] );
		pAjoutSimple->m_ListBox.AddString( ScanList[i] );	
		
	}
	
	// Tableaux sur toutes les combobox de regle multiples
	CComboBox * ComboTable[] = {
			&pAjoutMultiple->m_ctrlComboPort1,
			&pAjoutMultiple->m_ctrlComboPort2,
			&pAjoutMultiple->m_ctrlComboPort3,
			&pAjoutMultiple->m_ctrlComboPort4,
			&pAjoutMultiple->m_ctrlComboPort5,
			&pAjoutMultiple->m_ctrlComboPort6,
			&pAjoutMultiple->m_ctrlComboPort7,
			&pAjoutMultiple->m_ctrlComboPort8,
			&pAjoutMultiple->m_ctrlComboPort9,
			&pAjoutMultiple->m_ctrlComboPort10,
			NULL		
	};

	for( int b = 0; ComboTable[b]; b++ )
	{
		// Si la sélection es t de type Remplacer, réinitialisation de toutes
		// les combos de Règles multiples
		if( index == REPLACE_ALL || index == REPLACE_SELECTED )
		{
			ComboTable[b]->ResetContent();
		}
		
		// ajoute les ports
		for( int j = 0; !ScanList[j].IsEmpty(); j++ )
		{
			ComboTable[b]->AddString( ScanList[j] );
		}
	}

	// quitte propre
	if( ScanList )
	{
		delete[] ScanList;
		ScanList=NULL;
	}
}


void CAjout::SwitchString(CString &source, CString &dest)
{
	CString tmp = source;
	source      = dest;
	dest        = tmp;
}

void CAjout::Tribule(CString *List)
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
