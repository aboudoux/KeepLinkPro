// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// KeepLink2View.h : interface of the CKeepLink2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEEPLINK2VIEW_H__AF395C52_C9F8_42C6_AC0A_BE32F25BA3DC__INCLUDED_)
#define AFX_KEEPLINK2VIEW_H__AF395C52_C9F8_42C6_AC0A_BE32F25BA3DC__INCLUDED_

#include "KeepLink2Doc.h"
#include "Panneau.h"

typedef CTypedPtrList<CPtrList,CDocument*> DocumentList_t;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//

class CKeepLink2View : public CFormView
{
protected: // create from serialization only
	CKeepLink2View();
	DECLARE_DYNCREATE(CKeepLink2View)

public:
	//{{AFX_DATA(CKeepLink2View)
	enum { IDD = IDD_KEEPLINK2_FORM };
	CListCtrl m_tableau;
	//}}AFX_DATA

// Attributes
public:
	CKeepLink2Doc* GetDocument();
	static UINT Socket_Thread( LPVOID pParam );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeepLink2View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void CleanAllModifiedFlag();
	BOOL m_bEnableModif;
	void GetAllDocuments(DocumentList_t &Docs);
	CDocument * GetActiveDoc();
	void BringToTop(CDocument *pDoc);
	void SendSMS( int nThreadIndex );
	BOOL SendSyslogMessage( int nThreadIndex );
	CString ParseString( CString message, int nThreadIndex );
	BOOL SendMail( int nThreadIndex );
	void ExecAlerte( UINT nThreadIndex, UINT FailCount );
	afx_msg void OnStop();
	afx_msg void OnStart();
	//void OnStart();
	CPanneau * Panneau;
	CImageList m_ImageList;
	virtual ~CKeepLink2View();
	afx_msg void OnEditSelectall();
	afx_msg void OnOutilsRgledesurveillanceSupprimer();
	afx_msg void OnSaveall();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKeepLink2View)
	afx_msg void OnUpdateMenu(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRglesRglesNouveau();
	afx_msg void OnOutilsProp();
	afx_msg void OnModifRegle();
	afx_msg void OnStartall();
	afx_msg void OnStopall();	
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
	afx_msg void OnClickTableau(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAideenligne();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in KeepLink2View.cpp
inline CKeepLink2Doc* CKeepLink2View::GetDocument()
   { return (CKeepLink2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEEPLINK2VIEW_H__AF395C52_C9F8_42C6_AC0A_BE32F25BA3DC__INCLUDED_)
