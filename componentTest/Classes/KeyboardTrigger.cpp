#include "KeyboardTrigger.h"


KeyboardTrigger::KeyboardTrigger(int keyState)
{
	m_Type = 1;
	m_KeyState = keyState;
}

bool KeyboardTrigger::operator==(Trigger& trigger)
{
	if (trigger.getType() == getType())
	{
		KeyboardTrigger* other = (KeyboardTrigger*)&trigger;

		return (other->getKeyState() & getKeyState()) != 0;
	}
	else
	{
		return false;
	}
}
