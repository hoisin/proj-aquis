#include "CGraphics.h"
#include "COpenGL.h"
#include "CResourceManager.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CTexture2D.h"
#include "CCameraFPS.h"

CGraphics::CGraphics() : m_pOpenGL(NULL), m_pResourceMgr(NULL),  m_winWidth(0), m_winHeight(0)
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
	glClear(GL_COLOR_BUFFER_BIT);

	// Do drawing crap here
	//glActiveTexture(GL_TEXTURE0);
	//GLint texloc(glGetUniformLocation(pShader->GetShaderID(), "myTextureSampler")); //uniform sampler2D tex
	//glUniform1i(texloc,0); // 0 for GL_TEXTURE0
	//glBindTexture(GL_TEXTURE_2D, pTex->GetTexture());	// Only need this to set to 'use'

	//glBindVertexArray(pVert->GetVertexArray());
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIdx->GetElementBuffer());

	pVert->UseBuffer();
	pIdx->UseBuffer();
	pTex->UseTexture();
	pShader->UserShader();

	int projectionMatrixLocation = glGetUniformLocation(pShader->GetShaderID(), "projectionMatrix"); // Get the location of our projection matrix in the shader  
	int viewMatrixLocation = glGetUniformLocation(pShader->GetShaderID(), "viewMatrix"); // Get the location of our view matrix in the shader  
	int modelMatrixLocation = glGetUniformLocation(pShader->GetShaderID(), "worldMatrix"); // Get the location of our model matrix in the shader 

	glm::mat4 world(1);

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


void CGraphics::LoadScene()
{
	//MeshData *pMesh = m_pResourceMgr->CreateQuad("quad_1", 1, eVertexPT);//, glm::vec4(1,0,1,1));
	MeshData *pMesh = m_pResourceMgr->CreateTriangle("tri_1", 1, eVertexPC, glm::vec4(1,1,1,0));

	pVert = m_pResourceMgr->CreateVertexBuffer("mesh_1", pMesh);
	pIdx = m_pResourceMgr->CreateIndexBuffer("idx_1", pMesh);

	pTex = m_pResourceMgr->CreateTexture2D("tex_1", "..\\Textures\\wtf.bmp");

	//pShader = m_pResourceMgr->CreateShader("simple_shader_1", "..\\Shaders\\textureVertexShader.vsh", "..\\Shaders\\textureFragmentShader.fsh");
	pShader = m_pResourceMgr->CreateShader("simple_shader_1", "..\\Shaders\\simpleVertexShader.vsh", "..\\Shaders\\simpleFragmentShader.fsh");

	pCam = new CCameraFPS(glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec3(0,0,1), 1.f, 200.f, (float)(m_winWidth/m_winHeight), 45.0f);
}
