#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ComponentManager.h"
#include "StageManager.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "MissileManager.h"
#include "BaseComponent.h"
#include "AssemblyScene.h"
#include "EffectManager.h"
#include "GameScene.h"
#include "TitleScene.h"

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
	releaseInputManagerInstance();
	releaseResourceManagerInstance();
	releaseComponentManagerInstance();
	releaseStageManagerInstance();
	releaseUIManagerInstance();
	releaseSoundManagerInstance();
	releaseMissileManagerInstance();
	releaseEffectManagerInstance();
}
CREATE_SINGLETON_FUNC(UIManager)
CREATE_SINGLETON_FUNC(DataManager)
CREATE_SINGLETON_FUNC(InputManager)
CREATE_SINGLETON_FUNC(ResourceManager)
CREATE_SINGLETON_FUNC(ComponentManager)
CREATE_SINGLETON_FUNC(StageManager)
CREATE_SINGLETON_FUNC(SoundManager)
CREATE_SINGLETON_FUNC(MissileManager)
CREATE_SINGLETON_FUNC(EffectManager)

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

void GameManager::changeScene(SceneType sType)
{
	auto director = cocos2d::Director::getInstance();
	m_CurrentScene = getScene(sType);
	m_CurrentSceneType = sType;
	if(director->getRunningScene())
	{
		director->replaceScene(m_CurrentScene);
	}
	else
	{
		director->runWithScene(m_CurrentScene);
	}
}

cocos2d::Scene* GameManager::getScene(SceneType sType)
{
	cocos2d::Scene* scene = nullptr;
	switch(sType)
	{
		case TITLE_SCENE:
			GET_SOUND_MANAGER()->createBGM(SoundManager::BGM_CALLTOADVANTURE, true);
			if(sType != m_CurrentSceneType)
				scene = TitleScene::createScene();
			else
				scene = m_CurrentScene;
			break;
		case LOADING_SCENE:
			break;
		case ASSEMBLY_SCENE:
			GET_SOUND_MANAGER()->createBGM(SoundManager::BGM_FIVEARMIES, true);
			if(sType != m_CurrentSceneType)
				scene = AssemblyScene::createScene();
			else
				scene = m_CurrentScene;
			break;
		case GAME_SCENE:
			GET_SOUND_MANAGER()->createBGM(SoundManager::BGM_2, true);
			if(sType != m_CurrentSceneType)
				scene = GameScene::createScene();
			else
				scene = m_CurrentScene;
			break;
		default:
			break;
	}
	return scene;
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

int GameManager::getMicroSecondTime()
{
	timeval nowTime;

	cocos2d::gettimeofday(&nowTime, nullptr);

	return  nowTime.tv_usec / 1000 + nowTime.tv_sec * 1000;
}

