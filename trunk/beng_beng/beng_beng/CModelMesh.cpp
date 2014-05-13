#include "CModelMesh.h"


CModelMesh::CModelMesh(const std::string &meshID, const std::string &vertexID, const std::string &indexID, 
		const std::string &shaderID, const std::string &textureID) :
		m_meshID(meshID), m_vertexID(vertexID), m_indexID(indexID), m_shaderID(shaderID),
			m_textureID(textureID)
{
}


CModelMesh::~CModelMesh()
{
}