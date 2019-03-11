#include "shaderUtils.h"

int ShaderUtils::errorResult = GL_FALSE;
int ShaderUtils::errorInfoLength;
std::string ShaderUtils::errorMessage;

unsigned int ShaderUtils::generateShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) {
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = loadShader(vertexShaderFile, GL_VERTEX_SHADER);
	unsigned int fragmentShader = loadShader(fragmentShaderFile, GL_FRAGMENT_SHADER);

	if (!vertexShader || !fragmentShader) {
		return NULL;
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	validateShaderProgram(&program);

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

unsigned int ShaderUtils::validateShaderProgram(unsigned int* program)
{
	errorResult = GL_FALSE;

	glGetProgramiv(*program, GL_LINK_STATUS, &errorResult);
	glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &errorInfoLength);
	if (errorInfoLength > 0) {
		glGetProgramInfoLog(*program, errorInfoLength, NULL, &errorMessage[0]);

		std::cout << "ERROR: shader validation error: " << &errorMessage[0] << std::endl;
	}

	return 0;
}

unsigned int ShaderUtils::loadShader(const char* shaderFilePath, GLenum shaderType) {
	int shaderId = glCreateShader(shaderType);

	std::string shader = readShaderStream(shaderFilePath);
	compileShader(&shader, &shaderId);

	return shaderId;
}

std::string ShaderUtils::readShaderStream(const char* shaderFilePath)
{
	std::string shaderCode;
	std::stringstream sstr;
	std::ifstream shaderStream(shaderFilePath, std::ios::in);

	if (!shaderStream.is_open()) {
		std::cout << "ERROR: cannot open " << shaderFilePath << std::endl;
		return NULL;
	}

	sstr << shaderStream.rdbuf();
	shaderCode = sstr.str();
	shaderStream.close();

	return shaderCode;
}

void ShaderUtils::compileShader(std::string* shader, int* shaderId) {
	char const * sourcePointer = shader->c_str();

	glShaderSource(*shaderId, 1, &sourcePointer, NULL);
	glCompileShader(*shaderId);

	validateShader(shaderId);
}

unsigned int ShaderUtils::validateShader(int* shaderId)
{
	errorResult = GL_FALSE;

	glGetShaderiv(*shaderId, GL_COMPILE_STATUS, &errorResult);
	glGetShaderiv(*shaderId, GL_INFO_LOG_LENGTH, &errorInfoLength);
	if (errorInfoLength > 0) {
		glGetShaderInfoLog(*shaderId, errorInfoLength, NULL, &errorMessage[0]);

		std::cout << "ERROR: shader validation error: " << &errorMessage[0] << std::endl;
	}

	return 0;
}