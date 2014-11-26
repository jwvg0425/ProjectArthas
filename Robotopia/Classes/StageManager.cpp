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
}

StageManager::~StageManager()
{
}

bool StageManager::init()
{
	auto scene = GameScene::createScene();
	GET_GAME_MANAGER()->changeScene(scene, SceneType::GAME_SCENE);
	m_GameScene = static_cast<GameScene*>( scene->getChildByTag(GAME_SCENE_TAG) );
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
	ret = room->addObject(object, position, zOrder);
	_ASSERT(room != nullptr);
	return ret;
}

bool StageManager::changeRoom(int roomNum, cocos2d::Point pos)
{
	_ASSERT(m_GameScene != nullptr);
	auto layer = m_GameScene->getGameLayer();
	auto ui = m_GameScene->getUILayer();
	_ASSERT(layer != nullptr && ui != nullptr);
	layer->changeRoom(roomNum, pos);
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
