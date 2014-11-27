#include "pch.h"
#include "EquipmentAbstract.h"

bool EquipmentAbstract::init()
{
	if (!ItemAbstract::init())
	{
		return false;
	}

	return true;
}

void EquipmentAbstract::update(float dTime)
{

}

void EquipmentAbstract::enter()
{

}

void EquipmentAbstract::exit()
{

}

bool EquipmentAbstract::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentAbstract::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

void EquipmentAbstract::initEquipment()
{
}
