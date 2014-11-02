#include "ContactTrigger.h"
#include "Component.h"

Arthas::ContactTrigger::ContactTrigger()
{
	m_Type = TT_CONTACT;
	m_ComponentA = CT_NONE;
	m_ComponentB = CT_NONE;
	m_Direction = DIR_NONE;
}

Arthas::ContactTrigger::~ContactTrigger()
{

}

void Arthas::ContactTrigger::initContactingComponents(ComponentType componentA, ComponentType componentB, Direction dir)
{
	m_ComponentA = componentA;
	m_ComponentB = componentB;
	m_Direction = dir;
}

bool Arthas::ContactTrigger::operator==(Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	Arthas::ContactTrigger& other = (Arthas::ContactTrigger&) trigger;

	int myTypeA = m_ComponentA;
	int myTypeB = m_ComponentB;
	int otherTypeA = other.m_ComponentA;
	int otherTypeB = other.m_ComponentB;

	//null인 경우 해당 조건은 무시. 따라서 해당 조건은 상대와 같다고 가정한다.
	if (myTypeA == 0)
		myTypeA = otherTypeA;
	if (myTypeB == 0)
		myTypeB = otherTypeB;

	return (myTypeA == otherTypeA) && (myTypeB == otherTypeB) && (m_Direction & other.m_Direction);

}
