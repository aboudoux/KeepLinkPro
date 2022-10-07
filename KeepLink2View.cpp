// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// KeepLink2View.cpp : implementation of the CKeepLink2View class
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "ProprietiesDlg.h"
#include "KeepLink2Doc.h"
#include "KeepLink2View.h"
#include "AjoutRegle.h"
#include "Ajout.h"
#include "cSound.h"
#include "AlerteSyslogDlg.h"
#include "Smtp.h"
#include "SendSMSDlg.h"
#include "MainFrm.h"
#include "B64crypt.h"
#include <wininet.h>

#pragma comment( lib, "wininet.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CKeepLink2View

IMPLEMENT_DYNCREATE(CKeepLink2View, CFormView)

BEGIN_MESSAGE_MAP(CKeepLink2View, CFormView)
	//{{AFX_MSG_MAP(CKeepLink2View)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateMenu)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_RGLES_RGLES_NOUVEAU, OnRglesRglesNouveau)
	ON_COMMAND(ID_OUTILS_PROPRITS, OnOutilsProp)
	ON_COMMAND(ID_MODIF_REGLE, OnModifRegle)
	ON_COMMAND(ID_STARTALL, OnStartall)
	ON_COMMAND(ID_STOPALL, OnStopall)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_NOTIFY(NM_CLICK, IDC_TABLEAU, OnClickTableau)
	ON_WM_SIZE()
	ON_COMMAND(ID_SAVEALL, OnSaveall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(ID_RGL_DEMARRER, OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(ID_RGL_ARRETER, OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_RGLEDESURVEILLANCE_SUPPRIMER, OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(ID_MODIF_REGLE, OnUpdateMenu)
	ON_COMMAND(ID_OUTILS_RGLEDESURVEILLANCE_SUPPRIMER, OnOutilsRgledesurveillanceSupprimer)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_RGL_ARRETER, OnStop)
	ON_COMMAND(ID_RGL_DEMARRER, OnStart)
	ON_NOTIFY(NM_RCLICK, IDC_TABLEAU, OnClickTableau)
	ON_COMMAND(ID_BUTTON_START, OnStart)
	ON_COMMAND(ID_BUTTON_STOP, OnStop)
	ON_COMMAND(ID__AIDEENLIGNE, OnAideenligne)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2View construction/destruction

CKeepLink2View::CKeepLink2View()
	: CFormView(CKeepLink2View::IDD)
{
	//{{AFX_DATA_INIT(CKeepLink2View)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_bEnableModif     = FALSE;
}

CKeepLink2View::~CKeepLink2View()
{
	GetDocument()->pView = NULL;
}

void CKeepLink2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeepLink2View)
	DDX_Control(pDX, IDC_TABLEAU, m_tableau);
	//}}AFX_DATA_MAP
}

BOOL CKeepLink2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/**********************************************************
Initialisation du document
***********************************************************/
void CKeepLink2View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	// Initialisation du tableau de surveillance
	m_tableau.InsertColumn( 0, "Statut",   LVCFMT_CENTER, 70 );
	m_tableau.InsertColumn( 1, "Nom",      LVCFMT_CENTER, 200 );
	m_tableau.InsertColumn( 2, "Adresse",  LVCFMT_CENTER, 160 );
	m_tableau.InsertColumn( 3, "Port",     LVCFMT_CENTER, 80 );	
	m_tableau.InsertColumn( 4, "Retour",   LVCFMT_CENTER, 70 );
	
	m_tableau.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_ImageList.Create( IDB_VOYANT, 16, 1, (COLORREF)-1 );
	m_tableau.SetImageList( &m_ImageList, LVSIL_SMALL);

	GetDocument()->pView = this;

//	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
//	pFrame->pView = this;

	if( !GetDocument()->m_load )
	{	
		Panneau = new CPanneau;
		
		// initialisation des éléments du panneau
		Panneau->m_bAlerte        = FALSE;
		Panneau->m_nTemps         = 60 * 1000;	
		Panneau->m_NomDuPanneau   = GetDocument()->GetTitle();
		
		Panneau->m_bAlerteMail    = FALSE;
		Panneau->m_bAlerteSon     = FALSE;
		Panneau->m_bAlerteSms     = FALSE;
		Panneau->m_bAlerteSyslog  = FALSE;
		Panneau->m_bMailAuth      = FALSE;
		
		Panneau->m_nAlerteSyslog  = 3;
		Panneau->m_nAlerteSon     = 3;
		Panneau->m_nAlerteMail    = 3;
		Panneau->m_nAlerteSms     = 4;
		
		Panneau->m_AlerteSyslog_nService = LOG_DAEMON;
		Panneau->m_AlerteSyslog_nLevel   = LOG_ALERT;

		Panneau->m_AlerteMail_Login = "";
		Panneau->m_AlerteMail_Password = "";

		Panneau->m_AlerteSms_Message = "$regle_nom sur $panneau_nom est down !\r\n"
									   "détails : $regle_adresse:$regle_port -> erreur $regle_code-retour";
		
		Panneau->m_AlerteMail_Sujet   = "Alerte KEEPLINK le $date à $heure sur $panneau_nom";

		Panneau->m_AlerteMail_Message = "Une connexion n'est plus disponible sur le panneau de surveillance $panneau_nom.\r\n\r\n"
										"la règle $regle_nom a retournée l'erreur $regle_code-retour, car le \r\n"
										"serveur $regle_adresse ne répond plus aux connexions sur le port $regle_port\r\n\r\n"
										"Veuillez contacter $responsable pour une intervention d'urgence";

		Panneau->m_AlerteMail_AdrEmetteur = "do-not-reply@KeepLinkPro.com";
		
		Panneau->m_AlerteMail_Adresses    = "";
		Panneau->m_AlerteMail_Serveur     = "";
		Panneau->m_AlerteSms_Modem        = "";
		Panneau->m_AlerteSms_Numero       = "";
		Panneau->m_AlerteSon_Fichier      = "";
		
		Panneau->m_AlerteSyslog_Message = "Alerte KEEPLINK PRO [ $date - $heure ] une erreur dans le panneau de surveillance $panneau_nom demande l'intervention de $responsable. Problème : La règle $regle_nom est hors service";

	} else {

		CString tmp;
		Panneau = (CPanneau *)&GetDocument()->m_PanneauDoc;
		GetDocument()->SetTitle( Panneau->m_NomDuPanneau );
		
		if( !Panneau->m_ListSockThread.IsEmpty() )
		{	
			Panneau->m_CurrentListPosition = Panneau->m_ListSockThread.GetHeadPosition();
			while( Panneau->m_CurrentListPosition != Panneau->m_ListSockThread.GetTailPosition() )
			{				
				Panneau->m_SockThread = Panneau->m_ListSockThread.GetAt( Panneau->m_CurrentListPosition );						
				m_tableau.InsertItem( LVIF_TEXT | LVIF_IMAGE, Panneau->m_SockThread.nItem, "Stopped", 0, 0, 3, NULL);
				m_tableau.SetItemText( Panneau->m_SockThread.nItem, 1, Panneau->m_SockThread.Nom );
				m_tableau.SetItemText( Panneau->m_SockThread.nItem, 2, Panneau->m_SockThread.Adresse );
				
				tmp.Format("%u", Panneau->m_SockThread.port );			
				m_tableau.SetItemText( Panneau->m_SockThread.nItem, 3, tmp );
				
				Panneau->m_SockThread.pView = this;
				Panneau->m_ListSockThread.SetAt( Panneau->m_CurrentListPosition, Panneau->m_SockThread );
				
				Panneau->m_ListSockThread.GetNext( Panneau->m_CurrentListPosition );
			}	
			
			Panneau->m_SockThread = Panneau->m_ListSockThread.GetAt( Panneau->m_CurrentListPosition );						
			m_tableau.InsertItem( LVIF_TEXT | LVIF_IMAGE, Panneau->m_SockThread.nItem, "Stopped", 0, 0, 3, NULL);
			m_tableau.SetItemText( Panneau->m_SockThread.nItem, 1, Panneau->m_SockThread.Nom );
			m_tableau.SetItemText( Panneau->m_SockThread.nItem, 2, Panneau->m_SockThread.Adresse );
			
			tmp.Format("%u", Panneau->m_SockThread.port );			
			m_tableau.SetItemText( Panneau->m_SockThread.nItem, 3, tmp );
			
			Panneau->m_SockThread.pView = this;
			Panneau->m_ListSockThread.SetAt( Panneau->m_CurrentListPosition, Panneau->m_SockThread );
		}

		if( Panneau->m_FileVersion != "KL2" )		
			GetDocument()->SetModifiedFlag();		
	}

	Panneau->m_hMutex = TRUE;
	Panneau->m_bSupp  = TRUE;	
}

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2View diagnostics

#ifdef _DEBUG
void CKeepLink2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CKeepLink2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CKeepLink2Doc* CKeepLink2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKeepLink2Doc)));
	return (CKeepLink2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2View message handlers

void CKeepLink2View::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	
	CMenu menu;
	menu.LoadMenu( IDR_KEEPTYPE );
	CMenu * pContextMenu = menu.GetSubMenu(3);

	CBitmap bmp, bmp1, bmp2, bmp3, bmp4, bmp5, bmp6, bmp7;
	bmp.LoadBitmap( IDB_MENU_AJOUTER );
	bmp1.LoadBitmap( IDB_MENU_SUPPRIMER );
	bmp6.LoadBitmap( IDB_MENU_MODIFIER );
	bmp4.LoadBitmap( IDB_MENU_START );
	bmp5.LoadBitmap( IDB_MENU_STOP );	
	bmp2.LoadBitmap( IDB_MENU_STARTALL );
	bmp3.LoadBitmap( IDB_MENU_STOPALL );
	bmp7.LoadBitmap( IDB_MENU_PROPRIETE );
	

	pContextMenu->SetMenuItemBitmaps( 0, MF_BYPOSITION, &bmp, &bmp );
	pContextMenu->SetMenuItemBitmaps( 1, MF_BYPOSITION, &bmp1, &bmp1 );
	pContextMenu->SetMenuItemBitmaps( 2, MF_BYPOSITION, &bmp6, &bmp6 );
	pContextMenu->SetMenuItemBitmaps( 4, MF_BYPOSITION, &bmp4, &bmp4 );
	pContextMenu->SetMenuItemBitmaps( 5, MF_BYPOSITION, &bmp5, &bmp5 );
	pContextMenu->SetMenuItemBitmaps( 7, MF_BYPOSITION, &bmp2, &bmp2 );
	pContextMenu->SetMenuItemBitmaps( 8, MF_BYPOSITION, &bmp3, &bmp3 );
	pContextMenu->SetMenuItemBitmaps( 10, MF_BYPOSITION, &bmp7, &bmp7 );
	
	pContextMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd() );
	
	
}

/**********************************************************
Appel la boite de dialogue d'ajout de règles
***********************************************************/
void CKeepLink2View::OnRglesRglesNouveau() 
{
	CAjout DlgAjout;
	DlgAjout.SetParent( this );
	DlgAjout.DoModal();
}

/**********************************************************
Appel la boite de dialogue de propriété du panneau
***********************************************************/
void CKeepLink2View::OnOutilsProp() 
{
	CProprietiesDlg * Propriete = new CProprietiesDlg;
	Propriete->DoModal();
	delete Propriete;
}

/**********************************************************
Thread executé en boucle
***********************************************************/
UINT CKeepLink2View::Socket_Thread( LPVOID pParam )
{	
	CPanneau::THREADSTRUCT*  CurrentThread = (CPanneau::THREADSTRUCT* )pParam;
	CSocket MySocket;
	CString down;
	char ret_code[10];
	UINT nFailCount = 0;// nCount;
		
	while( 1 )
	{		
		MySocket.Create();

		if( MySocket.Connect( CurrentThread->Adresse, CurrentThread->port ) )
		{
			((CKeepLink2View *)CurrentThread->pView)->m_tableau.SetItem( CurrentThread->nItem, 0, LVIF_TEXT | LVIF_IMAGE, "Up", 1, 0, 0, 0 );
			nFailCount = 0;
			CurrentThread->Return_error = 0;
		}
		else
		{	
			CurrentThread->Return_error = MySocket.GetLastError();

			down.Format("Down(%u)", ++nFailCount );
			((CKeepLink2View *)CurrentThread->pView)->m_tableau.SetItem( CurrentThread->nItem, 0, LVIF_TEXT | LVIF_IMAGE, down, 0, 0, 0, 0 );
			
			if( CurrentThread->_this->m_bAlerte )
				((CKeepLink2View *)CurrentThread->pView)->ExecAlerte( CurrentThread->nItem, nFailCount );				
		}
				
		itoa( CurrentThread->Return_error, ret_code, 10 );
		MySocket.Close();
		((CKeepLink2View *)CurrentThread->pView)->m_tableau.SetItemText( CurrentThread->nItem, 4,  ret_code );
		
		Sleep( CurrentThread->_this->m_nTemps );		
	} 	
	return 0;
}

/**********************************************************
Démarrage des règles sélectionnées
***********************************************************/
void CKeepLink2View::OnStart()
{
	CPanneau::THREADSTRUCT*  t_SockThread;

	if( !m_tableau.GetSelectedCount() )
	{
		MessageBox("Aucune règle à démarrer, veuillez d'abord procéder à une sélection", "KeepLink PRO", MB_ICONERROR );
		return;
	}

	for( int i = 0; i < m_tableau.GetItemCount(); i++ )
	{
		if( m_tableau.GetItemState( i, LVIS_SELECTED ) )
		{
			t_SockThread          = &Panneau->m_ListSockThread.GetAt( Panneau->m_ListSockThread.FindIndex( i ) );
			t_SockThread->nItem   = i;

			if( t_SockThread->hThread )
				continue;

			t_SockThread->hThread = AfxBeginThread( Socket_Thread, t_SockThread );			
			m_tableau.SetItem( i, 0, LVIF_TEXT | LVIF_IMAGE, "Started", 2, 0, 0, 0 );
		}
	}	

	m_tableau.SetFocus();
}

/**********************************************************
Arrêt des règles sélectionnées
***********************************************************/
void CKeepLink2View::OnStop()
{
	CPanneau::THREADSTRUCT* t_SockThread;

	if( !m_tableau.GetSelectedCount() )
	{
		MessageBox("Aucune règle à arrêter, veuillez d'abord procéder à une sélection", "KeepLink PRO", MB_ICONERROR );
		return;
	}

	for( int i = 0; i < m_tableau.GetItemCount(); i++ )
	{
		if( m_tableau.GetItemState( i, LVIS_SELECTED ) )
		{
			t_SockThread = &Panneau->m_ListSockThread.GetAt( Panneau->m_ListSockThread.FindIndex( i ) );			

			if( !t_SockThread->hThread )
				continue;
			
			if( TerminateThread( t_SockThread->hThread->m_hThread, 0 ) )
			{
				WaitForSingleObject( t_SockThread->hThread->m_hThread, INFINITE );
				m_tableau.SetItem( i, 0, LVIF_TEXT | LVIF_IMAGE, "Stopped", 3, 0, 0, 0 );
				t_SockThread->hThread = NULL;				
			}
			else
				m_tableau.SetItemText( i, 3, "Thread Error" );			
		}
	}
	m_tableau.SetFocus();
}


/**********************************************************
Supprime les règles sélectionnées
***********************************************************/
void CKeepLink2View::OnOutilsRgledesurveillanceSupprimer() 
{
	POSITION pos;
	BOOL bFlag = FALSE;

	if( !m_tableau.GetSelectedCount() )
	{
		if( !Panneau->m_bSupp  )
			return;
		
		MessageBox("Aucune règle à supprimer, veuillez d'abord procéder à une sélection", "KeepLink PRO", MB_ICONERROR );
		return;
	}

	if( Panneau->m_bSupp )
	{
		if( IDNO == MessageBox("Cette action va procéder à la suppression des règles sélectionnées\r\n"
			"êtes vous sûr de vouloir continuer ?", "KeepLink PRO", MB_YESNO + MB_ICONEXCLAMATION ) )
			return;
	}
	

	// stop les Threads selectionnés
	OnStop();

	for( int i = 0; i < m_tableau.GetItemCount(); i++ )
	{	
		// optiens la position de l'item courante
		pos = Panneau->m_ListSockThread.FindIndex( i );

		// si l'item est selectionné
		if( m_tableau.GetItemState( i, LVIS_SELECTED ) )
		{			
			m_tableau.DeleteItem( i );		// suppression du tableau
			Panneau->m_ListSockThread.RemoveAt( pos );	// suppression de la liste chainé
						
			if( --i < 0 )
			{
				i = 0; // si la decrémentation < 0, current item = 0
				bFlag = TRUE;
			} 				

			pos = Panneau->m_ListSockThread.FindIndex( i ); // reajuste la position dans la liste
		}

		// quit si plus d'item dans le tableau
		if( !m_tableau.GetItemCount() )
			break;
	
		Panneau->m_SockThread = Panneau->m_ListSockThread.GetAt( pos ); // optiens le pointeur de la pos courante
		Panneau->m_SockThread.nItem = i; // reajuste le numero d'item dans la liste
		
		Panneau->m_ListSockThread.SetAt( pos, Panneau->m_SockThread ); // update la liste chainé

		if( bFlag ) 
		{
			i = -1;
			bFlag = FALSE;
		}		
	}
	
	GetDocument()->SetModifiedFlag();
}

/**********************************************************
Sélectionne toutes les règles du document actif
***********************************************************/
void CKeepLink2View::OnEditSelectall() 
{
	m_tableau.SetFocus();
	
	for( int i = 0; i < m_tableau.GetItemCount() ; i++ )		
		m_tableau.SetItemState( i, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED );
	
	m_bEnableModif = (m_tableau.GetSelectedCount()) ? TRUE : FALSE;
}

/**********************************************************
Fonction d'execution des alertes
***********************************************************/
void CKeepLink2View::ExecAlerte( UINT nThreadIndex, UINT FailCount )
{
	CPanneau::THREADSTRUCT* t_SockThread;
	t_SockThread = &Panneau->m_ListSockThread.GetAt( Panneau->m_ListSockThread.FindIndex( nThreadIndex ) );

	if( Panneau->m_bAlerteSon && Panneau->m_nAlerteSon == FailCount )
	{
		cSound sound;
		sound.PlaySoundFile( Panneau->m_AlerteSon_Fichier.GetBuffer(0) );	
	}
		
	if( Panneau->m_bAlerteMail && Panneau->m_nAlerteMail == FailCount)
	{
		SendMail( nThreadIndex );		
	}

	if( Panneau->m_bAlerteSms && Panneau->m_nAlerteSms == FailCount)
	{
		SendSMS( nThreadIndex );
	}

	if( Panneau->m_bAlerteSyslog && Panneau->m_nAlerteSyslog == FailCount )
	{
		SendSyslogMessage( nThreadIndex );
	}
}

/**********************************************************
Fonction d'envoie de mail
***********************************************************/
BOOL CKeepLink2View::SendMail( int nThreadIndex )
{
	CSmtp mail;
	CSmtpMessage msg;
	//CSmtpAddress cc;
	CSmtpMessageBody body;
	//CSmtpAttachment attach;
	BOOL ret;
	// Initialize winsock  
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,0),&wsa);
	
	if( Panneau->m_bMailAuth )
	{
		CString tmp;
		tmp = Panneau->m_AlerteMail_Password;
		
		CB64crypt obj64Crypt;
		obj64Crypt.DeCrypt( tmp.GetBuffer( 0 ) );
		
		mail.m_strUser = Panneau->m_AlerteMail_Login;
		mail.m_strPass = obj64Crypt.pCrypt;
	}
	
	char *cAddress, *p;	
	cAddress = Panneau->m_AlerteMail_Adresses.GetBuffer(0);
	p = strtok( cAddress, ";");
		
	while( p )
	{				
		msg.Sender.Name    = "KeepLink PRO";			 //Panneau->m_AlerteMail_NomEmetteur;
		msg.Sender.Address = Panneau->m_AlerteMail_AdrEmetteur;
		
		msg.Recipient.Name = Panneau->m_NomDuResponsable;
		msg.Recipient.Address = p;
		
		msg.Subject = ParseString( Panneau->m_AlerteMail_Sujet, nThreadIndex );
		body = ParseString( Panneau->m_AlerteMail_Message, nThreadIndex );
		
		msg.Message.Add( body );	
		
		if( mail.Connect( Panneau->m_AlerteMail_Serveur.GetBuffer(0) ) )
		{
			if( mail.SendMessage(msg) == 554)
				ret = 2;
			else
				ret = FALSE;

			mail.Close();			
		}
		else
			ret = TRUE;
		
		p = strtok( NULL, ";" );
	}		

	WSACleanup();
	return ret;
}

/*
**********************************************************
Remplace les variables par les éléments des règles
**********************************************************
Parser
-> $panneau_nom			: retourne le nom assigné au panneau de surveillance
-> $responsable			: retourne le nom du résponsable
-> $regle_nom			: retourne le nom de la règle ayant creer l'alerte
-> $regle_adresse		: retourne l'adresse de la regle qui a engendré l'alerte
-> $regle_port			: retourne le port de communication de la regle qui a engendré l'alerte
-> $regle_code-retour	: retourne le code d'erreur
-> $date                : retourne la date courante
-> $heure               : retourne l'heure courante
*/
CString CKeepLink2View::ParseString( CString message, int nThreadIndex )
{
	CPanneau::THREADSTRUCT* t_SockThread;
	SYSTEMTIME  SystemTime;
	CString m_time;
	char *tmp = new char[1024];

	GetLocalTime( &SystemTime );
	
	if( nThreadIndex == -1 )
	{
		t_SockThread = new CPanneau::THREADSTRUCT;
		t_SockThread->Nom          = "TEST KEEPLINK";
		t_SockThread->Adresse      = "www.techandfeel.net";		
		t_SockThread->port         = 80;
		t_SockThread->Return_error = 10061;
	}	
	else
		t_SockThread = &Panneau->m_ListSockThread.GetAt( Panneau->m_ListSockThread.FindIndex( nThreadIndex ) );

	message.Replace( "$responsable", Panneau->m_NomDuResponsable );
	message.Replace( "$regle_nom", t_SockThread->Nom );
	message.Replace( "$regle_adresse", t_SockThread->Adresse );
	message.Replace( "$panneau_nom", Panneau->m_NomDuPanneau );

	itoa( t_SockThread->port, tmp, 10 );
	message.Replace( "$regle_port", tmp );

	itoa( t_SockThread->Return_error, tmp, 10 );
	message.Replace( "$regle_code-retour", tmp );

	m_time.Format("%.2d:%.2d:%.2d", SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
	message.Replace( "$heure", m_time );

	m_time.Format("%.2d/%.2d/%.4d", SystemTime.wDay, SystemTime.wMonth, SystemTime.wYear );
	message.Replace( "$date", m_time );

	if( nThreadIndex == -1 )
	{
		delete t_SockThread;
		t_SockThread=NULL;
	}

	return message;
}

/**********************************************************
Envoie un message syslog
***********************************************************/
BOOL CKeepLink2View::SendSyslogMessage( int nThreadIndex )
{
	CSocket SyslogSocket;
	CString message;

	if( !SyslogSocket.Create( 0, SOCK_DGRAM ) )
		return FALSE;

	if( SyslogSocket.Connect( Panneau->m_AlerteSyslog_Serveur , 514 ) )
	{
		if( Panneau->m_AlerteSyslog_Message.IsEmpty() )
			Panneau->m_AlerteSyslog_Message = "KEEPLINK PRO : Message d'alerte syslog non renseigné";
		
		message.Format( "<%u>%s", Panneau->m_AlerteSyslog_nService | Panneau->m_AlerteSyslog_nLevel, ParseString( Panneau->m_AlerteSyslog_Message, nThreadIndex ) );
		SyslogSocket.Send( message, message.GetLength() );

		return TRUE;
	}
	
	return FALSE;
}


/**********************************************************
Modification de la prmière règle sélectionnée
***********************************************************/
void CKeepLink2View::OnModifRegle() 
{
	char port[10];
	POSITION pos;

	if( !m_tableau.GetSelectedCount() )
	{
		MessageBox("Aucune règle à modifier, veuillez d'abord procéder à une sélection", "KeepLink PRO", MB_ICONERROR );
		return;
	}

	for( int i = 0; i < m_tableau.GetItemCount(); i++ )
	{			
		pos = Panneau->m_ListSockThread.FindIndex( i );
		
		if( m_tableau.GetItemState( i, LVIS_SELECTED ) )
		{
			Panneau->m_SockThread = Panneau->m_ListSockThread.GetAt( pos );
			
			CAjoutRegle * ModifRegle = new CAjoutRegle;

			ModifRegle->SetParent( this, Panneau );
			ModifRegle->m_strTitre   = "Modification d'une règle de surveillance";
			ModifRegle->m_strAdresse = Panneau->m_SockThread.Adresse;
			ModifRegle->m_strNom     = Panneau->m_SockThread.Nom;			
			itoa( Panneau->m_SockThread.port, port, 10 );			
			ModifRegle->m_strPort    = port;
			
			ModifRegle->DoModal();
			
			delete ModifRegle;
			ModifRegle=NULL;

			break;
		}
	}	
}

/**********************************************************
Envoie un SMS
***********************************************************/
void CKeepLink2View::SendSMS( int nThreadIndex )
{
	if( !Panneau->m_hMutex )
		return;

	Panneau->m_hMutex = FALSE;

	CSendSMSDlg SendSms;
	SendSms.SetParent( this, nThreadIndex );
	SendSms.DoModal();	

	Panneau->m_hMutex = TRUE;
}

void CKeepLink2View::OnStartall() 
{	
	CWinApp *pApp = AfxGetApp();
	CDocManager *pDocMgr = pApp->m_pDocManager;
	// For all document templates
	for( POSITION TmplPos = pDocMgr->GetFirstDocTemplatePosition(); TmplPos; )
	{
		CDocTemplate *pTmpl = pDocMgr->GetNextDocTemplate(TmplPos);
		ASSERT_VALID(pTmpl);
		// For All open documents of this document template type.
		for(POSITION Pos = pTmpl->GetFirstDocPosition();Pos;) 
		{
			CDocument *pDoc = pTmpl->GetNextDoc(Pos);	  	  
			// For all views of this document
			POSITION ViewPos = pDoc->GetFirstViewPosition();
			while(ViewPos)
			{
				CKeepLink2View *pView =  (CKeepLink2View *)pDoc->GetNextView(ViewPos); 		
				pView->OnEditSelectall();
				
				if( !pView->m_tableau.GetSelectedCount() )
					continue;
				
				pView->OnStart();				
			}
		}
	}	
}

void CKeepLink2View::OnStopall() 
{
	CWinApp *pApp = AfxGetApp();
	CDocManager *pDocMgr = pApp->m_pDocManager;
	// For all document templates
	for(POSITION TmplPos = pDocMgr->GetFirstDocTemplatePosition();
	TmplPos;)
	{
		CDocTemplate *pTmpl = pDocMgr->GetNextDocTemplate(TmplPos);
		ASSERT_VALID(pTmpl);
		// For All open documents of this document template type.
		for(POSITION Pos = pTmpl->GetFirstDocPosition();Pos;) 
		{
			CDocument *pDoc = pTmpl->GetNextDoc(Pos);	  	  
			// For all views of this document
			POSITION ViewPos = pDoc->GetFirstViewPosition();
			while(ViewPos)
			{
				CKeepLink2View *pView =  (CKeepLink2View *)pDoc->GetNextView(ViewPos); 		
				pView->OnEditSelectall();
				
				if( !pView->m_tableau.GetSelectedCount() )
					continue;
				
				pView->OnStop();
			}
		}
	}	
}

void CKeepLink2View::OnSaveall() 
{
	CDocument *pActiveDoc = GetActiveDoc();
	DocumentList_t Docs;
	GetAllDocuments(Docs);  
	for(POSITION pos = Docs.GetHeadPosition();pos;)
	{			  
		CDocument *pDoc = Docs.GetNext(pos);
		if (pDoc->IsModified())
		{
			//if (pDoc->GetPathName()=="") // if no path then promt is displayed
			BringToTop(pDoc);  //   so bring window to top!.			
			pDoc->DoFileSave();	  
		}
	}
	if (pActiveDoc) // Reset focus to the window
		BringToTop(pActiveDoc);
	
	
}

void CKeepLink2View::BringToTop(CDocument *pDoc)
{
	// get me a view for this doc.
	POSITION ViewPos = pDoc->GetFirstViewPosition();
	if (ViewPos)
	{
		CView *pView =  pDoc->GetNextView(ViewPos); 
		//pView->SetActiveWindow();
		CFrameWnd *pFrame = pView->GetParentFrame();
		if (pFrame)
			pFrame->ActivateFrame(); // activate.
	}
}

CDocument * CKeepLink2View::GetActiveDoc()
{
	
	CFrameWnd *pWnd = (CFrameWnd *) AfxGetMainWnd();  
	if (pWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
	{
		pWnd = pWnd->GetActiveFrame();
		if (pWnd)
			return pWnd->GetActiveDocument();
	}
	return 0;
	
}

void CKeepLink2View::GetAllDocuments(DocumentList_t &Docs)
{
	CWinApp *pApp = AfxGetApp();
	CDocManager *pDocMgr = pApp->m_pDocManager;  
	// For all document templates
	for(POSITION TmplPos = pDocMgr->GetFirstDocTemplatePosition();
	TmplPos;)
	{
		CDocTemplate *pTmpl = pDocMgr->GetNextDocTemplate(TmplPos);
		ASSERT_VALID(pTmpl);    
		// For All open documents of this document template type.
		for(POSITION Pos = pTmpl->GetFirstDocPosition();Pos;) 
		{
			CDocument *pDoc = pTmpl->GetNextDoc(Pos);	  	  
			Docs.AddTail(pDoc);
		}
	}
}

void CKeepLink2View::OnEditCopy() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	if( !m_tableau.GetSelectedCount() )
		return;	

	pFrame->Clipboard.m_ListSockThread.RemoveAll();

	for( int i = 0; i < m_tableau.GetItemCount(); i++ )
	{
		if( m_tableau.GetItemState( i, LVIS_SELECTED ) )
		{
			Panneau->m_SockThread = Panneau->m_ListSockThread.GetAt( Panneau->m_ListSockThread.FindIndex( i ) );
			pFrame->Clipboard.m_ListSockThread.AddTail( Panneau->m_SockThread );
		}
	}
}

void CKeepLink2View::OnEditPaste() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString tmp;

	if( pFrame->Clipboard.m_ListSockThread.IsEmpty() )
		return;

	Panneau->m_CurrentListPosition          = Panneau->m_ListSockThread.GetTailPosition();
	pFrame->Clipboard.m_CurrentListPosition = pFrame->Clipboard.m_ListSockThread.GetHeadPosition();
	int ListCount = Panneau->m_ListSockThread.GetCount();

	while( pFrame->Clipboard.m_CurrentListPosition != pFrame->Clipboard.m_ListSockThread.GetTailPosition() )
	{
		pFrame->Clipboard.m_SockThread = pFrame->Clipboard.m_ListSockThread.GetAt( pFrame->Clipboard.m_CurrentListPosition );
		
		pFrame->Clipboard.m_SockThread.pView = this;
		pFrame->Clipboard.m_SockThread._this = Panneau;
		pFrame->Clipboard.m_SockThread.nItem = ListCount++;
		pFrame->Clipboard.m_SockThread.hThread = NULL;
		
		m_tableau.InsertItem( LVIF_TEXT | LVIF_IMAGE, pFrame->Clipboard.m_SockThread.nItem, "Stopped", 0, 0, 3, NULL);
		m_tableau.SetItemText( pFrame->Clipboard.m_SockThread.nItem, 1, pFrame->Clipboard.m_SockThread.Nom );
		m_tableau.SetItemText( pFrame->Clipboard.m_SockThread.nItem, 2, pFrame->Clipboard.m_SockThread.Adresse );
		
		tmp.Format("%u", pFrame->Clipboard.m_SockThread.port );			
		m_tableau.SetItemText( pFrame->Clipboard.m_SockThread.nItem, 3, tmp );
		
		Panneau->m_ListSockThread.AddTail( pFrame->Clipboard.m_SockThread );
		
		pFrame->Clipboard.m_ListSockThread.GetNext( pFrame->Clipboard.m_CurrentListPosition );
	}
	
	pFrame->Clipboard.m_SockThread = pFrame->Clipboard.m_ListSockThread.GetAt( pFrame->Clipboard.m_CurrentListPosition );
	
	pFrame->Clipboard.m_SockThread.pView = this;
	pFrame->Clipboard.m_SockThread._this = Panneau;
	pFrame->Clipboard.m_SockThread.nItem = ListCount++;
	pFrame->Clipboard.m_SockThread.hThread = NULL;
	
	m_tableau.InsertItem( LVIF_TEXT | LVIF_IMAGE, pFrame->Clipboard.m_SockThread.nItem, "Stopped", 0, 0, 3, NULL);
	m_tableau.SetItemText( pFrame->Clipboard.m_SockThread.nItem, 1, pFrame->Clipboard.m_SockThread.Nom );
	m_tableau.SetItemText( pFrame->Clipboard.m_SockThread.nItem, 2, pFrame->Clipboard.m_SockThread.Adresse );
	
	tmp.Format("%u", pFrame->Clipboard.m_SockThread.port );			
	m_tableau.SetItemText( pFrame->Clipboard.m_SockThread.nItem, 3, tmp );
	
	Panneau->m_ListSockThread.AddTail( pFrame->Clipboard.m_SockThread );
	
	GetDocument()->SetModifiedFlag( TRUE );
}

void CKeepLink2View::OnEditCut() 
{
	OnEditCopy();
	Panneau->m_bSupp = FALSE;
	OnOutilsRgledesurveillanceSupprimer();	
	Panneau->m_bSupp = TRUE;
}


void CKeepLink2View::OnClickTableau(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_bEnableModif = (m_tableau.GetSelectedCount()) ? TRUE : FALSE;
	
	*pResult = 0;
}

// 
void CKeepLink2View::OnUpdateMenu(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_bEnableModif );		
}

void CKeepLink2View::CleanAllModifiedFlag()
{
	CDocument *pActiveDoc = GetActiveDoc();
	DocumentList_t Docs;
	GetAllDocuments(Docs);  
	for(POSITION pos = Docs.GetHeadPosition();pos;)
	{			  
		CDocument *pDoc = Docs.GetNext(pos);
		if (pDoc->IsModified())
		{
			BringToTop(pDoc);  //   so bring window to top!.			
			pDoc->SetModifiedFlag( FALSE );
		}
	}
	if (pActiveDoc) // Reset focus to the window
		BringToTop(pActiveDoc);
}


void CKeepLink2View::OnSize(UINT nType, int cx, int cy) 
{
	//CFormView::OnSize(nType, cx, cy);
	
	if( m_tableau )
		m_tableau.SetWindowPos( &wndTop, 0, 0, cx , cy, SWP_SHOWWINDOW );
	
}

void CKeepLink2View::OnAideenligne() 
{
	WinExec( "explorer.exe http://www.techandfeel.com/keeplink/", SW_SHOW );	
}
