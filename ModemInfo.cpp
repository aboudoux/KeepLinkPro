// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)

/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1999 by Seain B. Conover, Tarasoft Corporation
// All rights reserved
//
// Distribute freely. Absolutely do not remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
//
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Read *Atlas Shrugged*, http://www.aynrand.org
//
/////////////////////////////////////////////////////////////////////////////


// ModemInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ModemInfo.h"

#include "RegistryEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_ENUM_COUNT		10

/////////////////////////////////////////////////////////////////////////////
// CModemInfo

CModemInfo::CModemInfo()
{
}

CModemInfo::~CModemInfo()
{
}

/////////////////////////////////////////////////////////////////////////////
// CModemInfo message handlers

const CString CModemInfo::GetProfileString( LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault, HKEY hKey ) const
{
	CString strValue = lpszDefault;

	// get section key
	HKEY hSectionKey = NULL;
	::RegOpenKeyEx( hKey, lpszSection, 0, KEY_READ, &hSectionKey );

	// if section does not exist, return default
	if ( hSectionKey != NULL )
	{
		// get desired entry
		DWORD dwType = 0;
		DWORD dwCount = 0;

		if ( ::RegQueryValueEx( hSectionKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount ) == ERROR_SUCCESS )
		{
			ASSERT( dwType == REG_SZ );
	
			if ( ::RegQueryValueEx( hSectionKey, (LPTSTR)lpszEntry, NULL, &dwType, (LPBYTE)strValue.GetBuffer( dwCount / sizeof( TCHAR ) ), &dwCount ) == ERROR_SUCCESS )
			{
				strValue.ReleaseBuffer();
			}
			else
			{
				strValue.ReleaseBuffer();
				strValue = lpszDefault; // just in case
			}
		}

		::RegCloseKey( hSectionKey );
	}

	return strValue;
}


const CString CModemInfo::GetPaddedIndex( const int nIndex ) const
{
	CString strIndex;
	strIndex.Format( "%d", nIndex );
	return CString( "0000" ).Left( 4 - strIndex.GetLength() ) + strIndex;
}

const int CModemInfo::GetModemIndex( CString strName ) const
{
	int nResult = -1;

	if ( !strName.IsEmpty() )
	{
		strName.MakeUpper();

		int nCount;
		for ( nCount = 0; nCount < MAX_ENUM_COUNT; nCount++ )
		{
			CString strGetModemName = GetModemName( nCount );
			strGetModemName.MakeUpper();
			if ( strName == strGetModemName && GetModemComPortByIndex( nCount ) > 0 )
			{
				nResult = nCount;
				break;
			}
		}
	}

	return nResult;
}

const BOOL CModemInfo::GetIsModem( const CString strName ) const
{
	return GetModemIndex( strName ) != -1;
}

const int CModemInfo::GetModemCount() const
{
	int nResult = 0;

	int nCount;
	for ( nCount = 0; nCount < MAX_ENUM_COUNT; nCount++ )
	{
		CString strName = GetModemName( nCount );
		if ( !strName.IsEmpty() && strName.Find( "IP Virtual Modem" ) == -1 ) // don't count COM/IP Virtual Modem
		{
			nResult++;
		}
	}

	return nResult;
}

const CString CModemInfo::GetModemClassGuid() const
{
//	return GetProfileString( "SYSTEM\\CurrentControlSet\\Enum\\Root\\MDMGEN\\" + GetFirstRegistrySubKey( HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Enum\\Root\\MDMGEN" ), "ClassGUID", "", HKEY_LOCAL_MACHINE );
	return "{4D36E96D-E325-11CE-BFC1-08002BE10318}";
}

const CString CModemInfo::GetModemRegistrySection( const int nIndex ) const
{
	CString strResult;

	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	GetVersionEx( &osvi );

	if ( osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
	{
		strResult = "SYSTEM\\CurrentControlSet\\Services\\Class\\Modem\\" + GetPaddedIndex( nIndex );
	}
	else
	{
		strResult = "SYSTEM\\CurrentControlSet\\Control\\Class\\" + GetModemClassGuid() + "\\" + GetPaddedIndex( nIndex );
	}

	return strResult;
}

const CString CModemInfo::GetFirstModemName() const
{
	CString strResult;

	int nCount;
	for ( nCount = 0; nCount < MAX_ENUM_COUNT; nCount++ )
	{
		CString strName = GetModemName( nCount );
		if ( !strName.IsEmpty() && strName.Find( "IP Virtual Modem" ) == -1 ) // don't add COM/IP Virtual Modem
		{
			strResult = strName;
			break;
		}
	}

	return strResult;
}

const CString CModemInfo::GetModemName( const int nIndex ) const
{
	return GetProfileString( GetModemRegistrySection( nIndex ), "Model", "", HKEY_LOCAL_MACHINE );
}

const CString CModemInfo::GetModemResetString( const CString strName ) const
{
	CString strResetString = GetProfileString( GetModemRegistrySection( GetModemIndex( strName ) ), "Reset", "", HKEY_LOCAL_MACHINE );
	
	CString strUpper = strResetString;
	strUpper.MakeUpper();
	if ( strUpper == "NONE" )
	{
		strResetString.Empty();
	}

	return strResetString;
}

const CString CModemInfo::GetModemInitString( const CString strName, const int nSpeakerVolume ) const
{
	CString strInit = "AT";

	const CString strKey = GetModemRegistrySection( GetModemIndex( strName ) ) + "\\Settings";

	CString strCallSetupFailTimer = GetProfileString( strKey, "CallSetupFailTimer", "", HKEY_LOCAL_MACHINE );
	strCallSetupFailTimer.Replace( "<#>", "60" );

	CString strInactivityTimeout = GetProfileString( strKey, "InactivityTimeout", "", HKEY_LOCAL_MACHINE );
	strInactivityTimeout.Replace( "<#>", "0" );

	strInit += strCallSetupFailTimer + strInactivityTimeout;

	if ( nSpeakerVolume != -1 && GetModemHasSpeaker( strName ) )
	{
		const int nNumVolumeLevels = GetModemVolumeLevelsCount( strName );
		const CString strSpeakerOn = GetProfileString( GetModemRegistrySection( GetModemIndex( strName ) ) + "\\Settings", "SpeakerMode_Dial", "", HKEY_LOCAL_MACHINE );

		switch ( nSpeakerVolume )
		{
		case 0:
			strInit += GetProfileString( strKey, "SpeakerMode_OFF", "", HKEY_LOCAL_MACHINE );
			break;
		case 1:
			strInit += nNumVolumeLevels == 0 ? strSpeakerOn : GetProfileString( strKey, "SpeakerVolume_Low", "", HKEY_LOCAL_MACHINE ) + strSpeakerOn;
			break;
		case 2:
			strInit += nNumVolumeLevels > 0 ? GetProfileString( strKey, "SpeakerVolume_Med", "", HKEY_LOCAL_MACHINE ) + strSpeakerOn : "";
			break;
		case 3:
			strInit += nNumVolumeLevels > 0 ? GetProfileString( strKey, "SpeakerVolume_High", "", HKEY_LOCAL_MACHINE ) + strSpeakerOn : "";
			break;
		default:
			ASSERT( FALSE );
		}
	}

	strInit += GetProfileString( strKey, "ErrorControl_On", "", HKEY_LOCAL_MACHINE );
	strInit += GetProfileString( strKey, "Compression_On", "", HKEY_LOCAL_MACHINE );
	strInit += GetProfileString( strKey, "FlowControl_Hard", "", HKEY_LOCAL_MACHINE );
	strInit += GetProfileString( strKey, "Modulation_CCITT", "", HKEY_LOCAL_MACHINE );
	strInit += GetProfileString( strKey, "Blind_Off", "", HKEY_LOCAL_MACHINE );

	return strInit + "<cr>";
}

const BOOL CModemInfo::GetModemHasSpeaker( const CString strName ) const 
{
	return !GetProfileString( GetModemRegistrySection( GetModemIndex( strName ) ) + "\\Settings", "SpeakerMode_Dial", "", HKEY_LOCAL_MACHINE ).IsEmpty() &&
		   !GetProfileString( GetModemRegistrySection( GetModemIndex( strName ) ) + "\\Settings", "SpeakerMode_OFF", "", HKEY_LOCAL_MACHINE ).IsEmpty();
}

const int CModemInfo::GetModemVolumeLevelsCount( const CString strName ) const
{
	int nResult = 0;

	if ( !GetProfileString( GetModemRegistrySection( GetModemIndex( strName ) ) + "\\Settings", "SpeakerVolume_Low", "", HKEY_LOCAL_MACHINE ).IsEmpty() ) nResult++;
	if ( !GetProfileString( GetModemRegistrySection( GetModemIndex( strName ) ) + "\\Settings", "SpeakerVolume_Med", "", HKEY_LOCAL_MACHINE ).IsEmpty() ) nResult++;
	if ( !GetProfileString( GetModemRegistrySection( GetModemIndex( strName ) ) + "\\Settings", "SpeakerVolume_High", "", HKEY_LOCAL_MACHINE ).IsEmpty() ) nResult++;

	return nResult;
}

const CString CModemInfo::GetFirstRegistrySubKey( const HKEY hKey, const CString strSection ) const
{
	CString strResult;

	CRegistryEx RegistryEx;
	if ( RegistryEx.Open( hKey, "" ) )
	{
		CStringArray arSubKeys;
		if ( RegistryEx.ListKey( strSection, arSubKeys ) )
		{
			strResult = arSubKeys[ 0 ];
		}
		RegistryEx.Close();
	}
	
	return strResult;
}

const int CModemInfo::GetModemBps( const CString strName ) const
{
	int nResult = 0;

	CRegistryEx RegistryEx;
	if ( RegistryEx.Open( HKEY_LOCAL_MACHINE, GetModemRegistrySection( GetModemIndex( strName ) ) ) )
	{
		const int nSize = 255;
		char* pBuffer = new char[ nSize + 1];
		if ( RegistryEx.Read( "DCB", pBuffer, nSize ) )
		{
			memcpy( &nResult, &pBuffer[4], 4 );
			if ( nResult != 230400 &&
				 nResult != 115200 &&
				 nResult !=  57600 &&
				 nResult !=  38400 &&
				 nResult !=  19200 &&
				 nResult !=   9600 &&
				 nResult !=   4800 &&
				 nResult !=   2400 &&
				 nResult !=   1200 &&
				 nResult !=    300 &&
				 nResult !=    110 )
			{
				nResult = 0;
			}
		}
		delete [] pBuffer;
		pBuffer=NULL;
		RegistryEx.Close();
	}

	return nResult;
}

const int CModemInfo::GetModemComPortByIndex( const int nIndex ) const
{
	int nResult = 0;

	const CString strPort = GetProfileString( GetModemRegistrySection( nIndex ), "AttachedTo", "", HKEY_LOCAL_MACHINE );
	if ( !strPort.IsEmpty() )
	{
		nResult = atol( strPort.Mid( 3 ) );		// ie, COM3
	}
	else
	{
		CRegistryEx RegistryEx;
		if ( RegistryEx.Open( HKEY_LOCAL_MACHINE, "" ) )
		{
			CString strKey = RegistryEx.FindKey( "Enum", "Driver", "Modem\\" + GetPaddedIndex( nIndex ) );
			if ( !strKey.IsEmpty() )
			{
				const CString strPort = GetProfileString( strKey, "PORTNAME", "", HKEY_LOCAL_MACHINE );
				if ( !strPort.IsEmpty() )
				{
					nResult = atol( strPort.Mid( 3 ) );
				}
			}
			RegistryEx.Close();
		}
	}
		
	return nResult;
}

const int CModemInfo::GetModemComPort( const CString strName ) const
{
	return GetModemComPortByIndex( GetModemIndex( strName ) );
}

void CModemInfo::FillComboBoxWithModemNames( CComboBox* pComboBox )
{
	// delete exiting items
	while ( pComboBox->DeleteString( 0 ) != CB_ERR );

	// add all detected modems
	int nCount;
	for ( nCount = 0; nCount < MAX_ENUM_COUNT; nCount++ )
	{
		CString strName = GetModemName( nCount );
		if ( !strName.IsEmpty() && strName.Find( "IP Virtual Modem" ) == -1 ) // don't add COM/IP Virtual Modem
		{
			pComboBox->AddString( strName );
		}
	}
}

void CModemInfo::FillListBoxWithModemNames( CListBox* pListBox )
{
	// delete exiting items
	while ( pListBox->DeleteString( 0 ) != CB_ERR );

	// add all detected modems
	int nCount;
	for ( nCount = 0; nCount < MAX_ENUM_COUNT; nCount++ )
	{
		CString strName = GetModemName( nCount );
		if ( !strName.IsEmpty() && strName.Find( "IP Virtual Modem" ) == -1 ) // don't add COM/IP Virtual Modem
		{
			pListBox->AddString( strName );
		}
	}
}