#include "Tile.h"
#include "SpriteComponent.h"

bool Arthas::Tile::init()
{
	auto spriteComp = Arthas::SpriteComponent::create();
	addComponent( spriteComp );
	spriteComp->enter();

	return true;
}