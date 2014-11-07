#include "pch.h"
#include "AttackState.h"

bool Arthas::AttackState::init()
{
	if (!StateComponent::init())
	{
		return false;
	}

	return true;
}

void Arthas::AttackState::enter()
{
}

void Arthas::AttackState::exit()
{
}

void Arthas::AttackState::update(float dTime)
{
}
