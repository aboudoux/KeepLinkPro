#if !defined(AFX_UPDATE_H__A480B9BC_0F81_41C5_9C83_F8D61B4C957D__INCLUDED_)
#define AFX_UPDATE_H__A480B9BC_0F81_41C5_9C83_F8D61B4C957D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Update.h : header file
//
#include "PictureEx.h"

/////////////////////////////////////////////////////////////////////////////
// CUpdate dialog

class CUpdate : public CDialog
{
// Construction
public:
	CWinThread *m_thread;
	static UINT Download( LPVOID pParam );
	CUpdate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpdate)
	enum { IDD = IDD_UPDATE };
	CProgressCtrl	m_progress;
	CPictureEx m_picture;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdate)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpdate)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAnnuler();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATE_H__A480B9BC_0F81_41C5_9C83_F8D61B4C957D__INCLUDED_)
