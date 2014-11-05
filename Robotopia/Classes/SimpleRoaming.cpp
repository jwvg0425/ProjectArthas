#include "SimpleRoaming.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "TriggerManager.h"
#include "MoveState.h"

bool Arthas::SimpleRoamingFSM::init()
{
	if(!FSMComponent::init())
		return false;

	return true;
}

void Arthas::SimpleRoamingFSM::initRoaming(const cocos2d::Point& leftPoint, const cocos2d::Point& rightPoint, float speed)
{
	m_LeftPoint = leftPoint;
	m_RightPoint = rightPoint;
	m_Speed = speed;
}

void Arthas::SimpleRoamingFSM::enter()
{
	m_Type = FSMT_PLAYER_MOVE;

	MoveState* leftMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	leftMove->setAttribute(m_Parent, DIR_LEFT, 200, true);

	MoveState* rightMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	rightMove->setAttribute(m_Parent, DIR_RIGHT, 200, true);

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
}

void Arthas::SimpleRoamingFSM::exit()
{

}

