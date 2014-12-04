
#ifndef __CBUFFERMANAGER_H__
#define __CBUFFERMANAGER_H__

#include <map>
#include <string>
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CBufferManager
{
public:
	CBufferManager();
	~CBufferManager();

	CVertexBuffer* CreateVertexBuffer(const std::string &vertexID, MeshData *pData);
	CIndexBuffer* CreateIndexBuffer(const std::string& indexID, MeshData* pData);

	void RemoveVertexBuffer(const std::string& vertexID);
	void RemoveIndexBuffer(const std::string& indexID);

	void CleanUp();

private:
	std::map<std::string, CVertexBuffer*> m_vertexBufferMap;
	std::map<std::string, CIndexBuffer*> m_indexBufferMap;
};


#endif