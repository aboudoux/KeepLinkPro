// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_ALERTEMAILDLG_H__6B5FE1A9_8E8E_42F9_B0C1_34BF2A8132FD__INCLUDED_)
#define AFX_ALERTEMAILDLG_H__6B5FE1A9_8E8E_42F9_B0C1_34BF2A8132FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlerteMailDlg.h : header file
//
#include "KeepLink2Doc.h"
#include "KeepLink2View.h"
#include "ProprietiesDlg.h"
#include "CCheckSK.h"
#include "FlatToolTipCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CAlerteMailDlg dialog

class CAlerteMailDlg : public CDialog
{
// Construction
public:
	CToolTipCtrlEx m_ToolTip;
	void OnCheckClick();
	void ButtonTest();
	CProprietiesDlg * pPropDlg;
	CKeepLink2View * pView;
	CKeepLink2Doc * pDoc;
	CAlerteMailDlg(CWnd* pParent = NULL);   // standard constructor
	afx_msg void OnCheckActiveMail();

// Dialog Data
	//{{AFX_DATA(CAlerteMailDlg)
	enum { IDD = IDD_ALERTE_MAIL };
	CEdit	m_EditDest;
	CEdit	m_MessageCtrl;
	CEdit	m_sujetCtrl;
	CButton	m_HelpButton;
	CStatic	m_helpMail;
	CCheckSK m_ctlCheckMail;
	BOOL	m_bCheckMail;
	CString	m_strDestAddr;
	UINT	m_nEchec;
	CString	m_strMessage;
	CString	m_strSMTP;
	CString	m_strSujet;
	CString	m_strLogin;
	CString	m_strPassword;
	BOOL	m_bCheckAuth;
	CString	m_strSource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlerteMailDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlerteMailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinmail(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChange();
	afx_msg void OnCheckAuth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALERTEMAILDLG_H__6B5FE1A9_8E8E_42F9_B0C1_34BF2A8132FD__INCLUDED_)
