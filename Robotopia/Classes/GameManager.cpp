#include "GameManager.h"
#include "DataManager.h"
#include "TriggerManager.h"

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
	SAFE_DELETE(m_Instance);
}

Arthas::GameManager::GameManager()
{
	m_DataManagerInstance = nullptr;
	m_TriggerManagerInstance = nullptr;
}

Arthas::GameManager::~GameManager()
{
	releaseDataManagerInstance();
	releaseTriggerManagerInstance();
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
	SAFE_DELETE(m_DataManagerInstance);
}

Arthas::TriggerManager* Arthas::GameManager::getTriggerManagerInstance()
{
	if (m_TriggerManagerInstance == nullptr)
	{
		m_TriggerManagerInstance = new Arthas::TriggerManager();
		m_TriggerManagerInstance->init();
	}
	return m_TriggerManagerInstance;
}

void Arthas::GameManager::releaseTriggerManagerInstance()
{
	SAFE_DELETE(m_TriggerManagerInstance);
}

