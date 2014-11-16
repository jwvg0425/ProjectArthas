#include "pch.h"
#include "IdleState.h"


bool IdleState::init()
{
	if (!StateComponent::init())
	{
		return false;
	}

	m_Type = STAT_IDLE;

	return true;
}

void IdleState::enter()
{
}

void IdleState::exit()
{
}

void IdleState::update(float dTime)
{
}
