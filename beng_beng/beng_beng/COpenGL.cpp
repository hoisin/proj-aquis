#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "COpenGL.h"
#include "CShader.h"

// Initialise statics
bool COpenGL::m_bClassRegistered = false;
bool COpenGL::m_bGlewInitialised = false;


COpenGL::COpenGL() : m_pHwnd(NULL), m_iMajorVer(3), m_iMinorVer(3)
{
}


COpenGL::~COpenGL()
{
	ReleaseOpenGLControl();
}


//------------------------------------------------------------------
//
//	InitOpenGL(..)
//
//	Params:
//	hInstance		-	App instance
//	hwnd			-	Handle to window
//	majorVer		-	Major version of OpenGL
//	minorVer		-	Minor version of OpenGL
//	funcCallback	-	Callback function
//
//	Initialises OpenGL
//
//------------------------------------------------------------------
bool COpenGL::InitOpenGL(HINSTANCE hInstance, HWND* pHwnd, int majorVer, int minorVer, WNDPROC funcCallback)
{
	if(!InitGLEW(hInstance, funcCallback))
		return false;

	m_pHwnd = pHwnd;
	m_hDC = GetDC(*m_pHwnd);

	bool bError = false;
	PIXELFORMATDESCRIPTOR pfd;

	if(majorVer <= 2)
	{
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion   = 1;
		pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;
 
		int iPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		if (iPixelFormat == 0)return false;

		if(!SetPixelFormat(m_hDC, iPixelFormat, &pfd))return false;

		// Create the old style context (OpenGL 2.1 and before)
		m_hRC = wglCreateContext(m_hDC);
		if(m_hRC)wglMakeCurrent(m_hDC, m_hRC);
		else bError = true;
	}
	else if(WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
	{
		const int iPixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0 // End of attributes list
		};
		int iContextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVer,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVer,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0 // End of attributes list
		};

		int iPixelFormat, iNumFormats;
		wglChoosePixelFormatARB(m_hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);

		// PFD seems to be only redundant parameter now
		if(!SetPixelFormat(m_hDC, iPixelFormat, &pfd))return false;

		m_hRC = wglCreateContextAttribsARB(m_hDC, 0, iContextAttribs);
		// If everything went OK
		if(m_hRC) wglMakeCurrent(m_hDC, m_hRC);
		else bError = true;

	}
	else bError = true;
	
	if(bError)
	{
		// Generate error messages
		char sErrorMessage[255], sErrorTitle[255];
		sprintf_s(sErrorMessage, "OpenGL %d.%d is not supported! Please download latest GPU drivers!", majorVer, minorVer);
		sprintf_s(sErrorTitle, "OpenGL %d.%d Not Supported", majorVer, minorVer);
		MessageBox(*m_pHwnd, sErrorMessage, sErrorTitle, MB_ICONINFORMATION);
		return false;
	}

	// Set the clear colour
	glClearColor(0.5, 0.0, 0.0, 1.0);

	return true;
}


//------------------------------------------------------------------
//
//	ResizeOpenGLViewportFull(..)
//
//	Resizes viewport to full window with perspective projection
//
//------------------------------------------------------------------
void COpenGL::ResizeOpenGLViewportFull()
{
	if(m_pHwnd == NULL)
		return;

	RECT rRect; GetClientRect(*m_pHwnd, &rRect);
	glViewport(0, 0, rRect.right, rRect.bottom);
}


//------------------------------------------------------------------
//
//	ReleaseOpenGLControl(..)
//
//	Releases OpenGL
//
//------------------------------------------------------------------
void COpenGL::ReleaseOpenGLControl()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	ReleaseDC(*m_pHwnd, m_hDC);

	m_pHwnd = NULL;
}


//------------------------------------------------------------------
//
//	RegisterOpenGLClass(..)
//
//	hInstance	-	Application instance
//
//	Registers the OpenGL window class
//
//------------------------------------------------------------------
void COpenGL::RegisterOpenGLClass(HINSTANCE hInstance, WNDPROC funcCallback)
{
	if(m_bClassRegistered)
		return;

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style =  CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.lpfnWndProc = funcCallback;
	wc.cbClsExtra = 0; wc.cbWndExtra = 0;
	wc.hInstance = hInstance;

	// Memory Access Violation error
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_MENUBAR+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = OPENGL_CLASS_NAME;

	RegisterClassEx(&wc);

	m_bClassRegistered = true;
}


//------------------------------------------------------------------
//
//	UnregisterOpenGLClass(..)
//
//	hInstance	-	Application instance
//
//	Unegisters the OpenGL window class
//
//------------------------------------------------------------------
void COpenGL::UnregisterOpenGLClass(HINSTANCE hInstance)
{
	if(m_bClassRegistered)
	{
		UnregisterClass(OPENGL_CLASS_NAME, hInstance);
		m_bClassRegistered = false;
	}
}


//------------------------------------------------------------------
//
//	SetCurrentShader(..)
//
//	pNewShader	-	New shader to be used as current
//
//	Simply sets new shader to be stored as current
//
//------------------------------------------------------------------
void COpenGL::SetCurrentShader(CShader* pNewShader)
{
	m_pRefCurrentShader = pNewShader;
}


void COpenGL::SetShaderParam(EShaderParamType type, char* paramID, void* pData, UINT count, bool bTranspose)
{
	// Get handle to shader param
	int shaderParam = glGetUniformLocation(m_pRefCurrentShader->GetShaderID(), paramID);

	switch(type){
	case eShaderParam1i:
		glUniform1i(shaderParam, *((GLint*)(pData)));
		break;

	case eShaderParam2i:
		{
			glm::ivec2* data = (glm::ivec2*)pData;
			glUniform2i(shaderParam, data->x, data->y);
		}
		break;

	case eShaderParam3i:
		{
			glm::ivec3* data = (glm::ivec3*)pData;
			glUniform3i(shaderParam, data->x, data->y, data->z);
		}
		break;

	case eShaderParam4i:
		{
			glm::ivec4* data = (glm::ivec4*)pData;
			glUniform4i(shaderParam, data->x, data->y, data->z, data->w);
		}
		break;

	case eShaderParam1iv:
		glUniform1iv(shaderParam, count, (GLint*)pData);
		break;

	case eShaderParam2iv:
		glUniform2iv(shaderParam, count, (GLint*)pData);
		break;

	case eShaderParam3iv:
		glUniform3iv(shaderParam, count, (GLint*)pData);
		break;

	case eShaderParam4iv:
		glUniform4iv(shaderParam, count, (GLint*)pData);
		break;

	case eShaderParam1f:
		glUniform1f(shaderParam, *((GLfloat*)pData));
		break;

	case eShaderParam2f:
		{
			glm::vec2* data = (glm::vec2*)pData;
			glUniform2f(shaderParam, data->x, data->y);
		}
		break;

	case eShaderParam3f:
		{
			glm::vec3* data = (glm::vec3*)pData;
			glUniform3f(shaderParam, data->x, data->y, data->z);
		}
		break;

	case eShaderParam4f:
		{
			glm::vec4* data = (glm::vec4*)pData;
			glUniform4f(shaderParam, data->x, data->y, data->z, data->w);
		}
		break;

	case eShaderParam1fv:
		glUniform1fv(shaderParam, count, (GLfloat*)pData);
		break;

	case eShaderParam2fv:
		glUniform2fv(shaderParam, count, (GLfloat*)pData);
		break;

	case eShaderParam3fv:
		glUniform3fv(shaderParam, count, (GLfloat*)pData);
		break;

	case eShaderParam4fv:
		glUniform4fv(shaderParam, count, (GLfloat*)pData);
		break;

	case eShaderParamMat2fv:
		glUniformMatrix2fv(shaderParam, count, bTranspose, (GLfloat*)pData);
		break;

	case eShaderParamMat3fv:
		glUniformMatrix3fv(shaderParam, count, bTranspose, (GLfloat*)pData);
		break;

	case eShaderParamMat4fv:
		glUniformMatrix4fv(shaderParam, count, bTranspose, (GLfloat*)pData);
		break;
	}
}


void COpenGL::BeginDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void COpenGL::EndDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//------------------------------------------------------------------
//
//	RenderBuffer(..)
//
//	pVertBuffer		-	pointer to the vertex buffer object
//	pIndexBuffer	-	pointer to the index buffer object
//
//	Draws passed vertex data
//
//------------------------------------------------------------------
void COpenGL::RenderBuffer(CVertexBuffer* pVertBuffer, CIndexBuffer* pIndexBuffer)
{
	pVertBuffer->UseBuffer();
	pIndexBuffer->UseBuffer();

	// Set Shader stuff
	// Set textures

	glDrawElements(GL_TRIANGLES, pIndexBuffer->GetIndexCount(), GL_UNSIGNED_INT, 0);
}


//------------------------------------------------------------------
//
//	MakeCurrent(..)
//
//	Makes current device and OpenGL rendering context to those
//	associated with OpenGL control
//
//------------------------------------------------------------------

void COpenGL::MakeCurrent()
{
	wglMakeCurrent(m_hDC, m_hRC);
}



//------------------------------------------------------------------
//
//	ClearScreen(..)
//
//	Clears the screen
//
//------------------------------------------------------------------
void COpenGL::ClearScreen()
{
	// Clear screen before drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//------------------------------------------------------------------
//
//	SwapBuffersM(..)
//
//	Swaps back and front buffer
//
//------------------------------------------------------------------
void COpenGL::SwapBuffersM()
{
	SwapBuffers(m_hDC);
}


//------------------------------------------------------------------
//
//	InitGLEW(..)
//
//	Initialises the GLEW library
//
//------------------------------------------------------------------
bool COpenGL::InitGLEW(HINSTANCE hInstance, WNDPROC funcCallback)
{
	if(m_bGlewInitialised)
		return true;

	RegisterOpenGLClass(hInstance, funcCallback);

	HWND hWndTemp = CreateWindow(OPENGL_CLASS_NAME, "FAKE", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 0, 0,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	m_hDC = GetDC(hWndTemp);

	
	// Choose pixel format
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
 
	int iPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	if (iPixelFormat == 0)
		return false;

	if(!SetPixelFormat(m_hDC, iPixelFormat, &pfd))
		return false;

	// Create the false, old style context (OpenGL 2.1 and before)
	HGLRC hRCFake = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, hRCFake);

	bool bResult = true;

	if(!m_bGlewInitialised)
	{
		if(glewInit() != GLEW_OK)
		{
			MessageBox(*m_pHwnd, "Couldn't initialize GLEW!", "Fatal Error", MB_ICONERROR);
			bResult = false;
		}

		m_bGlewInitialised = true;
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRCFake);
	DestroyWindow(hWndTemp);

	return bResult;
}
