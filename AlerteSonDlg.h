// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_ALERTESONDLG_H__7A3E895F_F667_4C81_9072_635B7E0EBC3C__INCLUDED_)
#define AFX_ALERTESONDLG_H__7A3E895F_F667_4C81_9072_635B7E0EBC3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlerteSonDlg.h : header file
//
#include "KeepLink2Doc.h"
#include "KeepLink2View.h"
#include "ProprietiesDlg.h"
#include "CCheckSK.h"

/////////////////////////////////////////////////////////////////////////////
// CAlerteSonDlg dialog

class CAlerteSonDlg : public CDialog
{
// Construction
public:
	void OnCheckClick();
	void ButtonTest();
	CProprietiesDlg * pPropDlg;
	CKeepLink2Doc * pDoc;
	CKeepLink2View * pView;
	CAlerteSonDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlerteSonDlg)
	enum { IDD = IDD_ALERTE_SON };
	CCheckSK m_ctlCheckSon;
	UINT	m_nEchecSon;
	CString	m_strSound;
	BOOL	m_bCheckSon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlerteSonDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlerteSonDlg)
	afx_msg void OnCheckSonenable();
	afx_msg void OnDeltaposSpinson(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditFichierson();
	afx_msg void OnButtonParcourir();
	afx_msg void OnChangeEditEchecson();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALERTESONDLG_H__7A3E895F_F667_4C81_9072_635B7E0EBC3C__INCLUDED_)
