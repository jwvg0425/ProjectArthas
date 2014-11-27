#include "pch.h"
#include "Portal.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "RoomLayer.h"

bool Portal::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_PORTAL_CLOSED;
	m_SpriteType = ST_BLOCK;
	m_Room = nullptr;
	return true;
}

void Portal::update(float dTime)
{
	if(m_Room != nullptr)
	{
		auto roomData = m_Room->getRoomData();
		auto currentState = roomData.m_Data[m_PositionIndex];
		if(currentState != m_Type)
		{
			stateChange(currentState);
		}
	}
}

void Portal::enter()
{

}

void Portal::exit()
{

}



void Portal::initTile(cocos2d::Rect tileRect)
{
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	auto roomData = m_Room->getRoomData();
	int xIdx = tileRect.origin.x / tileSize.width;
	int yIdx = tileRect.origin.y / tileSize.height;
	m_PositionIndex = xIdx + yIdx*roomData.m_Width;
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_BLOCK);
	initSprite(tileRect.size);
}

void Portal::stateChange(ObjectType currentState)
{
	m_Type = currentState;
	if(m_Type == OT_PORTAL_OPEN) open();
	else close();
}

void Portal::open()
{
	getPhysicsBody()->setEnable(false);
	setVisible(false);
}

void Portal::close()
{
	getPhysicsBody()->setEnable(true);
	setVisible(true);
}

void Portal::setRoom(RoomLayer* room)
{
	if(room != nullptr)
	{
		m_Room = room;
	}
}

