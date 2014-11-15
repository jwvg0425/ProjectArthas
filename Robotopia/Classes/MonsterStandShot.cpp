#include "pch.h"
#include "MonsterStandShot.h"


bool Arthas::MonsterStandShot::init()
{
	if (!Monster::init())
	{
		return false;
	}

	return true;
}

void Arthas::MonsterStandShot::update(float dTime)
{

}


bool Arthas::MonsterStandShot::initMosnter()
{
	return true;
}

void Arthas::MonsterStandShot::enter()
{
}
void Arthas::MonsterStandShot::exit()
{
}
