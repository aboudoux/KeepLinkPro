// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_MYTAB_H__87809245_64BD_465B_9E93_36823BB30D4B__INCLUDED_)
#define AFX_MYTAB_H__87809245_64BD_465B_9E93_36823BB30D4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTab.h : header file
//
#include "KeepLink2View.h"

/////////////////////////////////////////////////////////////////////////////
// CMyTab window

class CMyTab : public CTabCtrl
{
// Construction
public:
	CMyTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTab)
	//}}AFX_VIRTUAL

// Implementation
public:
	CKeepLink2View * pView;
	void SetTitle( UINT nItem );
	UINT m_tabCurrent;
	void Init();
	void SetRectangle();
	UINT m_nNumberOfPages;
	CDialog * m_tabPages[5];
	virtual ~CMyTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTab)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTAB_H__87809245_64BD_465B_9E93_36823BB30D4B__INCLUDED_)
