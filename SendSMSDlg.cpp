// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

// SendSMSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeepLink2.h"
#include "SendSMSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendSMSDlg dialog


CSendSMSDlg::CSendSMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendSMSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendSMSDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSendSMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendSMSDlg)
	DDX_Control(pDX, IDC_IZSSMSX1, m_sms);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendSMSDlg, CDialog)
	//{{AFX_MSG_MAP(CSendSMSDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendSMSDlg message handlers

BOOL CSendSMSDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer( 1, 500, NULL );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSendSMSDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(1);
		
	m_sms.SetInitString( pView->Panneau->m_strInitString );
	m_sms.SetPort( pView->Panneau->m_strComPort );
	m_sms.SetSendTo( pView->Panneau->m_AlerteSms_Numero );
	m_sms.SetText( pView->ParseString( pView->Panneau->m_AlerteSms_Message, m_Index ) );
	m_sms.Send();

	// Patch
	//m_sms.SetPrefixString("0");

	Sleep( 3000 );	
	EndDialog(0);	
	CDialog::OnTimer(nIDEvent);
}


BEGIN_EVENTSINK_MAP(CSendSMSDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSendSMSDlg)
	ON_EVENT(CSendSMSDlg, IDC_IZSSMSX1, 1 /* OnNotification */, OnOnNotificationIzssmsx1, VTS_I4 VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSendSMSDlg::OnOnNotificationIzssmsx1(long TheState, LPCTSTR NotificationMessage) 
{
	SetWindowText( NotificationMessage );
}

void CSendSMSDlg::SetParent(CKeepLink2View *hWnd, int nIndex )
{
	pView   = hWnd;
	m_Index = nIndex;
}
