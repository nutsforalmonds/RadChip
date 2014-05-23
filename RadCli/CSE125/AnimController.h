#pragma once
#include "Structures.h"

struct AnimSeg{
	AnimSeg(double s, double d){
		start = s;
		duration = d;
	}
	AnimSeg(const AnimSeg& other){
		start = other.start;
		duration = other.duration;
	}
	double start;
	double duration;
};

class AnimController{
public:
	AnimController(){}
	AnimController(const AnimController& other){
		segList = other.segList;
	}
	void add(double start, double duration){
		segList.push_back(AnimSeg(start, duration));
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
			if (time - startTimeOnce <= segList[currentOnce].duration){
				return time - startTimeOnce + segList[currentOnce].start;
			}
			AnimOnceOn = false;
		}

		return fmod(time - startTimeLoop, segList[currentLoop].duration) + segList[currentLoop].start;
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
