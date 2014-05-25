#ifndef SOUND_H
#define	SOUND_H

#include <string>
#include <conio.h>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

class SoundSystem
{
public:
	SoundSystem(){
		// Create FMOD interface object
		result = FMOD::System_Create(&system);
		FMODErrorCheck(result);

		// Check version
		result = system->getVersion(&version);
		FMODErrorCheck(result);

		if (version < FMOD_VERSION)
		{
			std::cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;
			//return 0;
		}

		// Get number of sound cards
		result = system->getNumDrivers(&numDrivers);
		FMODErrorCheck(result);

		// No sound cards (disable sound)
		if (numDrivers == 0)
		{
			result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
			FMODErrorCheck(result);
		}

		// At least one sound card
		else
		{
			// Get the capabilities of the default (0) sound card
			result = system->getDriverCaps(0, &caps, 0, &speakerMode);
			FMODErrorCheck(result);

			// Set the speaker mode to match that in Control Panel
			result = system->setSpeakerMode(speakerMode);
			FMODErrorCheck(result);

			// Increase buffer size if user has Acceleration slider set to off
			if (caps & FMOD_CAPS_HARDWARE_EMULATED)
			{
				result = system->setDSPBufferSize(1024, 10);
				FMODErrorCheck(result);
			}

			// Get name of driver
			result = system->getDriverInfo(0, name, 256, 0);
			FMODErrorCheck(result);

			// SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
			// PCM floating point output seems to solve it.
			if (strstr(name, "SigmaTel"))
			{
				result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
				FMODErrorCheck(result);
			}
		}

		// Initialise FMOD
		result = system->init(100, FMOD_INIT_NORMAL, 0);

		// If the selected speaker mode isn't supported by this sound card, switch it back to stereo
		if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
		{
			result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
			FMODErrorCheck(result);

			result = system->init(100, FMOD_INIT_NORMAL, 0);
		}
		FMODErrorCheck(result);
	}

	~SoundSystem(){
		FMODErrorCheck(system->release());
	}


	FMOD::Sound createSound(){
		FMOD::Sound *sound;

		// Load sound effects into memory (not streaming)
		result = system->createSound("Effect.mp3", FMOD_DEFAULT, 0, &sound);
		FMODErrorCheck(result);

		system->playSound(FMOD_CHANNEL_FREE, sound, false, 0);
	}

	FMOD::Sound createMusic(){
		FMOD::Sound *song;
		
		// Open music as a stream
		result = system->createStream("Music/backgroundMenu.wav", FMOD_DEFAULT, 0, &song);
		FMODErrorCheck(result);

		// Assign each song to a channel and start them paused
		result = system->playSound(FMOD_CHANNEL_FREE, song, true, &channel1);
		FMODErrorCheck(result);

		// Songs should repeat forever
		channel1->setLoopCount(-1);

		channel1->setVolume(0.05);

		channel1->setPaused(false);
		return *song;
	}

	void playMusic(){

	}

private:
	
	void FMODErrorCheck(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
			exit(-1);
		}
	}
	
	char name[256];
	FMOD::System *system;
	FMOD_RESULT result;
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;

	FMOD::Channel *channel1, *channel2;

};

/*
class Sound
{
public:
	Sound(FMOD_SYSTEM *mySystemSet, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound){		
		mySystem = mySystemSet;
		mySound = *sound;
		volume = 0.5;
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
/*
void Mode(FMOD_MODE mode){
		result = FMOD_Sound_SetMode(mySound, mode);
		ERRCHECK(result);
	}

	void setVolume(float v){
		volume = v;
		if (volume > 255){ volume = 255; }
		if (volume < 0){ volume = 0; }
	}

private:
	//used for err checking
	FMOD_RESULT       result;
	FMOD_SYSTEM      *mySystem;
	FMOD_SOUND       *mySound;	
	float volume;
};

*/

#endif	/* SOUND_H */