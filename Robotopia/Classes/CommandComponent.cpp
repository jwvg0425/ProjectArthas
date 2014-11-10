#include "pch.h"
#include "CommandComponent.h"

bool Arthas::CommandComponent::init()
{
	if(!Component::init())
	{
		return false;
	}
	return true;
}

void Arthas::CommandComponent::update( float dTime )
{
}

void Arthas::CommandComponent::enter()
{
}

void Arthas::CommandComponent::exit()
{
}

Arthas::ObserverComponent* Arthas::CommandComponent::getObserverComponent()
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


