#include "Tile.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"

bool Arthas::Tile::init()
{
	auto spriteComp = SpriteComponent::create();
	addComponent( spriteComp );
	spriteComp->enter(); //나중에 바꿔야된다

	

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

void Arthas::Tile::setRect( float x, float y, float width, float height )
{
	m_BoxRect.setRect( x, y, width, height );
}
