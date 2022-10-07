// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_GENERALDLG_H__5CEE1CD3_5E4E_4CB9_93C1_BFA077ABD0D7__INCLUDED_)
#define AFX_GENERALDLG_H__5CEE1CD3_5E4E_4CB9_93C1_BFA077ABD0D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeneralDlg.h : header file
//

#include "KeepLink2Doc.h"
#include "KeepLink2View.h"
#include "ProprietiesDlg.h"
#include "CCheckSK.h"

/////////////////////////////////////////////////////////////////////////////
// CGeneralDlg dialog

class CGeneralDlg : public CDialog
{
// Construction
public:
	CImageList m_imageList;
	void OnCheckClick();
	CProprietiesDlg * pPropDlg;
	CKeepLink2View * pView;
	CKeepLink2Doc * pDoc;
	CGeneralDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeneralDlg)
	enum { IDD = IDD_GENERAL };
	CCheckSK	m_ctlCheckAlerte;
	CSpinButtonCtrl	m_spinTime;
	CString	m_OperatorName;
	CString	m_PanneauName;
	UINT	m_nTime;
	BOOL	m_bCheckAlerte;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneralDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeneralDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinTime(NMHDR* pNMHDR, LRESULT* pResult);	
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALDLG_H__5CEE1CD3_5E4E_4CB9_93C1_BFA077ABD0D7__INCLUDED_)
