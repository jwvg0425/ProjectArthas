#include "pch.h"
#include "ItemAbstract.h"

bool ItemAbstract::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	return true;
}

void ItemAbstract::update(float dTime)
{
}

void ItemAbstract::enter()
{
}

void ItemAbstract::exit()
{
}

bool ItemAbstract::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void ItemAbstract::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

