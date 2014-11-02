#include "Tile.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"



bool Arthas::Tile::init()
{
	m_BoxRect = cocos2d::Rect();
	m_SpriteType = ST_END;
	return true;
}

void Arthas::Tile::initTile( float x, float y, float width, float height )
{
	//크기를 설정한뒤
	m_BoxRect.setRect( x, y, width, height );

	//물리 컴포넌트 추가
	cocos2d::Rect physicsRect = cocos2d::Rect(0, 0, m_BoxRect.size.width, m_BoxRect.size.height);
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent( physics );
	physics->initPhysics(physicsRect, false, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);
	physics->setAnchorPoint(cocos2d::Point::ZERO);
	setPosition( cocos2d::Point(x,y) );
}

void Arthas::Tile::initTile( cocos2d::Rect rect )
{
	initTile( rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}
