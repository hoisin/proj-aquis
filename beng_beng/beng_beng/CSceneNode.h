//--------------------------------------------------------------------------
//
//	09/04/2014
//
//	Base scene node class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CSCENENODE_H__
#define __CSCENENODE_H__

#include "ISceneNode.h"

#include <list>

class CSceneNode : public ISceneNode
{
public:
	CSceneNode();
	virtual ~CSceneNode();

	virtual void VRender();

	virtual void VPreSceneRender();
	virtual void VSceneRender();
	virtual void VPostSceneRender();

	void VAddChild(ISceneNode *pNode);

	virtual void VShutDown();

protected:
	std::list<ISceneNode *> m_pChildList;
};

#endif