#include "pch.h"
#include "openglwindowmanager.h"
#include "windowmanager.h"

void OpenGLWindowManager::Initialise(int w, int h, const char* title) {
	InitialiseOpenGL(w, h, title, NULL, NULL);
};

WindowManager* OpenGLWindowManager::getInstance()
{
	if (!instanceFlag) {
		windowManager = new OpenGLWindowManager();
		instanceFlag = true;
		return windowManager;
	}

	return windowManager;
}

void OpenGLWindowManager::InitialiseOpenGL(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	width = w;
	height = h;
	titleString = title;
	glfwMonitor = monitor;
	glfwShareWindow = share;

	if (!glfwInit()) {
		std::cout << "ERROR: Failed to initialise GLFW" << std::endl;
		return;
	}

	window = glfwCreateWindow(width, height, titleString, glfwMonitor, glfwShareWindow);

	if (!window) {
		std::cout << "ERROR: Failed to create OpenGL Window!" << std::endl;
		glfwTerminate();
		return;
	}
}
void OpenGLWindowManager::runScene()
{
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
};