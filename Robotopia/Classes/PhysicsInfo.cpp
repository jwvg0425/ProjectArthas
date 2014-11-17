#include "pch.h"
#include "PhysicsInfo.h"

bool PhysicsInfo::init()
{

	m_Type = IT_PHYSICS;

	ComponentTypes emptyTypes;

	emptyTypes.clear();

	m_Info.contactObjects.clear();
	m_Info.contactDirections = DIR_NONE;

	return true;
}

void PhysicsInfo::update(float dTime)
{

}

void PhysicsInfo::enter()
{

}

void PhysicsInfo::exit()
{

}

PhysicsInfo::Info* PhysicsInfo::getInfo()
{
	return &m_Info;
}

void PhysicsInfo::setInfo(Info info)
{
	m_Info = info;
}
