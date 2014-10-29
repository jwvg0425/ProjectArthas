#include "ContactTrigger.h"
#include "Component.h"

Arthas::ContactTrigger::ContactTrigger()
{
	m_ComponentA = nullptr;
	m_ComponentB = nullptr;
}

Arthas::ContactTrigger::~ContactTrigger()
{

}

void Arthas::ContactTrigger::initContactingComponents(Component* componentA, Component* componentB)
{
	m_Type = TT_CONTACT;
	m_ComponentA = componentA;
	m_ComponentB = componentB;
}

bool Arthas::ContactTrigger::operator==(Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	Arthas::ContactTrigger& other = (Arthas::ContactTrigger&) trigger;

	int myTypeA = (m_ComponentA) ? m_ComponentA->getType() : -1;
	int myTypeB = (m_ComponentB) ? m_ComponentB->getType() : -1;
	int otherTypeA = (other.m_ComponentA) ? other.m_ComponentA->getType() : -1;
	int otherTypeB = (other.m_ComponentB) ? other.m_ComponentB->getType() : -1;

	//null인 경우 해당 조건은 무시. 따라서 해당 조건은 상대와 같다고 가정한다.
	if (myTypeA == -1)
		myTypeA = otherTypeA;
	if (myTypeB == -1)
		myTypeB = otherTypeB;

	return (myTypeA == otherTypeA) && (myTypeB == otherTypeB);

}
