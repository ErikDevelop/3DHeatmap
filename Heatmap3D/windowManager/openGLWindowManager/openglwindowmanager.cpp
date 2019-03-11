#include "openglwindowmanager.h"
#include "windowManager/windowmanager.h"

int OpenGLWindowManager::Initialise(int w, int h, const char* title) {
	return InitialiseOpenGL(w, h, title, NULL, NULL);
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

int OpenGLWindowManager::InitialiseOpenGL(int w, int h, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	width = w;
	height = h;
	titleString = title;
	glfwMonitor = monitor;
	glfwShareWindow = share;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit()) {
		std::cout << "ERROR: Failed to initialise GLFW" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(width, height, titleString, glfwMonitor, glfwShareWindow);
	if (!window) {
		std::cout << "ERROR: Failed to create OpenGL Window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error! Cannot initialise GLEW" << std::endl;
		return -1;
	}

	std::cout << "Running OpenGL Ver.: " << glGetString(GL_VERSION) << std::endl;

	return 0;
}
void OpenGLWindowManager::runScene(Scene* scene)
{
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	scene->start();

	do {
		glClear(GL_COLOR_BUFFER_BIT);

		scene->update();

		glfwSwapBuffers(window);

		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);

	scene->destroy();

	glfwTerminate();
};