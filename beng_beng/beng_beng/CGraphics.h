//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Main interface class for graphics
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CGRAPHICS_H__
#define __CGRAPHICS_H__

#include <Windows.h>

class COpenGL;

class CGraphics
{
public:
	CGraphics();
	~CGraphics();

	bool Initialise(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, WNDPROC funcCallback);

	bool RenderScene();

	void ShutDown();

	// Temporary test method for general loading stuff.....
	void LoadScene();

protected:
	HINSTANCE m_hInstance;
	COpenGL *m_pOpenGL;
};

#endif