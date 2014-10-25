#include"Player.h"
#include"SpriteComponent.h"


bool Player::init()
{
	if (!Object::init())
	{
		return false;
	}
	
	SpriteComponent* sprite = new SpriteComponent(this, "player_stand1.png", cocos2d::Point(0, 0));

	addComponent(sprite);


	return true;
}

Player::~Player()
{
	removeAllComponent();
}
