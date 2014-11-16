#include "pch.h"
#include "CommandComponent.h"

bool CommandComponent::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}
	return true;
}

void CommandComponent::update( float dTime )
{
}

void CommandComponent::enter()
{
}

void CommandComponent::exit()
{
}

ObserverComponent* CommandComponent::getObserverComponent()
{
	if(GET_COMP_PARENT() != nullptr)
	{
		auto observerComponent = (ObserverComponent*) GET_COMP_PARENT()->getComponent(CT_OBSERVER);
		if(observerComponent != nullptr)
		{
			return observerComponent;
		}
	}
	return nullptr;
}


