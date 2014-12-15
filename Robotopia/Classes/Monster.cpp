#include "pch.h"
#include "Monster.h"

bool Monster::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	return true;
}

void Monster::update(float dTime)
{

}

void Monster::enter()
{
	resume();
}

void Monster::exit()
{
	//애니메이션 올스탑하고
	//박스
}
