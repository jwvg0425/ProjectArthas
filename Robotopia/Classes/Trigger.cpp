#include "pch.h"
#include "Trigger.h"


int Trigger::getType() const
{
	return m_Type;
}

bool Trigger::isEqualTypeTrigger(const Trigger& enemy)
{
	if (m_Type == enemy.getType())
	{
		return true;
	}
	
	return false;
}

Trigger::Trigger()
{
}

Trigger::~Trigger()
{

}
