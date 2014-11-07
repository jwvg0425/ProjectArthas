#include "pch.h"
#include "PositionTrigger.h"

Arthas::PositionTrigger::PositionTrigger()
{
	m_Type = TT_POSITION;
}

void Arthas::PositionTrigger::initPositionTrigger(cocos2d::Point point)
{
	m_TriggerPoint = point;
}

bool Arthas::PositionTrigger::operator==(Trigger& trigger )
{
	if(!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	Arthas::PositionTrigger& other = ( Arthas::PositionTrigger& )trigger;
	cocos2d::Point otherPoint = other.getTriggerPoint();
	return otherPoint == m_TriggerPoint;
}

const cocos2d::Point Arthas::PositionTrigger::getTriggerPoint()
{
	return m_TriggerPoint;
}



