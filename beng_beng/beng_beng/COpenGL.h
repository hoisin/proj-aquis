//--------------------------------------------------------------------------
//
//	20/03/2014
//
//	Class managing OpenGL stuff.....
//
//	This class should handle OpenGL specific setup & call related to drawing.
//	Should not contain model/vertex data.
//
//	Author: SeaFooD © 2014
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
	COpenGL();
	~COpenGL();

	bool InitOpenGL(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, WNDPROC funcCallback);

	void ResizeOpenGLViewportFull();

	void ReleaseOpenGLControl();

	static void RegisterOpenGLClass(HINSTANCE hInstance, WNDPROC funcCallback);
	static void UnregisterOpenGLClass(HINSTANCE hInstance);

	void SetCurrentShader(CShader* pNewShader);
	void SetShaderParam(EShaderParamType type, char* paramID, void* pData, UINT count = 1, bool bTranspose = false);
	CShader* GetCurrentShader() { return m_pRefCurrentShader; }

	void BeginDraw();
	void EndDraw();

	void RenderBuffer(CVertexBuffer* pVertBuffer, CIndexBuffer* pIndexBuffer);

	void MakeCurrent();
	void ClearScreen();
	void SwapBuffersM();

private:
	bool InitGLEW(HINSTANCE hInstance, WNDPROC funcCallback);

private:
	HWND* m_pHwnd;

	HDC m_hDC;
	HGLRC m_hRC;
	static bool m_bClassRegistered;
	static bool m_bGlewInitialised;
	int m_iMajorVer, m_iMinorVer;

	CShader* m_pRefCurrentShader;			// A reference, do not handle cleanup here
};


#endif