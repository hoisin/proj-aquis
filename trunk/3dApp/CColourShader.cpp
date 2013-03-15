#include "CColourShader.h"


CColourShader::CColourShader(void) : m_pVertexShader(NULL),
	m_pPixelShader(NULL),
	m_pLayout(NULL),
	m_pMatrixBuffer(NULL)
{
}


CColourShader::~CColourShader(void)
{
	VShutDown();
}


bool CColourShader::VInitialize(ID3D11Device* pDevice, const std::string& fileVertexShader, 
	const std::string& filePixelShader)
{
	HRESULT result =  VInitializeShader(pDevice, fileVertexShader, filePixelShader);
	
	if(FAILED(result))
		return false;

	return true;
}


void CColourShader::VShutDown()
{
	VShutDownShader();
}


bool CColourShader::VRender(ID3D11DeviceContext* pContext, int indexCount, ShaderBaseParams* pParams)
{
	// Set the shader parameters that it will use for rendering.
	if(!VSetShaderParameters(pContext, pParams))
		return false;

	// Now render the prepared buffers with the shader.
	VRenderShader(pContext, indexCount);

	return true;
}


bool CColourShader::VInitializeShader(ID3D11Device* pDevice, const std::string& fileVertexShader, 
	const std::string& filePixelShader)
{
	HRESULT result;
	ID3DBlob* errorMessage;
	ID3DBlob* vertexShaderBuffer;
	ID3DBlob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	std::wstring wFileVertexShader = std::wstring(fileVertexShader.begin(), fileVertexShader.end());

	// Compile the vertex shader code.
	result = D3DCompileFromFile(wFileVertexShader.c_str(), NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
				       &vertexShaderBuffer, &errorMessage);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			//OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			//MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	std::wstring wFilePixelShader = std::wstring(filePixelShader.begin(), filePixelShader.end());

	// Compile the pixel shader code.
	result = D3DCompileFromFile(wFilePixelShader.c_str(), NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 
				       &pixelShaderBuffer, &errorMessage);

	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			//OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// If there was  nothing in the error message then it simply could not find the file itself.
		else
		{
			//MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	result = pDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_pVertexShader);
	if(FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer.
	result = pDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader);
	if(FAILED(result))
	{
		return false;
	}

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	// Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	result = pDevice->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), 
					   vertexShaderBuffer->GetBufferSize(), &m_pLayout);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

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
	{
		return false;
	}

	return true;
}


void CColourShader::VShutDownShader()
{
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


bool CColourShader::VSetShaderParameters(ID3D11DeviceContext* pContext, ShaderBaseParams* pParams)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferTypeWVP* dataPtr;
	unsigned int bufferNumber;

	// Lock the constant buffer so it can be written to.
	HRESULT result = pContext->Map(m_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if(FAILED(result))
		return false;
	
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

	// Finanly set the constant buffer in the vertex shader with the updated values.
	pContext->VSSetConstantBuffers(bufferNumber, 1, &m_pMatrixBuffer);

	return true;

}


void CColourShader::VRenderShader(ID3D11DeviceContext* pContext, int indexCount)
{
	// Set the vertex input layout.
	pContext->IASetInputLayout(m_pLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	pContext->VSSetShader(m_pVertexShader, NULL, 0);
	pContext->PSSetShader(m_pPixelShader, NULL, 0);

	// Render the triangle.
	pContext->DrawIndexed(indexCount, 0, 0);

	return;

}