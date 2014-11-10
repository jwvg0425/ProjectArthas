#include "pch.h"
#include "GameManager.h"
#include "StageManager.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"

Arthas::StageManager::StageManager()
{
	m_GameScene = nullptr;
	m_CurrentStageNum = -1;
}

Arthas::StageManager::~StageManager()
{
}

bool Arthas::StageManager::init()
{
	auto scene = GameScene::createScene();
	GET_GAME_MANAGER()->changeScene(scene, Arthas::SceneType::GAME_SCENE);
	m_GameScene = (Arthas::GameScene*)(scene->getChildByTag( GAME_SCENE_TAG ));
	m_GameScene->scheduleUpdate();
	return true;
}

void Arthas::StageManager::initStage( int stageNum )
{
	m_CurrentStageNum = stageNum;
	m_GameScene->getGameLayer()->initGameLayer(stageNum);
}

const Arthas::Player* Arthas::StageManager::getPlayer()
{
	if(m_GameScene)
	{
		auto layer = m_GameScene->getGameLayer();
		if(layer)
		{
			return layer->getPlayer();
		}
	}
	return nullptr;
}

int Arthas::StageManager::getStageNum()
{
	return m_CurrentStageNum;
}

Arthas::StageData Arthas::StageManager::getCurrentStageData()
{
	return m_StageData;
}

Arthas::RoomData Arthas::StageManager::getCurrentRoomData()
{
	int roomNum = m_GameScene->getGameLayer()->getCurrentRoomNum();
	return m_StageData.Rooms[roomNum];
}

int Arthas::StageManager::getRoomNum()
{
	if(m_GameScene)
	{
		auto layer = m_GameScene->getGameLayer();
		if(layer)
		{
			return layer->getCurrentRoomNum();
		}
	}
	return -1;
}
