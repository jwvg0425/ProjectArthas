#include "ObserverComponent.h"
#include "Trigger.h"
#include "Object.h"


ObserverComponent::ObserverComponent(Object* parent)
{
	m_Parent = parent;
	m_Type = 3;
}

ObserverComponent::~ObserverComponent()
{
	removeAllTrigger();
	m_Triggers.swap(m_NextTriggers);
	removeAllTrigger();
}

void ObserverComponent::update(float dTime)
{
	removeAllTrigger();
	m_Triggers.swap(m_NextTriggers);
}

void ObserverComponent::enter()
{

}

void ObserverComponent::exit()
{

}

void ObserverComponent::addTrigger(Trigger* trigger)
{
	m_NextTriggers.push_back(trigger);
}

void ObserverComponent::removeTrigger(Trigger* remTrigger)
{
	for (auto& it = m_Triggers.begin(); it != m_Triggers.end();)
	{
		Trigger* trigger = *it;

		if (trigger->getType() == remTrigger->getType())
		{
			delete trigger;
			it = m_Triggers.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void ObserverComponent::removeAllTrigger()
{
	for (auto& trigger : m_Triggers)
	{
		delete trigger;
	}

	m_Triggers.clear();
}

std::vector<Trigger*>& ObserverComponent::getTriggers()
{
	return m_Triggers;
}

