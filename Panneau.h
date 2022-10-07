// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// Panneau.h: interface for the CPanneau class.
//

#if !defined(AFX_PANNEAU_H__35AD887B_097E_43A8_B5B8_DAADEF4ED4E0__INCLUDED_)
#define AFX_PANNEAU_H__35AD887B_097E_43A8_B5B8_DAADEF4ED4E0__INCLUDED_

#include <afxtempl.h>

//#include "KeepLink2View.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPanneau  
{
public:
	CString m_AlerteMail_AdrEmetteur;
	CString m_FileVersion;
	BOOL m_bMailAuth;
	CString m_AlerteMail_Password;
	CString m_AlerteMail_Login;
	BOOL m_bInternet;
	BOOL m_bSupp;
	BOOL m_hMutex;
	CString m_strComPort;
	CString m_strInitString;
	CString m_AlerteSyslog_Message;
	int m_AlerteSyslog_nLevel;
	int m_AlerteSyslog_nService;
	CString m_AlerteSyslog_Serveur;
	UINT m_nAlerteSyslog;
	BOOL m_bAlerteSyslog;	
	CString m_AlerteMail_Sujet;	
	UINT m_nTemps;
	CString m_AlerteMail_Message;
	CString m_AlerteMail_Adresses;
	CString m_AlerteMail_Serveur;
	CString m_AlerteSon_Fichier;
	CString m_AlerteSms_Message;
	CString m_AlerteSms_Numero;
	CString m_AlerteSms_Modem;
	UINT m_nAlerteSms;
	UINT m_nAlerteSon;
	UINT m_nAlerteMail;
	BOOL m_bAlerte;
	BOOL m_bAlerteSms;
	BOOL m_bAlerteSon;
	BOOL m_bAlerteMail;
	CString m_NomDuResponsable;
	CString m_NomDuPanneau;
	CPanneau();
	virtual ~CPanneau();

	typedef struct THREADSTRUCT
	{
		CWinThread*     hThread;
		int             Return_error;
		CView*			pView;		
		int             port;
		CString         Adresse;
		UINT			nItem;
		CString		    Nom;
		CPanneau*		_this;
		
	} THREADSTRUCT;

	THREADSTRUCT                       m_SockThread;
	CList <THREADSTRUCT, THREADSTRUCT> m_ListSockThread;
	POSITION                           m_CurrentListPosition;

};

#endif // !defined(AFX_PANNEAU_H__35AD887B_097E_43A8_B5B8_DAADEF4ED4E0__INCLUDED_)
