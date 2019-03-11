#include "scene.h"

bool Scene::instanceFlag = false;
Scene* Scene::scene = NULL;

Scene* Scene::getInstance()
{
	if (!instanceFlag) {
		scene = new Scene();
		instanceFlag = true;
		return scene;
	}

	return scene;
}
void Scene::initialise() {
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(0, 0, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	vp = projection * view;
};

void Scene::start() {
	for (int index = 0; index < components.size(); index++) {
		components[index]->start();
	}
};

void Scene::update() {
	for (int index = 0; index < components.size(); index++) {
		components[index]->update();
	}
};

void Scene::destroy() {
	for (int index = 0; index < components.size(); index++) {
		components[index]->destroy();
	}
};
