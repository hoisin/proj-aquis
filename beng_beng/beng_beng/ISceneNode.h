//--------------------------------------------------------------------------
//
//	09/04/2014
//
//	Interface scene node class
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __ISCENENODE_H__
#define __ISCENENODE_H__

class ISceneNode
{
public:
	ISceneNode() {}
	virtual ~ISceneNode() {}

	virtual void VPreSceneRender() = 0;
	virtual void VSceneRender() = 0;
	virtual void VPostSceneRender() = 0;

	virtual void AddChild(ISceneNode *pNode) {}
};

#endif