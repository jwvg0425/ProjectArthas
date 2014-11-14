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
	m_Velocity = { 0, };
	m_AttackDir = DIR_NONE;
	m_TargetPos = { 0, };

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

