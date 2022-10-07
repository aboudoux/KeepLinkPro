// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_AJOUTREGLE_H__CF4FFA5A_7B33_421F_86AE_07E9AABFC2E6__INCLUDED_)
#define AFX_AJOUTREGLE_H__CF4FFA5A_7B33_421F_86AE_07E9AABFC2E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AjoutRegle.h : header file
//
#include "KeepLink2View.h"
#include "Panneau.h"
#include "HyperLink.h"
#include "ColorStaticST.h"
#include "CISBitmap.h"


/////////////////////////////////////////////////////////////////////////////
// CAjoutRegle dialog

class CAjoutRegle : public CDialog
{
// Construction
public:
	void Tribule( CString *List );
	void SwitchString( CString &source, CString &dest );
	CString * m_strPortList;
	CString m_strTitre;
	CCISBitmap m_bitmap;
	CPanneau * m_Panneau;
	CKeepLink2View * m_pWnd;
	void SetParent( CKeepLink2View *pWnd, CPanneau *Panneau );
	CAjoutRegle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAjoutRegle)
	enum { IDD = IDD_NEW_RULE };
	CComboBox	m_Combo;
	CColorStaticST 	m_staticSurveille;
	CColorStaticST 	m_staticRuleName;
	CColorStaticST 	m_staticIP;
	CHyperLink	m_title;
	CString	m_strAdresse;
	CString	m_strNom;
	CString	m_strPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjoutRegle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjoutRegle)
	virtual BOOL OnInitDialog();
	afx_msg void OnQuit();
	afx_msg void OnAjout();
	afx_msg void OnPaint();
	afx_msg void OnChangeEditAdresse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTREGLE_H__CF4FFA5A_7B33_421F_86AE_07E9AABFC2E6__INCLUDED_)
