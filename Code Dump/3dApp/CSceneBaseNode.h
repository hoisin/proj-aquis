/*
	Date: 20/02/2014
	Author: Matthew Tsang

	Base Scene node class.

	Subject to change....
*/

#ifndef __CSCENEBASENODE_H__
#define __CSCENEBASENODE_H__

#include <list>


// Enumerates for type of nodes
enum ESceneNodeType
{
	eBaseNode,			// Base node
	eCameraNode,		// Node containing a camera
	eModelNode,			// Node containing a drawable object
	eSceneTotalNode		
};

class CSceneBaseNode
{
protected:
	std::list<CSceneBaseNode *> m_nodeList;

public:
	CSceneBaseNode(void);
	virtual CSceneBaseNode(void);

	virtual void VAddChild(CSceneBaseNode *pChild);

	virtual void VPreRender(void);
	virtual void VRender(void);
	virtual void VPostRender(void);

	virtual ESceneNodeType VGetNodeType(void);
};


#endif