#if !defined(AFX_ARRET_H__C60C200B_E7D4_4630_8DAF_110C0BD5C811__INCLUDED_)
#define AFX_ARRET_H__C60C200B_E7D4_4630_8DAF_110C0BD5C811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Arret.h : header file
//
#define ENDDIALOG_SAVEALL_AND_QUIT  0
#define ENDDIALOG_QUIT_WITHOUT_SAVE 1
#define ENDDIALOG_SYSTRAY_REDUCE    2
#define ENDDIALOG_TASKBAR_REDUCE    3

/////////////////////////////////////////////////////////////////////////////
// CArret dialog

class CArret : public CDialog
{
// Construction
public:
	CArret(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArret)
	enum { IDD = IDD_ARRET };
	CComboBox	m_combo;
	CString	m_description;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArret)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArret)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARRET_H__C60C200B_E7D4_4630_8DAF_110C0BD5C811__INCLUDED_)
