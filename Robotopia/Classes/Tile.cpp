#include "Tile.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"



bool Arthas::Tile::init()
{


	return true;
}

void Arthas::Tile::update()
{

}

void Arthas::Tile::enter()
{

}

void Arthas::Tile::exit()
{

}

void Arthas::Tile::initTile( float x, float y, float width, float height )
{
	//크기를 설정한뒤
	m_BoxRect.setRect( x, y, width, height );

	//물리 컴포넌트 추가
	auto physics = (PhysicsComponent*) GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	physics->setBody( m_BoxRect, false );
	addComponent( physics );

}

void Arthas::Tile::initTile( cocos2d::Rect rect )
{
	initTile( rect.origin.x, rect.origin.y, rect.size.width, rect.size.height );
}
