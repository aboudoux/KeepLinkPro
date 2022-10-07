// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_ALERTESYSLOGDLG_H__13E3AC98_DE1A_4A7D_81C2_0348D81D469A__INCLUDED_)
#define AFX_ALERTESYSLOGDLG_H__13E3AC98_DE1A_4A7D_81C2_0348D81D469A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlerteSyslogDlg.h : header file
#include "ProprietiesDlg.h"
#include "KeepLink2View.h"
#include "CCheckSK.h"
#include "FlatToolTipCtrl.h"

#define LOG_KERN        (0<<3)  /* kernel messages */
#define LOG_USER        (1<<3)  /* random user-level messages */
#define LOG_MAIL        (2<<3)  /* mail system */
#define LOG_DAEMON      (3<<3)  /* system daemons */
#define LOG_AUTH        (4<<3)  /* security/authorization messages */
#define LOG_SYSLOG      (5<<3)  /* messages generated internally by syslogd */
#define LOG_LPR         (6<<3)  /* line printer subsystem */
#define LOG_NEWS        (7<<3)  /* network news subsystem */
#define LOG_UUCP        (8<<3)  /* UUCP subsystem */
#define LOG_CRON        (9<<3)  /* clock daemon */
#define LOG_AUTHPRIV    (10<<3) /* security/authorization messages (private) */
#define LOG_FTP         (11<<3) /* ftp daemon */
#define LOG_NETINFO     (12<<3) /* NetInfo */
#define LOG_REMOTEAUTH  (13<<3) /* remote authentication/authorization */
#define LOG_INSTALL     (14<<3) /* installer subsystem */

#define LOG_EMERG       0       /* system is unusable */
#define LOG_ALERT       1       /* action must be taken immediately */
#define LOG_CRIT        2       /* critical conditions */
#define LOG_ERR         3       /* error conditions */
#define LOG_WARNING     4       /* warning conditions */
#define LOG_NOTICE      5       /* normal but significant condition */
#define LOG_INFO        6       /* informational */
#define LOG_DEBUG       7       /* debug-level messages */



/////////////////////////////////////////////////////////////////////////////
// CAlerteSyslogDlg dialog

class CAlerteSyslogDlg : public CDialog
{
// Construction
public:
	CToolTipCtrlEx m_ToolTip;
	void OnCheckClick();
	void ButtonTest();
	void GetPriority();
	void SetPriority();
	CKeepLink2View * pView;
	CProprietiesDlg * pPropDlg;
	CAlerteSyslogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlerteSyslogDlg)
	enum { IDD = IDD_ALERTE_SYSLOG };
	CEdit	m_MessageCtrl;
	CCheckSK	m_ctlCheckSyslog;
	BOOL	m_bCheckSyslog;
	CString	m_strMessageSyslog;
	CString	m_strServeurSyslog;
	UINT	m_nEchecSyslog;
	int		m_level;
	int		m_service;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlerteSyslogDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlerteSyslogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckSyslog();
	afx_msg void OnDeltaposSpinSyslog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALERTESYSLOGDLG_H__13E3AC98_DE1A_4A7D_81C2_0348D81D469A__INCLUDED_)
