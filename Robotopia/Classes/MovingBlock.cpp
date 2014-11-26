#include "pch.h"
#include "MovingBlock.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"

bool MovingBlock::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_BLOCK_MOVING;
	m_SpriteType = ST_BLOCK_MOVING;
	return true;
}

void MovingBlock::update(float dTime)
{
	for(auto child : getChildren())
	{
		child->update(dTime);
	}
}

void MovingBlock::enter()
{
	
}

void MovingBlock::exit()
{

}

void MovingBlock::initTile(cocos2d::Rect tileRect)
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_BLOCK);
	initSprite(tileRect.size);

	initFSM(tileRect.origin, cocos2d::Point(tileRect.origin.x + tileRect.size.width*3, tileRect.origin.y), 5.f); //나중에 변경
}

void MovingBlock::initFSM(cocos2d::Point leftPoint, cocos2d::Point rightPoint, float time)
{
}



