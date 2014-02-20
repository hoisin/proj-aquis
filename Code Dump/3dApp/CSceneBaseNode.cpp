#include "CSceneBaseNode.h"

CSceneBaseNode::CSceneBaseNode(void)
{
}



CSceneBaseNode::~CSceneBaseNode(void)
{
}


//----------------------------------------------------------------------
//
//	Params:
//	pChile		-	pointer to child node
//
//	Description:
//	Attaches new scene node to current node
//
//----------------------------------------------------------------------
void CSceneBaseNode::VAddChild(CSceneBaseNode *pChild)
{
	m_nodeList.push_back(pChild);
}


//----------------------------------------------------------------------
//
//	Description:
//	Method called before VRender(...)
//
//----------------------------------------------------------------------
void CSceneBaseNode::VPreRender(void)
{
	// Inherited classes should overwrite with own behaviour
}


//----------------------------------------------------------------------
//
//	Description:
//	Method called after VPreRender(...)
//
//----------------------------------------------------------------------
void CSceneBaseNode::VRender(void)
{
	// Inherited classes should overwrite with own behaviour
}


//----------------------------------------------------------------------
//
//	Description:
//	Method called after VRender(...)
//
//----------------------------------------------------------------------
void CSceneBaseNode::VPostRender(void)
{
	// Inherited classes should overwrite with own behaviour
}


//----------------------------------------------------------------------
//
//	Description:
//	Returns the node type, inherited classes must overwrite with their
//		own type preferably
//
//----------------------------------------------------------------------
ESceneNodeType CSceneBaseNode::VGetNodeType(void)
{
	return eBaseNode;
}