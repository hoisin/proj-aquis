//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Main interface class for graphics
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#include "CGraphics.h"
#include "COpenGL.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CTexture2D.h"
#include "CCameraFPS.h"
#include "CSubMesh.h"
#include "CMesh.h"
#include "CLight.h"

#include "CMeshDataManager.h"
#include "CBufferManager.h"
#include "CTextureManager.h"
#include "CShaderManager.h"
#include "CMeshManager.h"
#include "CSceneLoader.h"
#include "CMaterialManager.h"
#include "CMaterial.h"

#include <sstream>
#include <fstream>


std::string mySphere = "sphere_01";
std::string myTex = "tex_01";
std::string myShader = "simple_01";

// Testingzzzz remove pls when not needed
int g_numObjs = 1;

CLight g_light = CLight(eLightDir, glm::vec3(0, -1, 0), glm::vec3(1, 1, 1), 1,
	1, 0);

CLight g_ambLight = CLight(eLightAmb, glm::vec3(0,0,0), glm::vec3(1, 1, 1), 0.15f);

CGraphics::CGraphics() : m_pOpenGL(NULL),  m_winWidth(0), m_winHeight(0), m_bWireFrame(false), m_pMeshDataMgr(NULL),
	m_pBufferMgr(NULL), m_pTextureMgr(NULL), m_pShaderMgr(NULL), m_pMeshMgr(NULL), m_pSceneLoader(NULL), m_pMaterialMgr(NULL)
{
}


CGraphics::~CGraphics()
{
	ShutDown();
}


//------------------------------------------------------------------
//
//	Initialise(..)
//
//	Params:
//	hInstance		-	App instance
//	hwnd			-	Handle to window
//	majorVer		-	Major version of OpenGL
//	minorVer		-	Minor version of OpenGL
//	funcCallback	-	Callback function
//
//	Initialises all graphics related components
//
//------------------------------------------------------------------
bool CGraphics::Initialise(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, 
	UINT windowWidth, UINT windowHeight, WNDPROC funcCallback)
{
	if(!m_pOpenGL) {
		m_pOpenGL = new COpenGL;
	}

	if(!m_pOpenGL->InitOpenGL(hInstance, hwnd, majorVer, minorVer, funcCallback))
		return false;

	// Keep a reference
	m_hInstance = hInstance;

	glViewport(0, 0, windowWidth, windowHeight);

	m_winWidth = windowWidth;
	m_winHeight = windowHeight;

	// Vars/states that need porting 
	glDepthMask(GL_TRUE);		// Depth buffer enabled for writing
	glEnable(GL_DEPTH_TEST);	// Depth testing (stuff behind stuff don't get draw)
	glEnable(GL_CULL_FACE);		// Back facing triangles don't get drawn
	glFrontFace(GL_CCW);

	// Create the managers
	m_pMeshDataMgr = new CMeshDataManager;
	m_pBufferMgr = new CBufferManager;
	m_pTextureMgr = new CTextureManager;
	m_pShaderMgr = new CShaderManager;
	m_pMeshMgr = new CMeshManager;
	m_pSceneLoader = new CSceneLoader;
	m_pMaterialMgr = new CMaterialManager;

	return true;
}


//------------------------------------------------------------------
//
//	RenderScene(..)
//
//	Main draw call
//
//------------------------------------------------------------------
bool CGraphics::RenderScene()
{
	// Make sure we have actual OpenGL access
	if(!m_pOpenGL)
		return false;

	// Clear screen before drawing
	m_pOpenGL->BeginDraw();

	// For objects.list size (to do)

	// for all objects in world ---- 
	std::map<std::string, CMesh*>* pMeshes = m_pMeshMgr->GetMap();
	std::map<std::string, CMesh*>::iterator it;

	for(it = pMeshes->begin(); it != pMeshes->end(); it++) {
		CMesh* pCurrentMesh = it->second;

		// Draw each sub-mesh in the mesh
		for(unsigned int subMesh = 0; subMesh < pCurrentMesh->GetSubMeshCount(); subMesh++) {
			m_pBufferMgr->GetVertexBuffer(pCurrentMesh->GetSubMesh(subMesh)->m_vertexID)->UseBuffer();
			m_pBufferMgr->GetIndexBuffer(pCurrentMesh->GetSubMesh(subMesh)->m_indexID)->UseBuffer();

			CMaterial* pMat = m_pMaterialMgr->GetMaterial(pCurrentMesh->GetSubMesh(subMesh)->m_textureID.c_str());
			CShader* pCurrentShader = m_pShaderMgr->GetShader(myShader);
			pCurrentShader->UserShader();

			// Setup textures
			//pCurrentShader->SetShaderParam1i("texture0", 0);
			//pCurrentShader->SetShaderParam1i("texture1", 1);

			//glActiveTexture(GL_TEXTURE0);
			//m_pTextureMgr->GetTexture(pMat->m_diffuseTexID)->UseTexture();

			//glActiveTexture(GL_TEXTURE1);
			//m_pTextureMgr->GetTexture(pMat->m_bumpTexID)->UseTexture();

			// Setup shader parameters
			glm::mat4 world;
			world = glm::translate(glm::mat4(1.0), pCurrentMesh->GetPos());

			pCurrentShader->SetShaderParamMatrix4fv("projectionMatrix", pCam->GetProjectionMatrix(), 1);
			pCurrentShader->SetShaderParamMatrix4fv("viewMatrix", pCam->GetViewMatrix(), 1);
			pCurrentShader->SetShaderParamMatrix4fv("worldMatrix", world, 1);

			glm::mat4 invWorld(1);
			invWorld = glm::inverse(invWorld);
			invWorld = glm::transpose(invWorld);

			pCurrentShader->SetShaderParamMatrix4fv("worldInvMatrix", invWorld, 1);

			glm::vec4 col = glm::vec4(g_light.m_col, 1);
			pCurrentShader->SetShaderParam3f("lightDirection", g_light.m_pos.x, g_light.m_pos.y, g_light.m_pos.z);
			pCurrentShader->SetShaderParam4f("diffuseLightCol", col.x, col.y, col.z, col.w);
			pCurrentShader->SetShaderParam3f("ambLightCol", g_ambLight.m_col.x, g_ambLight.m_col.y, g_ambLight.m_col.z);
			pCurrentShader->SetShaderParam1f("ambIntensity", g_ambLight.m_intensity);

			// Draw the sub-mesh
			glDrawElements(GL_TRIANGLES, m_pBufferMgr->GetIndexBuffer(pCurrentMesh->GetSubMesh(subMesh)->m_indexID)->GetIndexCount(), GL_UNSIGNED_INT, 0);

			// Free stuff for the next draw call
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);
		}
	}

	// end of loop

	// Swap buffers!!!
	m_pOpenGL->EndDraw();

	return true;
}


//------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Performs cleaup. Reverse order resource clean up
//
//------------------------------------------------------------------
void CGraphics::ShutDown()
{
	if (m_pMaterialMgr) {
		delete m_pMaterialMgr;
		m_pMaterialMgr = NULL;
	}

	if(m_pSceneLoader) {
		delete m_pSceneLoader;
		m_pSceneLoader = NULL;
	}

	if(m_pMeshMgr) {
		delete m_pMeshMgr;
		m_pMeshMgr = NULL;
	}

	if(m_pShaderMgr) {
		delete m_pShaderMgr;
		m_pShaderMgr = NULL;
	}

	if(m_pTextureMgr) {
		delete m_pTextureMgr;
		m_pTextureMgr = NULL;
	}

	if(m_pBufferMgr) {
		delete m_pBufferMgr;
		m_pBufferMgr = NULL;
	}

	if(m_pMeshDataMgr) {
		delete m_pMeshDataMgr;
		m_pMeshDataMgr = NULL;
	}

	if(m_pOpenGL) {
		m_pOpenGL->UnregisterOpenGLClass(m_hInstance);
		delete m_pOpenGL;
		m_pOpenGL = NULL;
	}

	// Temporary
	if(pCam) {
		delete pCam;

		pCam = NULL;
	}

}


//------------------------------------------------------------------
//
//	GetMeshPosition(..)
//
//	Params:
//	meshID	-	ID of the mesh 
//
//	Returns the current set position of the mesh in question
//
//------------------------------------------------------------------
glm::vec3 CGraphics::GetMeshPosition(const std::string& meshID)
{
	return m_pMeshMgr->GetMesh(meshID)->GetPos();
}


//------------------------------------------------------------------
//
//	SetMeshPosition(..)
//
//	Params:
//	meshID	-	ID of the mesh 
//	newPos	-	The new position to set to
//
//	Sets the specified mesh's new position
//
//------------------------------------------------------------------
void CGraphics::SetMeshPosition(const std::string& meshID, const glm::vec3& newPos)
{
	m_pMeshMgr->GetMesh(meshID)->SetPos(newPos);
}


//------------------------------------------------------------------
//
//	LoadScene(..)
//
// Temporary load scene function
//
//------------------------------------------------------------------
void CGraphics::LoadScene()
{
	//--------------------------------------------------------
	//
	//	New way of loading/creating assets/scene data
	//
	//--------------------------------------------------------

	// Create the scene
	m_pSceneLoader->TestScene(m_pMeshDataMgr, m_pTextureMgr, m_pMaterialMgr);

	std::string vertStr = "Vertex_Buffer_";
	std::string idxStr = "Index_Buffer_";
	std::map<std::string, MeshData*>* pMap = m_pMeshDataMgr->GetMap();
	std::map<std::string, MeshData*>::iterator it;

	// Proceed to load any shaders to be used
	m_pShaderMgr->CreateShader(myShader, "..\\Shaders\\testVertexShader.vsh", "..\\Shaders\\testFragmentShader.fsh");

	// For each mesh data in map, create vertex/index buffers and attach everything to a Mesh object
	unsigned int count = 0;
	for(it = pMap->begin(); it != pMap->end(); it++) {
		m_pBufferMgr->CreateVertexBuffer(vertStr + std::to_string(count), it->second);
		m_pBufferMgr->CreateIndexBuffer(idxStr + std::to_string(count), it->second);

		std::string meshStr = "mesh_";

		CMesh* pNewMesh = m_pMeshMgr->CreateMesh(glm::vec3(0, 0, 0), meshStr + std::to_string(count));
		pNewMesh->AddSubMesh(new CSubMesh("Submesh_" + std::to_string(count), vertStr + std::to_string(count), idxStr + std::to_string(count), myShader,
			it->second->material));

		count++;
	}

	pCam = new CCameraFPS(glm::vec3(0,50,200), glm::vec3(0,1,0), 1.f, 5000.f, (float)(m_winWidth/m_winHeight), 45.0f);
}


//------------------------------------------------------------------
//
//	SetWireFrame(..)
//
//	Params:
//	bool	-	Enables/disables wireframe mode
//
// Turns wire frame mode on/off
//
//------------------------------------------------------------------

void CGraphics::SetWireFrame(bool bWireFrame)
{
	m_bWireFrame = bWireFrame;

	if(bWireFrame)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}