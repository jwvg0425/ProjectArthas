#include "pch.h"
#include "Monster.h"

bool Arthas::Monster::init()
{
	if (!Component::init())
	{
		return false;
	}

	m_Type = OT_MONSTER;
	return true;
}

void Arthas::Monster::update(float dTime)
{

}

void Arthas::Monster::enter()
{
}

void Arthas::Monster::exit()
{
}
