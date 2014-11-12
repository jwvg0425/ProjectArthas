#include "pch.h"
#include "SeizeFireTrigger.h"

void Arthas::SeizeFireTrigger::initTrigger(int signifier)
{

}

bool Arthas::SeizeFireTrigger::operator==( const  Trigger& trigger )
{
	return ( trigger.getType() == m_Type ) ? true : false;
}

