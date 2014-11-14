#include "pch.h"
#include"PlayerMoveFSM.h"
#include"IdleState.h"
#include"MoveState.h"
#include"KeyboardTrigger.h"
#include"StateChangeTrigger.h"
#include"GameManager.h"
#include "TriggerManager.h"
#include"ComponentManager.h"
#include "CommandTrigger.h"


bool Arthas::PlayerMoveFSM::init()
{
	if (!FSMComponent::init())
		return false;

	return true;
}

void Arthas::PlayerMoveFSM::enter()
{
	m_Type = FSMT_PLAYER_MOVE;

	//speed는 임시로 상수값 넣음.
	IdleState* idle = GET_COMPONENT_MANAGER()->createComponent<IdleState>();

	MoveState* leftMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	leftMove->setAttribute(GET_COMP_PARENT(), DIR_LEFT, 200, true);

	MoveState* rightMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	rightMove->setAttribute(GET_COMP_PARENT(), DIR_RIGHT, 200, true);

	/*
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
	*/

	CommandTrigger* leftStartCmd = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	leftStartCmd->initCmdTrigger(CMD_LEFT_START);
	CommandTrigger* leftEndCmd = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	leftStartCmd->initCmdTrigger(CMD_LEFT_END);
	CommandTrigger* leftHoldCmd = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	leftStartCmd->initCmdTrigger(CMD_LEFT_MOVING);
	CommandTrigger* rightStartCmd = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	leftStartCmd->initCmdTrigger(CMD_RIGHT_START);
	CommandTrigger* rightEndCmd = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	leftStartCmd->initCmdTrigger(CMD_RIGHT_END);
	CommandTrigger* rightHoldCmd = GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
	leftStartCmd->initCmdTrigger(CMD_RIGHT_MOVING);

	addComponent(idle);
	idle->addTransition(std::make_pair(leftHoldCmd, leftMove));
	idle->addTransition(std::make_pair(rightHoldCmd, rightMove));

	addComponent(leftMove);
	leftMove->addTransition(std::make_pair(rightStartCmd, rightMove));
	leftMove->addTransition(std::make_pair(leftEndCmd, idle));

	addComponent(rightMove);
	rightMove->addTransition(std::make_pair(leftStartCmd, leftMove));
	rightMove->addTransition(std::make_pair(rightEndCmd, idle));

	m_NowState = idle;
}

void Arthas::PlayerMoveFSM::exit()
{

}