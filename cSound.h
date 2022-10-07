// Ce fichier est une partie de KeepLink PRO
// Copyright (c)2005 Tech&Feel (aurelien.boudoux@techandfeel.net)
/****************************************************************************
                 cSound.h  by  Elmü (elmue.de.vu)
****************************************************************************/


#if !defined(cSound_H_ElmueSoft)
#define cSound_H_ElmueSoft

#if _MSC_VER > 1000
#pragma once
#endif


#include "Mmsystem.h"


#define  ERR_INVALID_FILETYPE 50123
#define  ERR_PLAY_WAV         50124


class cSound
{
public:
	cSound();
	virtual   ~cSound();

	DWORD      PlaySoundFile(char *p_s8File);
	void       StopSoundFile();
};

#endif // !defined(cSound_H_ElmueSoft)
