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
	m_SpriteType = ST_BLOCK;
	m_isMovingRight = true;



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

void Arthas::MovingBlock::initTile(float x, float y, float width, float height)
{
	Tile::initTile(x, y, width, height);
	auto size = GET_DATA_MANAGER()->getTileSize();
	auto bodyRect = cocos2d::Rect(x, y, size.width, size.height);
	initPhysicsBody(bodyRect);
	initSprite();
	initFSM(cocos2d::Point(x, y), cocos2d::Point(x + width, y), 5.f);
	scheduleUpdate();
}

void Arthas::MovingBlock::initTile(cocos2d::Rect rect)
{
	initTile(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void Arthas::MovingBlock::move(float dTime)
{
	cocos2d::Point curPos = getPosition();
	if(curPos.x > m_RightPoint)
	{
		m_isMovingRight = false;
	}
	else if(curPos.x < m_LeftPoint)
	{
		m_isMovingRight = true;
	}

	m_MovingSpeed = m_isMovingRight ? 10.f : -10.f;
	getPhysicsBody()->setVelocity(cocos2d::Vect(m_MovingSpeed, 0));
	curPos.x += m_MovingSpeed*dTime;
	setPosition(curPos);
}

void Arthas::MovingBlock::initFSM(cocos2d::Point leftPoint, cocos2d::Point rightPoint, float time)
{
	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);

	auto roamingFSM = GET_COMPONENT_MANAGER()->createComponent<SimpleRoamingFSM>();
	roamingFSM->initRoaming(this, leftPoint, rightPoint, time);
	addComponent(roamingFSM);
}



