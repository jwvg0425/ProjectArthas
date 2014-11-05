#include "MovingBlock.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "SimpleRoaming.h"

bool Arthas::MovingBlock::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_MOVING_BLOCK;
	m_SpriteType = ST_BLOCK;
	return true;
}

void Arthas::MovingBlock::update(float dTime)
{
	getComponent(FSMT_SIMPLE_ROAMING)->update(dTime);
}

void Arthas::MovingBlock::enter()
{
	
}

void Arthas::MovingBlock::exit()
{

}

void Arthas::MovingBlock::initTile(float x, float y, float width, float height)
{
	Tile::initTile(x, y, width, height);
	auto size = GET_DATA_MANAGER()->getTileSize();
	auto bodyRect = cocos2d::Rect(x, y, size.width, size.height);
	initPhysicsBody(bodyRect);
	initSprite();
	initFSM(x, y, width, height);
}


void Arthas::MovingBlock::initFSM(float x, float y, float width, float height)
{
	auto fsm = GET_COMPONENT_MANAGER()->createComponent<SimpleRoamingFSM>();
	cocos2d::Point leftPoint = cocos2d::Point(x, y);
	cocos2d::Point rightPoint = cocos2d::Point(x + width, y);
	addComponent(fsm);
	fsm->initRoaming(leftPoint, rightPoint, 1);
}

