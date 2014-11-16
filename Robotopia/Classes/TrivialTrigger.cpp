#include "pch.h"
#include "TrivialTrigger.h"

TrivialTrigger::TrivialTrigger()
{
	m_Type = TT_TRIVIAL;
	m_Signifier = 0;
}

void TrivialTrigger::initTrigger(int signifier)
{
	m_Signifier = signifier;
}

bool TrivialTrigger::operator==( const Trigger& trigger )
{
	if(m_Type != trigger.getType())
	{
		return false;
	}
	
	auto tr = (TrivialTrigger&) trigger;
	return m_Signifier == tr.getSignifier() ? true : false;
}

int TrivialTrigger::getSignifier()
{
	return m_Signifier;
}

