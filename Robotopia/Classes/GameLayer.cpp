#include "pch.h"
#include "GameManager.h"
#include "InputManager.h"
#include "DataManager.h"
#include "StageManager.h"
#include "GameLayer.h"
#include "RoomLayer.h"
#include "Player.h"
#include "View.h"

bool Arthas::GameLayer::init()
{
	if( !Layer::init() )
	{
		return false;
	}
	
	GET_INPUT_MANAGER()->receiveKeyboardData( this );
	m_PhysicsWorld = nullptr;
	m_Player = nullptr;
	m_RoomCount = 0;
	m_CurrentRoomNum = 0;
	m_StageNum = 0;
	return true;
}

void Arthas::GameLayer::update( float dTime )
{
	//test code
	testCode();
	View::setViewPort(this, m_Player->getPosition(), cocos2d::Point::ANCHOR_MIDDLE);
	m_RoomLayers[m_CurrentRoomNum]->update(dTime);
	m_Player->update(dTime);
	checkIn();
}

void Arthas::GameLayer::initGameLayer( int stageNum )
{
	m_StageNum = stageNum;
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	m_RoomCount = data.Rooms.size();
	for(int idx = 0; idx < m_RoomCount; idx++)
	{
		m_RoomLayers[idx] = RoomLayer::create();
		m_RoomLayers[idx]->initRoom(data.Rooms[idx]);
		m_RoomLayers[idx]->retain();
		m_RoomLayers[idx]->roomSwitch(false);
	}

	m_Player = Player::create();
	m_Player->retain();
	changeRoom(0, cocos2d::Point(findFirstPoint(0)));
}

void Arthas::GameLayer::setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld )
{
	if(physicsWorld != nullptr)
	{
		m_PhysicsWorld = physicsWorld;
	}
}

const Arthas::Player* Arthas::GameLayer::getPlayer()
{
	return m_Player;
}

void Arthas::GameLayer::shakeRooms()
{
	GET_DATA_MANAGER()->initRoomPlace(m_StageNum);
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	m_RoomCount = data.Rooms.size();
	for(int idx = 0; idx < m_RoomCount; idx++)
	{
		m_RoomLayers[idx]->setPosition(cocos2d::Point(data.Rooms[idx].x, data.Rooms[idx].y));
	}
}

int Arthas::GameLayer::getCurrentRoomNum()
{
	return m_CurrentRoomNum;
}

Arthas::RoomLayer* Arthas::GameLayer::getRoomLayer(int roomNum)
{
	RoomLayer* resultRoomLayer = nullptr;
	if(roomNum >= 0 && roomNum < m_RoomCount)
	{
		resultRoomLayer = m_RoomLayers[roomNum];
	}
	return resultRoomLayer;
}

void Arthas::GameLayer::checkIn()
{
	cocos2d::Point pos = m_Player->getPosition();
	if(m_RoomLayers[m_CurrentRoomNum]->isOutOfRoom(pos))
	{
		int nextRoomNum = GET_DATA_MANAGER()->getNextRoomNumber(m_StageNum, m_CurrentRoomNum, pos);
		changeRoom(nextRoomNum, pos);
	}
}

void Arthas::GameLayer::changeRoom(int roomNum, cocos2d::Point pos)
{
	m_RoomLayers[m_CurrentRoomNum]->removeChildByTag(PLAYER_TAG);
	m_RoomLayers[m_CurrentRoomNum]->pause();
	m_RoomLayers[m_CurrentRoomNum]->roomSwitch(false);
	removeChild(m_RoomLayers[m_CurrentRoomNum]);

	m_CurrentRoomNum = roomNum;

	addChild(m_RoomLayers[m_CurrentRoomNum]);
	m_RoomLayers[m_CurrentRoomNum]->roomSwitch(true);
	m_RoomLayers[m_CurrentRoomNum]->resume();
	m_RoomLayers[m_CurrentRoomNum]->addChild(m_Player, 0, PLAYER_TAG);
	m_Player->setPosition(pos);
}

void Arthas::GameLayer::testCode()
{
	if(GET_INPUT_MANAGER()->getKeyState(KC_TEST2) == KS_PRESS)
	{
		shakeRooms();
	}
}

cocos2d::Point Arthas::GameLayer::findFirstPoint(int roomNum)
{
	cocos2d::Point pos;
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	auto moduleData = data.Rooms[roomNum].modulePlaceData;
	cocos2d::Size mSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tSize = GET_DATA_MANAGER()->getTileSize();
	int maxXIdx = data.Rooms[roomNum].width / mSize.width;
	int maxYIdx = data.Rooms[roomNum].height / mSize.height;
	int xIdx = 0, yIdx = 0;
	bool success = false;

	while(!success && xIdx < maxXIdx)
	{
		for(; yIdx < maxYIdx; yIdx++)
		{
			if(moduleData[xIdx + yIdx * maxXIdx] != 0)
			{
				success = true;
				break;
			}
			xIdx++;
		}
	}
	_ASSERT(success);

	pos.x = xIdx * mSize.width * tSize.width + 100;
	pos.y = yIdx * mSize.height * tSize.height + 100;

	return pos;
}
