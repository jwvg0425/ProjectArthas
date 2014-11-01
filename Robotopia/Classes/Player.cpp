#include "Player.h"
#include "SpriteComponent.h"
#include "PlayerMoveFSM.h"
#include "PlayerJumpFSM.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "KeyboardCommand.h"
#include "ObserverComponent.h"
#include "PhysicsComponent.h"

bool Arthas::Player::init()
{
	if (!Component::init())
	{
		return false;
	}

	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);

	auto keyboardCommand = GET_COMPONENT_MANAGER()->createComponent<KeyboardCommand>();
	addComponent(keyboardCommand);

	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, 32, 32), true);

	auto moveFSM = GET_COMPONENT_MANAGER()->createComponent <PlayerMoveFSM>();
	addComponent(moveFSM);
	moveFSM->enter();
	
	auto jumpFSM = GET_COMPONENT_MANAGER()->createComponent <PlayerJumpFSM>();
	addComponent(jumpFSM);
	jumpFSM->enter();

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
	for (auto& component : getChildren())
	{
		component->update(dTime);
	}
}

void Arthas::Player::enter()
{

}

void Arthas::Player::exit()
{

}
