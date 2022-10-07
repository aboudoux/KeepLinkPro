#if !defined(AFX_SCANNER_H__4529B52B_04B1_403F_B755_A902E76DBADC__INCLUDED_)
#define AFX_SCANNER_H__4529B52B_04B1_403F_B755_A902E76DBADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Scanner.h : header file
//
#include "Ajout.h"

#define APPEND_SELECTED  0
#define APPEND_ALL       1
#define REPLACE_SELECTED 2
#define REPLACE_ALL      3

/////////////////////////////////////////////////////////////////////////////
// CScanner dialog

class CScanner : public CDialog
{
// Construction
public:
	void SetParent( CAjout * pAjout );
	CString * pScanList;
	void OnScanStop();
	static UINT ConnectThread(LPVOID pParam);
	DWORD dwPort;
	void OnScanStart();
	typedef struct _MYTHREAD {
		
		DWORD       port;
		BOOL        *bMutex;
		CScanner *_this;
		
	} MYTHREAD;
	
	MYTHREAD * thisThread;
	BOOL * m_bStack;
	CScanner(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanner)
	enum { IDD = IDD_SCANNER };
	CComboBox	m_combo;
	CListBox	m_list;
	CProgressCtrl	m_progress;
	DWORD	m_pDest;
	DWORD	m_pSource;
	DWORD	m_max_thread;
	DWORD	m_lThread;
	DWORD	m_tThread;
	CString	m_strAdresse;
	CString	m_description;
	//}}AFX_DATA
		
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanner)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanner)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadioButton();
	afx_msg void OnButtonStart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangeEditScanAdresse();
	afx_msg void OnSelchangeComboScan();
	afx_msg void OnButtonOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CAjout * m_pAjout;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNER_H__4529B52B_04B1_403F_B755_A902E76DBADC__INCLUDED_)
