#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "shaderutils/shaderUtils.h"

class gameComponent
{
protected:
	glm::vec3 position;
	glm::quat orientation;
	glm::mat4 projection;
	glm::mat4 mvp;
	unsigned int vertexbuffer;
	unsigned int shaderProgram;
	unsigned int matrix;
	unsigned int shader;
	float points[9] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};
	unsigned int VertexArrayID;
	void regenerateMvp();
public:
	gameComponent();
	gameComponent(glm::mat4* parentProjection);
	virtual void start();
	virtual void update();
	virtual void destroy();
	glm::vec3 getPostition();
	void setPosition(glm::vec3* newPosition);
	glm::quat getOrientation();
	void setOrientation(glm::quat* newOrientation);
};