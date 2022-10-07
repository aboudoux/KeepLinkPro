// INSTALL2Dlg.h : header file
//

#if !defined(AFX_INSTALL2DLG_H__5735CF9C_14AA_4DEA_AD2E_BD442754CBEC__INCLUDED_)
#define AFX_INSTALL2DLG_H__5735CF9C_14AA_4DEA_AD2E_BD442754CBEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CINSTALL2Dlg dialog

class CINSTALL2Dlg : public CDialog
{
// Construction
public:
	CString m_tmpString;
	CString m_strItem;
	CString m_strFile;
	CString m_strText;
	UINT m_CurrentDialog;
	CINSTALL2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CINSTALL2Dlg)
	enum { IDD = IDD_DIALOG };
	CButton	m_next;
	CButton	m_exit;
	CButton	m_back;
	CButton Radio_Refuse;
	CButton Radio_Accept;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINSTALL2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnBrowse();
	void OnChangeEditName();
	CEdit EditCompagny;
	CEdit EditName;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CINSTALL2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNext();
	afx_msg void OnBack();
	afx_msg void OnExit();
	afx_msg void OnAccept();
	afx_msg void OnRefuse();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetRegProtection();
	void CreateLink( int nFolder );
	BOOL Depack( int DepackFile, char *cPath );
	void AddDlgItemText( const char *buff, ...);
	void CreatePath( CString wsPath );
	void CleanControl();
	CEdit m_Edit;
	CStatic m_Static, m_Static2;
	CRichEditCtrl RichEdit;
	CEdit EditBox;
	CString m_strText2;
	void SetBanner( CPaintDC *pDc, CString strTitre, CString strContenue );
	CRect lRect;
	HFONT hFont;
	BOOL m_bExit;
	void Affichage( UINT control );
	void CreateLine( CPaintDC *pDc, int offset );

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALL2DLG_H__5735CF9C_14AA_4DEA_AD2E_BD442754CBEC__INCLUDED_)
