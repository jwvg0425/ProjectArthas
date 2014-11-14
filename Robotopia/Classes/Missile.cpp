#include "pch.h"
#include "Missile.h"


bool Arthas::Missile::init()
{
	if (!Component::init())
	{
		return false;
	}


	m_IsUsable = true;
	m_Damage = 0;
	m_Velocity.x = 0;
	m_Velocity.y = 0;
	m_AttackDir = DIR_NONE;
	m_TargetPos.x = 0;
	m_TargetPos.y = 0;
	m_Triggers.reserve(20);

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

