#include "CModelBase.h"

CModelBase::CModelBase(void) :
	m_vertexBuffer(NULL),
	m_indexBuffer(NULL),
	m_pTexture(NULL),
	m_vertexCount(0),
	m_indexCount(0)
{
}


CModelBase::CModelBase(const CModelBase& other) :
	m_vertexBuffer(NULL),
	m_indexBuffer(NULL),
	m_pTexture(NULL),
	m_vertexCount(0),
	m_indexCount(0)
{
	// For now don't do anything but same as default c'tor
}


CModelBase::~CModelBase(void)
{
	VShutDown();
}


bool CModelBase::VInitialise(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string fileTextureName, const std::string fileModelName)
{
	// IMPORTANT! This must be called before initialising buffers!
	if(!VLoadModel(fileModelName))
		return false;

	// This is dependant on VLoadModel
	if(!VInitialiseBuffers(pDevice))
		return false;

	// Called last as its independant to the other two calls
	if(!VLoadTexture(pDevice, pContext, fileTextureName))
		return false;

	return true;
}


void CModelBase::VShutDown(void)
{
	VReleaseTexture();
	VShutDownBuffers();
}


void CModelBase::Render(ID3D11DeviceContext* pContext)
{
	VRenderBuffers(pContext);
}


ID3D11ShaderResourceView* CModelBase::GetTexture(void)
{
	return m_pTexture->GetTexture();
}


bool CModelBase::VInitialiseBuffers(ID3D11Device* pDevice)
{
	// Custom behaviour
	return true;
}


void CModelBase::VShutDownBuffers(void)
{
	if(m_indexBuffer)
		m_indexBuffer->Release();

	if(m_vertexBuffer)
		m_vertexBuffer->Release();

	m_indexBuffer = NULL;
	m_vertexBuffer = NULL;
}


void CModelBase::VRenderBuffers(ID3D11DeviceContext* pContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexTypePNT); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	pContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	pContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool CModelBase::VLoadModel(const std::string fileModelName)
{
	// Custom Behaviour
	return true;
}


bool CModelBase::VLoadTexture(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const std::string fileTextureName)
{
	// Custom behaviour
	return true;
}


void CModelBase::VReleaseTexture(void)
{
	if(m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = NULL;
	}
}