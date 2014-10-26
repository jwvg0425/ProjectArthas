#include "GameManager.h"

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

}

GameManager::~GameManager()
{

}

