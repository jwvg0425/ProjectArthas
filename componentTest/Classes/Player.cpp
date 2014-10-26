#include "Player.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "ObserverComponent.h"
#include "CommandComponent.h"
#include "PlayerFSM.h"


bool Player::init()
{
	if (!Object::init())
	{
		return false;
	}

	CommandComponent* command = new CommandComponent(this);

	addComponent(command);

	PlayerFSM* fsm = new PlayerFSM(this);

	addComponent(fsm);
	
	SpriteComponent* sprite = new SpriteComponent(this, "player_stand1.png", cocos2d::Point(0, 0));

	addComponent(sprite);

	PhysicsComponent* physics = new PhysicsComponent(this, cocos2d::Rect(0, 0, 32, 32), 0);

	addComponent(physics);

	ObserverComponent* observer = new ObserverComponent(this);

	addComponent(observer);


	return true;
}

Player::~Player()
{
	removeAllComponent();
}
