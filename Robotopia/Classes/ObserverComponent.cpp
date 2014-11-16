#include "pch.h"
#include "ObserverComponent.h"

ObserverComponent::~ObserverComponent()
{
	removeCurrentTrigger();
	for( auto trigger : m_NextTriggers )
	{
		if( trigger != nullptr )
		{
			delete trigger;
			trigger = nullptr;
		}
	}
	m_NextTriggers.clear();
}

bool ObserverComponent::init()
{
	if( !BaseComponent::init())
	{
		return false;
	}
	m_Type = ComponentType::CT_OBSERVER;
	return true;
}

void ObserverComponent::update( float dTime )
{
	removeCurrentTrigger();
	m_Triggers.swap( m_NextTriggers );
}

void ObserverComponent::enter()
{

}

void ObserverComponent::exit()
{

}

void ObserverComponent::addTrigger( Trigger* trigger )
{
	m_NextTriggers.push_back( trigger );
}

void ObserverComponent::removeTrigger( Trigger* trigger )
{
	auto triggerIter = std::find( m_Triggers.begin() , m_Triggers.end() , trigger );
	delete trigger;
	m_Triggers.erase( triggerIter );
}

void ObserverComponent::removeCurrentTrigger()
{
	for( auto trigger : m_Triggers )
	{
		if( trigger != nullptr )
		{
			delete trigger;
			trigger = nullptr;
		}
	}
	m_Triggers.clear();
}

const std::vector<Trigger*>& ObserverComponent::getTriggers()
{
	return m_Triggers;
}



