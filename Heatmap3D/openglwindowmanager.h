#pragma once

#include <GLFW/glfw3.h>
#include "windowmanager.h"

class OpenGLWindowManager : public WindowManager {
private:
	GLFWwindow* window;
	GLFWwindow* glfwShareWindow;
	GLFWmonitor* glfwMonitor;
	OpenGLWindowManager() { /*protected constructor*/ }
public:
	static WindowManager* getInstance();
	void Initialise(int w, int h, const char* title);
	void InitialiseOpenGL(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void runScene();
};