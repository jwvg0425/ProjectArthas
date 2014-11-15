#include "pch.h"
#include "MovingBlock.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "SimpleRoaming.h"
#include "ObserverComponent.h"

bool Arthas::MovingBlock::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_BLOCK_MOVING;
	m_SpriteType = ST_BLOCK_MOVING;
	return true;
}

void Arthas::MovingBlock::update(float dTime)
{
	for(auto child : getChildren())
	{
		child->update(dTime);
	}
}

void Arthas::MovingBlock::enter()
{
	
}

void Arthas::MovingBlock::exit()
{

}

void Arthas::MovingBlock::initTile(cocos2d::Rect tileRect)
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_BLOCK);
	initSprite(tileRect.size);

	initFSM(tileRect.origin, cocos2d::Point(tileRect.origin.x + tileRect.size.width*3, tileRect.origin.y), 5.f); //나중에 변경
}

void Arthas::MovingBlock::initFSM(cocos2d::Point leftPoint, cocos2d::Point rightPoint, float time)
{
	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);

	auto roamingFSM = GET_COMPONENT_MANAGER()->createComponent<SimpleRoamingFSM>();
	roamingFSM->initRoaming(this, leftPoint, rightPoint, time);
	addComponent(roamingFSM);
}



