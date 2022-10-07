// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// AjoutSimple.cpp : implementation file
//
/************************************************
Gère les événement de l'ajout simple des règles de surveillance
***************************************************/

#include "stdafx.h"
#include "KeepLink2.h"
#include "AjoutSimple.h"
#include "Ajout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAjoutSimple dialog


CAjoutSimple::CAjoutSimple(CWnd* pParent /*=NULL*/)
	: CDialog(CAjoutSimple::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAjoutSimple)
	m_strNom = _T("");
	m_strAdresse = _T("");
	m_strPort = _T("");
	m_strNewPort = _T("");
	//}}AFX_DATA_INIT

}


void CAjoutSimple::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAjoutSimple)
	DDX_Control(pDX, IDC_COMBO_PORT, m_ctlCombo);
	DDX_Control(pDX, IDC_LIST_PORT, m_ListBox);
	DDX_Text(pDX, IDC_EDIT_REGLE_NOM, m_strNom);
	DDX_Text(pDX, IDC_EDIT_ADRESSE, m_strAdresse);
	DDX_CBString(pDX, IDC_COMBO_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_AJOUT_PORT, m_strNewPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAjoutSimple, CDialog)
	//{{AFX_MSG_MAP(CAjoutSimple)
	ON_BN_CLICKED(IDC_RADIO_PORT_SIMPLE, OnRadioClicked)
	ON_EN_CHANGE(IDC_EDIT_REGLE_NOM, OnChangeEdit)
	ON_BN_CLICKED(IDC_BUTTON_AJOUT_PORT, OnButtonAjoutPort)
	ON_BN_CLICKED(IDC_SELECTALL, OnSelectall)
	ON_BN_CLICKED(IDC_RADIO_PORT_MULTIPLE, OnRadioClicked)
	ON_EN_CHANGE(IDC_EDIT_ADRESSE, OnChangeEdit)
	ON_BN_CLICKED(IDC_UNSELECTALL, OnUnselectall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAjoutSimple message handlers

/*********************************************
Activation/Désactivation des controles celon le bouton
radio choisie
************************************************/
void CAjoutSimple::OnRadioClicked() 
{
	BOOL mode;
	UpdateData( TRUE );
	
	UINT control[2][7] = {
		{
			IDC_STATIC_GB_PORT_SIMPLE,
			IDC_COMBO_PORT,			
			0, 0, 0, 0, 0
		},
		{
			IDC_STATIC_GB_PORT_MULTIPLE,
			IDC_EDIT_AJOUT_PORT,
			IDC_BUTTON_AJOUT_PORT,
			IDC_LIST_PORT,
			IDC_SELECTALL,
			IDC_UNSELECTALL,
			0
		}
	};
	
	mode = IsDlgButtonChecked( IDC_RADIO_PORT_MULTIPLE );

	for( int i = 0; i < 7; i++ )
	{
		if( control[mode][i] )
			GetDlgItem( control[mode][i] )->EnableWindow( TRUE );
		
		if( control[!mode][i] )
			GetDlgItem( control[!mode][i] )->EnableWindow( FALSE );
	}

	
}

/*********************************************
initialisation de la boite de dialogue
**********************************************/
BOOL CAjoutSimple::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pParent = (CAjout *)GetParent()->GetParent();

	CString *PortList = m_pParent->m_strPortList;
	
	for( int i = 0; !PortList[i].IsEmpty(); i++ )
	{
		m_ctlCombo.AddString( PortList[i] );
		m_ListBox.AddString( PortList[i] );
	}
	
	CheckDlgButton( IDC_RADIO_PORT_SIMPLE, TRUE );
	OnRadioClicked();
	OnChangeEdit();

	return TRUE;
}


/*********************************************
Active/Désactive le bouton ajouter
**********************************************/
void CAjoutSimple::OnChangeEdit() 
{
	UpdateData( TRUE );

	if( m_strNom.IsEmpty() || m_strAdresse.IsEmpty() )
		(m_pParent->GetDlgItem( IDOK ))->EnableWindow( FALSE );
	else
		(m_pParent->GetDlgItem( IDOK ))->EnableWindow( TRUE );

}


/*********************************************
Ajoute des port à la listbox, dns le cas ou l'utilisateur
désire définir une règle simple pointant sur plusieurs port
**********************************************/
void CAjoutSimple::OnButtonAjoutPort() 
{
		UpdateData( TRUE );

		if( m_strNewPort.IsEmpty() )
		{
			MessageBox("Veuillez indiquer un port à ajouter", NULL, MB_ICONERROR );
			return;
		}

		if( !atoi( m_strNewPort ) )
		{
			MessageBox("Le port de communication réseau doit être un nombre.", NULL, MB_ICONERROR );
			return;
		}

		int nIndex;
		nIndex = m_ListBox.AddString( m_strNewPort );
		m_ListBox.SetSel( nIndex );
		
		m_strNewPort.Empty();

		UpdateData( FALSE );
}

/*********************************************
Traitement du préssement des touches
1 - Evite de quitte la bdl si l'utilisateur clique sur Echap ou entrée
2 - Place le focus  sur l'ajout de port si l'utilisateur presse sur entrée
    Dans l'editBox d'ajout de port à la liste.
**********************************************/
BOOL CAjoutSimple::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
    {
		if( pMsg->wParam==VK_RETURN )
		{
			if( (GetFocus()->GetDlgCtrlID() == IDC_EDIT_AJOUT_PORT ) )			
				OnButtonAjoutPort();
		
			else if( m_pParent->GetDlgItem( IDOK )->IsWindowEnabled() )
			{
				m_pParent->OnAjouter();
			}			
			
			pMsg->wParam=NULL;

		}
		if( pMsg->wParam==VK_ESCAPE )			
				pMsg->wParam=NULL ;		
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}


/*********************************************
Sélectionne tous les ports de la listeBox
**********************************************/
void CAjoutSimple::OnSelectall() 
{
	for( int i = 0; i < m_ListBox.GetCount(); i++ )
		m_ListBox.SetSel( i );
}


/*********************************************
Désélectionne tout les ports de la liste box
**********************************************/
void CAjoutSimple::OnUnselectall() 
{
	for( int i = 0; i < m_ListBox.GetCount(); i++ )
		m_ListBox.SetSel( i, FALSE );	
}
