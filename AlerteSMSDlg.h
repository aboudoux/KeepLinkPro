// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_ALERTESMSDLG_H__DE20CCDE_CB68_4F7E_B470_C6E3886EA050__INCLUDED_)
#define AFX_ALERTESMSDLG_H__DE20CCDE_CB68_4F7E_B470_C6E3886EA050__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlerteSMSDlg.h : header file
//
#include "KeepLink2Doc.h"
#include "KeepLink2View.h"
#include "ModemInfo.h"
#include "ProprietiesDlg.h"
#include "CCheckSK.h"
#include "FlatToolTipCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CAlerteSMSDlg dialog

class CAlerteSMSDlg : public CDialog
{
// Construction
public:
	CToolTipCtrlEx m_ToolTip;
	void OnCheckClick();
	void ButtonTest();
	CProprietiesDlg * pPropDlg;
	CModemInfo m_ModemInfo;
	CKeepLink2View * pView;
	CKeepLink2Doc * pDoc;
	CAlerteSMSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlerteSMSDlg)
	enum { IDD = IDD_ALERTE_SMS };
	CEdit	m_MessageCtrl;
	CCheckSK	m_ctlCheckSMS;
	CComboBox	m_ComboModem;
	BOOL	m_CheckSMS;
	UINT	m_nEchecSMS;
	CString	m_strMessageSMS;
	CString	m_strNumeroSMS;
	CString	m_strComboModem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlerteSMSDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlerteSMSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckSmsEnable();
	afx_msg void OnDeltaposSpinsms(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALERTESMSDLG_H__DE20CCDE_CB68_4F7E_B470_C6E3886EA050__INCLUDED_)
