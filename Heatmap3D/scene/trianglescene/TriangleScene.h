#pragma once
#include "scene/scene.h"
#include "gameComponent/gamecomponent.h"

class TriangleScene : public Scene
{
private:
	TriangleScene() { /*protected constructor*/ };

	//Scene specific variables
	gameComponent triangleA;
	float triangleARotationAngle;
	glm::vec3 triangleAPostionVector;
	glm::vec3 triangleARotationVector;

	gameComponent triangleB;
	float triangleBRotationAngle;
	glm::vec3 triangleBDirectionVector;
	glm::vec3 triangleBPositionVector;
	float triangleBDistance;

	gameComponent triangleC;
	glm::vec3 triangleCPositionVector;
	glm::vec3 triangleCDirectionVector;
	glm::vec3 triangleCSineVector;
	float triangleCSpeed;
public:
	static Scene* getInstance();
	void start() override;
	void update() override;
	void destroy() override;
};