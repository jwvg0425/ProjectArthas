#include "pch.h"
#include "KeyboardTrigger.h"

void Arthas::KeyboardTrigger::initKeyCode(KeyCode keyCode, int keyState)
{
	m_Type = TT_KEYBOARD;
	m_KeyCode = keyCode;
	m_KeyState = keyState;
}

bool Arthas::KeyboardTrigger::operator==( const Trigger& trigger )
{
	if (!isEqualTypeTrigger(trigger))
		return false;

	KeyboardTrigger& other = (KeyboardTrigger&)trigger;

	if (m_KeyCode == other.m_KeyCode && (m_KeyState & other.m_KeyState))
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
