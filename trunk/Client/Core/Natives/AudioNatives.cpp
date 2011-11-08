//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: AudioNatives.cpp
// Project: Client.Core
// Author(s): RootKiller
// License: See LICENSE in root directory
//
//==============================================================================
#include "../Natives.h"
#include "../CAudio.h"
#include <Scripting/CScriptingManager.h>
#include <Squirrel/sqstate.h>
#include <Squirrel/sqvm.h>
#include <Squirrel/sqstring.h>

_MEMBER_FUNCTION_IMPL(Audio, constructor)
{
	const char *szSoundName;
	sq_getstring ( pVM, 2, &szSoundName );

	CAudio * pAudio = new CAudio ( szSoundName );

	if(!pAudio || SQ_FAILED(sq_setinstance(pVM, pAudio)))
	{
		CLogFile::Printf("Can't create Audio element.");
		sq_pushbool(pVM, false);
		return 1;
	}

	sq_pushbool(pVM, true);
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, deleteSound)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);

	SAFE_DELETE(pAudio);
	sq_pushbool ( pVM, true );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, play)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	pAudio->Play ( );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, stop)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	pAudio->Stop ( );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, pause)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	pAudio->Pause ( );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, setRepeats)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	int iRepeats = 0;

	sq_getinteger ( pVM, 2, &iRepeats );

	if ( pAudio->SetRepeats ( iRepeats ) )
	{
		sq_pushbool ( pVM, true );
	} else {
		sq_pushbool ( pVM, false );
	}
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, getRepeats)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	sq_pushinteger ( pVM, pAudio->GetRepeats ( ) );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, isStarted)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	sq_pushbool ( pVM, pAudio->IsStarted ( ) );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, setVolume)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	float fVolume;
	sq_getfloat ( pVM, 2, &fVolume );
	
	pAudio->SetVolume(fVolume);

	sq_pushbool ( pVM, true );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, restoreVolume)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);

	pAudio->RestoreVolume ( );

	sq_pushbool ( pVM, true );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, getVolume)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);
	sq_pushfloat ( pVM, pAudio->GetVolume( ) );
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, setPosition)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);

	float fX, fY, fZ, fR;

	sq_getfloat ( pVM, 2, &fX );
	sq_getfloat ( pVM, 3, &fY );
	sq_getfloat ( pVM, 4, &fZ );
	sq_getfloat ( pVM, 5, &fR );

	pAudio->SetPosition (CVector3(fX, fY, fZ), fR );

	sq_pushbool(pVM, true);
	return 1;
}

_MEMBER_FUNCTION_IMPL(Audio, clearPosition)
{
	CAudio * pAudio = sq_getinstance<CAudio *>(pVM);

	pAudio->ClearPosition();

	sq_pushbool(pVM, true);
	return 1;
}
