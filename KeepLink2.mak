# Microsoft Developer Studio Generated NMAKE File, Based on KeepLink2.dsp
!IF "$(CFG)" == ""
CFG=KeepLink2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to KeepLink2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "KeepLink2 - Win32 Release" && "$(CFG)" != "KeepLink2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\INSTALL\res\KeepLink2.exe"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\Ajout.obj"
	-@erase "$(INTDIR)\AjoutMultiple.obj"
	-@erase "$(INTDIR)\AjoutRegle.obj"
	-@erase "$(INTDIR)\AjoutSimple.obj"
	-@erase "$(INTDIR)\AlerteMailDlg.obj"
	-@erase "$(INTDIR)\AlerteSMSDlg.obj"
	-@erase "$(INTDIR)\AlerteSonDlg.obj"
	-@erase "$(INTDIR)\AlerteSyslogDlg.obj"
	-@erase "$(INTDIR)\Arret.obj"
	-@erase "$(INTDIR)\Base64.obj"
	-@erase "$(INTDIR)\CCheckSK.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\CISBitmap.obj"
	-@erase "$(INTDIR)\ColorStaticST.obj"
	-@erase "$(INTDIR)\cSound.obj"
	-@erase "$(INTDIR)\FlatToolTipCtrl.obj"
	-@erase "$(INTDIR)\GeneralDlg.obj"
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\izssmsx.obj"
	-@erase "$(INTDIR)\JMatrixCtrl.obj"
	-@erase "$(INTDIR)\KeepLink2.obj"
	-@erase "$(INTDIR)\KeepLink2.pch"
	-@erase "$(INTDIR)\KeepLink2.res"
	-@erase "$(INTDIR)\KeepLink2Doc.obj"
	-@erase "$(INTDIR)\KeepLink2View.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ModemInfo.obj"
	-@erase "$(INTDIR)\MyTab.obj"
	-@erase "$(INTDIR)\Panneau.obj"
	-@erase "$(INTDIR)\PictureEx.obj"
	-@erase "$(INTDIR)\ProprietiesDlg.obj"
	-@erase "$(INTDIR)\RegistryEx.obj"
	-@erase "$(INTDIR)\Scanner.obj"
	-@erase "$(INTDIR)\ScanViewDlg.obj"
	-@erase "$(INTDIR)\SendSMSDlg.obj"
	-@erase "$(INTDIR)\Smtp.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TabAjout.obj"
	-@erase "$(INTDIR)\Update.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\INSTALL\res\KeepLink2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\KeepLink2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\KeepLink2.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KeepLink2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\KeepLink2.pdb" /machine:I386 /out:"INSTALL/res/KeepLink2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\Ajout.obj" \
	"$(INTDIR)\AjoutMultiple.obj" \
	"$(INTDIR)\AjoutRegle.obj" \
	"$(INTDIR)\AjoutSimple.obj" \
	"$(INTDIR)\AlerteMailDlg.obj" \
	"$(INTDIR)\AlerteSMSDlg.obj" \
	"$(INTDIR)\AlerteSonDlg.obj" \
	"$(INTDIR)\AlerteSyslogDlg.obj" \
	"$(INTDIR)\Arret.obj" \
	"$(INTDIR)\Base64.obj" \
	"$(INTDIR)\CCheckSK.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\CISBitmap.obj" \
	"$(INTDIR)\ColorStaticST.obj" \
	"$(INTDIR)\cSound.obj" \
	"$(INTDIR)\FlatToolTipCtrl.obj" \
	"$(INTDIR)\GeneralDlg.obj" \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\izssmsx.obj" \
	"$(INTDIR)\JMatrixCtrl.obj" \
	"$(INTDIR)\KeepLink2.obj" \
	"$(INTDIR)\KeepLink2Doc.obj" \
	"$(INTDIR)\KeepLink2View.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ModemInfo.obj" \
	"$(INTDIR)\MyTab.obj" \
	"$(INTDIR)\Panneau.obj" \
	"$(INTDIR)\PictureEx.obj" \
	"$(INTDIR)\ProprietiesDlg.obj" \
	"$(INTDIR)\RegistryEx.obj" \
	"$(INTDIR)\Scanner.obj" \
	"$(INTDIR)\ScanViewDlg.obj" \
	"$(INTDIR)\SendSMSDlg.obj" \
	"$(INTDIR)\Smtp.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TabAjout.obj" \
	"$(INTDIR)\Update.obj" \
	"$(INTDIR)\KeepLink2.res"

".\INSTALL\res\KeepLink2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\KeepLink2.exe" "$(OUTDIR)\KeepLink2.bsc"


CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\AboutDlg.sbr"
	-@erase "$(INTDIR)\Ajout.obj"
	-@erase "$(INTDIR)\Ajout.sbr"
	-@erase "$(INTDIR)\AjoutMultiple.obj"
	-@erase "$(INTDIR)\AjoutMultiple.sbr"
	-@erase "$(INTDIR)\AjoutRegle.obj"
	-@erase "$(INTDIR)\AjoutRegle.sbr"
	-@erase "$(INTDIR)\AjoutSimple.obj"
	-@erase "$(INTDIR)\AjoutSimple.sbr"
	-@erase "$(INTDIR)\AlerteMailDlg.obj"
	-@erase "$(INTDIR)\AlerteMailDlg.sbr"
	-@erase "$(INTDIR)\AlerteSMSDlg.obj"
	-@erase "$(INTDIR)\AlerteSMSDlg.sbr"
	-@erase "$(INTDIR)\AlerteSonDlg.obj"
	-@erase "$(INTDIR)\AlerteSonDlg.sbr"
	-@erase "$(INTDIR)\AlerteSyslogDlg.obj"
	-@erase "$(INTDIR)\AlerteSyslogDlg.sbr"
	-@erase "$(INTDIR)\Arret.obj"
	-@erase "$(INTDIR)\Arret.sbr"
	-@erase "$(INTDIR)\Base64.obj"
	-@erase "$(INTDIR)\Base64.sbr"
	-@erase "$(INTDIR)\CCheckSK.obj"
	-@erase "$(INTDIR)\CCheckSK.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\CISBitmap.obj"
	-@erase "$(INTDIR)\CISBitmap.sbr"
	-@erase "$(INTDIR)\ColorStaticST.obj"
	-@erase "$(INTDIR)\ColorStaticST.sbr"
	-@erase "$(INTDIR)\cSound.obj"
	-@erase "$(INTDIR)\cSound.sbr"
	-@erase "$(INTDIR)\FlatToolTipCtrl.obj"
	-@erase "$(INTDIR)\FlatToolTipCtrl.sbr"
	-@erase "$(INTDIR)\GeneralDlg.obj"
	-@erase "$(INTDIR)\GeneralDlg.sbr"
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\HyperLink.sbr"
	-@erase "$(INTDIR)\izssmsx.obj"
	-@erase "$(INTDIR)\izssmsx.sbr"
	-@erase "$(INTDIR)\JMatrixCtrl.obj"
	-@erase "$(INTDIR)\JMatrixCtrl.sbr"
	-@erase "$(INTDIR)\KeepLink2.obj"
	-@erase "$(INTDIR)\KeepLink2.pch"
	-@erase "$(INTDIR)\KeepLink2.res"
	-@erase "$(INTDIR)\KeepLink2.sbr"
	-@erase "$(INTDIR)\KeepLink2Doc.obj"
	-@erase "$(INTDIR)\KeepLink2Doc.sbr"
	-@erase "$(INTDIR)\KeepLink2View.obj"
	-@erase "$(INTDIR)\KeepLink2View.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\ModemInfo.obj"
	-@erase "$(INTDIR)\ModemInfo.sbr"
	-@erase "$(INTDIR)\MyTab.obj"
	-@erase "$(INTDIR)\MyTab.sbr"
	-@erase "$(INTDIR)\Panneau.obj"
	-@erase "$(INTDIR)\Panneau.sbr"
	-@erase "$(INTDIR)\PictureEx.obj"
	-@erase "$(INTDIR)\PictureEx.sbr"
	-@erase "$(INTDIR)\ProprietiesDlg.obj"
	-@erase "$(INTDIR)\ProprietiesDlg.sbr"
	-@erase "$(INTDIR)\RegistryEx.obj"
	-@erase "$(INTDIR)\RegistryEx.sbr"
	-@erase "$(INTDIR)\Scanner.obj"
	-@erase "$(INTDIR)\Scanner.sbr"
	-@erase "$(INTDIR)\ScanViewDlg.obj"
	-@erase "$(INTDIR)\ScanViewDlg.sbr"
	-@erase "$(INTDIR)\SendSMSDlg.obj"
	-@erase "$(INTDIR)\SendSMSDlg.sbr"
	-@erase "$(INTDIR)\Smtp.obj"
	-@erase "$(INTDIR)\Smtp.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TabAjout.obj"
	-@erase "$(INTDIR)\TabAjout.sbr"
	-@erase "$(INTDIR)\Update.obj"
	-@erase "$(INTDIR)\Update.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\KeepLink2.bsc"
	-@erase "$(OUTDIR)\KeepLink2.exe"
	-@erase "$(OUTDIR)\KeepLink2.ilk"
	-@erase "$(OUTDIR)\KeepLink2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\KeepLink2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\KeepLink2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KeepLink2.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AboutDlg.sbr" \
	"$(INTDIR)\Ajout.sbr" \
	"$(INTDIR)\AjoutMultiple.sbr" \
	"$(INTDIR)\AjoutRegle.sbr" \
	"$(INTDIR)\AjoutSimple.sbr" \
	"$(INTDIR)\AlerteMailDlg.sbr" \
	"$(INTDIR)\AlerteSMSDlg.sbr" \
	"$(INTDIR)\AlerteSonDlg.sbr" \
	"$(INTDIR)\AlerteSyslogDlg.sbr" \
	"$(INTDIR)\Arret.sbr" \
	"$(INTDIR)\Base64.sbr" \
	"$(INTDIR)\CCheckSK.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\CISBitmap.sbr" \
	"$(INTDIR)\ColorStaticST.sbr" \
	"$(INTDIR)\cSound.sbr" \
	"$(INTDIR)\FlatToolTipCtrl.sbr" \
	"$(INTDIR)\GeneralDlg.sbr" \
	"$(INTDIR)\HyperLink.sbr" \
	"$(INTDIR)\izssmsx.sbr" \
	"$(INTDIR)\JMatrixCtrl.sbr" \
	"$(INTDIR)\KeepLink2.sbr" \
	"$(INTDIR)\KeepLink2Doc.sbr" \
	"$(INTDIR)\KeepLink2View.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\ModemInfo.sbr" \
	"$(INTDIR)\MyTab.sbr" \
	"$(INTDIR)\Panneau.sbr" \
	"$(INTDIR)\PictureEx.sbr" \
	"$(INTDIR)\ProprietiesDlg.sbr" \
	"$(INTDIR)\RegistryEx.sbr" \
	"$(INTDIR)\Scanner.sbr" \
	"$(INTDIR)\ScanViewDlg.sbr" \
	"$(INTDIR)\SendSMSDlg.sbr" \
	"$(INTDIR)\Smtp.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TabAjout.sbr" \
	"$(INTDIR)\Update.sbr"

"$(OUTDIR)\KeepLink2.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\KeepLink2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\KeepLink2.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\Ajout.obj" \
	"$(INTDIR)\AjoutMultiple.obj" \
	"$(INTDIR)\AjoutRegle.obj" \
	"$(INTDIR)\AjoutSimple.obj" \
	"$(INTDIR)\AlerteMailDlg.obj" \
	"$(INTDIR)\AlerteSMSDlg.obj" \
	"$(INTDIR)\AlerteSonDlg.obj" \
	"$(INTDIR)\AlerteSyslogDlg.obj" \
	"$(INTDIR)\Arret.obj" \
	"$(INTDIR)\Base64.obj" \
	"$(INTDIR)\CCheckSK.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\CISBitmap.obj" \
	"$(INTDIR)\ColorStaticST.obj" \
	"$(INTDIR)\cSound.obj" \
	"$(INTDIR)\FlatToolTipCtrl.obj" \
	"$(INTDIR)\GeneralDlg.obj" \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\izssmsx.obj" \
	"$(INTDIR)\JMatrixCtrl.obj" \
	"$(INTDIR)\KeepLink2.obj" \
	"$(INTDIR)\KeepLink2Doc.obj" \
	"$(INTDIR)\KeepLink2View.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ModemInfo.obj" \
	"$(INTDIR)\MyTab.obj" \
	"$(INTDIR)\Panneau.obj" \
	"$(INTDIR)\PictureEx.obj" \
	"$(INTDIR)\ProprietiesDlg.obj" \
	"$(INTDIR)\RegistryEx.obj" \
	"$(INTDIR)\Scanner.obj" \
	"$(INTDIR)\ScanViewDlg.obj" \
	"$(INTDIR)\SendSMSDlg.obj" \
	"$(INTDIR)\Smtp.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TabAjout.obj" \
	"$(INTDIR)\Update.obj" \
	"$(INTDIR)\KeepLink2.res"

"$(OUTDIR)\KeepLink2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("KeepLink2.dep")
!INCLUDE "KeepLink2.dep"
!ELSE 
!MESSAGE Warning: cannot find "KeepLink2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "KeepLink2 - Win32 Release" || "$(CFG)" == "KeepLink2 - Win32 Debug"
SOURCE=.\AboutDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AboutDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AboutDlg.obj"	"$(INTDIR)\AboutDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Ajout.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Ajout.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Ajout.obj"	"$(INTDIR)\Ajout.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\AjoutMultiple.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AjoutMultiple.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AjoutMultiple.obj"	"$(INTDIR)\AjoutMultiple.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\AjoutRegle.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AjoutRegle.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AjoutRegle.obj"	"$(INTDIR)\AjoutRegle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\AjoutSimple.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AjoutSimple.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AjoutSimple.obj"	"$(INTDIR)\AjoutSimple.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\AlerteMailDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AlerteMailDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AlerteMailDlg.obj"	"$(INTDIR)\AlerteMailDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\AlerteSMSDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AlerteSMSDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AlerteSMSDlg.obj"	"$(INTDIR)\AlerteSMSDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\AlerteSonDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AlerteSonDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AlerteSonDlg.obj"	"$(INTDIR)\AlerteSonDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\AlerteSyslogDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\AlerteSyslogDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\AlerteSyslogDlg.obj"	"$(INTDIR)\AlerteSyslogDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Arret.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Arret.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Arret.obj"	"$(INTDIR)\Arret.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Base64.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Base64.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Base64.obj"	"$(INTDIR)\Base64.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\CCheckSK.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\CCheckSK.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\CCheckSK.obj"	"$(INTDIR)\CCheckSK.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\CISBitmap.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\CISBitmap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\CISBitmap.obj"	"$(INTDIR)\CISBitmap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\ColorStaticST.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\ColorStaticST.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\ColorStaticST.obj"	"$(INTDIR)\ColorStaticST.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\cSound.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\cSound.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\cSound.obj"	"$(INTDIR)\cSound.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\FlatToolTipCtrl.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\FlatToolTipCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\FlatToolTipCtrl.obj"	"$(INTDIR)\FlatToolTipCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\GeneralDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\GeneralDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\GeneralDlg.obj"	"$(INTDIR)\GeneralDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\HyperLink.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\HyperLink.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\HyperLink.obj"	"$(INTDIR)\HyperLink.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\izssmsx.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\izssmsx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\izssmsx.obj"	"$(INTDIR)\izssmsx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\JMatrixCtrl.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\JMatrixCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\JMatrixCtrl.obj"	"$(INTDIR)\JMatrixCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\KeepLink2.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\KeepLink2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\KeepLink2.obj"	"$(INTDIR)\KeepLink2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\KeepLink2Doc.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\KeepLink2Doc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\KeepLink2Doc.obj"	"$(INTDIR)\KeepLink2Doc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\KeepLink2View.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\KeepLink2View.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\KeepLink2View.obj"	"$(INTDIR)\KeepLink2View.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\ModemInfo.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\ModemInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\ModemInfo.obj"	"$(INTDIR)\ModemInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\MyTab.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\MyTab.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\MyTab.obj"	"$(INTDIR)\MyTab.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Panneau.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Panneau.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Panneau.obj"	"$(INTDIR)\Panneau.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\PictureEx.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\PictureEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\PictureEx.obj"	"$(INTDIR)\PictureEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\ProprietiesDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\ProprietiesDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\ProprietiesDlg.obj"	"$(INTDIR)\ProprietiesDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\RegistryEx.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\RegistryEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\RegistryEx.obj"	"$(INTDIR)\RegistryEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Scanner.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Scanner.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Scanner.obj"	"$(INTDIR)\Scanner.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\ScanViewDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\ScanViewDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\ScanViewDlg.obj"	"$(INTDIR)\ScanViewDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\SendSMSDlg.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\SendSMSDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\SendSMSDlg.obj"	"$(INTDIR)\SendSMSDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Smtp.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Smtp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Smtp.obj"	"$(INTDIR)\Smtp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Splash.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Splash.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\KeepLink2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KeepLink2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\KeepLink2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\KeepLink2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TabAjout.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\TabAjout.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\TabAjout.obj"	"$(INTDIR)\TabAjout.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\Update.cpp

!IF  "$(CFG)" == "KeepLink2 - Win32 Release"


"$(INTDIR)\Update.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ELSEIF  "$(CFG)" == "KeepLink2 - Win32 Debug"


"$(INTDIR)\Update.obj"	"$(INTDIR)\Update.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\KeepLink2.pch"


!ENDIF 

SOURCE=.\KeepLink2.rc

"$(INTDIR)\KeepLink2.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

