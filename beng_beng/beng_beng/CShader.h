//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Class handling shader
//
//	For current development purposes, implement to get simple drawing going.
//	This class will probably evolve or get replaced.
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CSHADER_H__
#define __CSHADER_H__

#include <gl/glew.h>
#include <gl/wglew.h>
#include <string>
#include "GfxDefs.h"

class CShader
{
public:
	CShader();
	~CShader();

	bool LoadShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, GLuint &outID);
	
	void UserShader();

	void SetShaderParam1f(const std::string& paramID, glm::float32 data);
	void SetShaderParam1fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount);
	void SetShaderParam1i(const std::string& paramID, glm::int32 data);
	void SetShaderParam1iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount);

	void SetShaderParam2f(const std::string& paramID, glm::float32 data1, glm::float32 data2);
	void SetShaderParam2fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount);
	void SetShaderParam2i(const std::string& paramID, glm::int32 data1, glm::int32 data2);
	void SetShaderParam2iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount);

	void SetShaderParam3f(const std::string& paramID, glm::float32 data1, glm::float32 data2, glm::float32 data3);
	void SetShaderParam3fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount);
	void SetShaderParam3i(const std::string& paramID, glm::int32 data1, glm::int32 data2, glm::int32 data3);
	void SetShaderParam3iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount);

	void SetShaderParam4f(const std::string& paramID, glm::float32 data1, glm::float32 data2, glm::float32 data3, glm::float32 data4);
	void SetShaderParam4fv(const std::string& paramID, glm::float32* dataArray, glm::uint sizeCount);
	void SetShaderParam4i(const std::string& paramID, glm::int32 data1, glm::int32 data2, glm::int32 data3, glm::int32 data4);
	void SetShaderParam4iv(const std::string& paramID, glm::int32* dataArray, glm::uint sizeCount);

	void SetShaderParamMatrix4fv(const std::string& paramID, const glm::mat4& matrix, glm::uint count,
		bool bTranspose = FALSE);

	GLuint GetShaderID() { return m_programID; }

protected:
	GLuint m_programID;
};

#endif