// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// KeepLink2Doc.h : interface of the CKeepLink2Doc class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_KEEPLINK2DOC_H__0B69DB13_AE62_40C9_A941_305E9811E6EB__INCLUDED_)
#define AFX_KEEPLINK2DOC_H__0B69DB13_AE62_40C9_A941_305E9811E6EB__INCLUDED_

#include "Panneau.h"	// Added by ClassView


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKeepLink2Doc : public CDocument
{
protected: // create from serialization only
	CKeepLink2Doc();
	DECLARE_DYNCREATE(CKeepLink2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeepLink2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CView * pView;
	CPanneau m_PanneauDoc;
	BOOL m_load;
	virtual ~CKeepLink2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKeepLink2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEEPLINK2DOC_H__0B69DB13_AE62_40C9_A941_305E9811E6EB__INCLUDED_)
