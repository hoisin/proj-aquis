#include "CD3DBase.h"

CD3DBase::CD3DBase(void) :
	m_pWICFactory(NULL),
	m_pDevice(NULL),
	m_pDeviceContext(NULL),
	m_pSwapChain(NULL),
	m_pD3dRenderTargetView(NULL),
	m_pD3dDepthStencilView(NULL),
	m_pDepthStencilBuffer(NULL),
	m_pDepthStencilState(NULL),
	m_pMatrixStack(NULL),
	m_renderTargetWidth(0),
	m_renderTargetHeight(0),
	m_bWindowSizeChangeInProgress(false),
	m_bVSync(false),
	m_bWireFrame(false),
	m_bFullScreen(false),
	m_bEnable4xMssa(false)
{
}


CD3DBase::~CD3DBase(void)
{
	ShutDown();
}


bool CD3DBase::Initialise(HWND hwnd, int screenHeight, int screenWidth, bool bVSync, bool bFullScreen, 
	float screenDepth, float screenNear)
{
	m_hwnd = hwnd;
	m_bVSync = bVSync;
	m_bFullScreen = bFullScreen;
	m_renderTargetWidth = screenWidth;
	m_renderTargetHeight = screenHeight;

	if(!CreateDeviceIndependentResources())
		return false;

	if(!CreateDeviceResources())
		return false;

	if(!CreateWindowSizeDependentResources())
		return false;

	return true;
}


/*
	Everything in here can be created without any dependence on the device.
*/
bool CD3DBase::CreateDeviceIndependentResources(void)
{
	//Create matrix stack
	m_pMatrixStack = new CD3DMatrixStack;

	CoInitialize(NULL);

	// Create WIC factory
	HRESULT result = CoCreateInstance(CLSID_WICImagingFactory1,
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWICImagingFactory),
		(LPVOID*)&m_pWICFactory);

	if(FAILED(result))
		return false;

	return true;
}


bool CD3DBase::CreateWindowSizeDependentResources(void)
{
	//Get current window 
	RECT winRect;
	GetClientRect(m_hwnd, &winRect);

	//Store the window bounds so the next time we get a SizeChanged event we can
    //avoid rebuilding everything if the size is identical.
    m_windowBounds = winRect;

	//For checking function return calls
	HRESULT result;

    if (m_pSwapChain != NULL)
    {
        //If the swap chain already exists, resize it.
        HRESULT hr = m_pSwapChain->ResizeBuffers(2, 0, 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED)
        {
            // If the device was removed for any reason, a new device and swapchain will need to be created.
            HandleDeviceLost();

            //Everything is set up now. Do not continue execution of this method.
            return true;
        }
        else
			return false;
    }
    else
    {
        // Otherwise, create a new one using the same adapter as the existing Direct3D device.
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};

		//Buffer description
		swapChainDesc.BufferDesc.Width = (winRect.right - winRect.left);			//Same as window
		swapChainDesc.BufferDesc.Height = (winRect.bottom - winRect.top);
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				//This is the most common swap chain format.
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;						//60Hz refresh rate
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		//Check m4xMsaa support
		UINT m4xMsaaQuality;
		m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);

		if(m4xMsaaQuality <= 0)
			m_bEnable4xMssa = false;

		if(m_bEnable4xMssa)
		{
			swapChainDesc.SampleDesc.Count = 4;
			swapChainDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
		}
		else	//No MSAA
		{
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
		}

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;									// Use double-buffering to minimize latency.
		swapChainDesc.OutputWindow = m_hwnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;			//Can't use multisampling with other settings
        swapChainDesc.Flags = 0;

		IDXGIDevice* pDxgiDevice = 0;

		result = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDxgiDevice);

		if(FAILED(result))
			return false;

		IDXGIAdapter* pDxgiAdapter = 0;

		result = pDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pDxgiAdapter);

		if(FAILED(result))
			return false;

		IDXGIFactory* pDxgiFactory = 0;

		result = pDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pDxgiFactory);

		if(FAILED(result))
			return false;

		//Create the swap chain
		result = pDxgiFactory->CreateSwapChain(m_pDevice, &swapChainDesc, &m_pSwapChain);

		if(FAILED(result))
			return false;

		//Release all acquired COM interfaces
		pDxgiFactory->Release();
		pDxgiAdapter->Release();
		pDxgiDevice->Release();
    }

    //Create a Direct3D render target view of the swap chain back buffer.
    ID3D11Texture2D* pBackBuffer = 0;
	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));

	if(FAILED(result))
		return false;

	result = m_pDevice->CreateRenderTargetView(pBackBuffer, 0 , &m_pD3dRenderTargetView);

	if(FAILED(result))
	{
		pBackBuffer->Release();
		return false;
	}

    // Cache the rendertarget dimensions in our helper class for convenient use.
    D3D11_TEXTURE2D_DESC backBufferDesc = {0};
    pBackBuffer->GetDesc(&backBufferDesc);
    m_renderTargetWidth  = static_cast<float>(backBufferDesc.Width);
    m_renderTargetHeight = static_cast<float>(backBufferDesc.Height);

	//Release COM interface
	pBackBuffer->Release();

    //Create a depth stencil view for use with 3D rendering if needed.
    CD3D11_TEXTURE2D_DESC bufferDepthStencilDesc(
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        backBufferDesc.Width,
        backBufferDesc.Height,
        1,
        1,
        D3D11_BIND_DEPTH_STENCIL
        );

	result = m_pDevice->CreateTexture2D(
		&bufferDepthStencilDesc,
		nullptr,
		&m_pDepthStencilBuffer
		);

	if(FAILED(result))
	{
		m_pDepthStencilBuffer->Release();
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);

	if(FAILED(result))
		return false;

	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState,1);

	result = m_pDevice->CreateDepthStencilView(
		m_pDepthStencilBuffer,
		NULL,
		&m_pD3dDepthStencilView
		);

	if(FAILED(result))
	{
		m_pDepthStencilBuffer->Release();
		return false;
	}
	
	m_pDeviceContext->OMSetRenderTargets(1, &m_pD3dRenderTargetView, m_pD3dDepthStencilView);

	// Create raster state for solid mode
	D3D11_RASTERIZER_DESC rasterDesc;

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	ID3D11RasterizerState* pRasterState;

	// Create the rasterizer state from the description we just filled out.
	result = m_pDevice->CreateRasterizerState(&rasterDesc, &pRasterState);
	m_vpRasterState.push_back(pRasterState);

	if(FAILED(result))
		return false;

	// Create ratester state for wireframe mode
	rasterDesc.FillMode = D3D11_FILL_WIREFRAME;

	// Create the rasterizer state from the description we just filled out.
	result = m_pDevice->CreateRasterizerState(&rasterDesc, &pRasterState);
	m_vpRasterState.push_back(pRasterState);

	if(FAILED(result))
		return false;
	
	// Now set the rasterizer state using solid mode
	m_pDeviceContext->RSSetState(m_vpRasterState[0]);

	 // Set the 3D rendering viewport to target the entire window.
    CD3D11_VIEWPORT viewport(
        0.0f,
        0.0f,
        static_cast<float>(backBufferDesc.Width),
        static_cast<float>(backBufferDesc.Height)
        );

    m_pDeviceContext->RSSetViewports(1, &viewport);

	return true;
}
	
/*
	Creation of device resources which require dependent on the device.
	(i.e. Needs a instance of a device created)
*/
bool CD3DBase::CreateDeviceResources(void)
{
	//This flag adds support for surfaces with a different color channel ordering
    //than the API default. It is required for compatibility with Direct2D.
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_SINGLETHREADED;

#if defined(_DEBUG)
    //If the project is in a debug build, enable debugging via SDK Layers with this flag.
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    //This array defines the set of DirectX hardware feature levels this app will support.
    //Note the ordering should be preserved.
    //Don't forget to declare your application's minimum required feature level in its
    //description.  All applications are assumed to support 9.1 unless otherwise stated.
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        //D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };

	HRESULT result;

    //Create the Direct3D 11 API device object and a corresponding context.
    result = D3D11CreateDevice(
            nullptr,                    //Specify nullptr to use the default adapter.
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            creationFlags,              //Set debug and Direct2D compatibility flags.
            featureLevels,              //List of feature levels this app can support.
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,          //Always set this to D3D11_SDK_VERSION for Metro style apps.
            &m_pDevice,                 //Returns the Direct3D device created.
            &m_featureLevel,            //Returns feature level of device created.
            &m_pDeviceContext           //Returns the device immediate context.
            );
       
	if(FAILED(result))
		return false;

    if(m_pDevice == NULL)
		return false;

	if(m_pDeviceContext == NULL)
		return false;


	return true;
}


void CD3DBase::HandleDeviceLost(void)
{
	// Reset these member variables to ensure that SetDpi recreates all resources.
	m_windowBounds.left = 0;
	m_windowBounds.right = 0;
	m_windowBounds.top = 0;
	m_windowBounds.bottom = 0;

    m_pSwapChain = nullptr;

    CreateDeviceResources();
}


void CD3DBase::UpdateForWindowSizeChange(void)
{
	//Get current window 
	RECT winRect;
	GetClientRect(m_hwnd, &winRect);

	//Check if there has been a window resize
	if( (m_windowBounds.right - m_windowBounds.left) != (winRect.right - winRect.left) ||	//Width compare
		(m_windowBounds.bottom - m_windowBounds.top) != (winRect.bottom - winRect.top) )
	{
		m_pD3dRenderTargetView = nullptr;
		m_pD3dDepthStencilView = nullptr;

		m_bWindowSizeChangeInProgress = true;

		CreateWindowSizeDependentResources();
	}
}


void CD3DBase::BeginDraw(float red, float green, float blue, float alpha)
{
	float bgColour[4] = { red, green, blue, alpha };

	// Clear render target
	m_pDeviceContext->ClearRenderTargetView(m_pD3dRenderTargetView, bgColour);

	// Clear the depth buffer.
	m_pDeviceContext->ClearDepthStencilView(m_pD3dDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}


void CD3DBase::EndDraw(void)
{
	if(m_bVSync)
		m_pSwapChain->Present(1, 0);
	else
		// Present as fast as possible.
		m_pSwapChain->Present(0, 0);
}


void CD3DBase::SetWireFrameMode(bool bWireframe)
{
	if(bWireframe)
	{
		m_pDeviceContext->RSSetState(m_vpRasterState[1]);
	}
	else
	{
		m_pDeviceContext->RSSetState(m_vpRasterState[0]);
	}
}


ID3D11Device* CD3DBase::GetDevice(void)
{
	return m_pDevice;
}


ID3D11DeviceContext* CD3DBase::GetContext(void)
{
	return m_pDeviceContext;
}


CD3DMatrixStack* CD3DBase::GetMatrixStack(void)
{
	return m_pMatrixStack;
}


void CD3DBase::ShutDown(void)
{
	//Release device then object
	if(m_pMatrixStack)
		delete m_pMatrixStack;

	if(m_pDepthStencilState)
		m_pDepthStencilState->Release();

	if(m_pDepthStencilBuffer)
		m_pDepthStencilBuffer->Release();

	if(m_pD3dDepthStencilView)
		m_pD3dDepthStencilView->Release();

	if(m_pD3dRenderTargetView)
		m_pD3dRenderTargetView->Release();

	for(int i = 0; i < (int)m_vpRasterState.size(); i++)
	{
		if(m_vpRasterState[i])
			m_vpRasterState[i]->Release();

		m_vpRasterState[i] = NULL;
	}

	if(m_pSwapChain)
		m_pSwapChain->Release();

	if(m_pDeviceContext)
		m_pDeviceContext->Release();

	if(m_pDevice)
		m_pDevice->Release();

	if(m_pWICFactory)
		m_pWICFactory->Release();

	m_pMatrixStack = NULL;
	m_pDepthStencilState = NULL;
	m_pDepthStencilBuffer = NULL;
	m_pD3dDepthStencilView = NULL;
	m_pD3dRenderTargetView = NULL;
	m_pSwapChain = NULL;
	m_pDeviceContext = NULL;
	m_pDevice = NULL;
	m_pWICFactory = NULL;
}