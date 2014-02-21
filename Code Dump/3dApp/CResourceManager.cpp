#include "CResourceManager.h"

CResourceManager::CResourceManager(void) : m_pMeshDataManager(NULL), m_pBufferManager(NULL), m_pShaderTextureManager(NULL)
{
}


CResourceManager::~CResourceManager(void)
{
	ShutDown();
}


bool CResourceManager::Initialise(void)
{
	m_pMeshDataManager = new CMeshDataManager;
	m_pBufferManager = new CBufferManager;
	m_pShaderTextureManager = new CShaderTextureManager;

	return true;
}


CMeshDataManager* CResourceManager::GetMeshDataManager(void)
{
	return m_pMeshDataManager;
}


CBufferManager* CResourceManager::GetBufferManager(void)
{
	return m_pBufferManager;
}


CShaderTextureManager* CResourceManager::GetShaderTextureManager(void)
{
	return m_pShaderTextureManager;
}


void CResourceManager::ShutDown(void)
{
	if(m_pShaderTextureManager)
		delete m_pShaderTextureManager;

	if(m_pBufferManager)
		delete m_pBufferManager;

	if(m_pMeshDataManager)
		delete m_pMeshDataManager;

	m_pShaderTextureManager = NULL;
	m_pBufferManager = NULL;
	m_pMeshDataManager =  NULL;
}