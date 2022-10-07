// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_SCANDLG_H__077F7E48_F81A_4157_8E0C_7E9D10F43634__INCLUDED_)
#define AFX_SCANDLG_H__077F7E48_F81A_4157_8E0C_7E9D10F43634__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanDlg.h : header file
//
#include "AjoutRegle.h"

/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog

class CScanDlg : public CDialog
{
// Construction
public:
	void SetPortArray( int * pArray, UINT nArray, CAjoutRegle *pDlg );
	CScanDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_SCAN };
	CListBox	m_list;
	CString	m_strList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT Max_Thread;
	int * port;
	CAjoutRegle * pAjout;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANDLG_H__077F7E48_F81A_4157_8E0C_7E9D10F43634__INCLUDED_)
