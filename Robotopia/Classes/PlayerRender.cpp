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
	idleStateChange->initChangingStates(nullptr, idleState);
	AnimationCompnent* idleAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleAnimation->setAnimation(AT_PLAYER_IDLE);
	addTransition(std::make_pair(idleStateChange, idleAnimation));
	addComponent(idleAnimation);

	StateChangeTrigger* moveStateChange = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	MoveState* moveState = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	moveStateChange->initChangingStates(nullptr, moveState);
	AnimationCompnent* moveAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveAnimation->setAnimation(AT_PLAYER_MOVE);
	addTransition(std::make_pair(moveStateChange, moveAnimation));
	addComponent(moveAnimation);

	StateChangeTrigger* jumpStateChange = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	JumpState* jumpState = GET_COMPONENT_MANAGER()->createComponent<JumpState>();
	jumpStateChange->initChangingStates(nullptr, jumpState);
	AnimationCompnent* jumpAnimation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpAnimation->setAnimation(AT_PLAYER_JUMP);
	addTransition(std::make_pair(jumpStateChange, jumpAnimation));
	addComponent(jumpAnimation);
}

void Arthas::PlayerRender::exit()
{
}
