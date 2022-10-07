// UninstallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Uninstall.h"
#include "UninstallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUninstallDlg dialog

CUninstallDlg::CUninstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUninstallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUninstallDlg)
	m_strStatus = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUninstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUninstallDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progressbar);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_strStatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUninstallDlg, CDialog)
	//{{AFX_MSG_MAP(CUninstallDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUninstallDlg message handlers

BOOL CUninstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	GetDlgItem( IDCANCEL )->EnableWindow( TRUE );
	GetDlgItem( IDOK )->EnableWindow( FALSE );
	SetTimer( 1, 500, NULL );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUninstallDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUninstallDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUninstallDlg::AddDlgItemText(const char *buff, ... )
{
	char *tmp = new char[65530];
	
	if (strlen (buff) < 1024 )
	{
		va_list args;
		va_start  (args, buff);
		wvsprintf (tmp, buff, args);
		va_end (args);
	}

	UpdateData( TRUE );

	m_strStatus += tmp;

	SetDlgItemText(IDC_EDIT_STATUS, m_strStatus);
	RedrawWindow();

	delete tmp;
}

void CUninstallDlg::OnTimer(UINT nIDEvent) 
{
	/* Variables */
	HKEY hKey;
	char cProgramPath[MAX_PATH];
	DWORD dwSize = MAX_PATH;
	DWORD dwType = REG_SZ;	
	
	KillTimer( 1 );

	/* Initialisation */
	RtlZeroMemory( cProgramPath, MAX_PATH );
	m_progressbar.SetRange( 0, 6 );
	m_progressbar.SetStep( 1 );

	//recupère le chemin du home directory
	RegCreateKey( HKEY_LOCAL_MACHINE, "SOFTWARE\\KEEPLINK", &hKey );
	RegQueryValueEx( hKey, "ProgramPath", 0, &dwType, (LPBYTE)cProgramPath, &dwSize );
	RegCloseKey( hKey );
	
	/* Début de la désinstallation */
	AddDlgItemText("Suppression des clés de registres...\r\n");
	
	AddDlgItemText("-> Clés d'enregistrements\r\n");
	RegDeleteKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\KEEPLINK");
	m_progressbar.StepIt();
	
	AddDlgItemText("-> Clés d'installations\r\n");
	RegDeleteKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\KEEPLINK");
	m_progressbar.StepIt();

	AddDlgItemText("\r\nSuppression des raccourcis...");
	m_strFile = "keeplink.exe";
	m_strItem = "KeepLink PRO";
	DeleteLink( CSIDL_COMMON_PROGRAMS );
	AddDlgItemText("OK\r\n");
	m_progressbar.StepIt();

	AddDlgItemText("Suppression de l'OCX...");
	m_strFile.Format("%s\\izsSmsX.ocx", cProgramPath );
	AddDlgItemText( DeleteFile( m_strFile.GetBuffer(0) ) ? "OK\r\n" : "Erreur\r\n" );
	m_progressbar.StepIt();

	AddDlgItemText("Suppression de KEEPLINK...");
	m_strFile.Format("%s\\Keeplink.exe", cProgramPath );
	AddDlgItemText( DeleteFile( m_strFile.GetBuffer(0) ) ? "OK\r\n" : "Erreur\r\n" );
	m_progressbar.StepIt();

	AddDlgItemText("\r\nKeepLink PRO a été désinstallé avec succès !");
	m_progressbar.StepIt();

	GetDlgItem( IDCANCEL )->EnableWindow( FALSE );
	GetDlgItem( IDOK )->EnableWindow( TRUE );

	
	CDialog::OnTimer(nIDEvent);
}

void CUninstallDlg::OnOK() 
{
	SelfDelete();
	
	CDialog::OnOK();
}

void CUninstallDlg::DeleteLink(int nFolder)
{
	//Check for empty strings ...
	if(m_strItem.IsEmpty() || m_strFile.IsEmpty())
	{
		AfxMessageBox("Please,enter the Menu Item and File name correctly.") ;
		return ;
	}
	
	//File system directory that contains the directories for the
	//common program groups that appear on the Start menu for all
	// users.
	LPITEMIDLIST pidl;
	
	// Get a pointer to an item ID list that represents the path
	// of a special folder
	HRESULT hr = SHGetSpecialFolderLocation(NULL, nFolder, &pidl);
	
	// Convert the item ID list's binary representation into a file
	// system path
	char szPath[_MAX_PATH];
	BOOL f = SHGetPathFromIDList(pidl, szPath);
	
	// Allocate a pointer to an IMalloc interface
	LPMALLOC pMalloc;
	
	// Get the address of our task allocator's IMalloc interface
	hr = SHGetMalloc(&pMalloc);
	
	// Free the item ID list allocated by SHGetSpecialFolderLocation
	pMalloc->Free(pidl);
	
	// Free our task allocator
	pMalloc->Release();
	
	CString szLinkName = m_strItem ;
	szLinkName+= _T(".lnk") ;
	
	CString m_szCurrentDirectory = szPath ;// "D:\\Documents and Settings\\Administrator\\Start Menu";
	
	CString szTemp = szLinkName;
	szLinkName.Format( "%s\\%s", m_szCurrentDirectory, szTemp );

	DeleteFile( szLinkName );
}

BOOL CUninstallDlg::SelfDelete()
{
	SHELLEXECUTEINFO sei;
	
	TCHAR szModule [MAX_PATH],
        szComspec[MAX_PATH],
        szParams [MAX_PATH];
	
	// get file path names:
	if((GetModuleFileName(0,szModule,MAX_PATH)!=0) &&
		(GetShortPathName(szModule,szModule,MAX_PATH)!=0) &&
		(GetEnvironmentVariable("COMSPEC",szComspec,MAX_PATH)!=0))
	{
		// set command shell parameters
		lstrcpy(szParams,"/c del ");
		lstrcat(szParams, szModule);
		lstrcat(szParams, " > nul");
		
		// set struct members
		sei.cbSize       = sizeof(sei);
		sei.hwnd         = 0;
		sei.lpVerb       = "Open";
		sei.lpFile       = szComspec;
		sei.lpParameters = szParams;
		sei.lpDirectory  = 0;
		sei.nShow        = SW_HIDE;
		sei.fMask        = SEE_MASK_NOCLOSEPROCESS;
		
		// increase resource allocation to program
		SetPriorityClass(GetCurrentProcess(),
			REALTIME_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(),
			THREAD_PRIORITY_TIME_CRITICAL);
		
		// invoke command shell
		if(ShellExecuteEx(&sei))
		{
			// suppress command shell process until program exits
			SetPriorityClass(sei.hProcess,IDLE_PRIORITY_CLASS);
			SetProcessPriorityBoost(sei.hProcess,TRUE);
			
			// notify explorer shell of deletion
			SHChangeNotify(SHCNE_DELETE,SHCNF_PATH,szModule,0);
			return TRUE;
		}
		else // if error, normalize allocation
		{
			SetPriorityClass(GetCurrentProcess(),
				NORMAL_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(),
				THREAD_PRIORITY_NORMAL);
		}
	}
	return FALSE;
}
