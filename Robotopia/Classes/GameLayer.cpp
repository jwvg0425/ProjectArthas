#include "pch.h"
#include "GameManager.h"
#include "InputManager.h"
#include "DataManager.h"
#include "StageManager.h"
#include "GameLayer.h"
#include "RoomLayer.h"
#include "Player.h"
#include "View.h"

bool GameLayer::init()
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
	m_Player = Player::create();
	m_Player->retain();
	return true;
}

void GameLayer::update( float dTime )
{
	//test code
	testCode();
	View::setViewPort(this, m_Player->getPosition(), cocos2d::Point::ANCHOR_MIDDLE);
	m_RoomLayers[m_CurrentRoomNum]->update(dTime);
	m_Player->update(dTime);
	checkIn();
}

void GameLayer::initGameLayer( int stageNum )
{
	m_StageNum = stageNum;
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	m_RoomCount = data.Rooms.size();
	for(int idx = 0; idx < m_RoomCount; idx++)
	{
		m_RoomLayers[idx] = RoomLayer::create();
		m_RoomLayers[idx]->initRoom(data.Rooms[idx]);
		m_RoomLayers[idx]->retain();
		m_RoomLayers[idx]->pause();
		m_RoomLayers[idx]->roomSwitch(false);
	}

	changeRoom(0, cocos2d::Point(findFirstPoint(0)));
}

void GameLayer::setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld )
{
	if(physicsWorld != nullptr)
	{
		m_PhysicsWorld = physicsWorld;
	}
}

const Player* GameLayer::getPlayer()
{
	return m_Player;
}

void GameLayer::shakeRooms()
{
	GET_DATA_MANAGER()->initRoomPlace(m_StageNum);
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	m_RoomCount = data.Rooms.size();
	for(int idx = 0; idx < m_RoomCount; idx++)
	{
		m_RoomLayers[idx]->setPosition(cocos2d::Point(data.Rooms[idx].x, data.Rooms[idx].y));
	}
}

int GameLayer::getCurrentRoomNum()
{
	return m_CurrentRoomNum;
}

RoomLayer* GameLayer::getRoomLayer(int roomNum)
{
	RoomLayer* resultRoomLayer = nullptr;
	if(roomNum >= 0 && roomNum < m_RoomCount)
	{
		resultRoomLayer = m_RoomLayers[roomNum];
	}
	return resultRoomLayer;
}

void GameLayer::checkIn()
{
	cocos2d::Point pos = m_Player->getPosition();
	if(m_RoomLayers[m_CurrentRoomNum]->isOutOfRoom(pos))
	{
		int nextRoomNum = GET_DATA_MANAGER()->getNextRoomNumber(m_StageNum, m_CurrentRoomNum, pos);
		changeRoom(nextRoomNum, pos);
	}
}

void GameLayer::changeRoom(int roomNum, cocos2d::Point pos)
{
	m_RoomLayers[m_CurrentRoomNum]->removeChildByTag(PLAYER_TAG);
	m_RoomLayers[m_CurrentRoomNum]->pause();
	m_RoomLayers[m_CurrentRoomNum]->roomSwitch(false);
	m_Player->exit();
	removeChild(m_RoomLayers[m_CurrentRoomNum]);

	m_CurrentRoomNum = roomNum;

	addChild(m_RoomLayers[m_CurrentRoomNum]);
	m_RoomLayers[m_CurrentRoomNum]->roomSwitch(true);
	m_RoomLayers[m_CurrentRoomNum]->resume();
	m_RoomLayers[m_CurrentRoomNum]->addChild(m_Player, 0, PLAYER_TAG);
	m_Player->enter();
	m_Player->setPosition(pos);
}

void GameLayer::testCode()
{
	if(GET_INPUT_MANAGER()->getKeyState(KC_TEST2) == KS_PRESS)
	{
		shakeRooms();
	}
}

cocos2d::Point GameLayer::findFirstPoint(int roomNum)
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

	for(yIdx = 0; yIdx < maxYIdx && !success; yIdx++)
	{
		for(xIdx = 0; xIdx < maxXIdx; xIdx++)
		{
			if(moduleData[xIdx + yIdx * maxXIdx] != 0)
			{
				success = true;
				break;
			}
		}
	}
	--yIdx;

	_ASSERT(success);

	for (int y = 1; y < mSize.height; y++)
	{
		for (int x = 0; x < mSize.width; x++)
		{
			if (data.Rooms[roomNum].data[y*data.Rooms[roomNum].width + x] == CT_NONE &&
				data.Rooms[roomNum].data[(y-1)*data.Rooms[roomNum].width + x] == OT_BLOCK)
			{
				pos.x = xIdx * mSize.width * tSize.width + x*tSize.width;
				pos.y = yIdx * mSize.height * tSize.height + y*tSize.height + 10;

				return pos;
			}
		}
	}
}
