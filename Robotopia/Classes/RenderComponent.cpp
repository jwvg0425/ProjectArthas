#include "RenderComponent.h"
#include "Trigger.h"
#include "StateComponent.h"
#include "ObserverComponent.h"
#include "StateChangeTrigger.h"
#include "AnimationComponent.h"

#define TRIGGERS_SIZE 20

bool Arthas::RenderComponent::init()
{
	m_Triggers.reserve(TRIGGERS_SIZE);
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

void Arthas::RenderComponent::addTransition(Arthas::Transition addTransition)
{
	m_Transitions.push_back(addTransition);
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

void Arthas::RenderComponent::initRender()
{
}


