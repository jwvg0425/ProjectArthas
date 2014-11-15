#include "pch.h"
#include "Tile.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"



bool Arthas::Tile::init()
{
	m_SpriteType = ST_END;
	return true;
}

void Arthas::Tile::initPhysicsBody(cocos2d::Rect physicalRect, PhysicsCategory categoryBitmask)
{
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	cocos2d::Rect physicsRect;
	physicsRect.origin.x = physicalRect.size.width / 2;
	physicsRect.origin.y = physicalRect.size.height / 2;
	physicsRect.size = physicalRect.size;
	addComponent(physics);
	physics->initPhysics(physicsRect, false, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);
}

void Arthas::Tile::initSprite(cocos2d::Size spriteSize)
{
	for(int yIdx = 0; yIdx < spriteSize.height; yIdx += GET_DATA_MANAGER()->getTileSize().height)
	{
		for(int xIdx = 0; xIdx < spriteSize.width; xIdx += GET_DATA_MANAGER()->getTileSize().width)
		{
			auto spriteComp = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
			spriteComp->initSprite(m_SpriteType, this, cocos2d::Point(xIdx, yIdx), cocos2d::Point(0,0));
			addComponent(spriteComp);
			spriteComp->enter();
		}
	}
}
