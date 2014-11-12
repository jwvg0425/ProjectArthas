#include "TrivialTrigger.h"

Arthas::TrivialTrigger::TrivialTrigger()
{
	m_Signifier = 0;
}

void Arthas::TrivialTrigger::initTrigger(int signifier)
{
	m_Signifier = signifier;
}

bool Arthas::TrivialTrigger::operator==( const Trigger& trigger )
{
	if(m_Type != trigger.getType())
	{
		return false;
	}
	
	auto tr = (TrivialTrigger&) trigger;
	return m_Signifier == tr.getSignifier() ? true : false;
}

int Arthas::TrivialTrigger::getSignifier()
{
	return m_Signifier;
}

