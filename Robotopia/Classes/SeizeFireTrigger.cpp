#include "pch.h"
#include "SeizeFireTrigger.h"

void Arthas::SeizeFireTrigger::initTrigger()
{
}

bool Arthas::SeizeFireTrigger::operator==( const  Trigger& trigger )
{
	return ( trigger.getType() == m_Type ) ? true : false;
}

Arthas::SeizeFireTrigger::SeizeFireTrigger()
{
	m_Type = TT_SEIZEFIRE;
}

