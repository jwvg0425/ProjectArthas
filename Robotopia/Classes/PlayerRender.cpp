#include "pch.h"
#include "PlayerRender.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "ResourceManager.h"
#include "TriggerManager.h"
#include "StateChangeTrigger.h"
#include "IdleState.h"
#include "MoveState.h"
#include "JumpState.h"
#include "AnimationComponent.h"
#include "PhysicsTrigger.h"



bool PlayerRender::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}

	m_CurrentSprite = nullptr;
	m_Type = RENDER_PLAYER;

	return true;
}

void PlayerRender::enter()
{
}

void PlayerRender::exit()
{
}

void PlayerRender::initRender()
{
	StateChangeTrigger* idle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idle->initChangingStates(CT_NONE, STAT_IDLE);
	StateChangeTrigger* moveLeftToIdle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveLeftToIdle->initChangingStates(STAT_MOVE_LEFT, STAT_IDLE);
	StateChangeTrigger* moveRightToIdle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveRightToIdle->initChangingStates(STAT_MOVE_RIGHT, STAT_IDLE);
	StateChangeTrigger* jumpToIdle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	jumpToIdle->initChangingStates(STAT_JUMP, STAT_IDLE);
	StateChangeTrigger* moveLeft = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveLeft->initChangingStates(CT_NONE, STAT_MOVE_LEFT);
	StateChangeTrigger* moveRight = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveRight->initChangingStates(CT_NONE, STAT_MOVE_RIGHT);
	StateChangeTrigger* jump = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	jump->initChangingStates(CT_NONE, STAT_JUMP);
	PhysicsTrigger* separate = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();
	separate->initTrigger(OT_PLAYER, OT_BLOCK, DIR_DOWN, CTT_SEPARATE);
	PhysicsTrigger* floorSeparate = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();
	floorSeparate->initTrigger(OT_PLAYER, OT_FLOOR, DIR_DOWN, CTT_SEPARATE);
	
	AnimationComponent* idleAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	idleAni->setAnimation(AT_PLAYER_IDLE, GET_COMP_PARENT());
	AnimationComponent* moveAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	moveAni->setAnimation(AT_PLAYER_MOVE, GET_COMP_PARENT());
	AnimationComponent* jumpAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	jumpAni->setAnimation(AT_PLAYER_JUMP, GET_COMP_PARENT());
	AnimationComponent* moveJumpAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	moveJumpAni->setAnimation(AT_PLAYER_JUMP, GET_COMP_PARENT());

	addComponent(idleAni);
	idleAni->addTransition(std::make_pair(moveLeft, moveAni));
	idleAni->addTransition(std::make_pair(moveRight, moveAni));
	idleAni->addTransition(std::make_pair(jump, jumpAni));

	addComponent(moveAni);
	moveAni->addTransition(std::make_pair(idle, idleAni));
	moveAni->addTransition(std::make_pair(jump, moveJumpAni));
	
	addComponent(jumpAni);
	jumpAni->addTransition(std::make_pair(jumpToIdle, idleAni));
	jumpAni->addTransition(std::make_pair(moveLeft, moveJumpAni));
	jumpAni->addTransition(std::make_pair(moveRight, moveJumpAni));

	addComponent(moveJumpAni);
	moveJumpAni->addTransition(std::make_pair(moveLeftToIdle, jumpAni));
	moveJumpAni->addTransition(std::make_pair(moveRightToIdle, jumpAni));
	moveJumpAni->addTransition(std::make_pair(jumpToIdle, moveAni));

	m_CurrentSprite = idleAni;
	m_CurrentSprite->enter();

}
