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

bool Arthas::PlayerJumpFSM::init()
{
	if (!FSMComponent::init())
		return false;

	return true;
}

void Arthas::PlayerJumpFSM::enter()
{
	m_Type = FSMT_PLAYER_JUMP;

	//speed는 임시로 상수값 넣음.
	IdleState* idle = GET_COMPONENT_MANAGER()->createComponent<IdleState>();

	JumpState* jump = GET_COMPONENT_MANAGER()->createComponent<JumpState>();
	jump->setAttribute(m_Parent, 300);

	KeyboardTrigger* jumpKey = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	jumpKey->initKeyCode(KC_JUMP, KS_PRESS | KS_HOLD);

	PhysicsTrigger* downContact = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();
	downContact->initTrigger(CT_NONE, CT_NONE,DIR_DOWN,CTT_CONTACT);


	addComponent(idle);
	idle->addTransition(std::make_pair(jumpKey, jump));

	addComponent(jump);
	jump->addTransition(std::make_pair(downContact, idle));
	
	m_NowState = idle;
}

void Arthas::PlayerJumpFSM::exit()
{

}