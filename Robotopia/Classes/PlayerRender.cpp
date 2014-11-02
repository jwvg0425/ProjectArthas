#include "PlayerRender.h"
#include "GameManager.h"
#include "ComponentManager.h"
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
	IdleState* idleState = GET_COMPONENT_MANAGER()->createComponent<IdleState>();
	idleState->retain();
	idleStateChange->initChangingStates(nullptr, idleState);
	AnimationCompnent* idleAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleAnimation->setAnimation(AT_PLAYER_IDLE);
	idleAnimation->retain();
	addComponent(idleAnimation);
	addTransition(std::make_pair(idleStateChange, idleAnimation));

	StateChangeTrigger* moveStateChange = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	MoveState* moveState = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	moveState->retain();
	moveStateChange->initChangingStates(nullptr, moveState);
	AnimationCompnent* moveAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveAnimation->setAnimation(AT_PLAYER_MOVE);
	moveAnimation->retain();
	addTransition(std::make_pair(moveStateChange, moveAnimation));
	addComponent(moveAnimation);

	StateChangeTrigger* jumpStateChange = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	JumpState* jumpState = GET_COMPONENT_MANAGER()->createComponent<JumpState>();
	jumpState->retain();
	jumpStateChange->initChangingStates(nullptr, jumpState);
	AnimationCompnent* jumpAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpAnimation->setAnimation(AT_PLAYER_JUMP);
	jumpAnimation->retain();
	addTransition(std::make_pair(jumpStateChange, jumpAnimation));
	addComponent(jumpAnimation);

	m_CurrentSprite = idleAnimation;
}

void Arthas::PlayerRender::exit()
{
}
