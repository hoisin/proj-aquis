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
#include <glm\gtc\matrix_transform.hpp>

class COpenGL;
class CResourceManager;
class CVertexBuffer;
class CIndexBuffer;
class CShader;
class CTexture2D;
class CCameraFPS;
class CSubMesh;

class CGraphics
{
public:
	CGraphics();
	~CGraphics();

	bool Initialise(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, CResourceManager *pResourceMgr,
		UINT windowWidth, UINT windowHeight, WNDPROC funcCallback);

	bool RenderScene();

	void ShutDown();

	// Temporary test method for general loading stuff.....
	void LoadScene();
	void SetWireFrame(bool bWireFrame);

	// Temporary camera get function
	CCameraFPS* GetCamera() { return pCam; }

protected:
	HINSTANCE m_hInstance;
	COpenGL *m_pOpenGL;
	CResourceManager *m_pResourceMgr;		// Don't delete/clean up this, its done else where

	int m_winWidth, m_winHeight;

	bool m_bWireFrame;


	// Test vars
	CVertexBuffer *pVert;
	CIndexBuffer *pIdx;
	CShader* pShader;
	CTexture2D* pTex;
	CCameraFPS* pCam;

	// Resource manager handles clean up
	CSubMesh* pModels[1000];
};

#endif