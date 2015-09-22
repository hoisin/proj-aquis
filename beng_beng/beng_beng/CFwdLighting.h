///--------------------------------------------------------------------------
//
//	26/08/2015
//
//	Techinque handing forward lighting implementation
//
//	Current handling:
//	Texture only.
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CFWDLIGHTING_H__
#define __CFWDLIGHTING_H__

#include <string>
#include "glm\glm.hpp"
#include "CTechnique.h"

class CFwdLighting : public CTechnique
{
public:
	CFwdLighting(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~CFwdLighting();

	bool VInit() override;

	void SetProjViewMatrix(const glm::mat4& projViewMat);
	void SetWorldMatrix(const glm::mat4& worldMat);
	void SetInvWorldMatrx(const glm::mat4& invWorldMat);

	void SetDiffuseTexture(GLuint textureID);

private:
	GLuint m_projViewMatLoc;
	GLuint m_worldMatLoc;
	GLuint m_invWorldMatLoc;
	GLuint m_diffuseTexSamplerLoc;

	std::string m_vertexShaderPath;
	std::string m_fragementShaderPath;
};


#endif