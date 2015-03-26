#include "CShader.h"

#include <fstream>
#include <vector>
#include <algorithm>

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
	::OutputDebugStringA(&vertexShaderErrorMessage[0]);
	
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
	::OutputDebugStringA(&fragShaderErrorMessage[0]);
	
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
	::OutputDebugStringA(&programErrorMessage[0]);

	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	outID = m_programID;

	return true;
}

//----------------------------------------------------------------------------------------------------
//
//	UserShader(..)
//
//	Description:
//	Sets this shader as the active shader
//
//----------------------------------------------------------------------------------------------------
void CShader::UserShader()
{
	// Free last used shader
	glUseProgram(0);

	glUseProgram(m_programID);
}


//----------------------------------------------------------------------------------------------------
//
//	SetShaderParam###(..)
//
//	Description:
//	Following functions perform setting the parameter/s of current active shader
//
//----------------------------------------------------------------------------------------------------

void CShader::SetShaderParam1f(const std::string& paramID, glm::float32 data)
{
	glUniform1f(glGetUniformLocation(m_programID, paramID.c_str()), data);
}


void CShader::SetShaderParam1fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount)
{
	glUniform1fv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParam1i(const std::string& paramID, glm::int32 data)
{
	glUniform1i(glGetUniformLocation(m_programID, paramID.c_str()), data);
}


void CShader::SetShaderParam1iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount)
{
	glUniform1iv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParam2f(const std::string& paramID, glm::float32 data1, glm::float32 data2)
{
	glUniform2f(glGetUniformLocation(m_programID, paramID.c_str()), data1, data2);
}


void CShader::SetShaderParam2fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount)
{
	glUniform2fv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParam2i(const std::string& paramID, glm::int32 data1, glm::int32 data2)
{
	glUniform2i(glGetUniformLocation(m_programID, paramID.c_str()), data1, data2);
}


void CShader::SetShaderParam2iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount)
{
	glUniform2iv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParam3f(const std::string& paramID, glm::float32 data1, glm::float32 data2, glm::float32 data3)
{
	glUniform3f(glGetUniformLocation(m_programID, paramID.c_str()), data1, data2, data3);
}


void CShader::SetShaderParam3fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount)
{
	glUniform3fv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParam3i(const std::string& paramID, glm::int32 data1, glm::int32 data2, glm::int32 data3)
{
	glUniform3i(glGetUniformLocation(m_programID, paramID.c_str()), data1, data2, data3);
}


void CShader::SetShaderParam3iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount)
{
	glUniform3iv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParam4f(const std::string& paramID, glm::float32 data1, glm::float32 data2, glm::float32 data3, glm::float32 data4)
{
	glUniform4f(glGetUniformLocation(m_programID, paramID.c_str()), data1, data2, data3, data4);
}


void CShader::SetShaderParam4fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount)
{
	glUniform4fv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParam4i(const std::string& paramID, glm::int32 data1, glm::int32 data2, glm::int32 data3, glm::int32 data4)
{
	glUniform4i(glGetUniformLocation(m_programID, paramID.c_str()), data1, data2, data3, data4);
}


void CShader::SetShaderParam4iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount)
{
	glUniform4iv(glGetUniformLocation(m_programID, paramID.c_str()), sizeCount, dataArray);
}


void CShader::SetShaderParamMatrix4fv(const std::string& paramID, const glm::mat4& matrix, glm::uint count, bool bTranspose)
{
	GLboolean transpose = GL_FALSE;

	if(bTranspose)
		transpose = GL_TRUE;

	glUniformMatrix4fv(glGetUniformLocation(m_programID, paramID.c_str()), count, transpose,
		&matrix[0][0]);
}