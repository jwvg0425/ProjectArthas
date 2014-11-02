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
	StateChangeTrigger* idleStateChange = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idleStateChange->initChangingStates(CT_NONE, STAT_IDLE);
	AnimationCompnent* idleAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleAnimation->setAnimation(AT_PLAYER_IDLE, this);
	idleAnimation->retain();
	//addComponent(idleAnimation);
	addTransition(std::make_pair(idleStateChange, idleAnimation));

	StateChangeTrigger* moveStateChange = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveStateChange->initChangingStates(CT_NONE, STAT_MOVE_RIGHT);
	AnimationCompnent* moveAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveAnimation->setAnimation(AT_PLAYER_MOVE, this);
	moveAnimation->retain();
	addTransition(std::make_pair(moveStateChange, moveAnimation));
	//addComponent(moveAnimation);

	StateChangeTrigger* jumpStateChange = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	jumpStateChange->initChangingStates(CT_NONE, STAT_JUMP);
	AnimationCompnent* jumpAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpAnimation->setAnimation(AT_PLAYER_JUMP, this);
	jumpAnimation->retain();
	addTransition(std::make_pair(jumpStateChange, jumpAnimation));
	//addComponent(jumpAnimation);
	m_CurrentSprite = idleAnimation;
	m_CurrentSprite->enter();
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

	return true;
}
