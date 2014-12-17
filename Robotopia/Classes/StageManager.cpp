#include "pch.h"
#include "GameManager.h"
#include "StageManager.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "RoomLayer.h"
#include "UILayer.h"
#include "Player.h"
#include "GameSceneUILayer.h"
#include "DataManager.h"
#include "AssemblyScene.h"

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
	static_cast<cocos2d::Scene*>(m_GameScene->getParent())->release();
}

bool StageManager::init()
{
	auto scene = GET_GAME_MANAGER()->getScene(GAME_SCENE);
	m_GameScene = static_cast<GameScene*>( scene->getChildByTag(GAME_SCENE_TAG) );
	return true;
}

void StageManager::start()
{
	auto scene = GET_GAME_MANAGER()->getScene(GAME_SCENE);
	m_GameScene = static_cast<GameScene*>( scene->getChildByTag(GAME_SCENE_TAG) );
	m_GameScene->scheduleUpdate();
	initStage(0);
}

void StageManager::initStage( int stageNum )
{
	m_CurrentStageNum = stageNum;
	m_StageData = GET_DATA_MANAGER()->getStageData(stageNum);
	m_GameScene->getGameLayer()->initGameLayer(stageNum);
}

Player* StageManager::getPlayer()
{
	if(m_GameScene == nullptr)
	{
		return nullptr;
	}
	auto layer = m_GameScene->getGameLayer();
	if(layer == nullptr)
	{
		return nullptr;
	}
	return layer->getPlayer();
}

int StageManager::getStageNum()
{
	return m_CurrentStageNum;
}

StageData StageManager::getCurrentStageData()
{
	return m_StageData;
}

RoomData StageManager::getCurrentRoomData()
{
	int roomNum = m_GameScene->getGameLayer()->getCurrentRoomNum();
	return m_StageData.m_Rooms[roomNum];
}

int StageManager::getRoomNum()
{
	_ASSERT(m_GameScene != nullptr);
	auto layer = m_GameScene->getGameLayer();
	_ASSERT(layer != nullptr);
	return layer->getCurrentRoomNum();
}

bool StageManager::addObject(BaseComponent* object, int roomNum, cocos2d::Point position, RoomZOrder zOrder)
{
	bool ret = false;
	_ASSERT(m_GameScene != nullptr);
	auto layer = m_GameScene->getGameLayer();
	_ASSERT(layer != nullptr);
	auto room = layer->getRoomLayer(roomNum);
	_ASSERT(room != nullptr);
	ret = room->addObject(object, position, zOrder);
	return ret;
}

bool StageManager::changeRoom(int roomNum, cocos2d::Point pos)
{
	_ASSERT(m_GameScene != nullptr);
	auto layer = m_GameScene->getGameLayer();
	auto ui = m_GameScene->getUILayer();
	_ASSERT(layer != nullptr && ui != nullptr);
	layer->changeRoom(roomNum, pos);
	cocos2d::log("Current Room %d", roomNum);
	static_cast<GameSceneUILayer*>( ui )->setMapUI(m_CurrentStageNum, roomNum);
	return true;
}

bool StageManager::shakeRoom()
{
	_ASSERT(m_GameScene != nullptr);
	auto layer = m_GameScene->getGameLayer();
	auto ui = m_GameScene->getUILayer();
	_ASSERT(layer != nullptr && ui != nullptr);
	layer->shakeRooms();
	static_cast<GameSceneUILayer*>( ui )->setMapUI(m_CurrentStageNum, layer->getCurrentRoomNum());
	return true;
}

cocos2d::Scene* StageManager::getGameScene()
{
	if(m_GameScene == nullptr)
	{
		return nullptr;
	}
	else
	{
		return static_cast<cocos2d::Scene*>(m_GameScene->getParent()); 
	}
}

cocos2d::Point StageManager::getGameLayerPosition()
{
	return m_GameScene->getGameLayer()->getPosition();
}

cocos2d::Point StageManager::getViewPosition()
{
	int currentRoomNum = m_GameScene->getGameLayer()->getCurrentRoomNum();
	cocos2d::Point gameLayerPos = getGameLayerPosition();
	auto roomLayer = m_GameScene->getGameLayer()->getRoomLayer(currentRoomNum);

	return gameLayerPos + roomLayer->getPosition();
}

void StageManager::setPlayerState(int idx, int state)
{
	if (m_GameScene == nullptr)
	{
		return;
	}
	auto layer = m_GameScene->getGameLayer();
	if (layer == nullptr)
	{
		return;
	}
	layer->setPlayerState(idx, state);
}

void StageManager::setPlayerInfo(const PlayerInfo& info)
{
	if (m_GameScene == nullptr)
	{
		return;
	}
	auto layer = m_GameScene->getGameLayer();
	if (layer == nullptr)
	{
		return;
	}
	layer->setPlayerInfo(info);
}

void StageManager::playerDead()
{
	if(m_GameScene == nullptr)
	{
		return;
	}
	auto layer = m_GameScene->getGameLayer();
	if(layer == nullptr)
	{
		return;
	}
	//layer->exit();
	GET_GAME_MANAGER()->changeScene(ASSEMBLY_SCENE);
}
