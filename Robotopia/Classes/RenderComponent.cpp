#include "pch.h"
#include "RenderComponent.h"
#include "Trigger.h"
#include "StateComponent.h"
#include "ObserverComponent.h"
#include "StateChangeTrigger.h"
#include "AnimationComponent.h"

#define TRIGGERS_SIZE 20

bool RenderComponent::init()
{
	m_Triggers.reserve(TRIGGERS_SIZE);
	return true;
}

void RenderComponent::enter()
{
}

void RenderComponent::exit()
{
}

void RenderComponent::update(float dTime)
{
	auto observer = (ObserverComponent*)GET_COMP_PARENT()->getComponent(CT_OBSERVER);
	m_Triggers = observer->getTriggers();
	
	m_CurrentSprite->update(dTime);

	SpriteComponent* prevSprite = m_CurrentSprite;
	for (auto& trigger : m_Triggers)
	{
		auto nextSprite = m_CurrentSprite->getNextSprite(trigger);
		if (nextSprite)
		{
			nextSprite->enter();
			m_CurrentSprite->exit();
			m_CurrentSprite = nextSprite;
		/*	m_CurrentSprite->exit();
			m_CurrentSprite = nextSprite;
			m_CurrentSprite->enter();*/
		}
	}
}

void RenderComponent::addTransition(Transition addTransition)
{
	m_Transitions.push_back(addTransition);
}


void RenderComponent::removeTransition(Transition removeTransition)
{
	for (auto& it = m_Transitions.begin(); it != m_Transitions.end();)
	{
		Transition transition = *it;
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

void RenderComponent::initRender()
{
}


