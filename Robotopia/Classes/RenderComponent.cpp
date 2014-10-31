#include "RenderComponent.h"
#include "Trigger.h"
#include "StateComponent.h"



bool Arthas::RenderComponent::init()
{
	return true;
}

void Arthas::RenderComponent::enter()
{

}

void Arthas::RenderComponent::exit()
{

}

void Arthas::RenderComponent::update(int dTime)
{

}

void Arthas::RenderComponent::addTransition(Transition addTransition)
{
	m_Transitions.push_back(addTransition);
}

void Arthas::RenderComponent::removeTransition(Transition remTranstion)
{

}
