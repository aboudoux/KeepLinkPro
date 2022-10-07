// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "KeepLink2View.h"
#include "MainFrm.h"
#include "Splash.h"
#include "Update.h"
#include "Arret.h"
#include <wininet.h>
#include <afxinet.h>
#include <version.h>

#pragma comment (lib, "version.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MYWM_NOTIFYICON (WM_USER+2)
#define KL_UPDATE (WM_USER+3)
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_TRAY, OnTray)
	ON_UPDATE_COMMAND_UI( ID_NEWORK_INDICATOR, OnUpdateNetworkIndicator)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_NEWORK_INDICATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{	
	m_bInternet = FALSE;
	m_MajFlag   = TRUE;
	m_bKillFlag = TRUE;
	
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HINSTANCE   hInstResource   = NULL;

	if( CreateMutex(NULL, TRUE, "KEEPLINK PRO") == NULL || GetLastError() == ERROR_ALREADY_EXISTS )
	{
		MessageBox("Une instance de Keeplink PRO est déjà en cours d'execution.", "KeepLink PRO", MB_ICONERROR );
		ExitProcess( 0 );
	}
	
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this ) || /*WS_CHILD | WS_VISIBLE | CBRS_BOTTOM*/
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{	
		pSysMenu->InsertMenu( 4, MF_BYPOSITION + MF_STRING, ID_TRAY, "Systray");
		//pSysMenu->AppendMenu(MF_STRING, ID_TRAY, "Placer dans le systray");		
	}

	

//	TrayMessage(NIM_ADD);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);

    hInstResource = AfxFindResourceHandle ( MAKEINTRESOURCE( IDI_ICON_GREEN ), RT_GROUP_ICON);  
    hIconOn  = (HICON)LoadImage( hInstResource, MAKEINTRESOURCE( IDI_ICON_INTERNET_ON ), IMAGE_ICON,16,16, LR_DEFAULTCOLOR );
	hIconOff = (HICON)LoadImage( hInstResource, MAKEINTRESOURCE( IDI_ICON_INTERNET_OFF ), IMAGE_ICON,16,16, LR_DEFAULTCOLOR );
	
	AfxBeginThread( InternetThread, this );
	Sleep( 3000 );
	AfxBeginThread( InterogateServerLoop, this );
		
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::TrayMessage(DWORD dwMessage)
{
	CString sTip(_T("Keeplink PRO"));
	NOTIFYICONDATA tnd;
	tnd.cbSize = sizeof(NOTIFYICONDATA);
	tnd.hWnd = m_hWnd;
	tnd.uID = IDR_TRAYICON;
	tnd.uFlags = NIF_MESSAGE|NIF_ICON;
	tnd.uCallbackMessage = MYWM_NOTIFYICON;
	tnd.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	VERIFY( tnd.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE (IDR_TRAYICON)) );
	lstrcpyn(tnd.szTip, (LPCTSTR)sTip, sizeof(tnd.szTip));
	
	return Shell_NotifyIcon(dwMessage, &tnd);	
}

void CMainFrame::OnClose() 
{
	if( m_bKillFlag )
	{
		CArret KeelinkEnd;
		switch( KeelinkEnd.DoModal() )
		{
		case ENDDIALOG_QUIT_WITHOUT_SAVE :
			{
				CMDIChildWnd *pChild  = (CMDIChildWnd *) GetActiveFrame();
				CKeepLink2View *pView = (CKeepLink2View *) pChild->GetActiveView();

				if( pView )
					pView->CleanAllModifiedFlag();
				
				break;
			}	
		case ENDDIALOG_SAVEALL_AND_QUIT :
			{
				CMDIChildWnd *pChild  = (CMDIChildWnd *) GetActiveFrame();
				CKeepLink2View *pView = (CKeepLink2View *) pChild->GetActiveView();

				if( pView )
					pView->OnSaveall();
				
				break;
			}			
		case ENDDIALOG_TASKBAR_REDUCE :
			{
				PostMessage( WM_SYSCOMMAND, SC_MINIMIZE );
				return;
			}
			break;

		case ENDDIALOG_SYSTRAY_REDUCE :
			{		
				OnTray();
				return;
				break;
			}

		default :
			return;
		}
	}

	TrayMessage( NIM_DELETE );
	
	CMDIFrameWnd::OnClose();	
}

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	
	// traite le message quand l'utilisateur choisie "systray" dans le
	// menu principale
	if( message == WM_SYSCOMMAND )
	{
		if( (wParam & 0xFFF0) == 32784 ) // Bidouille
			OnTray();		
	}
	
	// Open window when the user double-clicks the Systray Icon
    if(message == MYWM_NOTIFYICON)
	{		
		switch (lParam)
		{
			
        case WM_LBUTTONDBLCLK:
			
			switch (wParam) 
			{
				
            case IDR_TRAYICON:
				
				ShowWindow(SW_NORMAL);
				TrayMessage( NIM_DELETE );
				SetForegroundWindow();
				SetFocus();
				return TRUE;
				
				break;				
			}
			
			break;			
		}
		
	}

	if( message == KL_UPDATE )
	{
		if( IDYES == MessageBox( "Une nouvelle version de KeepLink PRO est disponible.\r\n\r\n"
			"Voulez vous mettre à jour votre logiciel maintenant ?",		
			NULL, MB_ICONINFORMATION + MB_YESNO ) )
		{
			CUpdate m_update;
			if( m_update.DoModal() )
			{
				m_bKillFlag = FALSE;
				PostMessage( WM_CLOSE );					
				
				char cTmpFile[MAX_PATH];
				RtlZeroMemory( cTmpFile, MAX_PATH );
				
				GetTempPath( MAX_PATH, cTmpFile );
				
				strncat( cTmpFile, "\\TmpUpdate.exe", MAX_PATH );
				WinExec( cTmpFile, SW_SHOW );
				m_MajFlag = FALSE;			
			}
		} else m_MajFlag = TRUE; 
	}
	
	return CMDIFrameWnd::WindowProc(message, wParam, lParam);
}

void CMainFrame::OnTray() 
{
	TrayMessage(NIM_ADD);
	ShowWindow( SW_HIDE );
}

void CMainFrame::OnUpdateNetworkIndicator( CCmdUI *pCmdUI )
{	
	if( m_bInternet )
	{
		pCmdUI->SetText( "Internet accessible");		
		m_wndStatusBar.SendMessage( SB_SETICON, 1, (LPARAM) (HICON)hIconOn );
	}
	else
	{
		pCmdUI->SetText( "Internet inaccessible");	
		m_wndStatusBar.SendMessage( SB_SETICON, 1, (LPARAM) (HICON)hIconOff );
	}

}


UINT CMainFrame::InternetThread(LPVOID pParam)
{
	CMainFrame * _this = (CMainFrame *)pParam;

	while( TRUE )
	{
		_this->m_bInternet = InternetCheckConnection( "http://www.microsoft.com", FLAG_ICC_FORCE_CONNECTION, 0 );		
		Sleep( 10000 );
	}
}


BOOL CMainFrame::CheckForNewVersion()
{
	CString version = "keeplink/version.bin";
	CString url     = "www.techandfeel.com";
	// ------
	CHttpConnection *connection = NULL;
	CHttpFile       *VerFile    = NULL;
	DWORD dwHiVersion = 0;
	DWORD dwLoVersion = 0;
	DWORD dwHiCurrentVersion = 0;
	DWORD dwLoCurrentVersion = 0;
	BOOL ret = FALSE;

	TRY
	{
		CInternetSession *Session = NULL;
		Session = new CInternetSession();
		
		connection = Session->GetHttpConnection( url, 80, (LPCSTR)_T(""), (LPCSTR)_T("") );
		VerFile = connection->OpenRequest( 1, version, NULL, 1, NULL, NULL, INTERNET_FLAG_RELOAD );

		// envoie l'autorisation du password en base64
		CString strRequestHeader = "Authorization: Basic "; 
		
		// requete sur www.techandfeel.com/keeplink/version.bin
		VerFile->AddRequestHeaders(strRequestHeader);
		VerFile->SendRequest();
		
		// recupere la version de l'update
		VerFile->Read( &dwHiVersion, sizeof( DWORD ) );
		VerFile->Read( &dwLoVersion, sizeof( DWORD ) );
				
		// affiche la version de l'update
		TRACE("Version de la mise à jour sur le serveur : %u.%u.%u.%u", 
			HIWORD( dwHiVersion ),
			LOWORD( dwHiVersion ),
			HIWORD( dwLoVersion ),
			LOWORD( dwLoVersion )
			);

		if( dwHiVersion > 1 )
			return FALSE;

		GetBinVersion( dwHiCurrentVersion, dwLoCurrentVersion );

		// comparaison de la version du serveur avec la version actuelle		
		ret = ( ((dwHiVersion < dwHiCurrentVersion) || ((dwHiVersion == dwHiCurrentVersion) && (dwLoVersion <= dwLoCurrentVersion))) ? FALSE : TRUE );	
	}
	CATCH(CInternetException, pEx)
	{
		switch( pEx->m_dwError ) 
		{

		case 12016 : 
			TRACE("Erreur, impossible de ce connecter au site d'update" );
			break;
				
		default:

			char * pError = new char[150];
			RtlZeroMemory( pError, 150 );
			pEx->GetErrorMessage( pError, 150 );			
			TRACE("%s", pError );
			delete[] pError;
			pError=NULL;
		}

		ret = FALSE;
	}
	END_CATCH

	connection->Close();
	
	return ret;
}



BOOL CMainFrame::GetBinVersion(DWORD &dwHiVersion, DWORD &dwLoVersion )
{
	DWORD var;
	char *pVersion, BinName[MAX_PATH];
	VS_FIXEDFILEINFO *VerInfo;

	// retrouve le nom du binaire
	RtlZeroMemory( BinName, MAX_PATH );
	GetModuleFileName( NULL, BinName, MAX_PATH - 1 );
	
	if ( !( var = GetFileVersionInfoSize( BinName, &var ) ) )
		return FALSE;
	
	pVersion = new char[ var ];
	
	GetFileVersionInfo( BinName, 0, var, pVersion );
	VerQueryValue( pVersion, "\\", (LPVOID *) &VerInfo, (PUINT) &var );

	// met la version du moteur dans les variables globales
	dwHiVersion = VerInfo->dwProductVersionMS;
	dwLoVersion = VerInfo->dwProductVersionLS;

	TRACE("Version du binaire : %u.%u.%u.%u", 
			HIWORD( dwHiVersion ),
			LOWORD( dwHiVersion ),
			HIWORD( dwLoVersion ),
			LOWORD( dwLoVersion )
			);
	
	delete[] pVersion;
	pVersion=NULL;
	
	return TRUE;
}

UINT CMainFrame::InterogateServerLoop(LPVOID pParam)
{
	CMainFrame * _this = (CMainFrame *)pParam;
	
	while( TRUE )
	{		
		if( _this->m_MajFlag ) 
		{
			if( _this->CheckForNewVersion() )
			{
				_this->m_MajFlag = FALSE;
				_this->PostMessage( KL_UPDATE );
			} 			
		}
	
		Sleep( 7200000 );
	}

	return 0;
}
