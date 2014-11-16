#include "pch.h"
#include "SeizeFireTrigger.h"

void SeizeFireTrigger::initTrigger()
{
}

bool SeizeFireTrigger::operator==( const  Trigger& trigger )
{
	return ( trigger.getType() == m_Type ) ? true : false;
}

SeizeFireTrigger::SeizeFireTrigger()
{
	m_Type = TT_SEIZEFIRE;
}

