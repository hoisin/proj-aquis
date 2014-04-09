#include "CGraphics.h"
#include "COpenGL.h"
#include "CResourceManager.h"
#include "CVertexBuffer.h"

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
	if(!m_pOpenGL)
	{
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
	glBindVertexArray(pVert->GetVertexArray());
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
	if(m_pOpenGL)
	{
		m_pOpenGL->UnregisterOpenGLClass(m_hInstance);
		delete m_pOpenGL;
		m_pOpenGL = NULL;
	}
}


void CGraphics::LoadScene()
{
	MeshData *pMesh = m_pResourceMgr->CreateTriangle("tri_1", 1, EVertexType::eVertexPC);

	pVert = m_pResourceMgr->CreateVertexBuffer("mesh_1", pMesh);

	shaderProgID = m_pResourceMgr->CreateShader("simple_shader_1", "..\\Shaders\\simpleVertexShader.vsh", "..\\Shaders\\simpleFragmentShader.fsh");

	glUseProgram(shaderProgID);
}
