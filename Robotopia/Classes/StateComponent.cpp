#include "pch.h"
#include "Trigger.h"
#include "StateComponent.h"

#define RESERVE_NUM 20
bool StateComponent::init()
{

	if (!BaseComponent::init())
	{
		return false;
	}
	
	m_Transitions.reserve(RESERVE_NUM);
	m_Ref = nullptr;

	return true;
}

void StateComponent::enter()
{
}

void StateComponent::exit()
{
}

void StateComponent::update(float dTime)
{
}

void StateComponent::addTransition(Transition addTransition)
{
	m_Transitions.push_back(addTransition);
}

void StateComponent::removeTransition(Transition remTransition)
{
	for (auto& it = m_Transitions.begin(); it != m_Transitions.end(); )
	{

		Transition transition = *it;
		if (remTransition.first == transition.first &&
			remTransition.second == transition.second)
		{
			delete transition.first;
			it = m_Transitions.erase(it);
		}
		else
		{
			++it;
		}
	}


}

StateComponent* StateComponent::getNextState(Trigger* trigger)
{
	for (unsigned int i = 0; i < m_Transitions.size(); ++i)
	{
		if (*m_Transitions[i].first == *trigger)
		{
			return (StateComponent*)m_Transitions[i].second;
		}
	}

	return nullptr;
}




