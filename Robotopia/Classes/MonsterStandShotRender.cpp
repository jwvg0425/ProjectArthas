#include "pch.h"
#include "MonsterStandShotRender.h"
#include "AnimationComponent.h"
#include "ComponentManager.h"
#include "GameManager.h"
#include "StateChangeTrigger.h"
#include "IdleState.h"
#include "TriggerManager.h"

bool Arthas::MonsterStandShotRender::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}
	return true;
}

void Arthas::MonsterStandShotRender::initRender()
{
	
	
	StateChangeTrigger* idle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idle->initChangingStates(CT_NONE, STAT_IDLE);

	StateChangeTrigger* attack = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	attack->initChangingStates(CT_NONE, STAT_ATTACK);

	auto idleAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	idleAni->setAnimation(AT_MONSTER_STAND_SHOT_IDLE, this);
	auto attackAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	attackAni->setAnimation(AT_MONSTER_STAND_SHOT_ATTACK, this, 1);
	
	addComponent(idleAni);
	addComponent(attackAni);

	idleAni->addTransition(std::make_pair(attack, attackAni));

	attackAni->addTransition(std::make_pair(idle, idleAni));
}

void Arthas::MonsterStandShotRender::enter()
{
}

void Arthas::MonsterStandShotRender::exit()
{
}