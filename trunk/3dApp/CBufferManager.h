/*
	Class for managing buffers
*/

#ifndef __CBUFFERMANAGER_H__
#define __CBUFFERMANAGER_H__

#include <vector>
#include <string>
#include "CD3DBase.h"

class CBufferManager
{
	struct SBufferInfo
	{
		std::string name;
		ID3D11Buffer* buffer;
	};

public:
	CBufferManager(void);
	~CBufferManager(void);

	int CreateVertexBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer);
	int CreateInstanceBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer);
	int CreateIndexBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer);

	void ShutDown(void);

private:
	std::vector<SBufferInfo> m_vertexBuffers;
	std::vector<SBufferInfo> m_instanceBuffers;
	std::vector<SBufferInfo> m_indexBuffers;
};

#endif