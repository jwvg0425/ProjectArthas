#include "pch.h"
#include "Tile.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"



bool Arthas::Tile::init()
{
	m_BoxRect = cocos2d::Rect();
	m_SpriteType = ST_END;
	return true;
}

void Arthas::Tile::initTile( float x, float y, float width, float height )
{
	m_BoxRect.setRect( x, y, width, height );
	setPosition(cocos2d::Point(x, y));
}

void Arthas::Tile::initTile( cocos2d::Rect rect )
{
	initTile( rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}


void Arthas::Tile::initPhysicsBody(cocos2d::Rect rect)
{
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(rect, false, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);
	physics->getBody()->setPositionOffset(cocos2d::Point(rect.size.width / 2, rect.size.height / 2));
}

void Arthas::Tile::initSprite(cocos2d::Point position, cocos2d::Point anchor)
{
	auto spriteComp = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	spriteComp->initSprite(m_SpriteType, this, position, anchor);
	addComponent(spriteComp);
	spriteComp->enter();
}
