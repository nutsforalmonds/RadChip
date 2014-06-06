#pragma once
#include "Structures.h"

struct AnimSeg{
	AnimSeg(double s, double d, float speedUp=1){
		start = s;
		duration = d;
		this->speedUp = speedUp;
	}
	AnimSeg(const AnimSeg& other){
		start = other.start;
		duration = other.duration;
		speedUp = other.speedUp;
	}
	double start;
	double duration;
	float speedUp;
};

class AnimController{
public:
	AnimController(){}
	AnimController(const AnimController& other){
		segList = other.segList;
		default_animation = other.default_animation;
		currentLoop = other.currentLoop;
		startTimeLoop = other.startTimeLoop;
		loopCounter = other.loopCounter;
		currentOnce = other.currentOnce;
		startTimeOnce = other.startTimeOnce;
		AnimOnceOn = other.AnimOnceOn;
	}
	AnimController& operator = (const AnimController& other){
		segList = other.segList;
		default_animation = other.default_animation;
		currentLoop = other.currentLoop;
		startTimeLoop = other.startTimeLoop;
		loopCounter = other.loopCounter;
		currentOnce = other.currentOnce;
		startTimeOnce = other.startTimeOnce;
		AnimOnceOn = other.AnimOnceOn;
		return *this;
	}
	void add(double start, double duration, float speedUp = 1){
		segList.push_back(AnimSeg(start, duration, speedUp));
	}
	AnimSeg& operator [] (int index){
		return segList[index];
	}
	void setDefault(int index){
		default_animation = index;
		currentLoop = default_animation;
	}
	void setAnimLoop(int index, double start_time){
		if (currentLoop == index){
			loopCounter++;
		}
		else{
			currentLoop = index;
			loopCounter = 1;
			startTimeLoop = start_time;
		}
	}
	void unsetAnimLoop(int index, double end_time = 0.0){
		if (currentLoop == index){
			loopCounter--;
			if (loopCounter < 0)
				loopCounter = 0;
			if (loopCounter == 0){
				currentLoop = default_animation;
				startTimeLoop = end_time;
			}
		}
	}
	void setAnimOnce(int index, double start_time){
		currentOnce = index;
		startTimeOnce = start_time;
		AnimOnceOn = true;
	}
	double getAnimation(double time){
		if (AnimOnceOn){
			if ((time - startTimeOnce)*segList[currentOnce].speedUp <= segList[currentOnce].duration){
				return (time - startTimeOnce)*segList[currentOnce].speedUp + segList[currentOnce].start;
			}
			AnimOnceOn = false;
		}

		return fmod(time*segList[currentLoop].speedUp - startTimeLoop, segList[currentLoop].duration) + segList[currentLoop].start;
	}

private:
	vector<AnimSeg> segList;
	int default_animation;

	int currentLoop;
	double startTimeLoop;
	int loopCounter = 0;

	int currentOnce;
	double startTimeOnce;
	bool AnimOnceOn = false;
};
