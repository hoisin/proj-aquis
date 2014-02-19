/*
	Direct11 buffer for storing index data
*/

#ifndef __CD3DINDEXEVERTEXBUFFER_H__
#define __CD3DINDEXEVERTEXBUFFER_H__

#include <d3d11>

class CD3DHardwareIndexBuffer
{
public:
	CD3DHardwareIndexBuffer(void);
	virtual ~CD3DHardwareIndexBuffer(void);

protected:
	CD3D11Buffer* m_pIndexBuffer;
};


#endif