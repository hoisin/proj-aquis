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


//----------------------------------------------------------------------------------------------------
//
//	LoadShader(..)
//
//	Params:
//	vertexShaderPath		-	file directory to vertex shader
//	fragmentShaderPath		-	file directory to fragment shader
//	outID					-	return ID of compiled program
//
//	Description:
//	Loads and compiles shaders and links them to generate a program ID.
//
//----------------------------------------------------------------------------------------------------
bool CShader::LoadShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, GLuint &outID)
{
	// Create shaders
	GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read from file, vertex shader code
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
	
	if(vertexShaderStream.is_open()) {
		std::string line = "";
		while(std::getline(vertexShaderStream, line))
			vertexShaderCode += "\n" + line;

		vertexShaderStream.close();
	}
	else {
		return false;
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
	else {
		return false;
	}
	
	GLint result = FALSE;
	int infoLogLength;

	// NOTE: TAKE OUT THE CONSOLE PRINTS LATER!
	// Compile vertex shader
	printf("Compiling shader : %s\n", vertexShaderPath);
	char const *vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertShaderID);

	// Check vertex shader
	glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> vertexShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(vertShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0]);
	
	// Compile fragment shader
	printf("Compiling shader: %s\n", fragmentShaderPath);
	char const *fragSourcePointer = fragShaderCode.c_str();
	glShaderSource(fragShaderID, 1, &fragSourcePointer, NULL);
	glCompileShader(fragShaderID);
	
	// Check fragment shader
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> fragShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(fragShaderID, infoLogLength, NULL, &fragShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &fragShaderErrorMessage);
	
	// Link program
	fprintf(stdout, "Linking program\n");
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertShaderID);
	glAttachShader(m_programID, fragShaderID);
	glLinkProgram(m_programID);

	// Check program
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> programErrorMessage( (std::max)(infoLogLength, int(1)) );
	glGetProgramInfoLog(m_programID, infoLogLength, NULL, &programErrorMessage[0]);
	fprintf(stdout, "%s\n", &programErrorMessage[0]);

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	outID = m_programID;

	return true;
}