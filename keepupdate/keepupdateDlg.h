// keepupdateDlg.h : header file
//

#if !defined(AFX_KEEPUPDATEDLG_H__4A1B8F0E_44C2_4135_B39D_EC35BAFDF3EC__INCLUDED_)
#define AFX_KEEPUPDATEDLG_H__4A1B8F0E_44C2_4135_B39D_EC35BAFDF3EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CISBitmap.h"
/////////////////////////////////////////////////////////////////////////////
// CKeepupdateDlg dialog

class CKeepupdateDlg : public CDialog
{
// Construction
public:
	CString m_strKeepLink;
	BOOL Depack(int DepackFile, char *cPath);
	void AddDlgItemText( const char *buff, ... );
	void CreateLine( CPaintDC *pDc, int offset );
	CKeepupdateDlg(CWnd* pParent = NULL);	// standard constructor
	CCISBitmap m_bitmap;

// Dialog Data
	//{{AFX_DATA(CKeepupdateDlg)
	enum { IDD = IDD_KEEPUPDATE_DIALOG };
	CProgressCtrl	m_progress;
	CString	m_strEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeepupdateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKeepupdateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEEPUPDATEDLG_H__4A1B8F0E_44C2_4135_B39D_EC35BAFDF3EC__INCLUDED_)
