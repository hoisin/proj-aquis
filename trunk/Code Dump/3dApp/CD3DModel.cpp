#include "CD3DModel.h"
#include "CD3DBase.h"
#include "ErrorCodes.h"

CD3DModel::CD3DModel(void) :
	m_pVertexBuffer(NULL),
	m_pIndexBuffer(NULL),
	m_pTexture(NULL),
	m_vertexCount(0),
	m_indexCount(0)
{
}


CD3DModel::CD3DModel(const CD3DModel& other) :
	m_pVertexBuffer(NULL),
	m_pIndexBuffer(NULL),
	m_pTexture(NULL),
	m_vertexCount(0),
	m_indexCount(0)
{
	// For now don't do anything but same as default c'tor
}


CD3DModel::~CD3DModel(void)
{
	ShutDown();
}


/*
	Inits stuff...
*/
int CD3DModel::Initialise(ID3D11Buffer* pVertexBuffer, int vertCount, ID3D11Buffer* pIndexBuffer, int indexCount, ID3D11ShaderResourceView* pTextureRes, 
	EVertexType type, const std::string& modelName)
{
	// User friendly ID for reference
	m_name = modelName;
	m_vertType = type;

	int errorCode = ERROR_PASS;

	if(pVertexBuffer == NULL || pIndexBuffer == NULL || vertCount <= 0 || indexCount <= 0)
	{
		errorCode = ERROR_GFX_MODEL_INIT;
	}
	else
	{
		m_pVertexBuffer = pVertexBuffer;
		m_pIndexBuffer = pIndexBuffer;
		m_pTexture = pTextureRes;
		m_vertexCount = vertCount;
		m_indexCount = indexCount;
	}

	return errorCode;
}


void CD3DModel::ShutDown(void)
{

}


void CD3DModel::Render(CD3DBase* pD3d)
{
	VRenderBuffers(pD3d->GetContext());
}


void CD3DModel::VRenderBuffers(ID3D11DeviceContext* pContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = GetSizeOfVertexType(m_vertType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

