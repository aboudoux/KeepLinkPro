// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// ScanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "ScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog


CScanDlg::CScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanDlg)
	m_strList = _T("");
	//}}AFX_DATA_INIT
}


void CScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanDlg)
	DDX_Control(pDX, IDC_LIST_PORT, m_list);
	DDX_LBString(pDX, IDC_LIST_PORT, m_strList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanDlg message handlers

BOOL CScanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString tmp;

	for( UINT i=0; i < Max_Thread; i++ )
	{
		if( (int)port[i] )
		{
			tmp.Format("%u", i );
			m_list.AddString( tmp );
		}
	}
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScanDlg::SetPortArray(int *pArray, UINT nArray, CAjoutRegle *pDlg )
{
	port = pArray;
	Max_Thread = nArray;
	pAjout = pDlg;
}

void CScanDlg::OnOK() 
{

	UpdateData( TRUE );
	pAjout->m_strPort = m_strList;
	pAjout->UpdateData( FALSE );

	CDialog::OnOK();
}
