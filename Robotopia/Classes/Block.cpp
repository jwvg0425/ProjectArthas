#include "pch.h"
#include "Block.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

bool Arthas::Block::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_BLOCK;
	m_SpriteType = ST_BLOCK;

	return true;
}

void Arthas::Block::update( float dTime )
{

}

void Arthas::Block::enter()
{
}

void Arthas::Block::exit()
{
}

void Arthas::Block::initTile( cocos2d::Rect tileRect )
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect.size, PHYC_BLOCK);
}

void Arthas::Block::extendBlock(cocos2d::Rect rect)
{
	PhysicsComponent* physics = (PhysicsComponent*)getComponent(CT_PHYSICS);
	if(physics)
	{
		physics->extendBody(rect);
	}
}
