#include "IdleState.h"


bool Arthas::IdleState::init()
{
	if (!StateComponent::init())
	{
		return false;
	}

	return true;
}

void Arthas::IdleState::enter()
{
}

void Arthas::IdleState::exit()
{
}

void Arthas::IdleState::update(int dTime)
{
}

