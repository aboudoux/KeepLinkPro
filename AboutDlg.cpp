#include "stdafx.h"
#include "KeepLink2.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_MATRIX, m_matrix);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HKEY m_hkSoftware;
	char cName[MAX_PATH];
	char cCompany[MAX_PATH];

	DWORD dwType = REG_SZ;
	DWORD dwSize = MAX_PATH;

	// ouvre / créé la clé de registre de configuration
	RegCreateKey( HKEY_LOCAL_MACHINE, "SOFTWARE\\KEEPLINK", &m_hkSoftware );

	// retrouve le nom d'utilisateur
	RtlZeroMemory( cName, MAX_PATH );
	RegQueryValueEx( m_hkSoftware, "OwnerName", 0, &dwType, (LPBYTE)cName, &dwSize );	
	
	// retrouve le nom de la société
	dwSize = MAX_PATH;
	RtlZeroMemory( cCompany, MAX_PATH );
	RegQueryValueEx( m_hkSoftware, "OwnerCompany", 0, &dwType, (LPBYTE)cCompany, &dwSize );

	RegCloseKey( m_hkSoftware );

	CRect rect;
	GetDlgItem(IDC_MATRIX)->GetWindowRect(rect);
	ScreenToClient(rect);

	m_matrix.Create(WS_VISIBLE | WS_CHILD, rect, this );


	m_matrix.AddTextLine("Keeplink PRO Version 1.1");
	m_matrix.AddTextLine("Copyright(c) 2005 - Tech & Feel");	
	m_matrix.AddTextLine("\x01 5");

	m_matrix.AddTextLine("Développé par Aurélien BOUDOUX");
	m_matrix.AddTextLine("\x01 3");

	m_matrix.AddTextLine("KeepLink PRO est un logiciel gratuit");
	m_matrix.AddTextLine("enregistré par");
	m_matrix.AddTextLine("------------------------------------");
	m_matrix.AddTextLine( cName);
	m_matrix.AddTextLine( cCompany );
	m_matrix.AddTextLine("------------------------------------");
	m_matrix.AddTextLine("\x01 3");

	m_matrix.AddTextLine("Tech & Feel");
	m_matrix.AddTextLine("31 rue de cuire, 69004 LYON");
	m_matrix.AddTextLine("Tel : 04 72 10 06 38");
	m_matrix.AddTextLine("");
	m_matrix.AddTextLine(" www.techandfeel.net");
	m_matrix.AddTextLine("\x01 5");	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}