#ifndef SOUND_H
#define	SOUND_H

#include <string>
#include <conio.h>
#include <FMOD/fmod.h>
#include <FMOD/fmod_errors.h>

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

class Sound
{
public:
	Sound(FMOD_SYSTEM *mySystemSet, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound){		
		mySystem = mySystemSet;
		mySound = *sound;
		FMOD_System_CreateSound(mySystem, name_or_data, mode, exinfo, &mySound);
		ERRCHECK(result);
	}
	~Sound(void){
		result = FMOD_Sound_Release(mySound);
		ERRCHECK(result);
	}

	void Play(FMOD_CHANNELINDEX channelid, FMOD_BOOL paused, FMOD_CHANNEL **channel){
		FMOD_System_PlaySound(mySystem, channelid, mySound, paused, channel);
		ERRCHECK(result);
	}

	/* If the file has embedded loop points which automatically makes looping turn happen, turn off like this. */
	void Mode(FMOD_MODE mode){
		result = FMOD_Sound_SetMode(mySound, mode);
		ERRCHECK(result);
	}

private:
	//used for err checking
	FMOD_RESULT       result;
	FMOD_SYSTEM      *mySystem;
	FMOD_SOUND       *mySound;	
};

#endif	/* SOUND_H */