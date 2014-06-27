#include "CGraphics.h"
#include "COpenGL.h"
#include "CResourceManager.h"
#include "CResourceVertexBuffer.h"
#include "CResourceModelMesh.h"
#include "CResourceIndexBuffer.h"
#include "CResourceModelMesh.h"
#include "CResourceShader.h"
#include "CResourceTexture2D.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CTexture2D.h"
#include "CCameraFPS.h"
#include "CModelMesh.h"

#include <sstream>

// Testingzzzz remove pls when not needed
int g_numObjs = 1;

CGraphics::CGraphics() : m_pOpenGL(NULL), m_pResourceMgr(NULL),  m_winWidth(0), m_winHeight(0), m_bWireFrame(false)
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
bool CGraphics::Initialise(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, CResourceManager *pResourceMgr, 
	UINT windowWidth, UINT windowHeight, WNDPROC funcCallback)
{
	if(!m_pOpenGL) {
		m_pOpenGL = new COpenGL;
	}

	if(!m_pOpenGL->InitOpenGL(hInstance, hwnd, majorVer, minorVer, funcCallback))
		return false;

	// Keep a reference
	m_pResourceMgr = pResourceMgr;
	m_hInstance = hInstance;

	glViewport(0, 0, windowWidth, windowHeight);

	m_winWidth = windowWidth;
	m_winHeight = windowHeight;

	// Vars/states that need porting 
	glDepthMask(GL_TRUE);		// Depth buffer enabled for writing
	glEnable(GL_DEPTH_TEST);	// Depth testing (stuff behind stuff don't get draw)
	glEnable(GL_CULL_FACE);		// Back facing triangles don't get drawn
		

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

	// Do drawing crap here
	//glActiveTexture(GL_TEXTURE0);
	//GLint texloc(glGetUniformLocation(pShader->GetShaderID(), "myTextureSampler")); //uniform sampler2D tex
	//glUniform1i(texloc,0); // 0 for GL_TEXTURE0
	//glBindTexture(GL_TEXTURE_2D, pTex->GetTexture());	// Only need this to set to 'use'

	//glBindVertexArray(pVert->GetVertexArray());
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIdx->GetElementBuffer());
	
	for(int i = 0; i < g_numObjs; i++)
	{
		/*pVert->UseBuffer();
		pIdx->UseBuffer();
		pTex->UseTexture();
		pShader->UserShader();*/

		((CResourceVertexBuffer*)(m_pResourceMgr->GetResource(pModels[i]->m_vertexID)))->m_pVertBuffer->UseBuffer();
		((CResourceIndexBuffer*)(m_pResourceMgr->GetResource(pModels[i]->m_indexID)))->m_pIdxBuffer->UseBuffer();
		((CResourceTexture2D*)(m_pResourceMgr->GetResource(pModels[i]->m_textureID)))->m_pTexture->UseTexture();
		((CResourceShader*)(m_pResourceMgr->GetResource(pModels[i]->m_shaderID)))->m_pShader->UserShader();

		int projectionMatrixLocation = glGetUniformLocation(pShader->GetShaderID(), "projectionMatrix"); // Get the location of our projection matrix in the shader  
		int viewMatrixLocation = glGetUniformLocation(pShader->GetShaderID(), "viewMatrix"); // Get the location of our view matrix in the shader  
		int modelMatrixLocation = glGetUniformLocation(pShader->GetShaderID(), "worldMatrix"); // Get the location of our model matrix in the shader 

		glm::mat4 world(1);

		std::string name = "";
		std::stringstream str;
		str << i;
		name = "myModel" + str.str();

		//world = glm::translate(glm::mat4(1.0), glm::vec3(rand()%50, rand()%50, -rand()%50));
		world = glm::translate(glm::mat4(1.0), 
			((CResourceModelMesh*)(m_pResourceMgr->GetResource(name)))->m_pModelMesh->pos);

		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &pCam->GetProjectionMatrix()[0][0]); // Send our projection matrix to the shader  
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &pCam->GetViewMatrix()[0][0]); // Send our view matrix to the shader  
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &world[0][0]); // Send our model matrix to the shader  

		glDrawElements(GL_TRIANGLES, pIdx->GetIndexCount(), GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Free stuff for the next draw call
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
	}
	
	// Swap buffers!!!
	m_pOpenGL->SwapBuffersM();

	return true;
}


//------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Performs cleaup
//
//------------------------------------------------------------------
void CGraphics::ShutDown()
{
	if(m_pOpenGL) {
		m_pOpenGL->UnregisterOpenGLClass(m_hInstance);
		delete m_pOpenGL;
		m_pOpenGL = NULL;
	}
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
	MeshData *pMesh = m_pResourceMgr->CreateSphere("sphere_1", 10, eVertexPT, 100);
	//MeshData *pMesh = m_pResourceMgr->CreateQuad("quad_1", 6, eVertexPT);//, glm::vec4(1,0,1,1));
	//MeshData *pMesh = m_pResourceMgr->CreatePlane("plane_1", 20, eVertexPT, 20);//, glm::vec4(1,0,1,1));
	//MeshData *pMesh = m_pResourceMgr->CreateTriangle("tri_1", 1, eVertexPC, glm::vec4(1,1,1,0));
	//MeshData *pMesh = m_pResourceMgr->CreateCube("cube_1", 1, eVertexPT, 10, glm::vec4(1,1,1,0));

	pVert = m_pResourceMgr->CreateVertexBuffer("mesh_1", pMesh);
	pIdx = m_pResourceMgr->CreateIndexBuffer("idx_1", pMesh);

	pTex = m_pResourceMgr->CreateTexture2D("tex_1", "..\\Textures\\wtf.bmp");

	pShader = m_pResourceMgr->CreateShader("simple_shader_1", "..\\Shaders\\textureVertexShader.vsh", "..\\Shaders\\textureFragmentShader.fsh");
	//pShader = m_pResourceMgr->CreateShader("simple_shader_1", "..\\Shaders\\simpleVertexShader.vsh", "..\\Shaders\\simpleFragmentShader.fsh");

	for(int i = 0; i < g_numObjs; i++) {
		std::string name = "";
		std::stringstream str;
		str << i;
		name = "myModel" + str.str();
		pModels[i] = m_pResourceMgr->CreateModelMesh(name, "sphere_1", "mesh_1", "idx_1", "simple_shader_1", "tex_1");
		pModels[i]->pos = glm::vec3(0, 0, 0);
		//pModels[i]->pos = glm::vec3(rand()%50, rand()%50, -rand()%50);
	}

	pCam = new CCameraFPS(glm::vec3(0,0,10), glm::vec3(0,1,0), 1.f, 200.f, (float)(m_winWidth/m_winHeight), 45.0f);
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