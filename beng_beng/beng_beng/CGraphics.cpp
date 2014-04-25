#include "CGraphics.h"
#include "COpenGL.h"
#include "CResourceManager.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CTexture2D.h"

CGraphics::CGraphics() : m_pOpenGL(NULL)
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
	MeshData *pMesh = m_pResourceMgr->CreateQuad("quad_1", 1, eVertexPT);//, glm::vec4(1,0,1,1));
	//MeshData *pMesh = m_pResourceMgr->CreateTriangle("tri_1", 1, eVertexPC, glm::vec4(1,1,1,0));

	pVert = m_pResourceMgr->CreateVertexBuffer("mesh_1", pMesh);
	pIdx = m_pResourceMgr->CreateIndexBuffer("idx_1", pMesh);

	pTex = m_pResourceMgr->CreateTexture2D("tex_1", "..\\Textures\\wtf.bmp");

	pShader = m_pResourceMgr->CreateShader("simple_shader_1", "..\\Shaders\\textureVertexShader.vsh", "..\\Shaders\\textureFragmentShader.fsh");
	//pShader = m_pResourceMgr->CreateShader("simple_shader_1", "..\\Shaders\\simpleVertexShader.vsh", "..\\Shaders\\simpleFragmentShader.fsh");
}