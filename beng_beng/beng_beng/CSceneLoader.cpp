#include "CSceneLoader.h"
#include "CMeshDataManager.h"
#include "GfxDefs.h"

CSceneLoader::CSceneLoader(void)
{
}


CSceneLoader::~CSceneLoader(void)
{
}


bool CSceneLoader::LoadScene(const std::string& fileName, CMeshDataManager* pMeshMgr)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices
		| aiProcess_SortByPType);

	if(!scene) 
		return false;

	std::string meshName = "mesh_";
	aiString texturePath;

	for(unsigned int mat = 0; mat < scene->mNumMaterials; mat++) {
			const struct aiMaterial* material = scene->mMaterials[mat];
			
			material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

			int test = 0;
			test = 2+2;
		}


	for(unsigned int meshNum = 0; meshNum < scene->mNumMeshes; meshNum++) {
		const struct aiMesh* mesh = scene->mMeshes[meshNum];

		unsigned int totalIndices = 0;
		for(int face = 0; face < mesh->mNumFaces; face++)
			totalIndices += mesh->mFaces[face].mNumIndices;

		MeshData* pNewMeshData = new MeshData(EVertexType::eVertexPNT, mesh->mNumVertices, totalIndices);

		for(unsigned int vert = 0; vert < pNewMeshData->vertexCount; vert++) {
			SVertexTypePNT* pVertex = (SVertexTypePNT*)pNewMeshData->pVertices;

			pVertex[vert].position = glm::vec3(mesh->mVertices[vert].x, mesh->mVertices[vert].y, mesh->mVertices[vert].z);
			pVertex[vert].normal = glm::vec3(mesh->mNormals[vert].x, mesh->mNormals[vert].y, mesh->mNormals[vert].z);
			pVertex[vert].textureCoord = glm::vec2(mesh->mTextureCoords[0][vert].x, mesh->mTextureCoords[0][vert].y);
		}

		unsigned int counter = 0;
		for(unsigned int face = 0; face < mesh->mNumFaces; face++) {
			for(unsigned int idx = 0; idx < mesh->mFaces[face].mNumIndices; idx++){
				pNewMeshData->pIndices[counter] = mesh->mFaces[face].mIndices[idx];
				counter++;
			}
		}

		if(mesh->mName.length == 0) {
			std::string meshStr = std::to_string((long double)meshNum);
			pMeshMgr->AddMeshData(pNewMeshData, meshName + meshStr );
		}
		else
			pMeshMgr->AddMeshData(pNewMeshData, mesh->mName.C_Str());
	}

	return true;
}