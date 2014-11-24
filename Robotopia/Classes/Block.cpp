#include "pch.h"
#include "Block.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

bool Block::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_BLOCK;
	m_SpriteType = ST_BLOCK;

	return true;
}

void Block::update( float dTime )
{

}

void Block::enter()
{
}

void Block::exit()
{
}

void Block::initTile( cocos2d::Rect tileRect )
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_BLOCK);
}

void Block::extendBlock(cocos2d::Rect rect)
{
	PhysicsComponent* physics = (PhysicsComponent*)getComponent(CT_PHYSICS);
	if(physics)
	{
		rect.origin.x += rect.size.width/2;
		rect.origin.y += rect.size.height/2;
		physics->extendBody(rect);
	}
}

void Block::initPhysicsBody(cocos2d::Rect physicsRect, PhysicsCategory categoryBitmask /*= PHYC_ALL*/)
{
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(physicsRect, false, 0, 0, 0);
}