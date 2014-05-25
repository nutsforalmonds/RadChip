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


	FMOD::Sound* createSound(string path){
		FMOD::Sound *sound;

		// Load sound effects into memory (not streaming)
		result = system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);
		FMODErrorCheck(result);

		return sound;
	}

	void playSound(FMOD::Sound *s, double v){
		FMOD::Channel *temp;
		system->playSound(FMOD_CHANNEL_FREE, s, false, &temp);
		temp->setVolume(v);
	}

	FMOD::Sound* createMusic(string path){
		FMOD::Sound *song;
		
		// Open music as a stream
		result = system->createStream(path.c_str(), FMOD_DEFAULT, 0, &song);
		FMODErrorCheck(result);

		// Assign each song to a channel and start them paused
		result = system->playSound(FMOD_CHANNEL_FREE, song, true, &music);
		FMODErrorCheck(result);
		
		return song;
	}

	FMOD::Channel* getLastMusicChan(){ return music; }

	void playMusic(FMOD::Channel *chan){
		chan->setPaused(false);
	}

	void stopMusic(FMOD::Channel *chan){
		chan->setPaused(true);
	}

	void setLoopCount(FMOD::Channel *chan, int loop){
		chan->setLoopCount(loop);
	}

	void setVolume(FMOD::Channel *chan, double v){
		chan->setVolume(v);
	}

	void update(){
		FMODErrorCheck(system->update());
	}

	void free(FMOD::Sound *t){
		FMODErrorCheck(t->release());
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
	
	//System Stuff
	char name[256];
	FMOD::System *system;
	FMOD_RESULT result;
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;

	//Testing code
	FMOD::Channel *music; 
	FMOD::Channel *sound;

};

class Music
{
public:
	Music(SoundSystem *s, string path){
		system = s;
		me = system->createMusic(path);
		myChan = s->getLastMusicChan();
		fadeDone = true;
	}
	~Music(){
		system->free(me);
	}

	void Play(){
		system->playMusic(myChan);
	}

	void Stop(){
		system->stopMusic(myChan);
	}

	void setLoopCount(int loop){
		loopCount = loop;
		system->setLoopCount(myChan, loopCount);
	}

	void setVolume(double v){
		volume = v;
		if (volume > 1.0){
			volume = 1.0;
		}
		else if (volume < 0.0){
			volume = 0.0;
		}
		system->setVolume(myChan, volume);
	}

	void setFade(double v, double s){
		fade = v;
		fadeStep = s;
		fadeDone = false;
		setVolume(0);
	}

	void fadeUpdate(){
		if ((!fadeDone) || volume < fade){
			double temp = volume + fadeStep;
			if (volume > fade){
				temp = fade;
			}
			setVolume(temp);
		}
		else{
			fadeDone = true;
		}
	}

	bool getFadeDone(){ return fadeDone; }

private:
	FMOD::Sound *me;
	FMOD::Channel *myChan;
	SoundSystem *system;
	double volume;
	int loopCount;
	double fade, fadeStep;
	bool fadeDone;
};

class Sound
{
public:
	Sound(SoundSystem *s, string path){
		system = s;
		me = system->createSound(path);
	}
	~Sound(){
		system->free(me);
	}

	void Play(){
		system->playSound(me, volume);
	}

	
	void setVolume(double v){
		volume = v;
		if (volume > 1.0){
			volume = 1.0;
		}
		else if (volume < 0.0){
			volume = 0.0;
		}
	}

	float getVolume(){ return volume; }

private:
	FMOD::Sound *me;
	FMOD::Channel *myChan;
	SoundSystem *system;
	double volume;
	int loopCount;
};

#endif	/* SOUND_H */