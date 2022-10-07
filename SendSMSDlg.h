// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

//{{AFX_INCLUDES()
#include "izssmsx.h"
//}}AFX_INCLUDES
#if !defined(AFX_SENDSMSDLG_H__C2E2BD11_2BB2_4AB4_BEF3_2BED7DC3B1C8__INCLUDED_)
#define AFX_SENDSMSDLG_H__C2E2BD11_2BB2_4AB4_BEF3_2BED7DC3B1C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendSMSDlg.h : header file
//
#include "KeepLink2View.h"

/////////////////////////////////////////////////////////////////////////////
// CSendSMSDlg dialog

class CSendSMSDlg : public CDialog
{
// Construction
public:
	int m_Index;
	void SetParent( CKeepLink2View * hWnd, int nIndex );
	CKeepLink2View * pView;
	CSendSMSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendSMSDlg)
	enum { IDD = IDD_SEND_SMS };
	CIzsSmsX	m_sms;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendSMSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendSMSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOnNotificationIzssmsx1(long TheState, LPCTSTR NotificationMessage);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDSMSDLG_H__C2E2BD11_2BB2_4AB4_BEF3_2BED7DC3B1C8__INCLUDED_)
