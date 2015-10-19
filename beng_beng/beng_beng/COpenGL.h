//--------------------------------------------------------------------------
//
//	20/03/2014
//
//	Class managing OpenGL stuff.....
//
//	This class should handle OpenGL specific setup & call related to drawing.
//
//	Author: Matt © 2014
//
//--------------------------------------------------------------------------

#ifndef __COPENGL_H__
#define __COPENGL_H__

#define OPENGL_CLASS_NAME "OpenGL_3_3_App"

#include <gl/glew.h>
#include <gl/wglew.h>
#include <Windows.h>
#include <iostream>

class CVertexBuffer;
class CIndexBuffer;
class CShader;

// Enumerates for shader parameter types
enum EShaderParamType {
	eShaderParam1i,				// Single values
	eShaderParam2i,
	eShaderParam3i,
	eShaderParam4i,
	eShaderParam1iv,			// Array, need to specify count
	eShaderParam2iv,
	eShaderParam3iv,
	eShaderParam4iv,

	eShaderParam1f,				// Single values
	eShaderParam2f,
	eShaderParam3f,
	eShaderParam4f,
	eShaderParam1fv,			// Array, need to specify count
	eShaderParam2fv,
	eShaderParam3fv,
	eShaderParam4fv,

	eShaderParamMat2fv,			// Matrices (2x2, 3x3, 4x4)
	eShaderParamMat3fv,
	eShaderParamMat4fv,

	eShaderParamTotal			// Dud
};

class COpenGL
{
public:
	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_TEXCOORD,
		GBUFFER_NUM_TEXTURES
	};

public:
	COpenGL();
	~COpenGL();

	bool InitOpenGL(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, int winWidth,
		int winHeight, WNDPROC funcCallback);

	void ResizeOpenGLViewportFull();

	void ReleaseOpenGLControl();

	static void RegisterOpenGLClass(HINSTANCE hInstance, WNDPROC funcCallback);
	static void UnregisterOpenGLClass(HINSTANCE hInstance);

	// Shader operations
	void SetCurrentShader(CShader* pNewShader);
	void SetShaderParam(EShaderParamType type, char* paramID, void* pData, UINT count = 1, bool bTranspose = false);
	CShader* GetCurrentShader() { return m_pRefCurrentShader; }

	// Deferred rendering operations
	void BindGBufferWriting(bool bVal);
	void BindGBufferReading();
	void UnbindGBufferingReading();
	void SetReadGBuffer(GBUFFER_TEXTURE_TYPE textureType);

	void BeginDraw();
	void EndDraw();

	void RenderBuffer(CVertexBuffer* pVertBuffer, CIndexBuffer* pIndexBuffer);

	void MakeCurrent();
	void ClearScreen();

private:
	void SwapBuffersM();

	bool InitGLEW(HINSTANCE hInstance, WNDPROC funcCallback);

private:
	HWND* m_pHwnd;

	HDC m_hDC;
	HGLRC m_hRC;
	static bool m_bClassRegistered;
	static bool m_bGlewInitialised;
	int m_iMajorVer;
	int m_iMinorVer;

	int m_winWidth;
	int m_winHeight;

	CShader* m_pRefCurrentShader;			// A reference, do not handle cleanup here

	// Deferred rendering variables
	GLuint m_fbo;			// Frame buffer object
	GLuint m_gTextures[GBUFFER_NUM_TEXTURES];
	GLuint m_depthTexture;
};


#endif