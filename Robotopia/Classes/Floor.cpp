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

void Arthas::Floor::initTile(cocos2d::Rect tileRect)
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_FLOOR);
}

