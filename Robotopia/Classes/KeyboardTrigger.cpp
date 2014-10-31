#include "KeyboardTrigger.h"

void Arthas::KeyboardTrigger::initKeyCode(KeyCode keyCode)
{
	m_KeyCode = keyCode;
}

bool Arthas::KeyboardTrigger::operator==(Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
		return false;

	KeyboardTrigger& other = (KeyboardTrigger&)trigger;

	if (m_KeyCode == other.m_KeyCode)
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
