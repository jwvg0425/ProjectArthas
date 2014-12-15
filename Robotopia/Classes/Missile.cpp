#include "pch.h"
#include "Missile.h"


bool Missile::init()
{
	if (!BaseComponent::init())
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
	m_State = MST_NONE;

	return true;
}

void Missile::update(float dTime)
{
}

void Missile::enter()
{
}

void Missile::exit()
{
}

bool Missile::isUsable() const
{
	return m_IsUsable;
}

float Missile::getDamage() const
{
	return m_Damage;
}

bool Missile::isPlayerMissile() const
{
	return m_IsPlayerMissile;
}

void Missile::setState(MissileState state)
{
	m_State = state;
}

Missile::MissileState Missile::getState()
{
	return m_State;
}

