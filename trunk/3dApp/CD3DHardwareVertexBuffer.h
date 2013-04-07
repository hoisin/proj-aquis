/*
	Direct11 buffer for storing vertex data
*/

#ifndef __CD3DHARDWAREVERTEXBUFFER_H__
#define __CD3DHARDWAREVERTEXBUFFER_H__

#include <d3d11>
#include "GfxDefs.h"


class CD3DHardwareVertexBuffer
{
public:
	CD3DHardwareVertexBuffer(ID3D11Device* pDevice, unsigned int bufferSize,
		);
	virtual ~CD3DHardwareVertexBuffer(void);

protected:
	CD3D11Buffer* m_pVertexBuffer;
};


#endif