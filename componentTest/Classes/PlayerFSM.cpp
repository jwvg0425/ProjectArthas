#include "PlayerFSM.h"
#include "IdleState.h"
#include "MoveState.h"
#include "KeyboardTrigger.h"
#include "Object.h"
#include "CommandComponent.h"

PlayerFSM::PlayerFSM(Object* parent)
{
	m_Parent = parent;

	IdleState* idle = new IdleState(parent);
	MoveState* leftMove = new MoveState(parent, false);
	MoveState* rightMove = new MoveState(parent, true);
	KeyboardTrigger* leftKey = new KeyboardTrigger(KEY_LEFT);
	KeyboardTrigger* rightKey = new KeyboardTrigger(KEY_RIGHT);
	Event idleToLeft = Event(leftKey, leftMove);
	Event idleToRight = Event(rightKey, rightMove);
	KeyboardTrigger* leftKey2 = new KeyboardTrigger(KEY_LEFT);
	Event RightToLeft = Event(leftKey2, leftMove);

	addState(idle);
	idle->addEvent(idleToLeft);
	idle->addEvent(idleToRight);
	addState(leftMove);
	addState(rightMove);
	rightMove->addEvent(RightToLeft);

	m_NowState = idle;
}

PlayerFSM::~PlayerFSM()
{
	removeAllState();
}

void PlayerFSM::enter()
{

}

void PlayerFSM::exit()
{

}
