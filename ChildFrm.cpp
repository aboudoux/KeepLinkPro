// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	/*
	cs.style &= ~(WS_THICKFRAME);
    cs.style &= ~(WS_MAXIMIZEBOX);
 
    cs.style |= WS_BORDER;
	*/

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::PreTranslateMessage(MSG* pMsg) 
{

	if( pMsg->message == WM_ENTERSIZEMOVE )
	{
		MessageBox("test");
	}
	
	return CMDIChildWnd::PreTranslateMessage(pMsg);
}
