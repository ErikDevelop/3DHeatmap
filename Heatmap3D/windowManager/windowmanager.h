#pragma once

#include <iostream>
#include <string>

#include "scene/scene.h"

class WindowManager
{
protected:
	int width;
	int height;
	const char* titleString;
	static bool instanceFlag;
	static WindowManager *windowManager;
	WindowManager(){ /*private constructor*/ }
public:
	static WindowManager* getInstance();
	virtual int Initialise(int w, int h, const char* title) = 0;
	virtual void runScene(Scene* scene) = 0;
	~WindowManager()
	{
		instanceFlag = false;
	}
};
