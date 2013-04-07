#include "CGraphics.h"

CGraphics::CGraphics(void) : m_pD3d(NULL), m_pD3dModelManager(NULL), m_pD3dShaderManager(NULL)
{
}


CGraphics::~CGraphics(void)
{
	VShutDown();
}


bool CGraphics::VInitialise(HWND hwnd, int screenHeight, int screenWidth, bool bVSync, bool bFullScreen, 
		float screenDepth, float screenNear)
{
	// If not already initialised
	if(m_pD3d == NULL)
	{
		// Create new instance
		m_pD3d = new CD3DBase;

		// Return false if fail to initialise d3d class
		if(!m_pD3d->Initialise(hwnd, screenHeight, screenWidth, bVSync, bFullScreen, screenDepth, screenNear))
			return false;
	}

	pCamera = new CFPCamera;
	pCamera->SetProjection(DirectX::XM_PI/4.f, 800/600, 1, 1000);
	pCamera->SetPosition(5,105,-18.f);
	pCamera->SetViewDirection(0,0,1);
	pCamera->SetRight(1,0,0);
	pCamera->SetUp(0,1,0);
	pCamera->SetRotation(0,0,0);

	m_pD3dModelManager = new CD3DModelManager;

	MeshData* myMesh = m_pGeoGenerator.CreateSinPlane("cubeGeo", 2000, 200, eVertexPT, DirectX::XMFLOAT4(0, 1, 0, 1.0));

	myModelID = m_pD3dModelManager->AddD3DModel(m_pD3d, m_pGeoGenerator.CreateSinPlane("cubeGeo", 2000, 200, eVertexPT, DirectX::XMFLOAT4(0, 1, 0, 1.0)), "myCube", "Assets\\Graphics\\Textures\\brick.bmp");

	D3D11_SAMPLER_DESC samplerDesc;

	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	m_pD3dShaderManager = new CD3DShaderManager;
	myShaderID = m_pD3dShaderManager->AddD3DShader(m_pD3d->GetDevice(), eVertexPT, samplerDesc, "colourShader", 
		"Assets\\Graphics\\Shaders\\Texture.vs", "TextureVertexShader", "vs_5_0", "Assets\\Graphics\\Shaders\\Texture.ps", "TexturePixelShader", "ps_5_0");
		

	/*for(int i = 0; i < 200; i++)
	{
		test.push_back(DirectX::XMFLOAT3(((rand()%1000)-500),((rand()%1000)-500),((rand()%1000)-500)));
		test2.push_back( (rand()%360) * 0.0174532925f );
		test3.push_back( (rand()%360) * 0.0174532925f );
	}*/

	return true;
}


void CGraphics::VShutDown(void)
{
	// Clean up crap
	if(m_pD3dShaderManager)
		delete m_pD3dShaderManager;

	if(m_pD3dModelManager)
		delete m_pD3dModelManager;

	if(m_pD3d)
		delete m_pD3d;

	delete pCamera;
	
	m_pD3dShaderManager = NULL;
	m_pD3dModelManager = NULL;
	m_pD3d = NULL;
}


bool CGraphics::VRenderScene(void)
{
	m_pD3d->BeginDraw(0.4f, 0.4f, 0.2f, 1.0f);
	
	// Draw stuff here
	m_pD3dModelManager->GetD3DModel(myModelID)->Render(m_pD3d);

	ShaderTextureParams params;
	params.projection = DirectX::XMLoadFloat4x4(&pCamera->VGetProjMatrix());
	params.view =  DirectX::XMLoadFloat4x4(&pCamera->VGetViewMatrix());
	params.world = DirectX::XMMatrixIdentity();
	params.pTexture = m_pD3dModelManager->GetD3DModel(myModelID)->GetTexture();

	//for(int i = 0; i < test.size(); i++)
	{
		//params.world = DirectX::XMMatrixRotationRollPitchYaw(test3[i],test2[i],0) * DirectX::XMMatrixTranslation(test[i].x,test[i].y,test[i].z);
		//params.world = 

		// Don't render if model's vertex structure differs from shader's expected vertex structure.
		if(m_pD3dModelManager->GetD3DModel(myModelID)->GetVertexType() == m_pD3dShaderManager->GetD3DShader(myShaderID)->GetVertexType())
			m_pD3dShaderManager->GetD3DShader(myShaderID)->Render(m_pD3d->GetContext(), m_pD3dModelManager->GetD3DModel(myModelID)->GetIndexCount(), &params);
	}

	//params.world = DirectX::XMMatrixIdentity();

	//pShader->Render(m_pD3d->GetContext(), m_pD3dModelManager->GetD3DModel(myModelID)->GetIndexCount(), &params);

	m_pD3d->EndDraw();

	return true;
}


bool CGraphics::VLoadScene(void)
{
	return true;
}


void CGraphics::SetWireFrameMode(bool bWireFrameMode)
{
	m_pD3d->SetWireFrameMode(bWireFrameMode);
}


CCamera* CGraphics::GetCamera(void)
{
	return pCamera;
}