// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// KeepLink2.h : main header file for the KEEPLINK2 application
//

#if !defined(AFX_KEEPLINK2_H__4E2FC4AC_99A4_428F_B305_EBEBF5149CBC__INCLUDED_)
#define AFX_KEEPLINK2_H__4E2FC4AC_99A4_428F_B305_EBEBF5149CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CKeepLink2App:
// See KeepLink2.cpp for the implementation of this class
//

class CKeepLink2App : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CKeepLink2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeepLink2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CKeepLink2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEEPLINK2_H__4E2FC4AC_99A4_428F_B305_EBEBF5149CBC__INCLUDED_)
