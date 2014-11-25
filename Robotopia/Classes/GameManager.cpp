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

CREATE_SINGLETON_FUNC(DataManager)
CREATE_SINGLETON_FUNC(TriggerManager)
CREATE_SINGLETON_FUNC(InputManager)
CREATE_SINGLETON_FUNC(ResourceManager)
CREATE_SINGLETON_FUNC(ComponentManager)
CREATE_SINGLETON_FUNC(StageManager)
CREATE_SINGLETON_FUNC(SoundManager)
CREATE_SINGLETON_FUNC(MissileManager)

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


SceneType GameManager::getCurrentSceneType()
{
	return m_CurrentSceneType;
}

timeval GameManager::getTime()
{
	timeval tv;
	
	cocos2d::gettimeofday(&tv, nullptr);

	return tv;
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

int GameManager::getContactComponentType(BaseComponent* target, cocos2d::Rect rect, Direction dir)
{
	const int FIRST = 0, MID = 1, LAST = 2, START = 0, END = 1;
	cocos2d::Point point[3][3];
	int currentStage = GET_STAGE_MANAGER()->getStageNum();
	int currentRoom = GET_STAGE_MANAGER()->getRoomNum();

	auto roomData = GET_DATA_MANAGER()->getRoomData(currentStage, currentRoom);

	switch (dir)
	{
	case DIR_LEFT:
		point[FIRST][START] = cocos2d::Point(rect.origin.x - rect.size.width / 2 - 1, rect.origin.y - rect.size.height / 2 + 2);
		point[MID][START] = cocos2d::Point(rect.origin.x - rect.size.width / 2 - 1, rect.origin.y);
		point[LAST][START] = cocos2d::Point(rect.origin.x - rect.size.width / 2 - 1, rect.origin.y + rect.size.height / 2 - 2);
		break;
	case DIR_UP:
		point[FIRST][START] = cocos2d::Point(rect.origin.x - rect.size.width / 2 + 2, rect.origin.y + rect.size.height / 2 + 1);
		point[MID][START] = cocos2d::Point(rect.origin.x, rect.origin.y + rect.size.height / 2 + 1);
		point[LAST][START] = cocos2d::Point(rect.origin.x + rect.size.width / 2 - 2, rect.origin.y + rect.size.height / 2 + 1);
		break;
	case DIR_RIGHT:
		point[FIRST][START] = cocos2d::Point(rect.origin.x + rect.size.width / 2 + 1, rect.origin.y - rect.size.height / 2 + 2);
		point[MID][START] = cocos2d::Point(rect.origin.x + rect.size.width / 2 + 1, rect.origin.y);
		point[LAST][START] = cocos2d::Point(rect.origin.x + rect.size.width / 2 + 1, rect.origin.y + rect.size.height / 2 - 2);
		break;
	case DIR_DOWN:
		point[FIRST][START] = cocos2d::Point(rect.origin.x - rect.size.width / 2 + 2, rect.origin.y - rect.size.height / 2 - 1);
		point[MID][START] = cocos2d::Point(rect.origin.x, rect.origin.y - rect.size.height / 2 - 1);
		point[LAST][START] = cocos2d::Point(rect.origin.x + rect.size.width / 2 - 2, rect.origin.y - rect.size.height / 2 - 1);
		break;
	}

	int componentType = CT_NONE;

	for (int idx = FIRST; idx <= LAST; idx++)
	{
		int type = CT_NONE;

		type = GET_DATA_MANAGER()->getTileData(currentStage, currentRoom, point[idx][START]);

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
