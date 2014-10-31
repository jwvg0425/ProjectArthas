#include "Player.h"
#include "SpriteComponent.h"
#include "PlayerFSM.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "KeyboardCommand.h"
#include "ObserverComponent.h"
#include "PhysicsComponent.h"

bool Arthas::Player::init()
{
	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);

	auto keyboardCommand = GET_COMPONENT_MANAGER()->createComponent<KeyboardCommand>();
	addComponent(keyboardCommand);

	auto fsm = GET_COMPONENT_MANAGER()->createComponent <PlayerFSM>();
	addComponent(fsm);

	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);

	auto spriteComp = GET_COMPONENT_MANAGER()->createComponent <SpriteComponent>();
	spriteComp->initSprite( ST_PLAYER , this );
	addComponent( spriteComp );
	spriteComp->enter();
	
	//test
	scheduleUpdate();

	return true;
}

void Arthas::Player::update( float dTime )
{
}

void Arthas::Player::enter()
{

}

void Arthas::Player::exit()
{

}
