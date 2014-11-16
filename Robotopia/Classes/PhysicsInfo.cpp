#include "pch.h"
#include "PhysicsInfo.h"

bool Arthas::PhysicsInfo::init()
{

	m_Type = IT_PHYSICS;

	ComponentTypes emptyTypes;

	emptyTypes.clear();

	m_Info.contactObjects.clear();

	return true;
}

void Arthas::PhysicsInfo::update(float dTime)
{

}

void Arthas::PhysicsInfo::enter()
{

}

void Arthas::PhysicsInfo::exit()
{

}

Arthas::PhysicsInfo::Info* Arthas::PhysicsInfo::getInfo()
{
	return &m_Info;
}

void Arthas::PhysicsInfo::setInfo(Info info)
{
	m_Info = info;
}
