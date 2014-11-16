#include "pch.h"
#include "PositionTrigger.h"

PositionTrigger::PositionTrigger()
{
	m_Type = TT_POSITION;
}

void PositionTrigger::initPositionTrigger(cocos2d::Point point)
{
	m_TriggerPoint = point;
}

bool PositionTrigger::operator==( const Trigger& trigger )
{
	if(!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	PositionTrigger& other = ( PositionTrigger& )trigger;
	cocos2d::Point otherPoint = other.getTriggerPoint();
	return otherPoint == m_TriggerPoint;
}

const cocos2d::Point PositionTrigger::getTriggerPoint()
{
	return m_TriggerPoint;
}



