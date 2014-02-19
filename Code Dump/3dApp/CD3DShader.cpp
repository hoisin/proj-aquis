#include "CD3DShader.h"
#include "ErrorCodes.h"

CD3DShader::CD3DShader(void) : m_pVertexShader(NULL),
	m_pPixelShader(NULL),
	m_pLayout(NULL),
	m_pMatrixBuffer(NULL),
	m_sampleState(NULL)
{
}


CD3DShader::~CD3DShader(void)
{
	ShutDown();
}


int CD3DShader::Initialize(ID3D11Device* pDevice, EVertexType vertexType, const D3D11_SAMPLER_DESC& samplerDesc, const std::string& shaderName, const std::string& fileVertexShader, 
		const std::string& vertexShaderEntry, const std::string& vertexShaderTarget, const std::string& filePixelShader, const std::string& pixelShaderEntry, const std::string& pixelShaderTarget)
{
	m_name = shaderName;
	int errorCode =  VInitializeShader(pDevice, vertexType, samplerDesc, fileVertexShader, vertexShaderEntry, vertexShaderTarget, filePixelShader, pixelShaderEntry, pixelShaderTarget);
	
	if( !SUCCESS(errorCode) )
		return errorCode;

	return ERROR_PASS;
}


void CD3DShader::ShutDown()
{
	VShutDownShader();
}


int CD3DShader::Render(ID3D11DeviceContext* pContext, int indexCount, ShaderBaseParams* pParams)
{
	// Set the shader parameters that it will use for rendering.
	int errorCode = ERROR_FAIL;

	errorCode = VSetShaderParameters(pContext, pParams);

	if( !SUCCESS(errorCode) )
		return errorCode;

	// Now render the prepared buffers with the shader.
	VRenderShader(pContext, indexCount);

	return ERROR_PASS;
}


std::string CD3DShader::GetName(void)
{
	return m_name;
}


EVertexType CD3DShader::GetVertexType(void)
{
	return m_vertexType;
}


int CD3DShader::VInitializeShader(ID3D11Device* pDevice, EVertexType vertexType, const D3D11_SAMPLER_DESC& samplerDesc, const std::string& fileVertexShader, 
		const std::string& vertexShaderEntry, const std::string& vertexShaderTarget, const std::string& filePixelShader, const std::string& pixelShaderEntry, const std::string& pixelShaderTarget)
{
	ID3DBlob* errorMessage = NULL;
	ID3DBlob* vertexShaderBuffer = NULL;
	ID3DBlob* pixelShaderBuffer = NULL;
	D3D11_INPUT_ELEMENT_DESC* pPolygonLayout = NULL;
	D3D11_BUFFER_DESC matrixBufferDesc;

	m_vertexType = vertexType;

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Probably don't need the define
	const D3D_SHADER_MACRO defines[] = {"EXAMPLE_DEFINE", "1", NULL, NULL};

	// Flags
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	// Convert to wide string
	std::wstring wFileVertexShader = std::wstring(fileVertexShader.begin(), fileVertexShader.end());

	// Compile the vertex shader code.
	HRESULT result = D3DCompileFromFile(wFileVertexShader.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, vertexShaderEntry.c_str(), vertexShaderTarget.c_str(), flags, 0,
				       &vertexShaderBuffer, &errorMessage);

	if(FAILED(result))
		return ERROR_GFX_SHADER_INIT;
	
	std::wstring wFilePixelShader = std::wstring(filePixelShader.begin(), filePixelShader.end());

	// Compile the pixel shader code.
	result = D3DCompileFromFile(wFilePixelShader.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE, pixelShaderEntry.c_str(), pixelShaderTarget.c_str(), flags, 0, 
				       &pixelShaderBuffer, &errorMessage);

	if(FAILED(result))
		return ERROR_GFX_SHADER_INIT;

	// Create the vertex shader from the buffer.
	result = pDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_pVertexShader);

	if(FAILED(result))
		return ERROR_GFX_SHADER_INIT;
	

	// Create the pixel shader from the buffer.
	result = pDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader);

	if(FAILED(result))
		return ERROR_GFX_SHADER_INIT;
	

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	unsigned int numElements = 0;

	GetLayout(&pPolygonLayout, numElements, vertexType);

	// Create the vertex input layout.
	result = pDevice->CreateInputLayout(pPolygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), 
					   vertexShaderBuffer->GetBufferSize(), &m_pLayout);

	if(FAILED(result))
		return ERROR_GFX_SHADER_INIT;

	if(pPolygonLayout)
		delete [] pPolygonLayout;

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = NULL;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = NULL;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferTypeWVP);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = pDevice->CreateBuffer(&matrixBufferDesc, NULL, &m_pMatrixBuffer);
	
	if(FAILED(result))
		return ERROR_GFX_SHADER_INIT;
	
	// Create the texture sampler state.
	result = pDevice->CreateSamplerState(&samplerDesc, &m_sampleState);

	if(FAILED(result))
		return ERROR_GFX_SHADER_INIT;

	//if(vertexType == eVertexPNT)
	//{
	//	D3D11_BUFFER_DESC lightBufferDesc;

	//	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	//	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	//	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//	lightBufferDesc.ByteWidth = sizeof(LightBuffer);
	//	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//	lightBufferDesc.MiscFlags = 0;
	//	lightBufferDesc.StructureByteStride = 0;

	//	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	//	result = pDevice->CreateBuffer(&lightBufferDesc, NULL, &m_pLightBuffer);
	//	if(FAILED(result))
	//	{
	//		return false;
	//	}
	//}

	return ERROR_PASS;
}


void CD3DShader::VShutDownShader()
{
	if(m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = NULL;
	}

	// Release the matrix constant buffer.
	if(m_pMatrixBuffer)
	{
		m_pMatrixBuffer->Release();
		m_pMatrixBuffer = NULL;
	}

	// Release the layout.
	if(m_pLayout)
	{
		m_pLayout->Release();
		m_pLayout = NULL;
	}

	// Release the pixel shader.
	if(m_pPixelShader)
	{
		m_pPixelShader->Release();
		m_pPixelShader = NULL;
	}

	// Release the vertex shader.
	if(m_pVertexShader)
	{
		m_pVertexShader->Release();
		m_pVertexShader = NULL;
	}

	return;

}


int CD3DShader::VSetShaderParameters(ID3D11DeviceContext* pContext, ShaderBaseParams* pParams)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferTypeWVP* dataPtr;
	unsigned int bufferNumber;

	// Lock the constant buffer so it can be written to.
	HRESULT result = pContext->Map(m_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if(FAILED(result))
		return ERROR_GFX_SHADER_PARAMSET;
	
	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferTypeWVP*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = DirectX::XMMatrixTranspose(pParams->world);
	dataPtr->view = DirectX::XMMatrixTranspose(pParams->view);
	dataPtr->projection = DirectX::XMMatrixTranspose(pParams->projection);

	// Unlock the constant buffer.
	pContext->Unmap(m_pMatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	pContext->VSSetConstantBuffers(bufferNumber, 1, &m_pMatrixBuffer);

	switch(pParams->GetType())
	{
	case SHADERTEXTURE:
		ShaderTextureParams* pShaderParams;
		pShaderParams = (ShaderTextureParams*)pParams;

		pContext->PSSetShaderResources(0, 1, &pShaderParams->pTexture);
		break;

	//case SHADERLIGHTTEXTURE:
	//	LightBuffer* dataPtr2;
	//	ShaderLightTextureParams* pShaderLighTextureParams;
	//	pShaderLighTextureParams = (ShaderLightTextureParams*)pParams;

	//	pContext->PSSetShaderResources(0, 1, &pShaderLighTextureParams->pTexture);

	//	// Lock the light constant buffer so it can be written to.
	//	result = pContext->Map(m_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//	if(FAILED(result))
	//	{
	//		return false;
	//	}

	//	// Get a pointer to the data in the constant buffer.
	//	dataPtr2 = (LightBuffer*)mappedResource.pData;

	//	// Copy the lighting variables into the constant buffer.
	//	dataPtr2->lightColour = pShaderLighTextureParams->lightColour;
	//	dataPtr2->lightDir = pShaderLighTextureParams->lightDirection;
	//	dataPtr2->lightIntensity = pShaderLighTextureParams->lightIntensity;

	//	// Unlock the constant buffer.
	//	pContext->Unmap(m_pLightBuffer, 0);

	//	// Set the position of the light constant buffer in the pixel shader.
	//	bufferNumber = 0;

	//	// Finally set the light constant buffer in the pixel shader with the updated values.
	//	pContext->PSSetConstantBuffers(bufferNumber, 1, &m_pLightBuffer);
	//	break;

	default:
		// Undefined parameter type
		return ERROR_GFX_SHADER_PARAMSET;
		break;
	}

	return ERROR_PASS;
}


void CD3DShader::VRenderShader(ID3D11DeviceContext* pContext, int indexCount)
{
	// Set the vertex input layout.
	pContext->IASetInputLayout(m_pLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	pContext->VSSetShader(m_pVertexShader, NULL, 0);
	pContext->PSSetShader(m_pPixelShader, NULL, 0);

	pContext->PSSetSamplers(0, 1, &m_sampleState);

	// Render the triangle.
	pContext->DrawIndexed(indexCount, 0, 0);

	return;
}


void CD3DShader::GetLayout(D3D11_INPUT_ELEMENT_DESC** pLayout, unsigned int& numElements, EVertexType type)
{
	D3D11_INPUT_ELEMENT_DESC* pInput = NULL;

	switch(type)
	{
	case eVertexPC:
		pInput = new D3D11_INPUT_ELEMENT_DESC[2];
	
		pInput[0].SemanticName = "POSITION";
		pInput[0].SemanticIndex = 0;
		pInput[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		pInput[0].InputSlot = 0;
		pInput[0].AlignedByteOffset = 0;
		pInput[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInput[0].InstanceDataStepRate = 0;

		pInput[1].SemanticName = "COLOR";
		pInput[1].SemanticIndex = 0;
		pInput[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		pInput[1].InputSlot = 0;
		pInput[1].AlignedByteOffset = 12;
		pInput[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInput[1].InstanceDataStepRate = 0;

		numElements = 2;
		break;

	case eVertexPT:
		pInput = new D3D11_INPUT_ELEMENT_DESC[2];
	
		pInput[0].SemanticName = "POSITION";
		pInput[0].SemanticIndex = 0;
		pInput[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		pInput[0].InputSlot = 0;
		pInput[0].AlignedByteOffset = 0;
		pInput[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInput[0].InstanceDataStepRate = 0;

		pInput[1].SemanticName = "TEXCOORD";
		pInput[1].SemanticIndex = 0;
		pInput[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		pInput[1].InputSlot = 0;
		pInput[1].AlignedByteOffset = 12;
		pInput[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInput[1].InstanceDataStepRate = 0;

		numElements = 2;
		break;

	case eVertexPNT:
		pInput = new D3D11_INPUT_ELEMENT_DESC[3];

		pInput[0].SemanticName = "POSITION";
		pInput[0].SemanticIndex = 0;
		pInput[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		pInput[0].InputSlot = 0;
		pInput[0].AlignedByteOffset = 0;
		pInput[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInput[0].InstanceDataStepRate = 0;

		pInput[1].SemanticName = "NORMAL";
		pInput[1].SemanticIndex = 0;
		pInput[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		pInput[1].InputSlot = 0;
		pInput[1].AlignedByteOffset = 12;
		pInput[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInput[1].InstanceDataStepRate = 0;

		pInput[2].SemanticName = "TEXCOORD";
		pInput[2].SemanticIndex = 0;
		pInput[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		pInput[2].InputSlot = 0;
		pInput[2].AlignedByteOffset = 24;
		pInput[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInput[2].InstanceDataStepRate = 0;

		numElements = 3;
		break;

	default:
		break;
	}

	*pLayout = pInput;
}