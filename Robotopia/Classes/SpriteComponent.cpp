#include "SpriteComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StateComponent.h"
#include "Trigger.h"

bool Arthas::SpriteComponent::init()
{
	if( !Component::init() )
	{
		return false;
	}
	m_Type = Arthas::ComponentType::CT_SPRITE;
	m_Sprite = nullptr;
	return true;
}

void Arthas::SpriteComponent::initSprite(ResourceType resourceType, Component* parent, 
										 cocos2d::Point position /*= cocos2d::Point(0.f, 0.f)*/, 
										 cocos2d::Point anchorPoint /*= cocos2d::Point(0.5f, 0.5f)*/)
{
	m_Sprite = GET_RESOURCE_MANAGER()->createSprite(resourceType);
	m_Sprite->setPosition(position);
	m_Sprite->setAnchorPoint(anchorPoint);
	parent->addChild(m_Sprite);
}

void Arthas::SpriteComponent::enter()
{
	m_Sprite->setVisible( true );
}

void Arthas::SpriteComponent::exit()
{
	m_Sprite->setVisible( false );
}

void Arthas::SpriteComponent::update( float dTime )
{
}

void Arthas::SpriteComponent::addTransition(Transition addTransition)
{
	m_Transitions.push_back(addTransition);
}

void Arthas::SpriteComponent::removeTransition(Transition remTranstion)
{
	for(auto& it = m_Transitions.begin(); it != m_Transitions.end();)
	{

		Arthas::Transition transition = *it;
		if(remTranstion.first == transition.first &&
		   remTranstion.second == transition.second)
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

Arthas::SpriteComponent* Arthas::SpriteComponent::getNextSprite(Trigger* trigger)
{
	for(unsigned int i = 0; i < m_Transitions.size(); ++i)
	{
		if(*m_Transitions[i].first == *trigger)
		{
			return (SpriteComponent*) m_Transitions[i].second;
		}
	}
	return nullptr;
}
