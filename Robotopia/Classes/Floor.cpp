#include "pch.h"
#include "Floor.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "PhysicsComponent.h"

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
	initPhysicsBody(tileRect, PHYC_ALL);
}

void Floor::extendBlock(cocos2d::Rect rect)
{
	PhysicsComponent* physics = (PhysicsComponent*) getComponent(CT_PHYSICS);
	if(physics)
	{
		rect.origin.x += rect.size.width / 2;
		rect.origin.y += rect.size.height / 2;
		physics->extendBody(rect);
	}
}

void Floor::initPhysicsBody(cocos2d::Rect physicsRect, PhysicsCategory categoryBitmask /*= PHYC_ALL*/)
{
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(physicsRect, false, 0, 0, 0);
}

