#include "pch.h"
#include "Floor.h"

bool Arthas::Floor::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_FLOOR;
	m_SpriteType = ST_FLOOR;

	return true;
}

void Arthas::Floor::update(float dTime)
{

}

void Arthas::Floor::enter()
{

}

void Arthas::Floor::exit()
{

}

void Arthas::Floor::initTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize)
{
	setPosition(origin);
	initPhysicsBody(physicalSize, PHYC_FLOOR);
}

