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
//	Author: Matt © 2014
//
//	Note: this class to be modified to be CSubsetMesh.
//
//--------------------------------------------------------------------------

#ifndef __CSUBMESH_H__
#define __CSUBMESH_H__

#include <glm\glm.hpp>
#include <string>

class CSubMesh
{
public:
	CSubMesh(const std::string &meshID, const std::string &vertexID, const std::string &indexID, 
		const std::string &shaderID, const std::string &textureID);
	~CSubMesh();

public:
	std::string m_meshID;		// Mesh geometry data (MeshData)
	std::string m_vertexID;		// Loaded vertex data
	std::string m_indexID;		// Loaded index data
	std::string m_shaderID;		// Shader ID (may be included in material)
	std::string m_textureID;	// Texture to use (swap to material ID)
};

#endif
