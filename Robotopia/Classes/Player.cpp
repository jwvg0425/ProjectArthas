#include "pch.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "PlayerMoveFSM.h"
#include "PlayerJumpFSM.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "KeyboardCommand.h"
#include "ObserverComponent.h"
#include "PhysicsComponent.h"
#include "PlayerRender.h"
#include "CommonInfo.h"
#include "PlayerAttackFSM.h"
#include "PhysicsInfo.h"

bool Arthas::Player::init()
{
	if (!Component::init())
	{
		return false;
	}

	auto info = GET_COMPONENT_MANAGER()->createComponent<CommonInfo>();
	addComponent(info);

	CommonInfo::Info tmp;
	tmp.dir = DIR_RIGHT;
	tmp.speed = 200;
	tmp.jumpSpeed = 500;
	tmp.size.width = 32.f;
	tmp.size.height = 32.f;
	tmp.maxHp = 100;
	tmp.maxSteam = 100;
	tmp.currentHp = 100;
	tmp.currentSteam = 100;

	info->setInfo(tmp);

	auto physicsInfo = GET_COMPONENT_MANAGER()->createComponent<PhysicsInfo>();

	addComponent(physicsInfo);

	m_Type = OT_PLAYER;
	

	auto keyboardCommand = GET_COMPONENT_MANAGER()->createComponent<KeyboardCommand>();
	addComponent(keyboardCommand);

	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, 32, 32), true, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);
	physics->addIgnoreCollision(OT_FLOOR, DIR_UP);

	auto moveFSM = GET_COMPONENT_MANAGER()->createComponent <PlayerMoveFSM>();
	addComponent(moveFSM);
	moveFSM->enter();

	auto jumpFSM = GET_COMPONENT_MANAGER()->createComponent <PlayerJumpFSM>();
	addComponent(jumpFSM);
	jumpFSM->enter();

	auto attackFSM = GET_COMPONENT_MANAGER()->createComponent<PlayerAttackFSM>();
	addComponent(attackFSM);
	attackFSM->enter();

	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);

	/*
	auto spriteComp = GET_COMPONENT_MANAGER()->createComponent <SpriteComponent>();
	spriteComp->initSprite( ST_PLAYER , this );
	addComponent( spriteComp );
	spriteComp->enter();
	*/

	auto render = GET_COMPONENT_MANAGER()->createComponent<PlayerRender>();
	addComponent(render);
	render->initRender();

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
	resume();
}

void Arthas::Player::exit()
{
	auto physicsInfo = (PhysicsInfo*)getComponent(IT_PHYSICS);

	physicsInfo->getInfo()->contactObjects.clear();
}
