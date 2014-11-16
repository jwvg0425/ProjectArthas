#include "pch.h"
#include "Monster.h"

bool Monster::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Type = OT_MONSTER;
	return true;
}

void Monster::update(float dTime)
{

}

void Monster::enter()
{
}

void Monster::exit()
{
}
