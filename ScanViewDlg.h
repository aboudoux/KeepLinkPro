// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

#if !defined(AFX_SCANVIEWDLG_H__9D276124_6A1E_4437_AB0D_9DC5B0989A9F__INCLUDED_)
#define AFX_SCANVIEWDLG_H__9D276124_6A1E_4437_AB0D_9DC5B0989A9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanViewDlg dialog

class CScanViewDlg : public CDialog
{
// Construction
public:
	CScanViewDlg(CWnd* pParent = NULL);   // standard constructor
	void SwitchString(CString &source, CString &dest);

// Dialog Data
	//{{AFX_DATA(CScanViewDlg)
	enum { IDD = IDD_SCAN_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanViewDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANVIEWDLG_H__9D276124_6A1E_4437_AB0D_9DC5B0989A9F__INCLUDED_)
