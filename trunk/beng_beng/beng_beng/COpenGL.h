//--------------------------------------------------------------------------
//
//	20/03/2014
//
//	Class managing OpenGL stuff.....
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

	void RenderBuffer(CVertexBuffer* pVertBuffer, CIndexBuffer* pIndexBuffer);

	void MakeCurrent();
	void ClearScreen();
	void SwapBuffersM();

private:
	bool InitGLEW(HINSTANCE hInstance, WNDPROC funcCallback);

private:
	HDC m_hDC;
	HWND* m_pHwnd;
	HGLRC m_hRC;
	static bool m_bClassRegistered;
	static bool m_bGlewInitialised;
	int m_iMajorVer, m_iMinorVer;

};


#endif