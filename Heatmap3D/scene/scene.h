#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
#include "gameComponent/gamecomponent.h"
#include "gameComponent/triangle/Triangle.h"

class Scene
{
protected:
	static bool instanceFlag;
	static Scene *scene;
	std::vector<gameComponent*> components;
	Scene() { /*private constructor*/ }
public:
	static Scene* getInstance();
	glm::mat4 vp;
	virtual void initialise();
	virtual void start();
	virtual void update();
	virtual void destroy();
	~Scene()
	{
		instanceFlag = false;
	}
};