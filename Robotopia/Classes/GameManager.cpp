#include "GameManager.h"
#include "DataManager.h"

Arthas::GameManager* Arthas::GameManager::m_Instance = nullptr;


Arthas::GameManager* Arthas::GameManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new Arthas::GameManager();
	}
	return m_Instance;
}

void Arthas::GameManager::releaseInstance()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

Arthas::GameManager::GameManager()
{
	m_DataManagerInstance = nullptr;
}

Arthas::GameManager::~GameManager()
{
	releaseDataManagerInstance();
}

Arthas::DataManager* Arthas::GameManager::getDataManagerInstance()
{
	if (m_DataManagerInstance == nullptr)
	{
		m_DataManagerInstance = new Arthas::DataManager();
		m_DataManagerInstance->init();
	}
	return m_DataManagerInstance;
}

void Arthas::GameManager::releaseDataManagerInstance()
{
	if (m_DataManagerInstance != nullptr)
	{
		delete m_DataManagerInstance;
		m_DataManagerInstance = nullptr;
	}
}

