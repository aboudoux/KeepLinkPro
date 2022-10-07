#if !defined(AFX_AJOUTSIMPLE_H__890575FB_B587_4E10_8148_D3A7F1B1A362__INCLUDED_)
#define AFX_AJOUTSIMPLE_H__890575FB_B587_4E10_8148_D3A7F1B1A362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AjoutSimple.h : header file
//
#include "Ajout.h"

/////////////////////////////////////////////////////////////////////////////
// CAjoutSimple dialog

class CAjoutSimple : public CDialog
{
// Construction
public:
	CAjout * m_pParent;
	CAjoutSimple(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAjoutSimple)
	enum { IDD = IDD_AJOUT_SIMPLE };
	CComboBox	m_ctlCombo;
	CListBox	m_ListBox;
	CString	m_strNom;
	CString	m_strAdresse;
	CString	m_strPort;
	CString	m_strNewPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjoutSimple)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjoutSimple)
	afx_msg void OnRadioClicked();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	afx_msg void OnButtonAjoutPort();
	afx_msg void OnSelectall();
	afx_msg void OnUnselectall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUTSIMPLE_H__890575FB_B587_4E10_8148_D3A7F1B1A362__INCLUDED_)
