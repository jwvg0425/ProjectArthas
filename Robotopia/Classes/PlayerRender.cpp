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
	m_Type = RENDER_PLAYER;

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
	StateChangeTrigger* idle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idle->initChangingStates(CT_NONE, STAT_IDLE);
	StateChangeTrigger* moveLeft = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveLeft->initChangingStates(CT_NONE, STAT_MOVE_LEFT);
	StateChangeTrigger* moveRight = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveRight->initChangingStates(CT_NONE, STAT_MOVE_RIGHT);
	StateChangeTrigger* jump = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	jump->initChangingStates(CT_NONE, STAT_JUMP);
	
	
	AnimationCompnent* idleLeftAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleLeftAni->setAnimation(AT_PLAYER_IDLE, this);
	AnimationCompnent* idleRightAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleRightAni->setAnimation(AT_PLAYER_IDLE, this);
	AnimationCompnent* moveLeftAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveLeftAni->setAnimation(AT_PLAYER_MOVE, this);
	AnimationCompnent* moveRightAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveRightAni->setAnimation(AT_PLAYER_MOVE, this);
	AnimationCompnent* jumpLeftAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpLeftAni->setAnimation(AT_PLAYER_JUMP, this);
	AnimationCompnent* jumpRightAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpRightAni->setAnimation(AT_PLAYER_JUMP, this);


	addComponent(idleLeftAni);
	idleLeftAni->addTransition(std::make_pair(moveLeft, moveLeftAni));
	idleLeftAni->addTransition(std::make_pair(moveRight, moveRightAni));
	idleLeftAni->addTransition(std::make_pair(jump, jumpLeftAni));

	addComponent(idleRightAni);
	idleRightAni->addTransition(std::make_pair(moveRight, moveRightAni));
	idleRightAni->addTransition(std::make_pair(moveLeft, moveLeftAni));
	idleRightAni->addTransition(std::make_pair(jump, jumpRightAni));

	addComponent(moveLeftAni);
	moveLeftAni->addTransition(std::make_pair(moveRight, moveRightAni));
	moveLeftAni->addTransition(std:: make_pair(jump, jumpLeftAni));
	
	addComponent(moveRightAni);
	moveRightAni->addTransition(std::make_pair(moveLeft, moveLeftAni));
	moveRightAni->addTransition(std::make_pair(jump, jumpRightAni));

	addComponent(jumpLeftAni);
	jumpLeftAni->addTransition(std::make_pair(idle, idleLeftAni));
	jumpLeftAni->addTransition(std::make_pair(jump, jumpRightAni));

	addComponent(jumpRightAni);
	jumpRightAni->addTransition(std::make_pair(idle, idleRightAni));
	jumpRightAni->addTransition(std::make_pair(jump, jumpLeftAni));

	m_CurrentSprite = idleRightAni;
	m_CurrentSprite->enter();

	return true;
}
