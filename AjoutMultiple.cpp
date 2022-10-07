// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// AjoutMultiple.cpp : implementation file
/******************************************
Traitement des évenements de la boite de dialogue
D'ajout multiple de règle de surveillance
*******************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "AjoutMultiple.h"
#include "Ajout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjoutMultiple dialog


CAjoutMultiple::CAjoutMultiple(CWnd* pParent /*=NULL*/)
	: CDialog(CAjoutMultiple::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjoutMultiple)
	m_strPort1 = _T("");
	m_strPort2 = _T("");
	m_strPort3 = _T("");
	m_strPort4 = _T("");
	m_strPort5 = _T("");
	m_strPort6 = _T("");
	m_strPort7 = _T("");
	m_strPort8 = _T("");
	m_strPort9 = _T("");
	m_strPort10 = _T("");
	m_strAdresse1 = _T("");
	m_strAdresse2 = _T("");
	m_strAdresse3 = _T("");
	m_strAdresse4 = _T("");
	m_strAdresse5 = _T("");
	m_strAdresse6 = _T("");
	m_strAdresse7 = _T("");
	m_strAdresse8 = _T("");
	m_strAdresse9 = _T("");
	m_strAdresse10 = _T("");
	m_strNom1 = _T("");
	m_strNom2 = _T("");
	m_strNom3 = _T("");
	m_strNom4 = _T("");
	m_strNom5 = _T("");
	m_strNom6 = _T("");
	m_strNom7 = _T("");
	m_strNom8 = _T("");
	m_strNom9 = _T("");
	m_strNom10 = _T("");
	//}}AFX_DATA_INIT
}


void CAjoutMultiple::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjoutMultiple)
	DDX_Control(pDX, IDC_COMBO_PORT10, m_ctrlComboPort10);
	DDX_Control(pDX, IDC_COMBO_PORT9, m_ctrlComboPort9);
	DDX_Control(pDX, IDC_COMBO_PORT8, m_ctrlComboPort8);
	DDX_Control(pDX, IDC_COMBO_PORT7, m_ctrlComboPort7);
	DDX_Control(pDX, IDC_COMBO_PORT6, m_ctrlComboPort6);
	DDX_Control(pDX, IDC_COMBO_PORT5, m_ctrlComboPort5);
	DDX_Control(pDX, IDC_COMBO_PORT4, m_ctrlComboPort4);
	DDX_Control(pDX, IDC_COMBO_PORT3, m_ctrlComboPort3);
	DDX_Control(pDX, IDC_COMBO_PORT2, m_ctrlComboPort2);
	DDX_Control(pDX, IDC_COMBO_PORT1, m_ctrlComboPort1);
	DDX_CBString(pDX, IDC_COMBO_PORT1, m_strPort1);
	DDX_CBString(pDX, IDC_COMBO_PORT2, m_strPort2);
	DDX_CBString(pDX, IDC_COMBO_PORT3, m_strPort3);
	DDX_CBString(pDX, IDC_COMBO_PORT4, m_strPort4);
	DDX_CBString(pDX, IDC_COMBO_PORT5, m_strPort5);
	DDX_CBString(pDX, IDC_COMBO_PORT6, m_strPort6);
	DDX_CBString(pDX, IDC_COMBO_PORT7, m_strPort7);
	DDX_CBString(pDX, IDC_COMBO_PORT8, m_strPort8);
	DDX_CBString(pDX, IDC_COMBO_PORT9, m_strPort9);
	DDX_CBString(pDX, IDC_COMBO_PORT10, m_strPort10);
	DDX_Text(pDX, IDC_EDIT_ADRESSE1, m_strAdresse1);
	DDX_Text(pDX, IDC_EDIT_ADRESSE2, m_strAdresse2);
	DDX_Text(pDX, IDC_EDIT_ADRESSE3, m_strAdresse3);
	DDX_Text(pDX, IDC_EDIT_ADRESSE4, m_strAdresse4);
	DDX_Text(pDX, IDC_EDIT_ADRESSE5, m_strAdresse5);
	DDX_Text(pDX, IDC_EDIT_ADRESSE6, m_strAdresse6);
	DDX_Text(pDX, IDC_EDIT_ADRESSE7, m_strAdresse7);
	DDX_Text(pDX, IDC_EDIT_ADRESSE8, m_strAdresse8);
	DDX_Text(pDX, IDC_EDIT_ADRESSE9, m_strAdresse9);
	DDX_Text(pDX, IDC_EDIT_ADRESSE10, m_strAdresse10);
	DDX_Text(pDX, IDC_EDIT_NOM1, m_strNom1);
	DDX_Text(pDX, IDC_EDIT_NOM2, m_strNom2);
	DDX_Text(pDX, IDC_EDIT_NOM3, m_strNom3);
	DDX_Text(pDX, IDC_EDIT_NOM4, m_strNom4);
	DDX_Text(pDX, IDC_EDIT_NOM5, m_strNom5);
	DDX_Text(pDX, IDC_EDIT_NOM6, m_strNom6);
	DDX_Text(pDX, IDC_EDIT_NOM7, m_strNom7);
	DDX_Text(pDX, IDC_EDIT_NOM8, m_strNom8);
	DDX_Text(pDX, IDC_EDIT_NOM9, m_strNom9);
	DDX_Text(pDX, IDC_EDIT_NOM10, m_strNom10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjoutMultiple, CDialog)
	//{{AFX_MSG_MAP(CAjoutMultiple)
	ON_EN_CHANGE(IDC_EDIT_NOM1, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE1, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM2, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE2, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM3, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE3, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM4, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE4, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM5, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE5, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM6, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE6, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM7, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE7, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM8, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE8, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM9, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE9, OnChange)
	ON_EN_CHANGE(IDC_EDIT_NOM10, OnChange)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE10, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT1, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT1, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT2, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT3, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT4, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT5, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT6, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT7, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT8, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT9, OnChange)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT10, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT10, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT2, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT3, OnChange)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT4, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT5, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT6, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT7, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT8, OnChange)
	ON_CBN_KILLFOCUS(IDC_COMBO_PORT9, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjoutMultiple message handlers

/*********************************************
initialisation de la feuille
*********************************************/
BOOL CAjoutMultiple::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString *PortList = ((CAjout *)GetParent()->GetParent())->m_strPortList;	

	CComboBox * ComboTable[] = {
		&m_ctrlComboPort1,
		&m_ctrlComboPort2,
		&m_ctrlComboPort3,
		&m_ctrlComboPort4,
		&m_ctrlComboPort5,
		&m_ctrlComboPort6,
		&m_ctrlComboPort7,
		&m_ctrlComboPort8,
		&m_ctrlComboPort9,
		&m_ctrlComboPort10,
		NULL		
	};

	// Initialise toutes les combos avec la liste générales de ports
	// (La liste ce situe dans CAjout
	for( int i =0; ComboTable[i]; i++ )
	{
		for( int j = 0; !PortList[j].IsEmpty(); j++ )
		{
			ComboTable[i]->AddString( PortList[j] );
		}
	}
	
	return TRUE; 
}

// évite que le fenetre ne ce ferme si l'utilisateur clique sur
// Echap ou ENTRER
BOOL CAjoutMultiple::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
    {
		if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
			pMsg->wParam=NULL ;
    }	
	
	return CDialog::PreTranslateMessage(pMsg);
}

/***************************************
Vérifie si il faut activer ou désactiver le bouton ajouter
A chaque changement d'EditBox
****************************************/
void CAjoutMultiple::OnChange() 
{
	BOOL Flag = FALSE;
	UpdateData( TRUE );
	
	RULES m_Rules[] = {

		{ &m_strNom1, &m_strAdresse1, &m_strPort1 },
		{ &m_strNom2, &m_strAdresse2, &m_strPort2 },
		{ &m_strNom3, &m_strAdresse3, &m_strPort3 },
		{ &m_strNom4, &m_strAdresse4, &m_strPort4 },
		{ &m_strNom5, &m_strAdresse5, &m_strPort5 },
		{ &m_strNom6, &m_strAdresse6, &m_strPort6 },
		{ &m_strNom7, &m_strAdresse7, &m_strPort7 },
		{ &m_strNom8, &m_strAdresse8, &m_strPort8 },
		{ &m_strNom9, &m_strAdresse9, &m_strPort9 },
		{ &m_strNom10, &m_strAdresse10, &m_strPort10 },
		{ NULL, NULL, NULL },

	};

	// Si une des 10 règles est bien renseigné (Nom, adresse + Port)
	// alors on peut activer le bouton ajouter
	for( int i = 0; m_Rules[i].Nom; i++ )
	{
		if( !m_Rules[i].Nom->IsEmpty() && !m_Rules[i].Adresse->IsEmpty() && !m_Rules[i].port->IsEmpty() )
		{
			Flag = TRUE;			
		}
	}

	((CAjout *)GetParent()->GetParent())->GetDlgItem( IDOK )->EnableWindow( Flag );		
}

