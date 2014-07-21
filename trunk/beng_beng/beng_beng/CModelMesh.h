//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Model mesh class which holds required handles for defining a "model"
//	Independent model which holds handle to:
//	- MeshData
//	- VertexData
//	- Shader
//	- Texture (Possibly)
//
//	Author: SeaFooD © 2014
//
//	Note: this class to be modified to be CSubsetMesh.
//
//--------------------------------------------------------------------------

#ifndef __CMODELMESH_H__
#define __CMODELMESH_H__

#include <glm\glm.hpp>
#include <string>

class CModelMesh
{
public:
	CModelMesh(const std::string &meshID, const std::string &vertexID, const std::string &indexID, 
		const std::string &shaderID, const std::string &textureID);
	~CModelMesh();

public:
	std::string m_meshID;
	std::string m_vertexID;
	std::string m_indexID;
	std::string m_shaderID;
	std::string m_textureID;
	
	// Temporary only, for testing
	glm::vec3 pos;
};

#endif
