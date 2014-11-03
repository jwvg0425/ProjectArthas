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

void Arthas::PlayerRender::initRender()
{
	StateChangeTrigger* idle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idle->initChangingStates(CT_NONE, STAT_IDLE);
	StateChangeTrigger* moveLeft = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveLeft->initChangingStates(CT_NONE, STAT_MOVE_LEFT);
	StateChangeTrigger* moveRight = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	moveRight->initChangingStates(CT_NONE, STAT_MOVE_RIGHT);
	StateChangeTrigger* jump = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	jump->initChangingStates(CT_NONE, STAT_JUMP);
	
	AnimationCompnent* idleAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleAni->setAnimation(AT_PLAYER_IDLE, m_Parent);
	AnimationCompnent* moveAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	moveAni->setAnimation(AT_PLAYER_MOVE, m_Parent);
	AnimationCompnent* jumpAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	jumpAni->setAnimation(AT_PLAYER_JUMP, m_Parent);

	addComponent(idleAni);
	idleAni->addTransition(std::make_pair(moveLeft, moveAni));
	idleAni->addTransition(std::make_pair(moveRight, moveAni));
	idleAni->addTransition(std::make_pair(jump, jumpAni));

	addComponent(moveAni);
	moveAni->addTransition(std::make_pair(idle, idleAni));
	moveAni->addTransition(std::make_pair(jump, jumpAni));
	
	addComponent(jumpAni);
	jumpAni->addTransition(std::make_pair(idle, idleAni));

	m_CurrentSprite = idleAni;
	m_CurrentSprite->enter();
}
