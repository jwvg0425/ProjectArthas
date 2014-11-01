#include "RenderComponent.h"
#include "Trigger.h"
#include "StateComponent.h"
#include "ObserverComponent.h"
#include "StateChangeTrigger.h"
#include "AnimationComponent.h"

#define TRIGGERS_SIZE 20


Arthas::RenderComponent::~RenderComponent()
{
	removeAllTransitions();
}


bool Arthas::RenderComponent::init()
{
	m_Triggers.resize(TRIGGERS_SIZE);
	return true;
}

void Arthas::RenderComponent::enter()
{

}

void Arthas::RenderComponent::exit()
{

}

void Arthas::RenderComponent::update(float dTime)
{
	auto observer = (ObserverComponent*)m_Parent->getComponent(CT_OBSERVER);
	m_Triggers = observer->getTriggers();

	for (unsigned int i = 0; i < m_Transitions.size(); ++i)
	{
		for (unsigned int j = 0; j < m_Triggers.size(); ++j)
		{
			if (m_Transitions[i].first == m_Triggers[j])
			{
				if (!(m_CurrentTransition->first == m_Triggers[j]))
				{
					//PrevTransition Exit
					m_CurrentTransition->second->exit();
					//CurrentTransition Start
					m_CurrentTransition->first = m_Transitions[i].first;
					m_CurrentTransition->second->enter();
				}
			}
		}
	}
}

void Arthas::RenderComponent::addTransition(Arthas::Transition addTransition)
{
	m_Transitions.push_back(addTransition);
}

void Arthas::RenderComponent::addTransition(Arthas::Trigger* trigger, Arthas::Component* component)
{
	Transition tmpTransition;
	tmpTransition.first = trigger;
	tmpTransition.second = component;
	Arthas::RenderComponent::addTransition(tmpTransition);
}

void Arthas::RenderComponent::removeTransition(Arthas::Transition removeTransition)
{
	for (auto& it = m_Transitions.begin(); it != m_Transitions.end();)
	{
		Arthas::Transition transition = *it;
		if (removeTransition.first == transition.first &&
			removeTransition.second == transition.second)
		{
			SAFE_DELETE(transition.first);
			SAFE_DELETE(transition.second);
			it = m_Transitions.erase(it);
		}
		else
		{
			++it;
		}
	}
}

Arthas::Transition Arthas::RenderComponent::createTransition(
											   Arthas::StateChangeTrigger* stateChangeTrigger,
											   Arthas::StateComponent* stateComponent,
											   Arthas::AnimationCompnent* animationComponent,
											   ResourceType resourceType)
{
	Transition tmpTransition;
	stateChangeTrigger->autoRelease();
	stateChangeTrigger->initChangingStates(nullptr, stateComponent);
	tmpTransition.first = stateChangeTrigger;
	animationComponent->setAnimation(resourceType);
	tmpTransition.second = animationComponent;

	return tmpTransition;
}

void Arthas::RenderComponent::removeAllTransitions()
{
	for (unsigned int i = 0; i < m_Transitions.size(); ++i)
	{
		SAFE_DELETE(m_Transitions[i].first);
		SAFE_DELETE(m_Transitions[i].second);
	}

	m_Transitions.erase(m_Transitions.begin(), m_Transitions.end());
}
