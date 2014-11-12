#include "pch.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "RenderMissilePlayerMelee.h"
#include "StateChangeTrigger.h"
#include "AnimationComponent.h"
#include "ComponentManager.h"

bool Arthas::RenderMissilePlayerMelee::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}

	m_Type = RENDER_MISSILE_PLAYER_MELEE;

	return true;
}

void Arthas::RenderMissilePlayerMelee::enter()
{
}

void Arthas::RenderMissilePlayerMelee::exit()
{
}

void Arthas::RenderMissilePlayerMelee::initRender()
{
	StateChangeTrigger* idle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idle->initChangingStates(CT_NONE, STAT_IDLE);



	AnimationCompnent* attackAni = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	attackAni->setAnimation(AT_MISSILE_PLAYER_MELEE, GET_COMP_PARENT());
}

