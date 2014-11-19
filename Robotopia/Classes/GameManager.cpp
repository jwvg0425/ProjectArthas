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
#include "MissileManager.h"
#include "BaseComponent.h"

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
	SAFE_DELETE(m_Instance);
}

GameManager::GameManager()
{
	m_DataManagerInstance = nullptr;
	m_TriggerManagerInstance = nullptr;
	m_InputManagerInstance = nullptr;
	m_ResourceManagerInstance = nullptr;
	m_ComponentManagerInstance = nullptr;
	m_StageManagerInstance = nullptr;
	m_UIManagerInstance = nullptr;
	m_SoundManagerInstance = nullptr;
	m_MissileManagerInstance = nullptr;

	m_CurrentSceneType = NONE_SCENE;
}

GameManager::~GameManager()
{
	releaseDataManagerInstance();
	releaseTriggerManagerInstance();
	releaseInputManagerInstance();
	releaseResourceManagerInstance();
	releaseComponentManagerInstance();
	releaseStageManagerInstance();
	releaseUIManagerInstance();
	releaseSoundManagerInstance();
	releaseMissileManagerInstance();
}

DataManager* GameManager::getDataManagerInstance()
{
	GET_SINGLETON_INSTANCE(DataManager);
}

void GameManager::releaseDataManagerInstance()
{
	SAFE_DELETE(m_DataManagerInstance);
}

TriggerManager* GameManager::getTriggerManagerInstance()
{
	GET_SINGLETON_INSTANCE(TriggerManager);
}

void GameManager::releaseTriggerManagerInstance()
{
	SAFE_DELETE(m_TriggerManagerInstance);
}

InputManager* GameManager::getInputManagerInstance()
{
	GET_SINGLETON_INSTANCE(InputManager);
}

void GameManager::releaseInputManagerInstance()
{
	SAFE_DELETE(m_InputManagerInstance);
}

timeval GameManager::getTime()
{
	timeval tv;
	
	cocos2d::gettimeofday(&tv, nullptr);

	return tv;
}

ResourceManager* GameManager::getResourceManagerInstance()
{
	GET_SINGLETON_INSTANCE(ResourceManager);
}

void GameManager::releaseResourceManagerInstance()
{
	SAFE_DELETE(m_ResourceManagerInstance);
}

ComponentManager* GameManager::getComponentManagerInstance()
{
	GET_SINGLETON_INSTANCE(ComponentManager);
}

void GameManager::releaseComponentManagerInstance()
{
	SAFE_DELETE(m_ComponentManagerInstance);
}

StageManager* GameManager::getStageManagerInstance()
{
	GET_SINGLETON_INSTANCE(StageManager);
}

void GameManager::releaseStageManagerInstance()
{
	SAFE_DELETE(m_StageManagerInstance);
}

UIManager* GameManager::getUIManagerInstance()
{
	//반드시 먼저 init 되어야 함.
	if (m_StageManagerInstance == nullptr)
	{
		GET_STAGE_MANAGER();
	}
	GET_SINGLETON_INSTANCE(UIManager);
}

void GameManager::releaseUIManagerInstance()
{
	SAFE_DELETE(m_UIManagerInstance);
}

SoundManager* GameManager::getSoundManagerInstance()
{
	GET_SINGLETON_INSTANCE(SoundManager);
}

void GameManager::releaseSoundManagerInstance()
{
	SAFE_DELETE(m_SoundManagerInstance);
}

SceneType GameManager::getCurrentSceneType()
{
	return m_CurrentSceneType;
}


void GameManager::changeScene(cocos2d::Scene* scene, SceneType sType)
{
	auto director = cocos2d::Director::getInstance();
	m_CurrentSceneType = sType;
	if(director->getRunningScene())
	{
		director->replaceScene(scene);
	}
	else
	{
		director->runWithScene(scene);
	}
}

MissileManager* GameManager::getMissileManagerInstance()
{
	GET_SINGLETON_INSTANCE(MissileManager);
}

void GameManager::releaseMissileManagerInstance()
{
	SAFE_DELETE(m_MissileManagerInstance);
}

bool GameManager::anyRay(cocos2d::PhysicsWorld& world, const cocos2d::PhysicsRayCastInfo& info, void* type)
{
	cocos2d::PhysicsBody* body = info.shape->getBody();

	*(int*)type = ((BaseComponent*)body->getNode())->getType();

	return false;
}

int GameManager::getContactComponentType(BaseComponent* target, cocos2d::Rect rect, Direction dir)
{
	const int FIRST = 0, MID = 1, LAST = 2, START = 0, END = 1;
	cocos2d::Point point[3][3];

	switch (dir)
	{
	case DIR_LEFT:
		point[FIRST][START] = cocos2d::Point(rect.origin.x - 1, rect.origin.y);
		point[FIRST][END] = cocos2d::Point(rect.origin.x - 3, rect.origin.y);
		point[MID][START] = cocos2d::Point(rect.origin.x - 1, rect.origin.y + rect.size.height / 2);
		point[MID][END] = cocos2d::Point(rect.origin.x - 3, rect.origin.y + rect.size.height / 2);
		point[LAST][START] = cocos2d::Point(rect.origin.x - 1, rect.origin.y + rect.size.height);
		point[LAST][END] = cocos2d::Point(rect.origin.x - 3, rect.origin.y + rect.size.height);
		break;
	case DIR_UP:
		point[FIRST][START] = cocos2d::Point(rect.origin.x, rect.origin.y + rect.size.height + 1);
		point[FIRST][END] = cocos2d::Point(rect.origin.x, rect.origin.y + rect.size.height + 3);
		point[MID][START] = cocos2d::Point(rect.origin.x + rect.size.width / 2, rect.origin.y + rect.size.height + 1);
		point[MID][END] = cocos2d::Point(rect.origin.x + rect.size.width / 2, rect.origin.y + rect.size.height + 3);
		point[LAST][START] = cocos2d::Point(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height + 1);
		point[LAST][END] = cocos2d::Point(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height + 3);
		break;
	case DIR_RIGHT:
		point[FIRST][START] = cocos2d::Point(rect.origin.x + rect.size.width + 1, rect.origin.y);
		point[FIRST][END] = cocos2d::Point(rect.origin.x + rect.size.width + 3, rect.origin.y);
		point[MID][START] = cocos2d::Point(rect.origin.x + rect.size.width + 1, rect.origin.y + rect.size.height / 2);
		point[MID][END] = cocos2d::Point(rect.origin.x + rect.size.width + 3, rect.origin.y + rect.size.height / 2);
		point[LAST][START] = cocos2d::Point(rect.origin.x + rect.size.width + 1, rect.origin.y + rect.size.height);
		point[LAST][END] = cocos2d::Point(rect.origin.x + rect.size.width + 3, rect.origin.y + rect.size.height);
		break;
	case DIR_DOWN:
		point[FIRST][START] = cocos2d::Point(rect.origin.x, rect.origin.y - 1);
		point[FIRST][END] = cocos2d::Point(rect.origin.x, rect.origin.y - 3);
		point[MID][START] = cocos2d::Point(rect.origin.x + rect.size.width / 2, rect.origin.y - 1);
		point[MID][END] = cocos2d::Point(rect.origin.x + rect.size.width / 2, rect.origin.y - 3);
		point[LAST][START] = cocos2d::Point(rect.origin.x + rect.size.width, rect.origin.y - 1);
		point[LAST][END] = cocos2d::Point(rect.origin.x + rect.size.width, rect.origin.y - 3);
		break;
	}

	int componentType = CT_NONE;

	for (int idx = FIRST; idx <= LAST; idx++)
	{
		int type;
		target->getScene()->getPhysicsWorld()->rayCast(CC_CALLBACK_3(GameManager::anyRay, this), point[idx][START], point[idx][END], &type);

		if (type == CT_NONE)
		{
			continue;
		}

		if (componentType == CT_NONE)
		{
			componentType = type;
		}
		else if(componentType != type)
		{
			componentType = MULTI_CONTACT;
		}
	}

	return componentType;
}
