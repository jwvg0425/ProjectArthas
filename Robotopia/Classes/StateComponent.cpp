#include "StateComponent.h"


bool Arthas::StateComponent::init()
{

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

		}
		else
		{
			++it;
		}
	}
}


