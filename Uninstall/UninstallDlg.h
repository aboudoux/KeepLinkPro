// UninstallDlg.h : header file
//

#if !defined(AFX_UNINSTALLDLG_H__E0BBC956_3D84_455F_B7E2_12B31C5F28B7__INCLUDED_)
#define AFX_UNINSTALLDLG_H__E0BBC956_3D84_455F_B7E2_12B31C5F28B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUninstallDlg dialog

class CUninstallDlg : public CDialog
{
// Construction
public:
	CString m_strItem;
	CString m_strFile;
	BOOL SelfDelete();
	void DeleteLink( int nFolder );
	CUninstallDlg(CWnd* pParent = NULL);	// standard constructor
	void AddDlgItemText(const char *buff, ... );

// Dialog Data
	//{{AFX_DATA(CUninstallDlg)
	enum { IDD = IDD_UNINSTALL_DIALOG };
	CProgressCtrl	m_progressbar;
	CString	m_strStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUninstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUninstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNINSTALLDLG_H__E0BBC956_3D84_455F_B7E2_12B31C5F28B7__INCLUDED_)
