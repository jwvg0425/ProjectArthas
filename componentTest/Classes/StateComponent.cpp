#include "StateComponent.h"
#include "ObserverComponent.h"
#include "Trigger.h"
#include "Object.h"


void StateComponent::addEvent(Event event)
{
	m_Events.push_back(event);
}

void StateComponent::removeEvent(Event remEvent)
{
	for (auto& it = m_Events.begin(); it != m_Events.end();)
	{
		Event event = *it;

		if (event.first == remEvent.first && event.second == remEvent.second)
		{
			delete event.first;
			it = m_Events.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void StateComponent::removeAllEvent()
{
	for (auto& event : m_Events)
	{
		delete event.first;
	}

	m_Events.clear();
}

StateComponent::~StateComponent()
{
	removeAllEvent();
}

StateComponent::StateComponent()
{
	m_Type = 2;
}

Event* StateComponent::hasEvent()
{
	ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(3);

	if (observer != nullptr)
	{
		std::vector<Trigger*>& nowTrigger = observer->getTriggers();
		for (auto& event : m_Events)
		{
			for (auto& trigger : nowTrigger)
			{
				if (*event.first == *trigger)
				{
					return &event;
				}
			}
		}
	}

	return nullptr;
}

