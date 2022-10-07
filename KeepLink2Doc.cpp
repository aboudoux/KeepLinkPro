// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// KeepLink2Doc.cpp : implementation of the CKeepLink2Doc class
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "KeepLink2Doc.h"
#include "KeepLink2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2Doc

IMPLEMENT_DYNCREATE(CKeepLink2Doc, CDocument)

BEGIN_MESSAGE_MAP(CKeepLink2Doc, CDocument)
	//{{AFX_MSG_MAP(CKeepLink2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2Doc construction/destruction

CKeepLink2Doc::CKeepLink2Doc()
{
	m_load = FALSE;
}

CKeepLink2Doc::~CKeepLink2Doc()
{
}

BOOL CKeepLink2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CKeepLink2Doc serialization

void CKeepLink2Doc::Serialize(CArchive& ar)
{
	// sauvegarde des données dans un fichier
	if (ar.IsStoring())
	{		
		if( !pView )
			return;

		((CKeepLink2View *)pView)->Panneau->m_FileVersion = "KL2";
		
		ar << ((CKeepLink2View *)pView)->Panneau->m_FileVersion;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteMail_AdrEmetteur;
		ar << ((CKeepLink2View *)pView)->Panneau->m_bMailAuth;		
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteMail_Adresses;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteMail_Message;		
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteMail_Serveur;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteMail_Sujet;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteMail_Login;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteMail_Password;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSms_Message;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSms_Modem;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSms_Numero;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSon_Fichier;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSyslog_Message;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSyslog_nLevel;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSyslog_nService;
		ar << ((CKeepLink2View *)pView)->Panneau->m_AlerteSyslog_Serveur;
		ar << ((CKeepLink2View *)pView)->Panneau->m_bAlerte;
		ar << ((CKeepLink2View *)pView)->Panneau->m_bAlerteMail;
		ar << ((CKeepLink2View *)pView)->Panneau->m_bAlerteSms;
		ar << ((CKeepLink2View *)pView)->Panneau->m_bAlerteSon;
		ar << ((CKeepLink2View *)pView)->Panneau->m_bAlerteSyslog;
		ar << ((CKeepLink2View *)pView)->Panneau->m_nAlerteMail;
		ar << ((CKeepLink2View *)pView)->Panneau->m_nAlerteSms;
		ar << ((CKeepLink2View *)pView)->Panneau->m_nAlerteSon;
		ar << ((CKeepLink2View *)pView)->Panneau->m_nAlerteSyslog;
		ar << ((CKeepLink2View *)pView)->Panneau->m_NomDuPanneau;
		ar << ((CKeepLink2View *)pView)->Panneau->m_NomDuResponsable;
		ar << ((CKeepLink2View *)pView)->Panneau->m_nTemps;

		if( ((CKeepLink2View *)pView)->Panneau->m_ListSockThread.IsEmpty() )					
			return;
		
		((CKeepLink2View *)pView)->Panneau->m_CurrentListPosition = ((CKeepLink2View *)pView)->Panneau->m_ListSockThread.GetHeadPosition();
		
		while( ((CKeepLink2View *)pView)->Panneau->m_CurrentListPosition != ((CKeepLink2View *)pView)->Panneau->m_ListSockThread.GetTailPosition() )
		{
			((CKeepLink2View *)pView)->Panneau->m_SockThread = ((CKeepLink2View *)pView)->Panneau->m_ListSockThread.GetNext( ((CKeepLink2View *)pView)->Panneau->m_CurrentListPosition );
			ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.Adresse; 
			ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.nItem;
			ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.Nom;
			ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.port;
			ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.Return_error;
		}
	
		((CKeepLink2View *)pView)->Panneau->m_SockThread = ((CKeepLink2View *)pView)->Panneau->m_ListSockThread.GetTail();
		ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.Adresse; 
		ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.nItem;
		ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.Nom;
		ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.port;
		ar << ((CKeepLink2View *)pView)->Panneau->m_SockThread.Return_error;		
		
	}
	else
	{

		ar >> m_PanneauDoc.m_FileVersion;

		if( m_PanneauDoc.m_FileVersion == "KL2" )
		{
			ar >> m_PanneauDoc.m_AlerteMail_AdrEmetteur;			
		}
		else
		{
			m_PanneauDoc.m_AlerteMail_AdrEmetteur = "do-not-reply@KeepLinkPro.com";			
		}

		ar >> m_PanneauDoc.m_bMailAuth;		
		ar >> m_PanneauDoc.m_AlerteMail_Adresses;
		ar >> m_PanneauDoc.m_AlerteMail_Message;		
		ar >> m_PanneauDoc.m_AlerteMail_Serveur;
		ar >> m_PanneauDoc.m_AlerteMail_Sujet;
		ar >> m_PanneauDoc.m_AlerteMail_Login;
		ar >> m_PanneauDoc.m_AlerteMail_Password;
		ar >> m_PanneauDoc.m_AlerteSms_Message;
		ar >> m_PanneauDoc.m_AlerteSms_Modem;
		ar >> m_PanneauDoc.m_AlerteSms_Numero;
		ar >> m_PanneauDoc.m_AlerteSon_Fichier;
		ar >> m_PanneauDoc.m_AlerteSyslog_Message;
		ar >> m_PanneauDoc.m_AlerteSyslog_nLevel;
		ar >> m_PanneauDoc.m_AlerteSyslog_nService;
		ar >> m_PanneauDoc.m_AlerteSyslog_Serveur;
		ar >> m_PanneauDoc.m_bAlerte;
		ar >> m_PanneauDoc.m_bAlerteMail;
		ar >> m_PanneauDoc.m_bAlerteSms;
		ar >> m_PanneauDoc.m_bAlerteSon;
		ar >> m_PanneauDoc.m_bAlerteSyslog;
		ar >> m_PanneauDoc.m_nAlerteMail;
		ar >> m_PanneauDoc.m_nAlerteSms;
		ar >> m_PanneauDoc.m_nAlerteSon;
		ar >> m_PanneauDoc.m_nAlerteSyslog;
		ar >> m_PanneauDoc.m_NomDuPanneau;
		ar >> m_PanneauDoc.m_NomDuResponsable;
		ar >> m_PanneauDoc.m_nTemps;

		try
		{
			while( TRUE )
			{			
				ar >> m_PanneauDoc.m_SockThread.Adresse; 
				ar >> m_PanneauDoc.m_SockThread.nItem;
				ar >> m_PanneauDoc.m_SockThread.Nom;
				ar >> m_PanneauDoc.m_SockThread.port;
				ar >> m_PanneauDoc.m_SockThread.Return_error;	
								
				m_PanneauDoc.m_SockThread._this   = &m_PanneauDoc;				
				m_PanneauDoc.m_SockThread.hThread = NULL;
				
				m_PanneauDoc.m_ListSockThread.AddTail( m_PanneauDoc.m_SockThread );			
			}		
		}
		
		catch( ... )
		{		
		}

		m_load = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2Doc diagnostics

#ifdef _DEBUG
void CKeepLink2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKeepLink2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2Doc commands



void CKeepLink2Doc::OnCloseDocument() 
{
	if( pView )
	{
		((CKeepLink2View *)pView)->Panneau->m_bSupp = FALSE;
		((CKeepLink2View *)pView)->OnEditSelectall();
		((CKeepLink2View *)pView)->OnOutilsRgledesurveillanceSupprimer();
	}
	
	CDocument::OnCloseDocument();
}


void CKeepLink2Doc::SetTitle(LPCTSTR lpszTitle) 
{
	CString tmpTile;
	tmpTile = lpszTitle;

	if( tmpTile.Find(".klp", tmpTile.GetLength() - 4 ) > 0 )
		tmpTile = GetTitle();
			
	CDocument::SetTitle( tmpTile );
}

BOOL CKeepLink2Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
