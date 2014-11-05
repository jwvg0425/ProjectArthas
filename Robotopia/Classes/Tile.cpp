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
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent( physics );
	physics->initPhysics(m_BoxRect, false, 0, 0, 10, PHYC_ALL, PHYC_ALL, PHYC_ALL);
	physics->getBody()->setPositionOffset(cocos2d::Point(width / 2, height / 2));
	setPosition(cocos2d::Point(x, y));
}

void Arthas::Tile::initTile( cocos2d::Rect rect )
{
	initTile( rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}
