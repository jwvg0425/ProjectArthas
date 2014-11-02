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



bool Arthas::PlayerRender::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}

	m_CurrentSprite = nullptr;

	return true;
}

void Arthas::PlayerRender::enter()
{
}

void Arthas::PlayerRender::exit()
{
}

bool Arthas::PlayerRender::initRender()
{
	StateChangeTrigger* idleLeft = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idleLeft->initChangingStates(CT_NONE, STAT_IDLE_LEFT);
	StateChangeTrigger* idleRight = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idleRight->initChangingStates(CT_NONE, STAT_IDLE_RIGHT);
	StateChangeTrigger* moveLeft = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveLeft->initChangingStates(CT_NONE, STAT_MOVE_LEFT);
	StateChangeTrigger* moveRight = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveRight->initChangingStates(CT_NONE, STAT_MOVE_RIGHT);
	StateChangeTrigger* jumpLeft = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	jumpLeft->initChangingStates(CT_NONE, STAT_JUMP_LEFT);
	StateChangeTrigger* jumpRight = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveRight->initChangingStates(CT_NONE, STAT_JUMP_RIGHT);
	
	AnimationCompnent* idleLeftAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleLeftAni->setAnimation(AT_PLAYER_IDLE, m_Parent);
	AnimationCompnent* idleRightAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleRightAni->setAnimation(AT_PLAYER_IDLE, m_Parent);
	AnimationCompnent* moveLeftAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveLeftAni->setAnimation(AT_PLAYER_MOVE, m_Parent);
	AnimationCompnent* moveRightAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveRightAni->setAnimation(AT_PLAYER_MOVE, m_Parent);
	AnimationCompnent* jumpLeftAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpLeftAni->setAnimation(AT_PLAYER_JUMP, m_Parent);
	AnimationCompnent* jumpRightAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpRightAni->setAnimation(AT_PLAYER_JUMP, m_Parent);


	addComponent(idleLeftAni);
	idleLeftAni->addTransition(std::make_pair(moveLeft, moveLeftAni));
	idleLeftAni->addTransition(std::make_pair(moveRight, moveRightAni));
	idleLeftAni->addTransition(std::make_pair(jumpLeft, jumpLeftAni));

	addComponent(idleRightAni);
	idleRightAni->addTransition(std::make_pair(moveRight, moveRightAni));
	idleRightAni->addTransition(std::make_pair(moveLeft, moveLeftAni));
	idleRightAni->addTransition(std::make_pair(jumpRight, jumpRightAni));

	addComponent(moveLeftAni);
	moveLeftAni->addTransition(std::make_pair(moveRight, moveRightAni));
	moveLeftAni->addTransition(std:: make_pair(jumpLeft, jumpLeftAni));
	
	addComponent(moveRightAni);
	moveRightAni->addTransition(std::make_pair(moveLeft, moveLeftAni));
	moveRightAni->addTransition(std::make_pair(jumpRight, jumpRightAni));

	addComponent(jumpLeftAni);
	jumpLeftAni->addTransition(std::make_pair(idleLeft, idleLeftAni));
	jumpLeftAni->addTransition(std::make_pair(jumpRight, jumpRightAni));

	addComponent(jumpRightAni);
	jumpRightAni->addTransition(std::make_pair(idleRight, idleRightAni));
	jumpRightAni->addTransition(std::make_pair(jumpLeft, jumpLeftAni));

	m_CurrentSprite = idleRightAni;
	m_CurrentSprite->enter();

	return true;
}
