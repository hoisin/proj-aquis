/*
	Class for managing buffers
*/

#ifndef __CBUFFERMANAGER_H__
#define __CBUFFERMANAGER_H__

#include <map>
#include <string>
#include "CD3DBase.h"

class CBufferManager
{
public:
	CBufferManager(void);
	~CBufferManager(void);

	int CreateVertexBuffer(ID3D11Device* pDevice, const std::string& nameID, int bufferSize, void* pData, ID3D11Buffer** outBuffer = NULL);
//	int CreateInstanceBuffer(ID3D11Device* pDevice, MeshData* pData, ID3D11Buffer** inBuffer);
	int CreateIndexBuffer(ID3D11Device* pDevice, const std::string& nameID, int bufferSize, void* pData,  ID3D11Buffer** outBuffer = NULL);

	ID3D11Buffer* GetVertexBuffer(const std::string& nameID);
	ID3D11Buffer* GetIndexBuffer(const std::string& nameID);

	void FreeVertexBuffer(const std::string &nameID);
	void FreeIndexBufffer(const std::string &nameID);

	void ClearVertexBuffers(void);
	void ClearIndexBuffers(void);

private:
	std::map<std::string, ID3D11Buffer*> m_vertexBuffers;
	//std::map<std::string, ID3D11Buffer*> m_instanceBuffers;
	std::map<std::string, ID3D11Buffer*> m_indexBuffers;
};

#endif