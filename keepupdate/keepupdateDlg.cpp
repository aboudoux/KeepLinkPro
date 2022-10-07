// keepupdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "keepupdate.h"
#include "keepupdateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeepupdateDlg dialog

CKeepupdateDlg::CKeepupdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeepupdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeepupdateDlg)
	m_strEdit = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeepupdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeepupdateDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Text(pDX, IDC_EDIT_ETAT, m_strEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeepupdateDlg, CDialog)
	//{{AFX_MSG_MAP(CKeepupdateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeepupdateDlg message handlers

BOOL CKeepupdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	/*
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	*/

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if (!m_bitmap.LoadBitmap(IDB_LOGO))
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	GetDlgItem( IDOK )->EnableWindow( FALSE );
	GetDlgItem( IDC_START )->EnableWindow( TRUE );

	SetTimer( 1, 1000, NULL );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeepupdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeepupdateDlg::OnPaint() 
{
	CPaintDC mdc( this );
	m_bitmap.DrawTransparent( &mdc, 0, 0, RGB( 128, 255, 255 ) );

	CreateLine( &mdc, 40 );

	mdc.SetBkMode( TRANSPARENT );
	mdc.TextOut(180, 20, "Mise à jour");

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
HCURSOR CKeepupdateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKeepupdateDlg::CreateLine(CPaintDC *pDc, int offset)
{
	CRect lRect;	
	CPen lPen( PS_SOLID, 1, RGB( 150, 150, 150 ) );
	CPoint lPoint;	

	GetClientRect( lRect );

	lPoint.x = 0;
	lPoint.y = lRect.Height() - offset ;
		
	pDc->SelectObject( lPen );
	pDc->MoveTo( lPoint );
	pDc->LineTo( lRect.Width() , lPoint.y );	
	lPen.DeleteObject();

	lPen.CreatePen( PS_SOLID, 1, RGB(255,255,255) );
	pDc->SelectObject( lPen );
	
	lPoint.y += 1 ;
	pDc->MoveTo( lPoint );
	pDc->LineTo( lRect.Width() , lPoint.y );
	lPen.DeleteObject();
}

void CKeepupdateDlg::OnStart() 
{
	CString m_tmpStr;
	HKEY hKey;
	char installPath[MAX_PATH];

	RtlZeroMemory( installPath, MAX_PATH );
	DWORD dwType = REG_SZ;
	DWORD dwSize = MAX_PATH;
	
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "KEEPLINK PRO" );
	
	if ( hMutex )
	{
		ReleaseMutex( hMutex );
		CloseHandle( hMutex );
		//ReleaseMutex( hMutex );
		MessageBox("ATTENTION, il a été detécté que KeepLink PRO était en cours d'exécution sur votre ordinateur.\r\n\r\n"
			"Veuillez procéder à la fermeture de celui ci, puis reessayez de mettre à jour le logiciel en cliquant sur le bouton Démarrer",
			"Mise à jour KeepLink PRO", MB_ICONEXCLAMATION );
		return;
	}

	GetDlgItem( IDOK )->EnableWindow( TRUE );
	GetDlgItem( IDC_START )->EnableWindow( FALSE );

	m_progress.SetRange32( 0, 4);
	m_progress.SetStep( 1 );

	AddDlgItemText("Récuperation du répertoire d'installation...");
	
	if( !((RegOpenKey( HKEY_LOCAL_MACHINE, "Software\\KEEPLINK", &hKey ) == ERROR_SUCCESS) &&
		(RegQueryValueEx( hKey, "ProgramPath", NULL, &dwType, (BYTE *)installPath, &dwSize ) == ERROR_SUCCESS)) )
	{	
		SetDlgItemText( IDC_EDIT_ETAT, "Erreur !");
		MessageBox("Keeplink PRO n'est pas correctement installé sur cet ordinateur.\r\n\r\n"
			       "Si vous êtes sûr d'avoir correctement installé Keeplink\r\n"
				   "veuillez verifier que vous possédez bien le privilège administrateur\r\n"
				   "puis recommencez la mise à jour du produit.", "Erreur lors de la mise à jour !", MB_ICONERROR );
		OnOK();
	}

	AddDlgItemText("OK\r\nKeepLink pro est installé dans %s\r\n\r\n", installPath );
	m_progress.StepIt();

	m_strKeepLink.Format("%s\\keeplink.exe", installPath );
	AddDlgItemText("Mise à jour de Keeplink.exe...%s\r\n\r\n", Depack( IDR_KEEPLINK, m_strKeepLink.GetBuffer(0)) ? "OK" : "Erreur" );
	m_progress.StepIt();

	AddDlgItemText("Mise à jour terminée !");
	m_progress.StepIt();

	GetDlgItem( IDOK )->EnableWindow( TRUE );
	GetDlgItem( IDC_START )->EnableWindow( FALSE );
	m_progress.StepIt();
}


void CKeepupdateDlg::AddDlgItemText(const char *buff, ...)
{
	char *tmp = new char[MAXWORD - 10];
	
	if (strlen (buff) < 1024 )
	{
		va_list args;
		va_start  (args, buff);
		wvsprintf (tmp, buff, args);
		va_end (args);
	}

	UpdateData( TRUE );

	m_strEdit += tmp;

	SetDlgItemText( IDC_EDIT_ETAT, m_strEdit );
	RedrawWindow();

	delete tmp;
}

BOOL CKeepupdateDlg::Depack(int DepackFile, char *cPath)
{
	HRSRC hRessource;
	HGLOBAL gRes;
	HANDLE hFile;
	DWORD dwSize, NumberOfBytesWritten;
	void *res_mem;
	
	// récupère la ressource
	if( !( hRessource = FindResource( NULL, MAKEINTRESOURCE(DepackFile), "BIN" ) ) )
		return FALSE;
	
	// charge la ressource
	if ( !( gRes = LoadResource( NULL, hRessource ) ) )
		return FALSE;
	
	// utilisation de la ressource
	if ( !( res_mem = LockResource( gRes ) ) )
	{
		FreeResource( gRes );
		return FALSE;
	}
	
	dwSize = SizeofResource( NULL, hRessource );
		
	hFile = CreateFile( cPath, 
		GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 0 );
	
	if( hFile == NULL ) 
	{
		FreeResource( gRes );
		return FALSE;
	}
	
	if( WriteFile(hFile, res_mem, dwSize, &NumberOfBytesWritten, NULL) == 0 )
	{
		FreeResource( gRes ); 
		CloseHandle( hFile );
		DeleteFile( cPath );
		return FALSE;
	}
	
	CloseHandle( hFile );
	FreeResource( gRes );
	return TRUE;
}

void CKeepupdateDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer( 1 );
	OnStart();
	
	CDialog::OnTimer(nIDEvent);
}

void CKeepupdateDlg::OnOK() 
{

	if( !m_strKeepLink.IsEmpty() )
		WinExec( m_strKeepLink, SW_SHOW );

	CDialog::OnOK();
}
