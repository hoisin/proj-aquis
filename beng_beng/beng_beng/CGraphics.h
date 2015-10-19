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

#include <string>
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

class CMeshDataManager;
class CBufferManager;
class CTextureManager;
class CShaderManager;
class CMeshManager;
class CSceneLoader;
class CMaterialManager;

class CGraphics
{
public:
	CGraphics();
	~CGraphics();

	bool Initialise(HINSTANCE hInstance, HWND* hwnd, int majorVer, int minorVer, 
		UINT windowWidth, UINT windowHeight, WNDPROC funcCallback, bool b2DMode = FALSE);

	bool RenderScene();

	void RenderForward();
	void RenderDeferred();	// Not used yet...

	void ShutDown();

	// 2D drawing, only available when in 2D mode
	void Draw2DSprite(glm::vec2 pos);

	glm::vec3 GetMeshPosition(const std::string& meshID);
	void SetMeshPosition(const std::string& meshID, const glm::vec3& newPos);

	// Temporary test method for general loading stuff.....
	void LoadScene();
	void SetWireFrame(bool bWireFrame);

	// Temporary camera get function
	CCameraFPS* GetCamera() { return pCam; }

protected:
	HINSTANCE m_hInstance;
	COpenGL *m_pOpenGL;
	
	CMeshDataManager* m_pMeshDataMgr;
	CBufferManager* m_pBufferMgr;
	CTextureManager* m_pTextureMgr;
	CShaderManager* m_pShaderMgr;
	CMeshManager*	m_pMeshMgr;
	CSceneLoader*	m_pSceneLoader;
	CMaterialManager* m_pMaterialMgr;

	int m_winWidth, m_winHeight;

	bool m_bDeferred;

	bool m_bWireFrame;

	// Test vars
	CCameraFPS* pCam;
};

#endif