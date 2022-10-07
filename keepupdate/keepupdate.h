// keepupdate.h : main header file for the KEEPUPDATE application
//

#if !defined(AFX_KEEPUPDATE_H__3DDCEED8_1B05_4C56_A58A_409A656A2AA5__INCLUDED_)
#define AFX_KEEPUPDATE_H__3DDCEED8_1B05_4C56_A58A_409A656A2AA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKeepupdateApp:
// See keepupdate.cpp for the implementation of this class
//

class CKeepupdateApp : public CWinApp
{
public:
	BOOL GetBinVersion( DWORD &dwHiVersion, DWORD &dwLoVersion );
	CKeepupdateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeepupdateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKeepupdateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEEPUPDATE_H__3DDCEED8_1B05_4C56_A58A_409A656A2AA5__INCLUDED_)
