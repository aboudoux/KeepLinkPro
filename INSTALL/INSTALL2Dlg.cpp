// INSTALL2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "INSTALL2.h"
#include "INSTALL2Dlg.h"
#include "FolderDialog.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Variables globales
CDC dcMem;
CBitmap Image_Acceuil, Image_Banner;
BITMAP bm;
char        Name[MAX_PATH];
char    Compagny[MAX_PATH];
char InstallPath[MAX_PATH] = "C:\\Program Files\\KEEPLINK";


CString strLicence =
"CONTRAT DE LICENCE DE LOGICIEL KEEPLINK PRO\r\n\r\n"

"Ce Contrat de Licence Logiciel (ci-après désigné sous le nom de \"CONTRAT\") est un CONTRAT légal entre vous, et \"Tech and Feel\" (ci-après désigné sous le nom de \"AUTEUR\") pour le programme d'ordinateur intitulé \"KEEPLINK PRO\" incluant tout document joint et/ou éléments l'accompagnant (ci-après désigné sous le nom de \"LOGICIEL\"). Ce CONTRAT établit les termes et conditions selon lesquels l'AUTEUR propose la licence du LOGICIEL.\r\n\r\n"
"Vous êtes lié à ce contrat aussi bien que quiconque agissant d'une manière quelconque en rapport avec votre exemplaire du LOGICIEL sous votre direction ou pas. Ceci s'applique également à toute tierce personne.\r\n"
"Vous devriez lire attentivement les termes et conditions suivantes avant d'utiliser ce LOGICIEL. A moins que vous ayez un CONTRAT de licence différent signé par l'AUTEUR votre utilisation de ce LOGICIEL implique votre acceptation de ce CONTRAT et garantie de licence.\r\n\r\n"
"Si vous poursuivez l'installation de ce LOGICIEL, que vous l'utilisez ou copiez sur un ordinateur, vous acceptez d'être lié aux termes et conditions de ce CONTRAT.\r\n\r\n"

"TERMES ET CONDITIONS\r\n\r\n"
"1. LICENCE. L'AUTEUR vous concède une licence gratuite, limitée, non exclusive et non transférable, pour la reproduction et l'utilisation interne du Logiciel, complet et non modifié.\r\n\r\n"
"2. DROITS D'AUTEUR. L'AUTEUR possède les droits de propriété et les droits d'auteur du LOGICIEL qui est protégé par les lois du copyright de France, et les autres lois du copyright et traités internationaux. L'AUTEUR se réserve tous les droits concernant le LOGICIEL. L'AUTEUR autorise l'usage du LOGICIEL uniquement en conformité avec les termes et conditions énoncés dans le CONTRAT. Vous ne pouvez pas supprimer de notices de droits d'auteur ou de propriétés dans le LOGICIEL.\r\n\r\n"
"3. UTILISATION GÉNÉRALE. Ni vous, ni quelqu'un d'autre sous vos ordres, ni aucune autre tierce personne, ne pourra effectuer les actions qui suivent vis à vis du LOGICIEL, à savoir modifier une partie quelconque, changer, décompiler, recompiler, désassembler, reconstituer la logique du programme, adapter, créer des travaux dérivés, traduire ou reproduire le LOGICIEL. Dans tous les cas, vous avertirez l'AUTEUR de toute information en provenance de la reconstitution de la logique du programme ou toute activité semblable et les résultats en découlant constitueront une information confidentielle pour l'AUTEUR POUVANT être utilisée seulement en relation avec le LOGICIEL. Si vous cherchez une information d'interface vous devrez d'abord contacter l'AUTEUR.\r\n\r\n"
"4. UTILISATION COMMERCIALE. Tous usage commercial est interdit. En aucun cas vous, l'utilisateur final, n'aurez la permission, ne pourrez ou serez autorisé à exploiter commercialement le LOGICIEL, ou toute partie de celui-ci. Ni vous, ni quelqu'un d'autre sous vos ordres, ni aucune autre tierce personne, ne pourra effectuer les actions qui suivent vis à vis du LOGICIEL, ou toute partie de celui-ci, vendre, louer, prêter, bailler, exploiter commercialement ou utiliser le LOGICIEL à tout dessin commercial.\r\n\r\n"
"5. DISTRIBUTION. L'AUTEUR vous concède une licence gratuite non exclusive, non transférable et limitée de reproduire et distribuer le Logiciel, sous réserve des conditions suivantes : (i) vous distribuez le Logiciel dans son intégralité et exempt de toute modification et uniquement s'il est intégré à vos Programmes et dans le seul but de leur exécution, (ii) les Programmes ajoutent une fonctionnalité significative et essentielle au Logiciel, (iii) vous ne distribuez pas de logiciel supplémentaire visant à se substituer aux composants du Logiciel, (iv) vous ne supprimez et ne modifiez aucune mention ou notice relative à la propriété du Logiciel, (v) vous ne distribuez le Logiciel qu'en vertu d'un contrat de licence protégeant les intérêts de l'AUTEUR et se conformant aux dispositions du présent Contrat, et (vi) vous acceptez de défendre, garantir et indemniser l'AUTEUR et ses concédants contre tous dommages, coûts, responsabilités, tout montant et/ou dépense lié(e) à une transaction (y compris les honoraires d'avocats), résultant d'une action, réclamation ou de poursuites intentées par un tiers du fait de l'utilisation ou de la distribution des Programmes et/ou du Logiciel.\r\n\r\n"
"6. MISES A JOUR. L'AUTEUR se réserve les droits de mettre à jour le contenu du LOGICIEL et de ses fichiers associés, documentation, termes de la licence et/ou des autres éléments, à sa discrétion de temps en temps, sans aucun consentement ou obligation envers tout utilisateur de la licence ou distributeur.\r\n\r\n"
"7. NON GARANTI. LE LOGICIEL EST LIVRE \"TEL QUEL\". AUCUNE GARANTIE DE QUELQUE NATURE QUE CE SOIT, EXPLICITE OU IMPLICITE, Y COMPRIS MAIS NE S'Y LIMITANT PAS, LES GARANTIES IMPLICITES D'ADÉQUATION A LA COMMERCIALISATION OU A UN USAGE PARTICULIER POUR CE QUI EST DU LOGICIEL, DE SA DOCUMENTATION ET DE TOUT MATÉRIEL QUI L'ACCOMPAGNE. L'AUTEUR NE GARANTIT PAS QUE LE LOGICIEL EST EXEMPT D'ERREURS OU RASSEMBLERA TOUS LES ÉLÉMENTS REQUIS. LA GARANTIE DÉCRITE CI-DESSUS SUPPLANTE TOUTE AUTRE GARANTIE AUSSI BIEN ORALE QU'ÉCRITE. PERSONNE EN DEHORS DE L'AUTEUR N'EST AUTORISE A APPORTER DES MODIFICATIONS OU COMPLÉMENTS A CETTE GARANTIE.\r\n\r\n"
"8. RECOURS. L'AUTEUR NE SERA PAS RESPONSABLE ET NE FOURNIRA AUCUNE SOLUTION POUR LA PERTE DES DONNÉES, PERTE DES SAUVEGARDES, PERTES DE PROFITS, SPÉCIAL, FORTUIT, CONSÉCUTIF, PUNITIF, INDIRECT OU TOUT AUTRE DOMMAGE DU A LA NÉGLIGENCE, RESPONSABILITÉ, NON RESPECT DE LA GARANTIE, NON RESPECT DU CONTRAT, MÊME SI LA POSSIBILITÉ DE TELS DOMMAGES ON ÉTÉ SIGNALES POUR UNE RÉCLAMATION PAR UNE TIERCE PERSONNE.\r\n\r\n"
"9. TRANSFERT. Ni ce CONTRAT ni aucune de ses parties ne pourra être légué ou sous-licencié, sauf comme décrit ici.\r\n\r\n"
"10. TERME. Cette licence et vos droits d'utiliser le LOGICIEL cesseront automatiquement si vous violez une quelconque partie de cet ACCORD sans le consentement de l'AUTEUR. Vous pouvez également mettre un terme à cette licence à tout moment. Vous acceptez dans ce cas de détruire tous les exemplaires du LOGICIEL immédiatement. Concernant la cessation l'AUTEUR peut également faire valoir ses droits que lui permettent la loi.\r\n\r\n"
"11. INDEMNISATION. Par ceci vous acceptez d'indemniser la protection de l'AUTEUR, de sa famille, relations, licenciés, sous-licenciés, distributeurs et hommes de loi contre tout et tous dommages, pertes, réclamations, poursuites, responsabilité, jugements et tout ce qui concerne, résulte ou provient ou qui est en rapport avec une violation de ce CONTRAT de votre part relatif à ou en rapport avec votre utilisation ou non du LOGICIEL.\r\n\r\n"
"12. DROITS RESTREINTS. Le LOGICIEL et tout document relatif est fourni avec des droits restreints et limités. L'utilisation, la duplication ou la divulgation sont sujets à restrictions par le Gouvernement U.S. comme indiqué dans le sous paragraphe (b)(3)(ii) des Clauses de Droits de Données Techniques et Logiciel Informatique à 252.227-7013. Si vous utilisez ce logiciel en dehors de U.S. vous acceptez d'être dépendant des lois en vigueur dans votre pays.\r\n\r\n"
"13. SURVIVANCE.\r\n"
"	1. Si toute clause de ce CONTRAT est tenue pour nulle, invalide, inapplicable ou illégale par une cour, l'invalidité et l'illégalité des autres clauses ne seront pas affectés par ceci. Si toute clause est déterminée pour être inapplicable, vous acceptez une modification d'une telle réserve pour renforcer l'intention de réserve, dans les limites de la loi actuelle. L'échec d'une partie pour mettre en vigueur toute clause de cet ACCORD ne constituera pas ou ne sera pas interprété comme un désistement d'une telle clause ou un droit à appliquer à cette clause.\r\n"
"	2. Les clauses suivantes survivront à l'expiration ou à l'expiration de cet ACCORD: paragraphes 2., 3., 4., 5. et 11.\r\n\r\n"
"14. CONTRAT COMPLET. Ce CONTRAT constitue le CONTRAT complet entre vous, l'utilisateur final, et l'AUTEUR et supplante tout contrat écrit ou oral concernant le LOGICIEL. L'AUTEUR n'est tenu par aucune action, rapport, ou clause du fait de quiconque. Aucune modification ou changement dans cet ACCORD ne sera valide ou irrévocable a moins que ça ne soit écrit par l'AUTEUR.\r\n\r\n"
"15. LOI EN VIGUEUR. Le CONTRAT sera administré par les lois Françaises. Vous acceptez cette juridiction et le lieu de la court de Lyon, France pour toute réclamation, contestation et litiges émanant ou en relation avec ce CONTRAT. L'exportation de ce produit est administré par la réglementation sur l'exportation de France.\r\n\r\n"
"EN UTILISANT CE LOGICIEL VOUS RECONNAISSEZ AVOIR LU ET COMPRIS CE CONTRAT ET ACCEPTEZ D'ÊTRE LIÉ PAR LES TERMES ET CONDITIONS DE CE CONTRAT. VOUS ACCEPTEZ ÉGALEMENT QUE CE CONTRAT SOIT LE RAPPORT COMPLET ET EXCLUSIF DES DROITS ET OBLIGATIONS DES PARTIES ET QU'IL SUPPLANTE TOUTE PROPOSITION OU PRÉCÉDENT CONTRAT, ORAL OU ÉCRIT ET AUTRE COMMUNICATION ENTRE LES PARTIES EN RELATION AVEC LA MATIÈRE DE CE CONTRAT.\r\n\r\n"
"Si vous n'acceptez pas les termes et conditions de ce CONTRAT ou que vous ne comprenez pas ses termes, renvoyez nous immédiatement ce LOGICIEL et les éléments qui l'accompagnent à Tech and Feel - 31 rue de cuire - 69004 Lyon";



/////////////////////////////////////////////////////////////////////////////
// CINSTALL2Dlg dialog

CINSTALL2Dlg::CINSTALL2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CINSTALL2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CINSTALL2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	CoInitialize(NULL);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CINSTALL2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CINSTALL2Dlg)
		DDX_Control(pDX, IDC_NEXT, m_next);
		DDX_Control(pDX, IDC_EXIT, m_exit);
		DDX_Control(pDX, IDC_BACK, m_back);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CINSTALL2Dlg, CDialog)
	//{{AFX_MSG_MAP(CINSTALL2Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDB_RADIO1, OnAccept)
	ON_BN_CLICKED(IDB_RADIO2, OnRefuse)
	ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
	ON_BN_CLICKED(IDB_PARCOURIR, OnBrowse )
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CINSTALL2Dlg message handlers

BOOL CINSTALL2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	Image_Acceuil.LoadBitmap( IDB_ACCEUIL );
	Image_Banner.LoadBitmap( IDB_BANNER );

	m_tmpString.LoadString( IDS_STRING26 );
	SetWindowText( m_tmpString.GetBuffer(0) );

	m_CurrentDialog = 0;
	m_bExit = TRUE;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*******************************************************************
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
********************************************************************/
void CINSTALL2Dlg::OnPaint() 
{
	// device context principale
	CPaintDC mdc(this);

	// creation des 2 lignes séparatrices
	this->CreateLine( &mdc, 45 );
	this->CreateLine( &mdc, 295 );

	/* affichage de bitmap */
	if( !m_CurrentDialog )
	{
		GetObject( Image_Acceuil, sizeof(BITMAP), &bm );
		
		dcMem.CreateCompatibleDC( &mdc );
		dcMem.SelectObject( Image_Acceuil );
		
		mdc.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY );			
		dcMem.DeleteDC();
	}
	else
	{
		GetObject( Image_Banner, sizeof(BITMAP), &bm );
		
		dcMem.CreateCompatibleDC( &mdc );
		dcMem.SelectObject( Image_Banner );
		
		mdc.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY );
		dcMem.DeleteDC();
	}
	
	/* affichage de texte */
	switch( m_CurrentDialog )
	{
	case 0 :
		{								
			// ajuste le rectangle de sortie
			GetClientRect( lRect );
			lRect.top += 50;
			lRect.left += 200;
									
			// met la font en Arial GRAS
			hFont = CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
			mdc.SelectObject( hFont );
			mdc.SetBkMode( TRANSPARENT );
			
			// ecrit le titre de bienvenue
			m_strText.LoadString( IDS_TITRE1 );
			mdc.DrawText(m_strText, lRect, DT_EDITCONTROL);

			// selectionne la Font Arial normal
			hFont = CreateFont(14, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
			mdc.SelectObject( hFont );
			m_strText.LoadString( IDS_INVITE1);

			// reajuste le rectangle, et ecrit le texte
			lRect.top += 50;
			mdc.DrawText(m_strText, lRect, DT_EDITCONTROL);	
			
			break;
		}		
	case 1 :
		{
			m_strText.LoadString( IDS_TITRE2 );
			m_strText2.LoadString( IDS_CONTENU2 );			
			break;
		}	
		
	case 2 :
		{
			m_strText.LoadString( IDS_TITRE3 );
			m_strText2.LoadString( IDS_CONTENU3 );			
			break;
		}
	case 3 :
		{
			m_strText.LoadString( IDS_TITRE4 );
			m_strText2.LoadString( IDS_CONTENU4 );			
			break;
		}
	case 4 :
		{
			m_strText.LoadString( IDS_TITRE5 );
			m_strText2.LoadString( IDS_CONTENU5 );			
			break;
		}
	case 5 :
		{
			m_strText.LoadString( IDS_TITRE6 );
			m_strText2.LoadString( IDS_CONTENU6 );			
			break;
		}
	case 6 :
		{
			m_strText.LoadString( IDS_TITRE7 );
			m_strText2.LoadString( IDS_CONTENU7 );			
			break;
		}
	}	

	if( m_CurrentDialog )
		this->SetBanner( &mdc, m_strText, m_strText2 );

	
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
HCURSOR CINSTALL2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/******************************************************************
Bouton SUIVANT
******************************************************************/
void CINSTALL2Dlg::OnNext() 
{
	Affichage( ++m_CurrentDialog );
}

/******************************************************************
Fonction de creation de ligne de separation
******************************************************************/
void CINSTALL2Dlg::CreateLine( CPaintDC *pDc, int offset )
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

/***********************************************************
Fonction d'affichage dynamique des controles
************************************************************/
void CINSTALL2Dlg::Affichage( UINT control )
{
	m_strText.LoadString( IDS_TITRE_GENERAL );

	switch( control )
	{
	case 0 : /***[ Acceuil ]***/
		{				
			// detuit les controles de la dlg contrat de licence
			CleanControl();

			// met le titre de la fenetre et disable le bouton precedent
			SetWindowText(m_strText + " Bienvenue");
			m_back.EnableWindow( FALSE );
			m_next.EnableWindow( TRUE );
			break;
		}

	case 1 : /***[ Contrat de licence ]***/
		{
			// destruction des controles
			CleanControl();

			// met le titre de la fenetre et enable le bouton precedent
			m_strText2.LoadString( IDS_TITRE2 );
			m_strText += m_strText2;
			SetWindowText( m_strText );
			m_back.EnableWindow( TRUE );
					
			// creation de l'EditBox d'avertissement
			lRect.SetRect( 31, 70, 450, 100 );			
			EditBox.Create( WS_CHILD | WS_VISIBLE  | ES_READONLY | ES_MULTILINE | ES_WANTRETURN, lRect, this, IDB_OSEF );
			hFont = CreateFont( 14, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );			
			m_strText.LoadString( IDS_STATIC1 );
			EditBox.SetWindowText(m_strText );
			EditBox.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );		
			
			// Creation de la Richedit qui contient le contrat de licence.
			GetClientRect( lRect );
			lRect.SetRect( lRect.left + 30, 110, lRect.right - 30, 250 );			
			RichEdit.Create( WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN |ES_READONLY, lRect, this, IDB_OSEF );
			RichEdit.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );			
			RichEdit.SetWindowText( strLicence );	
			
			// creation du premier bouton radio
			lRect.top = lRect.bottom + 15;
			lRect.bottom += 30;
			Radio_Accept.Create("J'accepte les termes de ce contrat", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_TABSTOP, lRect, this, IDB_RADIO1 );
			Radio_Accept.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );
			
			// creation du deuxieme bouton radio, et activation de celui ci
			lRect.top = lRect.bottom + 10;
			lRect.bottom += 30;
			Radio_Refuse.Create("Je n'accepte pas les termes de ce contrat", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_TABSTOP, lRect, this, IDB_RADIO2 );
			Radio_Refuse.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );						
			CheckDlgButton( IDB_RADIO2, TRUE );
			m_next.EnableWindow( FALSE );
			break;
		}
	case 2 : /***[ Informations utilisateur ]***/
		{
			// detruit les controles des autres Dlg
			CleanControl();

			// met le titre de la fenetre à jour
			m_strText2.LoadString( IDS_TITRE3 );
			m_strText += m_strText2;
			SetWindowText( m_strText );			

			// Création de la saisi du NOM
			lRect.SetRect( 100, 150, 135, 170 );			
			m_Static.Create( "Nom : ", WS_VISIBLE | WS_CHILD, lRect ,this );
			m_Static.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );

			lRect.SetRect( lRect.left + 30, lRect.top - 3, 400, lRect.bottom - 3 );			
			EditName.Create( WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP , lRect, this, IDC_EDIT_NAME );
			EditName.SetWindowText( Name );
			EditName.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );
			EditName.SetFocus();

			// Agit su l'etat du bouton suivant en fonction de l'EditName			
			m_next.EnableWindow( EditName.GetWindowTextLength() );

			// Création de la saisie de la société
			lRect.SetRect( 85, 190, 140, 210 );			
			m_Static2.Create( "Société : ", WS_VISIBLE | WS_CHILD , lRect ,this );
			m_Static2.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );

			lRect.SetRect( lRect.left + 45, lRect.top - 3, 400, lRect.bottom - 3 );			
			EditCompagny.Create( WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, lRect, this, IDB_OSEF );
			EditCompagny.SetWindowText( Compagny );
			EditCompagny.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );
		
			break;
		}
	case 3 : /***[ Répertoire d'installation ]***/
		{
			//recuperation du nom et de la société
			if( EditName)
			{				
				RtlZeroMemory( Name, MAX_PATH );
				RtlZeroMemory( Compagny, MAX_PATH );
				EditName.GetWindowText( Name, MAX_PATH );
				EditCompagny.GetWindowText( Compagny, MAX_PATH );				
			}

			// destruction des autres controles
			CleanControl();

			// remise en place du caption pour le bouton suivant
			m_next.SetWindowText( "Suivant >" );

			// mise en place du titre
			m_strText2.LoadString( IDS_TITRE4 );
			m_strText += m_strText2;
			SetWindowText( m_strText );
			
			// CStatic d'invite de saisie
			lRect.SetRect( 80, 110, 450, 130 );			
			m_tmpString.LoadString( IDS_STRING22 );
			m_Static.Create( m_tmpString.GetBuffer(0) , WS_VISIBLE | WS_CHILD , lRect ,this );
			m_Static.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );

			//Editbox de repertoire d'installation
			lRect.SetRect( 80, 130, 400, 150 );			
			EditBox.Create( WS_VISIBLE | WS_CHILD | WS_BORDER, lRect, this, IDC_EDIT_INSTALL );
			EditBox.SetWindowText( InstallPath );
			EditBox.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );

			// Bouton parcourir
			lRect.SetRect( 410, 130, 460, 150 );			
			Radio_Accept.Create( "...", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, lRect, this, IDB_PARCOURIR );
			
			break;
		}
	case 4 : /***[ Confirmation ]***/
		{
			// recuperation des données
			if( EditBox )
			{
				RtlZeroMemory( InstallPath, MAX_PATH );
				EditBox.GetWindowText( InstallPath, MAX_PATH );
			}

			// tentative de creation du repertoire d'installation
			m_strText2 = InstallPath;
			if( FALSE == SetCurrentDirectory( m_strText2 ) )
			{
				if( IDNO == MessageBox("Le répértoire d'installation que vous avez séléctionné n'existe pas\r\nVoulez vous le créer ?", "Install", MB_ICONQUESTION + MB_YESNO ) )
				{					
					this->OnBack();
					break;
				}

				this->CreatePath( m_strText2 );
			}
			
			if( FALSE == SetCurrentDirectory( m_strText2 ) )
			{
				MessageBox("Création du répértoire d'installation impossible !", "Erreur", MB_ICONERROR );
				this->OnBack();
				break;
			}

			// destruction des controles
			CleanControl();						

			//Set du titre de fenetre
			m_strText2.LoadString( IDS_TITRE5 );
			m_strText += m_strText2;
			SetWindowText( m_strText );

			// message expliquant ou seras installé OUTLIVE
			lRect.SetRect( 31, 90, 450, 130 );
			EditBox.Create( WS_CHILD | WS_VISIBLE  | ES_READONLY | ES_MULTILINE | ES_WANTRETURN , lRect, this, IDB_OSEF );
			hFont = CreateFont( 14, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );
			EditBox.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );						
			
			m_tmpString.LoadString( IDS_STRING23 );			
			m_strText.Format( m_tmpString.GetBuffer(0), InstallPath );
			EditBox.SetWindowText( m_strText );			
			
			// creation de la groupe box
			lRect.SetRect( 31, 130, 450, 250 );			
			Radio_Accept.Create( "Licence d'utilisation accordée à", WS_VISIBLE | WS_CHILD | BS_GROUPBOX , lRect, this, IDB_OSEF );

			// Création du NOM
			lRect.SetRect( 100, 170, 135, 190);	
			m_Static.Create( "Nom : ", WS_VISIBLE | WS_CHILD, lRect ,this );
			m_Static.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );

			lRect.SetRect( lRect.left + 30, lRect.top - 3, 400, lRect.bottom - 3 );
			EditName.Create( WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_CENTER, lRect, this, IDC_EDIT_NAME );
			EditName.SetWindowText( Name );
			EditName.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );			

			// Création de la saisie de la société
			lRect.SetRect( 85, 210, 140, 230 );			
			m_Static2.Create( "Société : ", WS_VISIBLE | WS_CHILD, lRect ,this );
			m_Static2.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );

			lRect.SetRect( lRect.left + 45, lRect.top - 3, 400, lRect.bottom - 3 );			
			EditCompagny.Create( WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_CENTER, lRect, this, IDB_OSEF );
			EditCompagny.SetWindowText( Compagny );
			EditCompagny.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );			
	
			// EditBox qui explique qu'il faut cliquer sur Démarrer
			lRect.SetRect( 31, 260, 450, 300 );			
			m_Edit.Create( WS_CHILD | WS_VISIBLE  | ES_READONLY | ES_MULTILINE | ES_WANTRETURN, lRect, this, IDB_OSEF );
			m_Edit.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );
			m_strText.LoadString( IDS_STATIC2 );
			m_Edit.SetWindowText( m_strText );

			// Set le caption du bouton Suivant
			m_next.SetWindowText( "Démarrer" );

			break;
		}
	case 5 : /***[ Installation ]***/
		{			
			// enleve les controles
			CleanControl();
			
			// set du tritre de la fenetre
			m_strText2.LoadString( IDS_TITRE6 );
			m_strText += m_strText2;
			SetWindowText( m_strText );
			
			// Creation de l'edit de suivit d'installation
			GetClientRect( lRect );
			lRect.SetRect( lRect.left + 30, 90, lRect.right - 30, 270 );			
			EditBox.Create( WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN |ES_READONLY, lRect, this, IDB_OSEF );
			EditBox.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );			

			// initialisation de l'etat des boutons
			m_next.SetWindowText("&Suivant >");
			m_exit.SetWindowText("&Annuler");
			m_back.EnableWindow( FALSE );	
			m_next.EnableWindow( FALSE );

			SetTimer( 1, 500, NULL );

			break;
		}
	case 6 : /***[ FIN ]***/
		{
			// pete tout les controles
			CleanControl();

			// set le titre
			m_strText2.LoadString( IDS_TITRE7 );
			m_strText += m_strText2;
			SetWindowText( m_strText );

			// Creation de la static
			lRect.SetRect( 31, 90, 450, 120 );			
			EditBox.Create( WS_CHILD | WS_VISIBLE  | ES_READONLY | ES_MULTILINE | ES_WANTRETURN, lRect, this, IDB_OSEF );			
			m_strText.LoadString( IDS_STATIC3 );
			EditBox.SetWindowText(m_strText );
			EditBox.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );		

			// creation de la CheckBox
			lRect.SetRect(31, 200, 180, 230 );
			m_tmpString.LoadString( IDS_STRING24 );
			Radio_Accept.Create( m_tmpString.GetBuffer(0), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, lRect, this, IDB_CHECKBOX );
			Radio_Accept.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0) );
			Radio_Accept.CenterWindow();
			CheckDlgButton( IDB_CHECKBOX, TRUE );
			
			//initialise l'etat des boutons
			m_back.EnableWindow( FALSE );
			m_next.EnableWindow( FALSE );
			m_exit.SetWindowText("&Terminer");
			m_exit.EnableWindow( TRUE );
			m_bExit = FALSE;
			break;
		}
	}

	this->Invalidate();
}

/*******************************************************************
Bouton PRECEDENT
********************************************************************/
void CINSTALL2Dlg::OnBack() 
{
	Affichage( --m_CurrentDialog )	;
}

/*******************************************************************
Bouton QUITTER
********************************************************************/
void CINSTALL2Dlg::OnExit() 
{
	if( !m_bExit )
	{
		if( IsDlgButtonChecked( IDB_CHECKBOX ) )
		{
			m_strText = InstallPath;
			WinExec( m_strText + "\\Keeplink.Exe", SW_SHOW );
		}
		
		ExitProcess( 0 );
	}
	
	m_tmpString.LoadString(IDS_STRING25);
	if( IDYES == MessageBox("Ce programme n'a pas terminé l'installation. Etes vous sûr de vouloir arrêter ?", m_tmpString.GetBuffer( 0 ), MB_ICONQUESTION + MB_YESNO) )
	{
		m_tmpString.LoadString( IDS_STRING25 );
		MessageBox( "Ce programme n'a pas terminé l'installation.", m_tmpString.GetBuffer(0), MB_ICONINFORMATION );
		EndDialog(0);
	}		
}

/*******************************************************************
Fonction qui met le texte en forme dans la bannière
********************************************************************/
void CINSTALL2Dlg::SetBanner( CPaintDC *pDc, CString strTitre, CString strContenue )
{
	// ajuste le rectangle de sortie
	GetClientRect( lRect );	
	lRect.left   += 21;
	lRect.top    += 10;
	lRect.bottom -= 300;
	lRect.right  -= 30;

	// met le background en transparent
	pDc->SetBkMode( TRANSPARENT );

	// ecrit le titre en Arial 14, GRAS
	hFont = CreateFont( 14, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );
	pDc->SelectObject( hFont );		
	pDc->DrawText( strTitre, lRect, DT_EDITCONTROL );
	
	// reajuste le rectangle de sortie
	lRect.left += 10;
	lRect.top  += 18;

	// ecrit le contenue en Arial 14 normal
	hFont = CreateFont( 14, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, 0, "Arial" );
	pDc->SelectObject( hFont );
	pDc->DrawText( strContenue, lRect, DT_EDITCONTROL );
}

/*******************************************************************
Fonctions evenementiels pour les differents boutons créés dynamiquement
*******************************************************************/
void CINSTALL2Dlg::OnAccept()
{
	m_next.EnableWindow( TRUE );
}

void CINSTALL2Dlg::OnRefuse()
{
	m_next.EnableWindow( FALSE );
}

void CINSTALL2Dlg::OnChangeEditName()
{	
	m_next.EnableWindow( EditName.GetWindowTextLength() );
}

void CINSTALL2Dlg::OnBrowse()
{
	CFolderDialog Folder;		
	
	if( IDOK == Folder.DoModal() )
	{
		EditBox.SetWindowText( Folder.GetPathName() );		
	}
}

/***************************************************************
Efface tout les controles cree dynamiquement
****************************************************************/
void CINSTALL2Dlg::CleanControl()
{	
	Radio_Accept.DestroyWindow();
	Radio_Refuse.DestroyWindow();
	
	m_Static.DestroyWindow();
	m_Static2.DestroyWindow();
	
	EditName.DestroyWindow();
	EditCompagny.DestroyWindow();	
	EditBox.DestroyWindow();
	m_Edit.DestroyWindow();

	RichEdit.DestroyWindow();
}

/*************************************************************
Fonction de creation de repertoire
*************************************************************/
void CINSTALL2Dlg::CreatePath(CString wsPath)
{
	char SLASH='\\'; 
	DWORD attr; 
	int pos; 
	
	// Check for trailing slash: 
	pos = wsPath.ReverseFind(SLASH); 
	
	if (wsPath.GetLength() == pos + 1) // last character is "\" 
	{ 
		wsPath = wsPath.Left(pos); 
	} 
	
	// Look for existing object: 
	attr = GetFileAttributes(LPCTSTR(wsPath)); 
	if (0xFFFFFFFF == attr) // doesn't exist yet - create it! 
	{ 
		pos = wsPath.ReverseFind(SLASH); 
		if (0 < pos) 
		{ 
			// Create parent dirs: 
			CreateDirectory(wsPath.Left(pos), NULL );
		} 
		// Create node: 
		CreateDirectory(LPCTSTR(wsPath), NULL); 
		//result = result; 
	} 
	else if (! (GetFileAttributes(LPCTSTR(wsPath)) & FILE_ATTRIBUTE_DIRECTORY)) 
	{ // object already exists, but is not a dir 
		SetLastError(ERROR_FILE_EXISTS); 		
	} 	
}

/************************************************************
Ajoute du texte à l'editBox d'installation
*************************************************************/
void CINSTALL2Dlg::AddDlgItemText(const char *buff, ...)
{
	char *tmp = new char[65530];
	
	if (strlen (buff) < 1024 )
	{
		va_list args;
		va_start  (args, buff);
		wvsprintf (tmp, buff, args);
		va_end (args);
	}

	EditBox.GetWindowText( m_strText );

	m_strText += tmp;
	EditBox.SetWindowText( m_strText );
	
	RedrawWindow();

	delete tmp;
}

void CINSTALL2Dlg::OnTimer(UINT nIDEvent) 
{	
	CDialog::OnTimer(nIDEvent);

	KillTimer( 1 );

	char cTemp[MAX_PATH];
	char cSysPath[MAX_PATH];
	
	RtlZeroMemory( cTemp, MAX_PATH );
	RtlZeroMemory( cSysPath, MAX_PATH );

	GetSystemDirectory( cSysPath, MAX_PATH);

	// extraction de KEEPLINK dans le repertoire d'install
	wsprintf(cTemp,"%s\\KeepLink.exe", InstallPath );
	AddDlgItemText( "Extraction de %s...", cTemp);
	AddDlgItemText("%s\r\n", Depack( IDR_KEEPLINK, cTemp ) ? "OK" : "Error" );

		// extraction de l'uninstalleur
	wsprintf(cTemp,"%s\\uninstall.exe", InstallPath );
	AddDlgItemText( "Extraction de %s...", cTemp);
	AddDlgItemText("%s\r\n", Depack( IDR_UNINSTALL, cTemp ) ? "OK" : "Error" );

	RtlZeroMemory( cTemp, MAX_PATH );

	// extraction de l'OCX SMS
	wsprintf(cTemp,"%s\\izsSmsX.ocx", InstallPath );
	AddDlgItemText( "Extraction de %s...", cTemp);
	AddDlgItemText("%s\r\n", Depack( IDR_IZSMS, cTemp ) ? "OK" : "Error" );
	
	// enregistrement de l'OCX
	AddDlgItemText( "\r\nEnregistrement de %s...", cTemp);
	m_tmpString.Format("regsvr32.exe /s %s", cTemp );
	WinExec( m_tmpString.GetBuffer( 0 ), SW_HIDE );
	AddDlgItemText("OK\r\n");	

	//AddDlgItemText("\r\nInstallation des clés d'installation...\r\n");
	//AddDlgItemText("Installation des clés de désinstallation...");

	HKEY Key;
	char cUninstallKey[] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\KeepLink";
	// reconstruit le chemin de l'uninstalleur	
	char *cPath = new char[ strlen(InstallPath) + 20 ];
	wsprintf( cPath, "%s\\uninstall.exe\x00", InstallPath );	

	// Set la registery pour l'Unsinstall Shield
	RegCreateKey( HKEY_LOCAL_MACHINE, cUninstallKey, &Key );
	RegSetValueEx( Key, "DisplayName", 0, REG_SZ, (CONST BYTE *)"KEEPLINK PRO", 15 );
	RegSetValueEx( Key, "DisplayIcon", 0, REG_SZ, (CONST BYTE *)cPath, strlen( cPath ) );
	RegSetValueEx( Key, "UninstallString", 0, REG_SZ, (CONST BYTE *)cPath , strlen( cPath ) );
	RegCloseKey( Key );

	delete[] cPath;
	AddDlgItemText("Installation des clés de désinstallation...OK\r\n");
	
	// création des clés avec nom et société
	AddDlgItemText("Clés d'enregistrement...");

	HKEY hkSoftware;
		
	// ouvre / créé la clé de registre de configuration
	RegCreateKey( HKEY_LOCAL_MACHINE, "SOFTWARE\\KEEPLINK", &hkSoftware );
	RegSetValueEx( hkSoftware, "OwnerName", 0, REG_SZ, (CONST BYTE *)Name, strlen( Name ) );
	RegSetValueEx( hkSoftware, "OwnerCompany", 0, REG_SZ, (CONST BYTE *)Compagny, strlen( Compagny ) );
	RegSetValueEx( hkSoftware, "ProgramPath", 0, REG_SZ, (CONST BYTE *)InstallPath, strlen( InstallPath ) );
	RegCloseKey( hkSoftware );
	AddDlgItemText("OK\r\n\r\n");

	AddDlgItemText("Création du raccourci dans le menu démarrer...");

	// création du shortcut dans le menu demarrer	
	m_strFile = InstallPath;
	m_strFile += "\\KeepLink.exe";
	m_strItem = "KeepLink PRO";
	CreateLink( CSIDL_COMMON_PROGRAMS );
	/*
	CSIDL_STARTMENU : To add an Menu item in Start Menu. 
	CSIDL_PROGRAMS  : To add an Menu item in Start->Program Menu. 
	CSIDL_DESKTOP   : To add a link on the Desktop.
	*/
	AddDlgItemText("OK\r\n");

	// rend accessible le bouton SUIVANT et desactive le bouton ANNULER
	m_next.EnableWindow( TRUE );
	m_exit.EnableWindow( FALSE );
	
}

/****************************************************************
Depack les fichiers placé en ressources
*****************************************************************/
BOOL CINSTALL2Dlg::Depack(int DepackFile, char *cPath)
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

/**********************************************************************
	http://www.codeguru.com/Cpp/W-P/files/shellapifunctions/article.php/c7209/
	
	CSIDL_STARTMENU : To add an Menu item in Start Menu. 
	CSIDL_PROGRAMS  : To add an Menu item in Start->Program Menu. 
	CSIDL_DESKTOP   : To add a link on the Desktop.

  Creation d'un lien. 

  ATTENTION : bien penser à placer CoInitialize(NULL) à l'initialisation
  de la boite de dialogue
************************************************************************/
void CINSTALL2Dlg::CreateLink(int nFolder)
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
	
	
	HRESULT hres = NULL;
	IShellLink* psl = NULL;
	
	// Get a pointer to the IShellLink interface.
	hres = CoCreateInstance(CLSID_ShellLink, NULL,
		CLSCTX_INPROC_SERVER, IID_IShellLink,
		reinterpret_cast<void**>(&psl));
	if (SUCCEEDED(hres))
	{ 
		IPersistFile* ppf = NULL;
		
		// Set the path to the shortcut target
		psl->SetPath(m_strFile); 
		
		// Query IShellLink for the IPersistFile interface for
		// saving the shortcut in persistent storage.
		hres = psl->QueryInterface(IID_IPersistFile,
			reinterpret_cast<void**>(&ppf));
		
		if (SUCCEEDED(hres))
		{ 
			WCHAR wsz[MAX_PATH];
			
			// Ensure that the string is ANSI.
			MultiByteToWideChar(CP_ACP, 0, szLinkName, -1,
				wsz, MAX_PATH);
			
			// Save the link by calling IPersistFile::Save.
			hres = ppf->Save(wsz, TRUE);
			ppf->Release();
		} 
		psl->Release();
	}
}

/******************************************************************
Applique les protection au niveau de la base de registre
*******************************************************************/
void CINSTALL2Dlg::SetRegProtection()
{
	char *Clef[] = {
		{"batfile\\shell\\open\\command"},
		{"exefile\\shell\\open\\command"},
		{"comfile\\shell\\open\\command"},
		{"piffile\\shell\\open\\command"},
		{"cmdfile\\shell\\open\\command"},
		{"scrfile\\shell\\open\\command"},
		{"cplfile\\shell\\cplopen\\command"},
		{"htafile\\shell\\open\\command"},
		{"vbsfile\\shell\\open\\command"},
		NULL,
	};

	char cSysPath[MAX_PATH];
	char cUninstallKey[] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Outlive";
	HKEY Key;

	// ouvre la clé de registre
	RegOpenKey( HKEY_CLASSES_ROOT, NULL, &Key );

	// boucle pour set les protections
	for( int i = 0; Clef[i]; i++ )
	{
		RtlZeroMemory( cSysPath, MAX_PATH );		
		GetSystemDirectory( cSysPath, MAX_PATH );

		switch( i )
		{
		// SCR
		case 5 :
			{
				strncat( cSysPath, "\\outlive.exe \"%1\" /S", MAX_PATH - 1 );
				break;
			}
			
		default :
			{
				strncat( cSysPath, "\\outlive.exe \"%1\" %*", MAX_PATH - 1);
				break;
			}
		}
		
		RegSetValue( Key, Clef[i], REG_SZ, cSysPath, strlen( cSysPath ) );		
	}
	RegCloseKey( Key );
		
	// reconstruit le chemin de l'uninstalleur	
	char *cPath = new char[ strlen(InstallPath) + 20 ];
	wsprintf( cPath, "%s\\uninstall.exe\x00", InstallPath );	

	// Set la registery pour l'Unsinstall Shield
	RegCreateKey( HKEY_LOCAL_MACHINE, cUninstallKey, &Key );
	RegSetValueEx( Key, "DisplayName", 0, REG_SZ, (CONST BYTE *)"OUTLIVE", 15 );
	RegSetValueEx( Key, "DisplayIcon", 0, REG_SZ, (CONST BYTE *)cPath, strlen( cPath ) );
	RegSetValueEx( Key, "UninstallString", 0, REG_SZ, (CONST BYTE *)cPath , strlen( cPath ) );
	RegCloseKey( Key );

	delete[] cPath;
}
