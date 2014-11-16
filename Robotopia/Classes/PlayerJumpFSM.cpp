#include "pch.h"
#include"PlayerJumpFSM.h"
#include"IdleState.h"
#include"MoveState.h"
#include"JumpState.h"
#include"KeyboardTrigger.h"
#include"StateChangeTrigger.h"
#include"GameManager.h"
#include"TriggerManager.h"
#include"ComponentManager.h"
#include"PhysicsTrigger.h"
#include "CommandTrigger.h"

bool PlayerJumpFSM::init()
{
	if (!FSMComponent::init())
		return false;

	return true;
}

void PlayerJumpFSM::enter()
{
	m_Type = FSMT_PLAYER_JUMP;

	//speed는 임시로 상수값 넣음.
	IdleState* idle = GET_COMPONENT_MANAGER()->createComponent<IdleState>();

	JumpState* jump = GET_COMPONENT_MANAGER()->createComponent<JumpState>();
	jump->setAttribute(GET_COMP_PARENT(), 300, false);

	JumpState* downJump = GET_COMPONENT_MANAGER()->createComponent<JumpState>();
	downJump->setAttribute(GET_COMP_PARENT(), 300, true);

	JumpState* fall = GET_COMPONENT_MANAGER()->createComponent<JumpState>();
	fall->setAttribute(GET_COMP_PARENT(), 0, false);

	
	KeyboardTrigger* jumpKey = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	jumpKey->initKeyCode(KC_JUMP, KS_PRESS | KS_HOLD);

	KeyboardTrigger* downJumpKey = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	downJumpKey->initKeyCode(KC_DOWN_JUMP, KS_PRESS);
	
	/*
	CommandTrigger* jumpCommand = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	jumpCommand->initCmdTrigger(CMD_JUMP);
	*/

	PhysicsTrigger* downContact = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();
	downContact->initTrigger(CT_NONE, CT_NONE, DIR_DOWN, CTT_CONTACT);

	PhysicsTrigger* ignore = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();
	ignore->initTrigger(CT_NONE, CT_NONE, DIR_DOWN, CTT_IGNORE);

	PhysicsTrigger* separate = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();
	separate->initTrigger(CT_NONE, CT_NONE, DIR_DOWN, CTT_SEPARATE);


	addComponent(idle);
	idle->addTransition(std::make_pair(jumpKey, jump));
	idle->addTransition(std::make_pair(downJumpKey, downJump));
	//idle->addTransition(std::make_pair(separate, fall));

	addComponent(jump);
	jump->addTransition(std::make_pair(downContact, idle));

	addComponent(downJump);
	downJump->addTransition(std::make_pair(ignore, fall));
	downJump->addTransition(std::make_pair(downContact, idle));

	addComponent(fall);
	fall->addTransition(std::make_pair(downContact, idle));

	m_NowState = idle;
}

void PlayerJumpFSM::exit()
{

}