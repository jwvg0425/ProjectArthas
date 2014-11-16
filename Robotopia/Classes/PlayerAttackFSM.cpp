#include "pch.h"
#include "PlayerAttackFSM.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "TriggerManager.h"
#include "IdleState.h"
#include "AttackState.h"
#include "SeizeFireTrigger.h"
#include "KeyboardTrigger.h"
#include "CommandTrigger.h"

bool PlayerAttackFSM::init()
{
	if(!FSMComponent::init())
		return false;
	m_Type = FSMT_PLAYER_ATTACK;
	return true;
}

void PlayerAttackFSM::enter()
{
	auto idle = GET_COMPONENT_MANAGER()->createComponent<IdleState>();
	
	auto attack = GET_COMPONENT_MANAGER()->createComponent<AttackState>();
	attack->setAttribute(GET_COMP_PARENT(), 0.f, 0.2f, OT_MISSILE_PLAYER_MELEE, 0);

	SeizeFireTrigger* endAttackTrigger = GET_TRIGGER_MANAGER()->createTrigger<SeizeFireTrigger>();
	
	KeyboardTrigger* attackKeyHold = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	attackKeyHold->initKeyCode(KC_ATTACK, KS_PRESS | KS_HOLD);

	/*
	CommandTrigger* attackCommand = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	attackCommand->initCmdTrigger(CMD_ATTACK);
	*/

	addComponent(idle);
	idle->addTransition(std::make_pair(attackKeyHold, attack));
	
	addComponent(attack);
	attack->addTransition(std::make_pair(endAttackTrigger, idle));

	m_NowState = idle;
}

void PlayerAttackFSM::exit()
{

}

