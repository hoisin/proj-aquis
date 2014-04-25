//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Main interfacing class for accessing/creating resources
//
//	Author: SeaFooD � 2014
//
//--------------------------------------------------------------------------

#ifndef __CRESOURCEMANAGER_H__
#define __CRESOURCEMANAGER_H__

#include <map>
#include <string>
#include <glm\glm.hpp>
#include "IResource.h"
#include "GfxDefs.h"

class CMeshDataGenerator;
class CTextureLoader;
class CVertexBuffer;
class CIndexBuffer;
class CShader;
class CTexture2D;

class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	bool Initialise();

	// Geometry generation methods
	MeshData* CreateTriangle(const std::string &geometryID, float size, EVertexType type,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));
	MeshData* CreateQuad(const std::string &geometryID, float size, EVertexType,
		const glm::vec4 &colour = glm::vec4(0, 0, 0, 0));

	// Buffer Stuff
	CVertexBuffer* CreateVertexBuffer(const std::string &vertexID, MeshData *pData);
	CIndexBuffer* CreateIndexBuffer(const std::string &indexID, MeshData *pData);

	// Shader stuff
	CTexture2D* CreateTexture2D(const std::string &textureID, const std::string &fileName);
	CShader* CreateShader(const std::string &shaderID, const std::string &vertexShaderFile,
		const std::string &fragShaderFile);

	IResource* GetResource(const std::string &esourceID);

	void ShutDown();

private:
	std::map<std::string, IResource *> m_resourceMap;

	CMeshDataGenerator *m_pMeshGenerator;
	CTextureLoader *m_pTextureLoader;
};

#endif