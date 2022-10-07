// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_PROPRIETIESDLG_H__CAC374C3_2A45_4156_9468_78238C843319__INCLUDED_)
#define AFX_PROPRIETIESDLG_H__CAC374C3_2A45_4156_9468_78238C843319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProprietiesDlg.h : header file
//
#include "MyTab.h"
#include "KeepLink2Doc.h"
#include "KeepLink2View.h"

#define GENERAL_TAB       0
#define ALERTE_SON_TAB    1
#define ALERTE_MAIL_TAB   2
#define ALERTE_SMS_TAB    3
#define ALERTE_SYSLOG_TAB 4

/////////////////////////////////////////////////////////////////////////////
// CProprietiesDlg dialog

class CProprietiesDlg : public CDialog
{
// Construction
public:
	CImageList m_imageList;
	CKeepLink2View * pView;
	CKeepLink2Doc * pDoc;
	CProprietiesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProprietiesDlg)
	enum { IDD = IDD_PROPRIETE };
	CMyTab	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProprietiesDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProprietiesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnQuitter();
	afx_msg void OnAppliquer();
	afx_msg void OnButtonTest();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPRIETIESDLG_H__CAC374C3_2A45_4156_9468_78238C843319__INCLUDED_)
