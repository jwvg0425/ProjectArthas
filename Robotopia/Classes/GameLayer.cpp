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
	return true;
}

void Arthas::GameLayer::update( float dTime )
{
	//test code
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
	{
		cocos2d::Point pos = getPosition();

		pos.x += 10;
		setPosition(pos);
	}
	else if (GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		cocos2d::Point pos = getPosition();

		pos.x -= 10;
		setPosition(pos);
	}
	else if (GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_HOLD)
	{
		cocos2d::Point pos = getPosition();

		pos.y -= 10;
		setPosition(pos);
	}
	else if (GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD)
	{
		cocos2d::Point pos = getPosition();

		pos.y += 10;
		setPosition(pos);
	}

	if (GET_INPUT_MANAGER()->getKeyState(KC_TEST) == KS_PRESS)
	{
		cocos2d::Point pos = m_Player->getPosition();

		pos.x -= GET_DATA_MANAGER()->getStageData(0).Rooms[m_CurrentRoomNum].x*GET_DATA_MANAGER()->getTileSize().width;
		pos.y -= GET_DATA_MANAGER()->getStageData(0).Rooms[m_CurrentRoomNum].y*GET_DATA_MANAGER()->getTileSize().height;
		setPosition(pos);
	}

	m_Player->update(dTime);
	cocos2d::Point pos = m_Player->getPosition();
	if(m_RoomLayers[m_CurrentRoomNum]->isOutOfRoom(pos))
	{
		int nextRoomNum = GET_DATA_MANAGER()->getNextRoomNumber(
			GET_STAGE_MANAGER()->getStageNum(), m_CurrentRoomNum, pos);
		//ChangeRoom(nextRoomNum, pos);
	}
}

void Arthas::GameLayer::initGameLayer( const StageData& data )
{
	for(m_RoomCount = 0; m_RoomCount < data.Rooms.size(); m_RoomCount++)
	{
		m_RoomLayers[m_RoomCount] = RoomLayer::create();
		m_RoomLayers[m_RoomCount]->initRoom(data.Rooms[m_RoomCount]);
		m_RoomLayers[m_RoomCount]->setPhysicsWorld(m_PhysicsWorld);
		m_RoomLayers[m_RoomCount]->pause();
		m_RoomLayers[m_RoomCount]->setVisible(false);
		addChild(m_RoomLayers[m_RoomCount]);
	}

	m_Player = Player::create();
	m_Player->retain();
	ChangeRoom(0, cocos2d::Point(100, 100));
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

void Arthas::GameLayer::shakeRooms(const StageData& data)
{
	for(m_RoomCount = 0; m_RoomCount < data.Rooms.size(); m_RoomCount++)
	{
		m_RoomLayers[m_RoomCount]->setPosition(cocos2d::Point(data.Rooms[m_RoomCount].x, data.Rooms[m_RoomCount].y));
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

void Arthas::GameLayer::ChangeRoom(int roomNum, cocos2d::Point pos)
{
	m_RoomLayers[m_CurrentRoomNum]->removeChildByTag(PLAYER_TAG);
	m_RoomLayers[m_CurrentRoomNum]->pause();
	m_RoomLayers[m_CurrentRoomNum]->setVisible(false);
	m_CurrentRoomNum = roomNum;
	m_RoomLayers[m_CurrentRoomNum]->addChild(m_Player, 0, PLAYER_TAG);
	m_RoomLayers[m_CurrentRoomNum]->resume();
	m_RoomLayers[m_CurrentRoomNum]->setVisible(true);
	m_Player->setPosition(pos);
}

