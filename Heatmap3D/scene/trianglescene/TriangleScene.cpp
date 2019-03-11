#include "TriangleScene.h"

Scene* TriangleScene::getInstance() {
	if (!instanceFlag) {
		scene = new TriangleScene();
		instanceFlag = true;
		return scene;
	}

	return scene;
};

void TriangleScene::start() {
	//Triangle A Rotates in the center
	triangleA = gameComponent(&vp);
	components.push_back(&triangleA);
	triangleAPostionVector = glm::vec3(-5.5f, 4.0f, -5.0f);
	triangleA.setPosition(&triangleAPostionVector);
	triangleARotationAngle = 0.0f;

	triangleARotationVector = glm::vec3(0.0f, 0.0f, 1.0f);
	triangleA.setOrientation(&glm::angleAxis(
		glm::radians(triangleARotationAngle),
		triangleARotationVector)
	);
	
	//Triangle B Rotates around Triangle A and faces it.
	triangleB = gameComponent(&vp);
	components.push_back(&triangleB);

	triangleBDirectionVector = glm::vec3(
		glm::cos(glm::radians(triangleARotationAngle + 90.0f)),
		glm::sin(glm::radians(triangleARotationAngle + 90.0f)),
		0.0f
	);

	triangleBDistance = 2.1f;
	triangleBPositionVector = triangleAPostionVector + (triangleBDirectionVector * triangleBDistance);
	triangleB.setPosition(&triangleBPositionVector);

	//Triangle C bounces off it's angles, happily dancing across the screen.
	triangleC = gameComponent(&vp);
	components.push_back(&triangleC);
	triangleCPositionVector = glm::vec3(0.0f, -2.0f, -5.0f);
	triangleC.setPosition(&triangleCPositionVector);

	triangleCDirectionVector = glm::vec3(-1.0f, 0.0f, 0.0f);
	triangleCSineVector = glm::vec3(0.0f, 0.03f, 0.0f);
	triangleCSpeed = 0.05f;
	Scene::start();
};

void TriangleScene::update() {
	if (triangleARotationAngle >= 360.0f) triangleARotationAngle = 0.0f;
	if (triangleC.getPostition().x <= -12.0f) triangleC.setPosition(&(triangleCPositionVector + glm::vec3(12.0f, 0.0f, 0.0f)));

	triangleARotationAngle++;
	triangleA.setOrientation(&glm::angleAxis(glm::radians(triangleARotationAngle), triangleARotationVector));

	triangleBDirectionVector = glm::vec3(
		glm::cos(glm::radians(triangleARotationAngle + 90.0f)),
		glm::sin(glm::radians(triangleARotationAngle + 90.0f)),
		0.0f);

	triangleBPositionVector = triangleAPostionVector + (triangleBDirectionVector * triangleBDistance);
	triangleB.setPosition(&triangleBPositionVector);
	triangleB.setOrientation(&glm::angleAxis(glm::radians(triangleARotationAngle - 180.0f), triangleARotationVector));

	triangleC.setOrientation(&glm::angleAxis(glm::radians(triangleARotationAngle), triangleARotationVector));
	triangleC.setPosition(&(
		triangleC.getPostition() + (triangleCDirectionVector * triangleCSpeed) +
		(triangleCSineVector * glm::sin(triangleC.getPostition().x))
	));
	Scene::update();
};

void TriangleScene::destroy() {
	Scene::destroy();
};