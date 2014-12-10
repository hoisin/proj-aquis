//--------------------------------------------------------------------------
//
//	16/05/2014
//
//	Simple N-Tree scene graph
//
//	Author: SeaFooD © 2014
//
//--------------------------------------------------------------------------

#ifndef __CSCENEGRAPH_H__
#define __CSCENEGRAPH_H__

class CSceneNode;

class CSceneGraph
{
public:
	CSceneGraph();
	~CSceneGraph();

protected:
	CSceneNode* m_pRoot;
};


#endif