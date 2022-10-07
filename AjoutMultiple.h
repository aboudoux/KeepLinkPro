#if !defined(AFX_AJOUTMULTIPLE_H__E169F2B7_8279_4702_B175_D70CBA6DB9DD__INCLUDED_)
#define AFX_AJOUTMULTIPLE_H__E169F2B7_8279_4702_B175_D70CBA6DB9DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AjoutMultiple.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAjoutMultiple dialog

class CAjoutMultiple : public CDialog
{
// Construction
public:
	CAjoutMultiple(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAjoutMultiple)
	enum { IDD = IDD_AJOUT_MULTIPLE };
	CComboBox	m_ctrlComboPort12;
	CComboBox	m_ctrlComboPort11;
	CComboBox	m_ctrlComboPort10;
	CComboBox	m_ctrlComboPort9;
	CComboBox	m_ctrlComboPort8;
	CComboBox	m_ctrlComboPort7;
	CComboBox	m_ctrlComboPort6;
	CComboBox	m_ctrlComboPort5;
	CComboBox	m_ctrlComboPort4;
	CComboBox	m_ctrlComboPort3;
	CComboBox	m_ctrlComboPort2;
	CComboBox	m_ctrlComboPort1;
	CString	m_strPort1;
	CString	m_strPort2;
	CString	m_strPort3;
	CString	m_strPort4;
	CString	m_strPort5;
	CString	m_strPort6;
	CString	m_strPort7;
	CString	m_strPort8;
	CString	m_strPort9;
	CString	m_strPort10;
	CString	m_strAdresse1;
	CString	m_strAdresse2;
	CString	m_strAdresse3;
	CString	m_strAdresse4;
	CString	m_strAdresse5;
	CString	m_strAdresse6;
	CString	m_strAdresse7;
	CString	m_strAdresse8;
	CString	m_strAdresse9;
	CString	m_strAdresse10;
	CString	m_strNom1;
	CString	m_strNom2;
	CString	m_strNom3;
	CString	m_strNom4;
	CString	m_strNom5;
	CString	m_strNom6;
	CString	m_strNom7;
	CString	m_strNom8;
	CString	m_strNom9;
	CString	m_strNom10;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjoutMultiple)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjoutMultiple)
	virtual BOOL OnInitDialog();
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTMULTIPLE_H__E169F2B7_8279_4702_B175_D70CBA6DB9DD__INCLUDED_)
