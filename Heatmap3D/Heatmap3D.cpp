#include <iostream>

#include "pch.h"
#include "dataController/datacontroller.h"
#include "windowManager/openGLWindowManager/openglwindowmanager.h"
#include "scene/trianglescene/TriangleScene.h"

int main()
{
	DataController::loadData("/res/data/335514.json");

	WindowManager* window = OpenGLWindowManager::getInstance();
	Scene* scene = TriangleScene::getInstance();
	window->Initialise(1024, 768, "3D Heatmap");
	scene->initialise();
	window->runScene(scene);

	return 1;
}
