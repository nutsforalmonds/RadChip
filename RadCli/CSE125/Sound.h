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

	void set3DAttributes(FMOD_VECTOR pt, FMOD_VECTOR vt){
		cout << "New Listener Pos: <" << pt.x << "," << pt.y << "," << pt.z << ">" << endl;
		cout << "New Listener Pos: <" << vt.x << "," << vt.y << "," << vt.z << ">" << endl;
		system->set3DListenerAttributes(0, &pt, &vt, 0, 0);
	}

	void set3DSettings(float dopplerscale, float distancefactor, float rolloffscale){
		system->set3DSettings(dopplerscale, distancefactor, rolloffscale);
	}

	void view3DSettings(){
		float dopplerscale, distancefactor, rolloffscale;
		system->get3DSettings(&dopplerscale, &distancefactor, &rolloffscale);
		cout << "Dop: " << dopplerscale << " Dis: " << distancefactor << " Rol: " << rolloffscale << endl;
	}


	FMOD::Sound* createSound(string path){
		FMOD::Sound *sound;

		// Load sound effects into memory (not streaming)
		result = system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);
		FMODErrorCheck(result);

		return sound;
	}

	FMOD::Sound* create3DSound(string path){
		FMOD::Sound *sound;

		// Load sound effects into memory (not streaming)
		result = system->createSound(path.c_str(), FMOD_3D, 0, &sound);
		FMODErrorCheck(result);

		return sound;
	}

	void playSound(FMOD::Sound *s, double v){
		FMOD::Channel *temp;
		system->playSound(FMOD_CHANNEL_FREE, s, true, &temp);
		temp->setVolume(v);
		temp->setPaused(false);
	}

	void play3DSound(FMOD::Sound *s, double v, FMOD_VECTOR pos, FMOD_VECTOR vel, float minD, float maxD){
		FMOD::Channel *temp;
		system->playSound(FMOD_CHANNEL_FREE, s, true, &temp);
		temp->set3DAttributes(&pos, &vel);
		temp->set3DMinMaxDistance(minD, maxD);
		temp->setVolume(v);
		temp->setPaused(false);
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

	FMOD::Sound* create3DMusic(string path){
		FMOD::Sound *song;

		// Open music as a stream
		result = system->createStream(path.c_str(), FMOD_3D, 0, &song);
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

	bool isMusicPlaying(FMOD::Channel *chan){
		bool temp;
		chan->isPlaying(&temp);
		return temp;
	}

	void play3DMusic(FMOD::Channel *chan, FMOD_VECTOR pos, FMOD_VECTOR vel, float minD, float maxD){
		chan->get3DAttributes(&pos, &vel);
		chan->set3DMinMaxDistance(minD, maxD);
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

	//position of listener needed for spatial & reverb effects
	void setListenerPos(FMOD_VECTOR p){
		listenerPos = p;
	}

	//velocity of listener needed for dopper effects
	void setListenerVel(FMOD_VECTOR v){
		listenerVel = v;
	}

	void setListenerPosVel(FMOD_VECTOR p, FMOD_VECTOR v){
		setListenerPos(p);
		setListenerVel(v);
	}

	void updateListener(){
	//	cout << "UpdateListener - Listener Pos: <" << listenerPos.x << "," << listenerPos.y << "," << listenerPos.z << ">" << endl;
	//	cout << "UpdateListener - Listener Pos: <" << listenerVel.x << "," << listenerVel.y << "," << listenerVel.z << ">" << endl;
		system->set3DListenerAttributes(0, &listenerPos, &listenerVel, 0, 0);
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

	FMOD_VECTOR listenerPos;
	FMOD_VECTOR listenerVel;

};

class Music
{
public:
	Music(SoundSystem *s, string path, bool set3D){
		system = s;
		amI3D = set3D;
		if (set3D){
			me = system->create3DMusic(path);
		}
		else{
			me = system->createMusic(path);
		}
		
		myChan = s->getLastMusicChan();
		fadeDone = true;
	}
	~Music(){
		system->free(me);
	}

	void Play(){
		system->playMusic(myChan);
	}

	bool isPlaying(){
		return (system->isMusicPlaying(myChan));
	}

	void setPosition(FMOD_VECTOR pos){
		position = pos;
	}

	void setVelocity(FMOD_VECTOR vel){
		velocity = vel;
	}

	void setPosVel(FMOD_VECTOR pos, FMOD_VECTOR vel){
		setPosition(pos);
		setVelocity(vel);
	}

	void setMinDistance(float min){
		minDistance = min;
	}

	float getMinDistance(){ return minDistance; }

	void setMaxDistance(float max){
		maxDistance = max;
	}

	float getMaxDistance(){ return maxDistance; }

	void Play3D(){
		system->play3DMusic(myChan, position, velocity, minDistance, maxDistance);
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

	bool get3D(){ return amI3D; }

private:
	FMOD::Sound *me;
	FMOD::Channel *myChan;
	SoundSystem *system;
	double volume;
	int loopCount;
	double fade, fadeStep;
	bool fadeDone;

	FMOD_VECTOR position;
	FMOD_VECTOR velocity;

	float minDistance;
	float maxDistance;

	float amI3D;
};

class Sound
{
public:
	Sound(SoundSystem *s, string path, bool set3D){
		system = s;
		amI3D = set3D;
		if (set3D){
			me = system->create3DSound(path);
		}
		else{
			me = system->createSound(path);
		}
	}
	~Sound(){
		system->free(me);
	}

	void Play(){
		system->playSound(me, volume);
	}

	void setPosition(FMOD_VECTOR pos){
		position = pos;
	}

	void setVelocity(FMOD_VECTOR vel){
		velocity = vel;
	}

	void setMinDistance(float min){
		minDistance = min;
	}

	float getMinDistance(){ return minDistance; }

	void setMaxDistance(float max){
		maxDistance = max;
	}

	float getMaxDistance(){ return maxDistance; }

	void setPosVel(FMOD_VECTOR pos, FMOD_VECTOR vel){
		setPosition(pos);
		setVelocity(vel);
	}

	void Play3D(mat4 v){
		glm::vec4 temp(position.x, position.y, position.z, 1.0);
		temp = v*temp;
		FMOD_VECTOR np = { temp.x, temp.y, temp.z };
		system->play3DSound(me, volume, np, velocity, minDistance, maxDistance);
		//cout << "Me: "<< me << "Vol: " << volume << "Min: " << minDistance << "Max: " << maxDistance << endl;
		//cout << position.x << position.y << position.z << endl;
		//cout << velocity.x << velocity.y << velocity.z << endl;
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

	bool get3D(){ return amI3D; }

private:
	FMOD::Sound *me;
	FMOD::Channel *myChan;
	SoundSystem *system;
	double volume;
	int loopCount;

	FMOD_VECTOR position;
	FMOD_VECTOR velocity;

	float minDistance;
	float maxDistance;

	float amI3D;
};

#endif	/* SOUND_H */