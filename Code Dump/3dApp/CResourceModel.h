//-------------------------------------------------------------------------
//
//	Date: 21/02/2014
//	Author: Matthew Tsang
//
//	Resource class holding a Model.
//
//	Debating over designs with regards to this resource type being needed.
//	This class is intended to hold the following data:
//		- vertex & index buffers
//		- size of vertex and index buffers
//		- mesh data
//		- texture?
//		- shader?
//
//	Initial design is that the CD3DModel class is to handle draw of the model &
//	reloading of vertex and index data if mesh data gets changed.
//	Also to potentially contain the shader and texture to use for rendering
//		(Although still debating on that since another solution could be used
//			i.e. scenegraph)
//
//-------------------------------------------------------------------------

#ifndef __CRESOURCEMODEL_H__
#define __CRESOURCEMODEL_H__

#include "IResource.h"

class CD3DModel;
class CResourceMeshData;
class CResourceVertexBuffer;
class CResourceIndexBuffer;

class CResourceModel : public IResource
{
protected:
	CD3DModel *m_pModel;

public:
	CResourceModel(CResourceMeshData *pInResMeshData, CResourceVertexBuffer *pInResVertBuf, 
		CResourceIndexBuffer *pInResIndexBuf);
	~CResourceModel(void);

	EResourceType VGetType(void);

	void VCleanUp(void);

	void* VGetData(void);
};


#endif