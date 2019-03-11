#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "windowManager/windowmanager.h"

class OpenGLWindowManager : public WindowManager {
private:
	GLFWwindow* window;
	GLFWwindow* glfwShareWindow;
	GLFWmonitor* glfwMonitor;
	OpenGLWindowManager() { /*protected constructor*/ }
public:
	static WindowManager* getInstance();
	int Initialise(int w, int h, const char* title);
	int InitialiseOpenGL(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void runScene(Scene* scene);
};