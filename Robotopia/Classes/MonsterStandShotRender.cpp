#include "pch.h"
#include "MonsterStandShotRender.h"
#include "AnimationComponent.h"
#include "ComponentManager.h"
#include "GameManager.h"
#include "StateChangeTrigger.h"
#include "IdleState.h"
#include "TriggerManager.h"

bool MonsterStandShotRender::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}
	return true;
}

void MonsterStandShotRender::initRender()
{
	
	StateChangeTrigger* idle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idle->initChangingStates(CT_NONE, STAT_IDLE);

	StateChangeTrigger* attack = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	attack->initChangingStates(CT_NONE, STAT_ATTACK);

	//StateChangeTrigger* attackToAttack = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	//attack->initChangingStates(STAT_ATTACK, STAT_ATTACK);


	auto idleAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	addComponent(idleAni);
	idleAni->setAnimation(AT_MONSTER_STAND_SHOT_IDLE, GET_COMP_PARENT());

	auto attackAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	addComponent(attackAni);
	attackAni->setAnimation(AT_MONSTER_STAND_SHOT_ATTACK, GET_COMP_PARENT(), 1);

	idleAni->addTransition(std::make_pair(attack, attackAni));
	attackAni->addTransition(std::make_pair(idle, idleAni));
	//attackAni->addTransition(std::make_pair(attackToAttack, attackAni));


	m_CurrentSprite = idleAni;
	m_CurrentSprite->enter();
}

void MonsterStandShotRender::enter()
{
}

void MonsterStandShotRender::exit()
{
}
