#include "CSceneNode.h"


CSceneNode::CSceneNode()
{
}


CSceneNode::~CSceneNode()
{
	VShutDown();
}


void CSceneNode::VRender()
{
	VPreSceneRender();
	VSceneRender();
	VPostSceneRender();
}


void CSceneNode::VPreSceneRender()
{
	// Call children
	std::list<ISceneNode *>::iterator it;

	for(it = m_pChildList.begin(); it != m_pChildList.end(); it++)
		(*it)->VPreSceneRender();
}


void CSceneNode::VSceneRender()
{
	// Call children
	std::list<ISceneNode *>::iterator it;

	for(it = m_pChildList.begin(); it != m_pChildList.end(); it++)
		(*it)->VSceneRender();
}


void CSceneNode::VPostSceneRender()
{
	// Call children
	std::list<ISceneNode *>::iterator it;

	for(it = m_pChildList.begin(); it != m_pChildList.end(); it++)
		(*it)->VPostSceneRender();
}


void CSceneNode::VAddChild(ISceneNode *pNode)
{
	m_pChildList.push_back(pNode);
}


void CSceneNode::VShutDown()
{
	std::list<ISceneNode *>::iterator it;

	for(it = m_pChildList.begin(); it != m_pChildList.end(); it++) {
		if((*it))
			delete (*it);
	}

	m_pChildList.clear();
}