#include "CSceneLoader.h"
#include "CMeshDataManager.h"
#include "CTextureManager.h"
#include "CMaterialManager.h"
#include "CMaterial.h"
#include "GfxDefs.h"

CSceneLoader::CSceneLoader(void)
{
}


CSceneLoader::~CSceneLoader(void)
{
}


bool CSceneLoader::LoadScene(const std::string& fileName, CMeshDataManager* pMeshMgr,
	CTextureManager* pTextureMgr, CMaterialManager* pMaterialMgr)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName, /*aiProcess_FlipUVs |*/ aiProcess_CalcTangentSpace | aiProcess_Triangulate /*| aiProcess_JoinIdenticalVertices*/
		| aiProcess_SortByPType | aiProcess_OptimizeMeshes | aiProcess_SplitLargeMeshes | aiProcess_FindDegenerates | aiProcess_FindInvalidData | aiProcess_ImproveCacheLocality);

	if(!scene) 
		return false;

	std::string meshName = "mesh_";
	aiString texturePath, bumpTexturePath, ambTexturePath, displacementTexturePath;

	for(unsigned int mat = 0; mat < scene->mNumMaterials; mat++) {
			const struct aiMaterial* material = scene->mMaterials[mat];
			
			if (material) {
				material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
				material->GetTexture(aiTextureType_HEIGHT, 0, &bumpTexturePath);					// HEIGHT is used to retrieve the bump in .obj files formats
				material->GetTexture(aiTextureType_AMBIENT, 0, &ambTexturePath);					// Does nothing
				material->GetTexture(aiTextureType_DISPLACEMENT, 0, &displacementTexturePath);		// Does nothing

				aiString materialName;
				material->Get(AI_MATKEY_NAME, materialName);

				CMaterial* pNewMaterial = new CMaterial;

				// Diffuse texture
				if (texturePath.C_Str() != "") {
					std::string textureFile = "C:\\Users\\Mathew\\Downloads\\hou\\MedievalHouse1.fbm\\" + std::string(texturePath.C_Str());
					pTextureMgr->LoadTexture(std::string(materialName.C_Str()) + "_diffuse", textureFile);

					pNewMaterial->m_diffuseTexID = std::string(materialName.C_Str()) + "_diffuse";
					
				}

				// Normal map texture
				if (bumpTexturePath.C_Str() != "") {
					std::string bumpTextureFile = "C:\\Users\\Mathew\\Downloads\\hou\\MedievalHouse1.fbm\\" + std::string(bumpTexturePath.C_Str());
					pTextureMgr->LoadTexture(std::string(materialName.C_Str()) + "_normal", bumpTextureFile);

					pNewMaterial->m_bumpTexID = std::string(materialName.C_Str()) + "_normal";
				}

				pMaterialMgr->AddMaterial(std::to_string(mat), pNewMaterial);
			}
		}


	for(unsigned int meshNum = 0; meshNum < scene->mNumMeshes; meshNum++) {
		const struct aiMesh* mesh = scene->mMeshes[meshNum];

		unsigned int totalIndices = 0;
		for(glm::uint face = 0; face < (glm::uint)mesh->mNumFaces; face++)
			totalIndices += mesh->mFaces[face].mNumIndices;

		MeshData* pNewMeshData = new MeshData(EVertexType::eVertexPT, mesh->mNumVertices, totalIndices);

		for(glm::uint vert = 0; vert < (glm::uint)pNewMeshData->vertexCount; vert++) {
			SVertexTypePT* pVertex = (SVertexTypePT*)pNewMeshData->pVertices;

			pVertex[vert].position = glm::vec3(mesh->mVertices[vert].x, mesh->mVertices[vert].y, mesh->mVertices[vert].z);
			//pVertex[vert].normal = glm::vec3(mesh->mNormals[vert].x, mesh->mNormals[vert].y, mesh->mNormals[vert].z);
			//pVertex[vert].tangent = glm::vec3(mesh->mTangents[vert].x, mesh->mTangents[vert].y, mesh->mTangents[vert].z);
			pVertex[vert].textureCoord = glm::vec2(mesh->mTextureCoords[0][vert].x, mesh->mTextureCoords[0][vert].y);
		}

		unsigned int counter = 0;
		for(unsigned int face = 0; face < mesh->mNumFaces; face++) {
			for(unsigned int idx = 0; idx < mesh->mFaces[face].mNumIndices; idx++){
				pNewMeshData->pIndices[counter] = mesh->mFaces[face].mIndices[idx];
				counter++;
			}
		}

		pNewMeshData->material = std::to_string(mesh->mMaterialIndex);

		if(mesh->mName.length == 0) {
			std::string meshStr = std::to_string((long double)meshNum);
			pMeshMgr->AddMeshData(pNewMeshData, meshName + meshStr );
		}
		else
			pMeshMgr->AddMeshData(pNewMeshData, mesh->mName.C_Str());
	}

	return true;
}


// Function to create a test scene.
//
// Objects created will vary throughout development
//
bool CSceneLoader::TestScene(CMeshDataManager* pMeshMgr,
	CTextureManager* pTextureMgr, CMaterialManager* pMaterialMgr)
{

	// Currenty create a flat plane 
	pMeshMgr->CreatePlane("myPlane", 100, EVertexType::eVertexPNC, 10, glm::vec4(1, 0, 0, 1));

	pMeshMgr->CreateSphere("mySphere", 10, EVertexType::eVertexPNC, 10, glm::vec4(0, 1, 0, 1));

	return true;
}