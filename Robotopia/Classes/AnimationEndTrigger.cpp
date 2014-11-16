#include "pch.h"
#include "AnimationEndTrigger.h"

void AnimationEndTrigger::initTrigger(ResourceType animationType)
{
	m_AnimationType = animationType;
}

bool AnimationEndTrigger::operator==(const Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	AnimationEndTrigger& other = (AnimationEndTrigger&)trigger;

	return m_AnimationType == other.getAnimationType() ? true : false;
}

ResourceType AnimationEndTrigger::getAnimationType() const
{
	return m_AnimationType;
}

AnimationEndTrigger::AnimationEndTrigger()
{
}

AnimationEndTrigger::~AnimationEndTrigger()
{
}
