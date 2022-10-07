// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// Update.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "Update.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdate dialog


CUpdate::CUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdate)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdate, CDialog)
	//{{AFX_MSG_MAP(CUpdate)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ANNULER, OnAnnuler)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdate message handlers

BOOL CUpdate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_picture.Load( MAKEINTRESOURCE( IDR_MONDE ), _T("GIFFILE") );
	m_picture.Draw();

	SetTimer( 1, 500, NULL );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CUpdate::Download(LPVOID pParam)
{
	CUpdate *_this = (CUpdate *)pParam;
	
	CString version = "keeplink/keepupdate.exe";
	CString url     = "www.techandfeel.com";
	// ------
	CString tmpString;
	CFile File;
	CHttpConnection *connection = NULL;
	CHttpFile       *UpdateFile    = NULL;
	DWORD dwHiVersion = 0;
	DWORD dwLoVersion = 0;
	DWORD dwHiCurrentVersion = 0;
	DWORD dwLoCurrentVersion = 0;
	int bytesread = 0, percent = 0, currentbytes = 0, kbreceived = 0;
	int ret;
	
	CInternetSession Session;
	
	TRY
	{		
		connection = Session.GetHttpConnection( url, 80, (LPCSTR)_T(""), (LPCSTR)_T("") );
		UpdateFile = connection->OpenRequest( 1, version, NULL, 1, NULL, NULL, INTERNET_FLAG_RELOAD );

		// envoie l'autorisation du password en base64
		CString strRequestHeader = "Authorization: Basic "; 
		
		// requete sur www.techandfeel.com/keeplink/keepupdate.exe
		UpdateFile->AddRequestHeaders(strRequestHeader);
		UpdateFile->SendRequest();

		// recuperation de la taille du fichier
		int len = UpdateFile->SeekToEnd();
		UpdateFile->SeekToBegin();
		char * buffer = new char[ len ];

		_this->SetDlgItemText( IDC_STATUS,  "Téléchargement de la mise à jour..." );

		tmpString.Format("%u,%u Mo", len / 1048576, len % 1048576 );
		_this->GetDlgItem( IDC_STATIC_TAILLE )->SetWindowText( tmpString );
		
		// set le range de la progressbar
		_this->m_progress.SetRange32( 0, len );
		
		// telecharge le fichier keepupdate.exe
		while( bytesread = UpdateFile->Read( &buffer[currentbytes] ,512) )
		{
			percent = currentbytes * 100 / len;	

			tmpString.Format( "%u%% téléchargé...", percent );
			_this->SetWindowText( tmpString );
						
			currentbytes += bytesread;			
						
			_this->m_progress.SetPos( currentbytes );
		}
		
		_this->SetWindowText("100% téléchargé.");
		_this->SetDlgItemText( IDC_STATUS,  "Téléchargement de la mise à jour terminé !" );

		// ecrit le fichier sur le disque dur
		char * cTmpFile = new char[MAX_PATH];
		RtlZeroMemory( cTmpFile, MAX_PATH );

		GetTempPath( MAX_PATH, cTmpFile );
		strncat( cTmpFile, "\\TmpUpdate.exe", MAX_PATH );

		File.Open( cTmpFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary );
		File.Write( buffer, len );
		File.Close();

		ret = 1;
		
		delete[] cTmpFile;								
	}
	CATCH(CInternetException, pEx)
	{
		switch( pEx->m_dwError ) 
		{

		case 12016 : 
			_this->SetDlgItemText( IDC_STATUS,  "Erreur, impossible d'optenir la mise à jour." );			
			break;
				
		default:

			char * pError = new char[150];
			RtlZeroMemory( pError, 150 );
			pEx->GetErrorMessage( pError, 150 );			
			_this->SetDlgItemText( IDC_STATUS, pError );
			delete[] pError;
		}
		
		Sleep( 1000 );
		ret = 0;
	}
	END_CATCH

	connection->Close();
	
	Sleep( 1000);
	_this->EndDialog( ret );
	AfxEndThread( ret );

	return 0;
}

void CUpdate::OnTimer(UINT nIDEvent) 
{

	KillTimer( 1 );
	m_thread = AfxBeginThread( Download, this );
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CUpdate::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
    {
		if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
			pMsg->wParam=NULL ;
    }		
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CUpdate::OnAnnuler() 
{
	TerminateThread( m_thread->m_hThread, 0 );
	EndDialog( 0 );	
}
