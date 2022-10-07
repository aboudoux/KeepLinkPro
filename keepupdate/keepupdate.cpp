// keepupdate.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "keepupdate.h"
#include "keepupdateDlg.h"
#include <version.h>

#pragma comment (lib, "version.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeepupdateApp

BEGIN_MESSAGE_MAP(CKeepupdateApp, CWinApp)
	//{{AFX_MSG_MAP(CKeepupdateApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeepupdateApp construction

CKeepupdateApp::CKeepupdateApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKeepupdateApp object

CKeepupdateApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKeepupdateApp initialization

BOOL CKeepupdateApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CString Command = GetCommandLine();

	// traitement des arguments
	if( -1 != Command.Find("/make", 0 ) )
	{	
		DWORD dwHiVersion;
		DWORD dwLoVersion;

		GetBinVersion( dwHiVersion, dwLoVersion );
		
		CFile version;
		version.Open( "version.bin", CFile::modeCreate  | CFile::typeBinary  | CFile::modeWrite   );
		version.Write( &dwHiVersion, sizeof( DWORD ) );
		version.Write( &dwLoVersion, sizeof( DWORD ) );
		version.Close();
		
		MessageBox( NULL, "Le fichier version a été créé avec succès !", "KEEPLINK UPDATE", MB_ICONINFORMATION );
		ExitProcess(0);
	}

	CKeepupdateDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CKeepupdateApp::GetBinVersion(DWORD &dwHiVersion, DWORD &dwLoVersion)
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
	
	return TRUE;
}
