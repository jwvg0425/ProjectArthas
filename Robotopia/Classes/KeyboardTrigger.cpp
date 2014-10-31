#include "KeyboardTrigger.h"

void Arthas::KeyboardTrigger::initKeyCode(KeyCode keyCode, KeyState keyState)
{
	m_KeyCode = keyCode;
	m_KeyState = keyState;
}

bool Arthas::KeyboardTrigger::operator==(Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
		return false;

	KeyboardTrigger& other = (KeyboardTrigger&)trigger;

	if (m_KeyCode == other.m_KeyCode && m_KeyState == other.m_KeyState)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Arthas::KeyboardTrigger::KeyboardTrigger()
{

}

Arthas::KeyboardTrigger::~KeyboardTrigger()
{

}
