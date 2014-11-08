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

void Arthas::Tile::initPhysicsBody(cocos2d::Size physicalSize)
{
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0.5f, 0.5f, physicalSize.width, physicalSize.height),
						 false, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);
}

void Arthas::Tile::initSprite(cocos2d::Size spriteSize)
{
	for(int xIdx = 0; xIdx < spriteSize.width; xIdx += GET_DATA_MANAGER()->getTileSize().width)
	{
		for(int yIdx = 0; yIdx < spriteSize.height; yIdx += GET_DATA_MANAGER()->getTileSize().height)
		{
			auto spriteComp = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
			spriteComp->initSprite(m_SpriteType, this, cocos2d::Point(xIdx, yIdx));
			addComponent(spriteComp);
			spriteComp->enter();
		}
	}
}
