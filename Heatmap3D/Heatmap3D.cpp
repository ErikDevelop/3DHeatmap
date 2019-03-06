#include <iostream>

#include "pch.h"
#include "dataController/datacontroller.h"
#include "openglwindowmanager.h"

int main()
{
	DataController::loadData("335514.json");

	//WindowManager* window = OpenGLWindowManager::getInstance();
	//window->Initialise(1024, 768, "3D Heatmap");
	//window->runScene();

	return 1;
}
