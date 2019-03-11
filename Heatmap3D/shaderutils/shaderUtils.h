#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>

class ShaderUtils {
private:
	static int errorResult;
	static int errorInfoLength;
	static std::string errorMessage;

	static unsigned int validateShaderProgram(unsigned int* program);
	static unsigned int loadShader(const char* shaderFilePath, GLenum shaderType);
	static std::string readShaderStream(const char* shaderFilePath);
	static void compileShader(std::string* shader, int* shaderId);
	static unsigned int validateShader(int* shaderId);
public:
	static unsigned int generateShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);
};