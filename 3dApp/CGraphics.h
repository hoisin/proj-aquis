/*
	Date: 30/01/2013
	Implementation of graphics interface
*/

#pragma once
#ifndef __CGRAPHICS_H__
#define __CGRAPHICS_H__

#include "IGraphics.h"
#include "CD3DBase.h"

#include "CFPCamera.h"
#include "CGeometryGenerator.h"
#include "CD3DModelManager.h"
#include "CD3DShaderManager.h"

class CGraphics
{
protected:
	CD3DBase*				m_pD3d;						// Base Direct3D
	CD3DModelManager*		m_pD3dModelManager;			// Manager handling our models
	CD3DShaderManager*		m_pD3dShaderManager;		// Manager handling shaders
	CFPCamera* pCamera;
	CGeometryGenerator m_pGeoGenerator;

	int myModelID;
	int myShaderID;

public:
	CGraphics(void);
	~CGraphics(void);

	bool VInitialise(HWND hwnd, int screenHeight, int screenWidth, bool bVSync, bool bFullScreen, 
		float screenDepth, float screenNear);
	void VShutDown(void);

	bool VRenderScene(void);

	bool VLoadScene(void);

	void SetWireFrameMode(bool bWireFrame);

	CCamera* GetCamera(void);
};

#endif