#include "gamecomponent.h"

gameComponent::gameComponent()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::quat(glm::vec3(0, 0, 0));
}

gameComponent::gameComponent(glm::mat4* parentProjection)
{
	projection = *parentProjection;
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::quat(glm::vec3(0, 0, 0));

	regenerateMvp();
}

void gameComponent::start()
{
	VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	shaderProgram = ShaderUtils::generateShaderProgram("res/shaders/TriangleVertexShader.glsl", "res/shaders/TriangleFragmentShader.glsl");

	matrix = glGetUniformLocation(shaderProgram, "u_MVP");
}

void gameComponent::update()
{
	glUseProgram(shaderProgram);

	glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}

void gameComponent::destroy()
{
	glDeleteProgram(shader);
}

glm::vec3 gameComponent::getPostition()
{
	return position;
}

void gameComponent::setPosition(glm::vec3 * newPosition)
{
	position = *newPosition;

	regenerateMvp();
}

glm::quat gameComponent::getOrientation()
{
	return orientation;
}

void gameComponent::setOrientation(glm::quat* newOrientation)
{
	orientation = *newOrientation;

	regenerateMvp();
}

void gameComponent::regenerateMvp()
{
	mvp = projection * (
		glm::translate(glm::mat4(1.0f), position) *
		glm::toMat4(orientation));
}