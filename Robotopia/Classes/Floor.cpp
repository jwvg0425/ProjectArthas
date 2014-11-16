#include "pch.h"
#include "Floor.h"

bool Floor::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_FLOOR;
	m_SpriteType = ST_FLOOR;

	return true;
}

void Floor::update(float dTime)
{

}

void Floor::enter()
{

}

void Floor::exit()
{

}

void Floor::initTile(cocos2d::Rect tileRect)
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_FLOOR);
}

