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

	virtual void VRender() = 0;

	virtual void VPreSceneRender() = 0;
	virtual void VSceneRender() = 0;
	virtual void VPostSceneRender() = 0;

	virtual void VAddChild(ISceneNode *pNode) = 0;

	virtual void VShutDown() = 0;
	
};

#endif