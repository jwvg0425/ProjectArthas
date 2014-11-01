#include"PlayerFSM.h"
#include"IdleState.h"
#include"MoveState.h"
#include"KeyboardTrigger.h"
#include"StateChangeTrigger.h"
#include"GameManager.h"
#include "TriggerManager.h"
#include"ComponentManager.h"


bool Arthas::PlayerFSM::init()
{
	if (!FSMComponent::init())
		return false;

	m_Type = FSMT_PLAYER;

	//speed는 임시로 상수값 넣음.
	IdleState* idle = GET_COMPONENT_MANAGER()->createComponent<IdleState>();

	MoveState* leftMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	leftMove->setAttribute(DIR_LEFT, 200, false);

	MoveState* rightMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	rightMove->setAttribute(DIR_RIGHT, 200, false);

	KeyboardTrigger* leftKeyDown = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	leftKeyDown->initKeyCode(KC_LEFT, KS_PRESS);

	KeyboardTrigger* rightKeyDown = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	rightKeyDown->initKeyCode(KC_RIGHT, KS_PRESS);

	KeyboardTrigger* leftKeyUp = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	leftKeyUp->initKeyCode(KC_LEFT, KS_RELEASE);

	KeyboardTrigger* rightKeyUp = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	rightKeyUp->initKeyCode(KC_RIGHT, KS_RELEASE);

	KeyboardTrigger* leftKeyHold = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	leftKeyHold->initKeyCode(KC_LEFT, KS_PRESS | KS_HOLD);

	KeyboardTrigger* rightKeyHold = GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
	rightKeyHold->initKeyCode(KC_RIGHT, KS_PRESS | KS_HOLD);

	addComponent(idle);
	idle->addTransition(std::make_pair(leftKeyHold, leftMove));
	idle->addTransition(std::make_pair(rightKeyHold, rightMove));

	addComponent(leftMove);
	leftMove->addTransition(std::make_pair(rightKeyDown, rightMove));
	leftMove->addTransition(std::make_pair(leftKeyUp, idle));

	addComponent(rightMove);
	rightMove->addTransition(std::make_pair(leftKeyDown, leftMove));
	rightMove->addTransition(std::make_pair(rightKeyUp, idle));

	m_NowState = idle;

	return true;
}

void Arthas::PlayerFSM::enter()
{

}

void Arthas::PlayerFSM::exit()
{

}