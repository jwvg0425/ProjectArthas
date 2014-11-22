#include "pch.h"
#include "GameManager.h"
#include "StageManager.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "RoomLayer.h"
#include "UILayer.h"
#include "CommonInfo.h"
#include "Player.h"
#include "GameSceneUILayer.h"
#include "DataManager.h"

StageManager::StageManager()
{
	m_GameScene = nullptr;
	m_CurrentStageNum = -1;
}

StageManager::~StageManager()
{
}

bool StageManager::init()
{
	auto scene = GameScene::createScene();
	GET_GAME_MANAGER()->changeScene(scene, SceneType::GAME_SCENE);
	m_GameScene = (GameScene*)(scene->getChildByTag( GAME_SCENE_TAG ));
	m_GameScene->scheduleUpdate();
	return true;
}

void StageManager::initStage( int stageNum )
{
	m_CurrentStageNum = stageNum;
	m_StageData = GET_DATA_MANAGER()->getStageData(stageNum);
	m_GameScene->getGameLayer()->initGameLayer(stageNum);
}

const Player* StageManager::getPlayer()
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
	return m_StageData.Rooms[roomNum];
}

int StageManager::getRoomNum()
{
	_ASSERT(m_GameScene != nullptr);
	if(m_GameScene == nullptr)
	{
		return -1;
	}
	auto layer = m_GameScene->getGameLayer();
	_ASSERT(layer != nullptr);
	if(layer == nullptr)
	{
		return -1;
	}
	return layer->getCurrentRoomNum();
}

bool StageManager::addObject(BaseComponent* object, int roomNum, cocos2d::Point position, RoomZOrder zOrder)
{
	bool ret = false;
	_ASSERT(m_GameScene != nullptr);
	if(m_GameScene == nullptr)
	{
		return ret;
	}
	auto layer = m_GameScene->getGameLayer();
	_ASSERT(layer != nullptr);
	if(layer == nullptr)
	{
		return ret;
	}
	auto room = layer->getRoomLayer(roomNum);
	if(room == nullptr)
	{
		return ret;
	}
	ret = room->addObject(object, position, zOrder);
	_ASSERT(room != nullptr);
	return ret;
}

bool StageManager::changeRoom(int roomNum, cocos2d::Point pos)
{
	_ASSERT(m_GameScene != nullptr);
	if(m_GameScene == nullptr)
	{
		return false;
	}
	auto layer = m_GameScene->getGameLayer();
	auto ui = m_GameScene->getUILayer();
	_ASSERT(layer != nullptr && ui != nullptr);
	if(layer == nullptr || ui == nullptr)
	{
		return false;
	}
	layer->changeRoom(roomNum, pos);
	((GameSceneUILayer*)ui)->setMapUI(m_CurrentStageNum, roomNum);
}

bool StageManager::shakeRoom()
{
	_ASSERT(m_GameScene != nullptr);
	if(m_GameScene == nullptr)
	{
		return false;
	}
	auto layer = m_GameScene->getGameLayer();
	auto ui = m_GameScene->getUILayer();
	_ASSERT(layer != nullptr && ui != nullptr);
	if(layer == nullptr || ui == nullptr)
	{
		return false;
	}
	layer->shakeRooms();
	( (GameSceneUILayer*) ui )->setMapUI(m_CurrentStageNum, layer->getCurrentRoomNum());
}
