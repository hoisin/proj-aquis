/*
	Date: 24/08/2012
	Author: Matthew Tsang

	Class handles the management of the D3D device, context, swap chain, etc etc.

	Forward rendering	- Going to use deferred, for now forward to get something working...
*/

#pragma once
#ifndef __CD3DBASE_H__
#define __CD3DBASE_H__

// Base stuff
#include <Windows.h>
#include <atlbase.h>

// WIC image stuff
#include <wincodec.h>

// Direct3D 11 Headers
#include <D3D11.h>

// Helper stuff
#include <DirectXMath.h>

#include "GfxDefs.h"

class CD3DBase
{
public:
	CD3DBase(void);
	virtual ~CD3DBase(void);

	// Performs D3DX initialisation and other sub systems
	int Initialise(HWND hwnd, int screenHeight, int screenWidth, bool bVSync, bool bFullScreen, 
		float screenDepth, float screenNear);

	// These should be private/protected
	int CreateDeviceIndependentResources(void);			// Create resources required that are independent of device
	int CreateWindowSizeDependentResources(void);		// Allocate memory resources that change on window resize
	int CreateDeviceResources(void);					// Create resources that are dependent on device

	// Probably don't need since D3D11 does not have the lost device concept
	void HandleDeviceLost();

	int UpdateForWindowSizeChange(void);

	// Clears screen & presents
	void BeginDraw(float red, float green, float blue, float alpha);
	void EndDraw(void);

	void SetWireFrameMode(bool bWireframe);

	// Get stuff
	ID3D11Device* GetDevice(void);
	ID3D11DeviceContext* GetContext(void);
	CD3DMatrixStack* GetMatrixStack(void);

	// Shutdown all systems used by the renderer and clear all objects in memory
	void ShutDown(void);

protected:
	HWND m_hwnd;			//Handle to the window

	// Makes image/texture loading easier
	IWICImagingFactory*				m_pWICFactory;

	// DirectX core objects required by 3D
	ID3D11Device*							m_pDevice;
	ID3D11DeviceContext*					m_pDeviceContext;
	IDXGISwapChain*							m_pSwapChain;
	ID3D11RenderTargetView*					m_pD3dRenderTargetView;
	std::vector<ID3D11RasterizerState*>		m_vpRasterState;

	// Direct3D Rendering Objects. Required for 3D.
    ID3D11DepthStencilView*			m_pD3dDepthStencilView;
	ID3D11Texture2D*				m_pDepthStencilBuffer;
	ID3D11DepthStencilState*		m_pDepthStencilState;

	// Matrix stack (will be useful for scenegraphs)
	CD3DMatrixStack*				m_pMatrixStack;

    // Cached renderer properties.
    D3D_FEATURE_LEVEL				m_featureLevel;
	RECT							m_windowBounds;
	unsigned int					m_renderTargetWidth;
	unsigned int					m_renderTargetHeight;
    bool							m_bWindowSizeChangeInProgress;		

	// Toggle vars
	bool							m_bVSync;
	bool							m_bWireFrame;	
	bool							m_bFullScreen;
	bool							m_bEnable4xMssa;
};

#endif