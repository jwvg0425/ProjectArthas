#include "pch.h"
#include "AnimationEndTrigger.h"

void Arthas::AnimationEndTrigger::initTrigger(ResourceType animationType)
{
	m_AnimationType = animationType;
}

bool Arthas::AnimationEndTrigger::operator==(const Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	AnimationEndTrigger& other = (AnimationEndTrigger&)trigger;

	return m_AnimationType == other.getAnimationType() ? true : false;
}

Arthas::ResourceType Arthas::AnimationEndTrigger::getAnimationType() const
{
	return m_AnimationType;
}

Arthas::AnimationEndTrigger::AnimationEndTrigger()
{
}

Arthas::AnimationEndTrigger::~AnimationEndTrigger()
{
}
