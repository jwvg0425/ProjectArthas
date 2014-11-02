#include "SeparateTrigger.h"
#include "Component.h"


void Arthas::SeparateTrigger::initSeparatingComponents(ComponentType componentA, ComponentType componentB, Direction dir)
{
	m_ComponentA = componentA;
	m_ComponentB = componentB;
	m_Direction = dir;
}

bool Arthas::SeparateTrigger::operator==(Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	Arthas::SeparateTrigger& other = (Arthas::SeparateTrigger&) trigger;

	int myTypeA = m_ComponentA;
	int myTypeB = m_ComponentB;
	int otherTypeA = other.m_ComponentA;
	int otherTypeB = other.m_ComponentB;

	//null인 경우 해당 조건은 무시. 따라서 해당 조건은 상대와 같다고 가정한다.
	if (myTypeA == -1)
		myTypeA = otherTypeA;
	if (myTypeB == -1)
		myTypeB = otherTypeB;

	return (myTypeA == otherTypeA) && (myTypeB == otherTypeB) && (m_Direction & other.m_Direction);
}

Arthas::SeparateTrigger::SeparateTrigger()
{
	m_Type = TT_SEPARATE;
	m_ComponentA = CT_NONE;
	m_ComponentB = CT_NONE;
}

Arthas::SeparateTrigger::~SeparateTrigger()
{

}

