#include "CShader.h"

#include <fstream>
#include <vector>
#include <cmath>

CShader::CShader() 
{
}


CShader::~CShader()
{
	glDeleteProgram(m_programID);
}


GLuint CShader::LoadShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
	// Create shaders
	GLuint m_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint m_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read from file, vertex shader code
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
	
	if(vertexShaderStream.is_open()) {
		std::string line = "";
		while(std::getline(vertexShaderStream, line))
			vertexShaderCode += "\n" + line;

		vertexShaderStream.close();
	}

	// Read from file, fragment shader code
	std::string fragShaderCode;
	std::ifstream fragShaderStream(fragmentShaderPath,  std::ios::in);

	if(fragShaderStream.is_open()) {
		std::string line = "";
		while(std::getline(fragShaderStream, line))
			fragShaderCode += "\n" + line;

		fragShaderStream.close();
	}

	GLint result = FALSE;
	int infoLogLength;

	// NOTE: TAKE OUT THE CONSOLE PRINTS LATER!
	// Compile vertex shader
	printf("Compiling shader : %s\n", vertexShaderPath);
	char const *vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(m_vertShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(m_vertShaderID);

	// Check vertex shader
	glGetShaderiv(m_vertShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_vertShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> vertexShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(m_vertShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0]);

	// Compile fragment shader
	printf("Compiling shader: %s\n", fragmentShaderPath);
	char const *fragSourcePointer = fragShaderCode.c_str();
	glShaderSource(m_fragShaderID, 1, &fragSourcePointer, NULL);
	glCompileShader(m_fragShaderID);

	// Check fragment shader
	glGetShaderiv(m_fragShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_fragShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> fragShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(m_fragShaderID, infoLogLength, NULL, &fragShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &fragShaderErrorMessage);

	// Link program
	fprintf(stdout, "Linking program\n");
	m_programID = glCreateProgram();
	glAttachShader(m_programID, m_vertShaderID);
	glAttachShader(m_programID, m_fragShaderID);
	glLinkProgram(m_programID);

	// Check program
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> programErrorMessage( (std::max)(infoLogLength, int(1)) );
	glGetProgramInfoLog(m_programID, infoLogLength, NULL, &programErrorMessage[0]);
	fprintf(stdout, "%s\n", &programErrorMessage[0]);

	glDeleteShader(m_vertShaderID);
	glDeleteShader(m_fragShaderID);

	return m_programID;
}