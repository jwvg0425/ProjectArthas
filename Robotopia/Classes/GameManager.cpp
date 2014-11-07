#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"
#include "TriggerManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ComponentManager.h"
#include "StageManager.h"
#include "UIManager.h"
#include "SoundManager.h"

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
	m_StageManagerInstance = nullptr;
	m_UIManagerInstance = nullptr;
	m_SoundManagerInstance = nullptr;
}

Arthas::GameManager::~GameManager()
{
	releaseDataManagerInstance();
	releaseTriggerManagerInstance();
	releaseInputManagerInstance();
	releaseResourceManagerInstance();
	releaseComponentManagerInstance();
	releaseStageManagerInstance();
	releaseUIManagerInstance();
	releaseSoundManagerInstance();
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

Arthas::StageManager* Arthas::GameManager::getStageManagerInstance()
{
	GET_SINGLETON_INSTANCE(StageManager);
}

void Arthas::GameManager::releaseStageManagerInstance()
{
	SAFE_DELETE(m_StageManagerInstance);
}

Arthas::UIManager* Arthas::GameManager::getUIManagerInstance()
{
	GET_SINGLETON_INSTANCE(UIManager);
}

void Arthas::GameManager::releaseUIManagerInstance()
{
	SAFE_DELETE(m_UIManagerInstance);
}

Arthas::SoundManager* Arthas::GameManager::getSoundManagerInstance()
{
	GET_SINGLETON_INSTANCE(SoundManager);
}

void Arthas::GameManager::releaseSoundManagerInstance()
{
	SAFE_DELETE(m_SoundManagerInstance);
}

