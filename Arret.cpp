// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// Arret.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "Arret.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArret dialog


CArret::CArret(CWnd* pParent /*=NULL*/)
	: CDialog(CArret::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArret)
	m_description = _T("");
	//}}AFX_DATA_INIT
}


void CArret::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArret)
	DDX_Control(pDX, IDC_COMBO, m_combo);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArret, CDialog)
	//{{AFX_MSG_MAP(CArret)
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArret message handlers

BOOL CArret::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_combo.SetCurSel( 0 );
	OnSelchangeCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArret::OnSelchangeCombo() 
{
	CString Descript[4] = {
	"Enregistre tous les panneaux de surveillance, puis ferme le logiciel",
	"Force le logiciel à fermer sans vérifier si des informations doivent être sauvegardées",	
	"Place l'application dans la barre d'icône située en bas à droite de votre barre des tâches",
	"Place l'application dans la barre des tâches, située en bas de votre bureau",
	};	
	
	int cursel = m_combo.GetCurSel();
	m_description = Descript[cursel];
	UpdateData( FALSE );
}


void CArret::OnOK() 
{
	int cursel = m_combo.GetCurSel();
	EndDialog( cursel );	
}

void CArret::OnCancel() 
{
	EndDialog( -1 );
}
