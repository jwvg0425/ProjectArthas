#include "GameManager.h"
#include "DataManager.h"

GameManager* GameManager::m_Instance = nullptr;


GameManager* GameManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager();
	}
	return m_Instance;
}

void GameManager::releaseInstance()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

GameManager::GameManager()
{
	m_DataManagerInstance = nullptr;
}

GameManager::~GameManager()
{
	releaseDataManagerInstance();
}

DataManager* GameManager::getDataManagerInstance()
{
	if (m_DataManagerInstance == nullptr)
	{
		m_DataManagerInstance = new DataManager();
		m_DataManagerInstance->init();
	}
	return m_DataManagerInstance;
}

void GameManager::releaseDataManagerInstance()
{
	if (m_DataManagerInstance != nullptr)
	{
		delete m_DataManagerInstance;
		m_DataManagerInstance = nullptr;
	}
}

