// INSTALL2.h : main header file for the INSTALL2 application
//

#if !defined(AFX_INSTALL2_H__125B9A7C_A235_4244_9406_C78C676F6ACA__INCLUDED_)
#define AFX_INSTALL2_H__125B9A7C_A235_4244_9406_C78C676F6ACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CINSTALL2App:
// See INSTALL2.cpp for the implementation of this class
//

class CINSTALL2App : public CWinApp
{
public:
	CINSTALL2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINSTALL2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CINSTALL2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALL2_H__125B9A7C_A235_4244_9406_C78C676F6ACA__INCLUDED_)
