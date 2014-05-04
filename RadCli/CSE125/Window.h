#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "Object.h"

class Window	  // output window related routines
{
  public:
    static int width, height; 	            // window size

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void addDrawList(Object* obj);
	static void removeDrawList(const std::string& input);
};

#endif

