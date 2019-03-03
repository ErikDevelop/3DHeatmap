#include "pch.h"
#include "windowmanager.h"

bool WindowManager::instanceFlag = false;
WindowManager* WindowManager::windowManager = NULL;
WindowManager* WindowManager::getInstance()
{
	std::cout << "ERROR: WindowManager is an Abstract Class, and is not to be used for instantiation." << std::endl;
	return NULL;
}