#include "Trigger.h"


int Arthas::Trigger::getType() const
{
	return m_Type;
}

bool Arthas::Trigger::isEqualTypeTrigger(const Trigger& enemy)
{
	if (m_Type == enemy.getType())
	{
		return true;
	}
	
	return false;
}
