#if !defined(AFX_TABAJOUT_H__FB75DE0A_54DD_4637_976B_47530F76A7BE__INCLUDED_)
#define AFX_TABAJOUT_H__FB75DE0A_54DD_4637_976B_47530F76A7BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabAjout.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabAjout window

class CTabAjout : public CTabCtrl
{
// Construction
public:
	CTabAjout();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabAjout)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Init();
	void SetRectangle();
	UINT m_tabCurrent;
	UINT m_nNumberOfPages;
	CDialog * m_tabPages[2];
	virtual ~CTabAjout();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabAjout)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABAJOUT_H__FB75DE0A_54DD_4637_976B_47530F76A7BE__INCLUDED_)
