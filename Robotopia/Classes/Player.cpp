#include "Player.h"
#include "SpriteComponent.h"

bool Arthas::Player::init()
{
	auto spriteComp = Arthas::SpriteComponent::create();
	spriteComp->setSprite( "player_stand1.png" , false );
	addComponent( spriteComp );
	spriteComp->enter();
	return true;
}