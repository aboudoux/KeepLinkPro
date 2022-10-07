#if !defined(AFX_AJOUT_H__1DC657D3_C37E_489C_8067_1E8737BFC221__INCLUDED_)
#define AFX_AJOUT_H__1DC657D3_C37E_489C_8067_1E8737BFC221__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ajout.h : header file
//
#include "TabAjout.h"
#include "CISBitmap.h"
#include "KeepLink2View.h"
#include "Panneau.h"

/////////////////////////////////////////////////////////////////////////////
// CAjout dialog

class CAjout : public CDialog
{
// Construction
public:
	void Tribule( CString * List );
	void SwitchString( CString & source, CString & dest );
	void SetParent( CKeepLink2View * pView );
	CKeepLink2View * m_pWnd;
	CPanneau * m_Panneau;
	BOOL AddRule( CString m_strNom, CString m_strAdresse, CString m_strPort );
	~CAjout();
	CString *m_strPortList;
	CCISBitmap m_bitmap;
	CAjout(CWnd* pParent = NULL);   // standard constructor
	afx_msg void OnAjouter();

// Dialog Data
	//{{AFX_DATA(CAjout)
	enum { IDD = IDD_AJOUT };
	CTabAjout	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAjout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAjout)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnScan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AJOUT_H__1DC657D3_C37E_489C_8067_1E8737BFC221__INCLUDED_)

typedef struct _RULES 
{
	CString *Nom;
	CString *Adresse;
	CString *port;
} RULES;