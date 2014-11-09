#include "pch.h"
#include "Portal.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"

bool Arthas::Portal::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_PORTAL_CLOSED;
	m_SpriteType = ST_FLOOR;

	return true;
}

void Arthas::Portal::update(float dTime)
{
	auto roomData =  GET_STAGE_MANAGER()->getCurrentRoomData();
	auto currentState = roomData.data[m_PositionIndex];
	if(currentState != m_Type)
	{
		stateChange(currentState);
	}
}

void Arthas::Portal::enter()
{

}

void Arthas::Portal::exit()
{

}

void Arthas::Portal::initTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize)
{
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	auto roomData = GET_STAGE_MANAGER()->getCurrentRoomData();
	int xIdx = origin.x / tileSize.width;
	int yIdx = origin.x / tileSize.height;
	m_PositionIndex = xIdx + yIdx*roomData.width;
	setPosition(origin);
	initPhysicsBody(physicalSize, PHYC_BLOCK);
	initSprite(spriteSize);
	scheduleUpdate();
}

void Arthas::Portal::stateChange(ComponentType currentState)
{
	m_Type = currentState;
	if(m_Type == OT_PORTAL_OPEN) open();
	else close();
}

void Arthas::Portal::open()
{
	getPhysicsBody()->setEnable(false);
	setVisible(false);
}

void Arthas::Portal::close()
{
	getPhysicsBody()->setEnable(true);
	setVisible(true);
}

