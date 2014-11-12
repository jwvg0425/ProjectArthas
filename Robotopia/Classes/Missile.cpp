#include "pch.h"
#include "Missile.h"


bool Arthas::Missile::init()
{
	if (!Component::init())
	{
		return false;
	}

	return true;
}

void Arthas::Missile::update(float dTime)
{
}

void Arthas::Missile::enter()
{
}

void Arthas::Missile::exit()
{
}

bool Arthas::Missile::isUsable() const
{
	return m_IsUsable;
}

