#pragma once

#include <iostream>
#include <string>

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
	virtual void Initialise(int w, int h, const char* title) = 0;
	virtual void createWindow() = 0;
	virtual void loadScene() = 0;
	~WindowManager()
	{
		instanceFlag = false;
	}
};
