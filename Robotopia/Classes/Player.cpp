#include "Player.h"
#include "SpriteComp.h"

bool Player::init()
{
	auto spriteComp = SpriteComp::create();
	spriteComp->setSprite( "player_stand1.png" , false );
	addComponent( spriteComp );
	spriteComp->enter();
	return true;
}