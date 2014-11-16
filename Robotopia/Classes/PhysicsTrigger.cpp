﻿#include "pch.h"
#include "PhysicsTrigger.h"
#include "BaseComponent.h"

PhysicsTrigger::PhysicsTrigger()
{
	m_Type = TT_PHYSICS;
	m_ComponentA = CT_NONE;
	m_ComponentB = CT_NONE;
	m_Direction = DIR_NONE;
}

PhysicsTrigger::~PhysicsTrigger()
{

}

void PhysicsTrigger::initTrigger(ComponentType componentA, ComponentType componentB,
											Direction dir, ContactType type)
{
	m_ComponentA = componentA;
	m_ComponentB = componentB;
	m_Direction = dir;
	m_ContactType = type;
}

bool PhysicsTrigger::operator==( const Trigger& trigger )
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	PhysicsTrigger& other = (PhysicsTrigger&) trigger;

	int myTypeA = m_ComponentA;
	int myTypeB = m_ComponentB;
	int otherTypeA = other.m_ComponentA;
	int otherTypeB = other.m_ComponentB;

	//null인 경우 해당 조건은 무시. 따라서 해당 조건은 상대와 같다고 가정한다.
	if (myTypeA == 0)
		myTypeA = otherTypeA;
	if (myTypeB == 0)
		myTypeB = otherTypeB;

	return (myTypeA == otherTypeA) && (myTypeB == otherTypeB) 
		&& (m_Direction & other.m_Direction) && (m_ContactType == other.m_ContactType);

}

cocos2d::PhysicsContactData PhysicsTrigger::getContactData()
{
	return m_ContactData;
}

void PhysicsTrigger::setContactData(cocos2d::PhysicsContactData contactData)
{
	m_ContactData = contactData;
}
