//--------------------------------------------------------------------------
//
//	10/04/2015
//
//	Class which holds all information on a material
//
//	Author: SeaFooD © 2015
//
//--------------------------------------------------------------------------

#ifndef __CMATERIAL_H__
#define __CMATERIAL_H__

#include "GfxDefs.h"

class CMaterial
{
public:
	CMaterial(void);
	~CMaterial(void);

//protected:
public:
	glm::float32 m_ambient;
	glm::float32 m_diffuse;
	glm::float32 m_specular;
	glm::float32 m_specExpo;

	glm::vec3 m_ambientCol;			// Ambient reflective colour
	glm::vec3 m_diffuseCol;			// Diffuse reflective colour
	glm::vec3 m_specularCol;		// Specular reflective colour
	std::string m_ambTexID;
	std::string m_diffuseTexID;		// May change texture manager to use numeric IDs
	std::string m_specTexID;
	std::string m_bumpTexID;		

	// Values used to indicate certain values are used or not (textures) for shader
	bool m_bAmbTexture;
	bool m_bDiffuseTexture;
	bool m_bSpecTexture;
	bool m_bBumpTexture;

	std::string m_shader;			// Which shader is used
};


#endif