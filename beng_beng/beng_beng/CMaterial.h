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

protected:
	
	glm::float32 m_ambient;
	glm::float32 m_diffuse;
	glm::float32 m_specular;
	glm::float32 m_specExpo;

	glm::vec3 m_diffuseCol;			// Diffuse colour
	glm::vec3 m_specularCol;		// Specular colour
	std::string m_ambTexID;
	std::string m_specTextID;
	std::string m_diffuseTexID;		// May change texture manager to use numeric IDs
	std::string m_bumpTexID;		

	std::string m_shader;			// Which shader is used

};


#endif