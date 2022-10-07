# Microsoft Developer Studio Project File - Name="KeepLink2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=KeepLink2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "KeepLink2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KeepLink2.mak" CFG="KeepLink2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KeepLink2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "KeepLink2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"INSTALL/res/KeepLink2.exe"

!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "KeepLink2 - Win32 Release"
# Name "KeepLink2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ajout.cpp
# End Source File
# Begin Source File

SOURCE=.\AjoutMultiple.cpp
# End Source File
# Begin Source File

SOURCE=.\AjoutRegle.cpp
# End Source File
# Begin Source File

SOURCE=.\AjoutSimple.cpp
# End Source File
# Begin Source File

SOURCE=.\AlerteMailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlerteSMSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlerteSonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlerteSyslogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Arret.cpp
# End Source File
# Begin Source File

SOURCE=.\Base64.cpp
# End Source File
# Begin Source File

SOURCE=.\CCheckSK.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CISBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.cpp
# End Source File
# Begin Source File

SOURCE=.\cSound.cpp
# End Source File
# Begin Source File

SOURCE=.\FlatToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\izssmsx.cpp
# End Source File
# Begin Source File

SOURCE=.\JMatrixCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\KeepLink2.cpp
# End Source File
# Begin Source File

SOURCE=.\KeepLink2Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\KeepLink2View.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ModemInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTab.cpp
# End Source File
# Begin Source File

SOURCE=.\Panneau.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ProprietiesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Scanner.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendSMSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Smtp.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabAjout.cpp
# End Source File
# Begin Source File

SOURCE=.\Update.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\Ajout.h
# End Source File
# Begin Source File

SOURCE=.\AjoutMultiple.h
# End Source File
# Begin Source File

SOURCE=.\AjoutRegle.h
# End Source File
# Begin Source File

SOURCE=.\AjoutSimple.h
# End Source File
# Begin Source File

SOURCE=.\AlerteMailDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlerteSMSDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlerteSonDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlerteSyslogDlg.h
# End Source File
# Begin Source File

SOURCE=.\Arret.h
# End Source File
# Begin Source File

SOURCE=.\B64crypt.h
# End Source File
# Begin Source File

SOURCE=.\Base64.h
# End Source File
# Begin Source File

SOURCE=.\CCheckSK.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CISBitmap.h
# End Source File
# Begin Source File

SOURCE=.\ColorStaticST.h
# End Source File
# Begin Source File

SOURCE=.\cSound.h
# End Source File
# Begin Source File

SOURCE=.\FlatToolTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GeneralDlg.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\izssmsx.h
# End Source File
# Begin Source File

SOURCE=.\JMatrixCtrl.h
# End Source File
# Begin Source File

SOURCE=.\KeepLink2.h
# End Source File
# Begin Source File

SOURCE=.\KeepLink2Doc.h
# End Source File
# Begin Source File

SOURCE=.\KeepLink2View.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ModemInfo.h
# End Source File
# Begin Source File

SOURCE=.\MyTab.h
# End Source File
# Begin Source File

SOURCE=.\Panneau.h
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\ProprietiesDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegistryEx.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Scanner.h
# End Source File
# Begin Source File

SOURCE=.\ScanViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\SendSMSDlg.h
# End Source File
# Begin Source File

SOURCE=.\Smtp.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabAjout.h
# End Source File
# Begin Source File

SOURCE=.\Update.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\AssortedQ-21.ico"
# End Source File
# Begin Source File

SOURCE=.\res\banner.bmp
# End Source File
# Begin Source File

SOURCE=".\res\BeBox-42.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\desktop.ico
# End Source File
# Begin Source File

SOURCE=.\res\dialup.ico
# End Source File
# Begin Source File

SOURCE=.\res\email05.ico
# End Source File
# Begin Source File

SOURCE=.\res\fin.ico
# End Source File
# Begin Source File

SOURCE=.\res\frame.bmp
# End Source File
# Begin Source File

SOURCE=.\res\green.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_gre.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_mai.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_sms.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_son.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_sys.ico
# End Source File
# Begin Source File

SOURCE=.\res\KeepLink2.ico
# End Source File
# Begin Source File

SOURCE=.\KeepLink2.rc
# End Source File
# Begin Source File

SOURCE=.\res\KeepLink2.rc2
# End Source File
# Begin Source File

SOURCE=.\res\KeepLink2Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.ico
# End Source File
# Begin Source File

SOURCE=.\res\Logo2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menu_ajo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menu_mod.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menu_sta.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menu_sto.bmp
# End Source File
# Begin Source File

SOURCE=.\res\nom.ico
# End Source File
# Begin Source File

SOURCE=".\res\petit logo.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\red.ico
# End Source File
# Begin Source File

SOURCE=.\res\search.ico
# End Source File
# Begin Source File

SOURCE=.\res\Slash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sms.ico
# End Source File
# Begin Source File

SOURCE=".\res\Software-59.ico"
# End Source File
# Begin Source File

SOURCE=.\res\sound08.ico
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\syslog.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tray.ico
# End Source File
# Begin Source File

SOURCE=.\res\vbanner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vbanner2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Voyant.bmp
# End Source File
# Begin Source File

SOURCE=.\res\voyant1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\world2.gif
# End Source File
# End Group
# Begin Source File

SOURCE=.\KeepLink2.reg
# End Source File
# Begin Source File

SOURCE=.\TODO.txt
# End Source File
# End Target
# End Project
# Section KeepLink2 : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
# Section KeepLink2 : {ACBF5346-FD5B-4DC4-B081-ABE0783AF663}
# 	2:21:DefaultSinkHeaderFile:izssmsx.h
# 	2:16:DefaultSinkClass:CIzsSmsX
# End Section
# Section KeepLink2 : {6323463F-A00D-4D0F-B048-9D0A710D6472}
# 	2:5:Class:CIzsSmsX
# 	2:10:HeaderFile:izssmsx.h
# 	2:8:ImplFile:izssmsx.cpp
# End Section
