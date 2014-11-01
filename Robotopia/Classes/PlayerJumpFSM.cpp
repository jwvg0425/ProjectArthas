#include"PlayerJumpFSM.h"
#include"IdleState.h"
#include"MoveState.h"
#include"JumpState.h"
#include"KeyboardTrigger.h"
#include"StateChangeTrigger.h"
#include"GameManager.h"
#include"TriggerManager.h"
#include"ComponentManager.h"


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

	addComponent(idle);
	addComponent(jump);

	idle->addTransition(std::make_pair(jumpKey, jump));

	m_NowState = idle;
}

void Arthas::PlayerJumpFSM::exit()
{

}