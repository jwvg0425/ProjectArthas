﻿#include "GameManager.h"
#include "DataManager.h"
#include "TriggerManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ComponentManager.h"

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
	m_InputManagerInstance = nullptr;
	m_ResourceManagerInstance = nullptr;
	m_ComponentManagerInstance = nullptr;
}

Arthas::GameManager::~GameManager()
{
	releaseDataManagerInstance();
	releaseTriggerManagerInstance();
	releaseInputManagerInstance();
	releaseResourceManagerInstance();
	releaseComponentManagerInstance();
}

Arthas::DataManager* Arthas::GameManager::getDataManagerInstance()
{
	GET_SINGLETON_INSTANCE(DataManager);
}

void Arthas::GameManager::releaseDataManagerInstance()
{
	SAFE_DELETE(m_DataManagerInstance);
}

Arthas::TriggerManager* Arthas::GameManager::getTriggerManagerInstance()
{
	GET_SINGLETON_INSTANCE(TriggerManager);
}

void Arthas::GameManager::releaseTriggerManagerInstance()
{
	SAFE_DELETE(m_TriggerManagerInstance);
}

Arthas::InputManager* Arthas::GameManager::getInputManagerInstance()
{
	GET_SINGLETON_INSTANCE(InputManager);
}

void Arthas::GameManager::releaseInputManagerInstance()
{
	SAFE_DELETE(m_InputManagerInstance);
}

timeval Arthas::GameManager::getTime()
{
	timeval tv;
	
	cocos2d::gettimeofday(&tv, nullptr);

	return tv;
}

Arthas::ResourceManager* Arthas::GameManager::getResourceManagerInstance()
{
	GET_SINGLETON_INSTANCE(ResourceManager);
}

void Arthas::GameManager::releaseResourceManagerInstance()
{
	SAFE_DELETE(m_ResourceManagerInstance);
}

Arthas::ComponentManager* Arthas::GameManager::getComponentManagerInstance()
{
	GET_SINGLETON_INSTANCE(ComponentManager);
}

void Arthas::GameManager::releaseComponentManagerInstance()
{
	SAFE_DELETE(m_ComponentManagerInstance);
}

