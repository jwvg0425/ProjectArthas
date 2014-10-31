#include "Trigger.h"
#include "StateComponent.h"

#define RESERVE_NUM 10
bool Arthas::StateComponent::init()
{

	if (!Arthas::Component::init())
	{
		return false;
	}
	// 몇개로 할지 어디서 정해놓지? 
	m_Transitions.reserve(RESERVE_NUM);

	return true;
}

void Arthas::StateComponent::enter()
{
}

void Arthas::StateComponent::exit()
{
}

void Arthas::StateComponent::update(int dTime)
{
}

void Arthas::StateComponent::addTransition(Arthas::Transition addTransition)
{
	m_Transitions.push_back(addTransition);
}

void Arthas::StateComponent::removeTransition(Arthas::Transition remTransition)
{
	for (auto& it = m_Transitions.begin(); it != m_Transitions.end(); )
	{

		Arthas::Transition transition = *it;
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

Arthas::Component* Arthas::StateComponent::getNextState(Arthas::Trigger* trigger)
{
	for (unsigned int i = 0; i < m_Transitions.size(); ++i)
	{
		if (m_Transitions[i].first->getType() == trigger->getType())
		{
			return m_Transitions[i].second;
		}
	}

	return nullptr;
}




