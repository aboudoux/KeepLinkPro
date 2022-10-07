// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1688FF87_3AAE_4713_AD76_9792B555ABE9__INCLUDED_)
#define AFX_MAINFRM_H__1688FF87_3AAE_4713_AD76_9792B555ABE9__INCLUDED_

#include "Panneau.h"
#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	static UINT InterogateServerLoop( LPVOID pParam );
	BOOL m_bKillFlag;
	BOOL m_MajFlag;
	BOOL GetBinVersion( DWORD & dwHiVersion, DWORD &dwLoVersion );
	BOOL CheckForNewVersion();
	static UINT InternetThread( LPVOID pParam );
	HICON hIconOff;
	HICON hIconOn;
	BOOL m_bInternet;
	BOOL TrayMessage( DWORD dwMessage );
	virtual ~CMainFrame();
	CPanneau Clipboard;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnTray();
	afx_msg void OnUpdateNetworkIndicator( CCmdUI *pCmdUI );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1688FF87_3AAE_4713_AD76_9792B555ABE9__INCLUDED_)
