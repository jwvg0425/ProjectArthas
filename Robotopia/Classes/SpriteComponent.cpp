#include "pch.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StateComponent.h"
#include "CommonInfo.h"

bool SpriteComponent::init()
{
	if( !BaseComponent::init() )
	{
		return false;
	}
	m_Type = ComponentType::CT_SPRITE;
	m_Sprite = nullptr;
	return true;
}

void SpriteComponent::initSprite(SpriteType resourceType, BaseComponent* parent, 
										 cocos2d::Point position /*= cocos2d::Point(0.f, 0.f)*/, 
										 cocos2d::Point anchorPoint /*= cocos2d::Point(0.5f, 0.5f)*/)
{
	m_Sprite = GET_RESOURCE_MANAGER()->createSprite(resourceType);
	m_Sprite->setPosition(position);
	m_Sprite->setAnchorPoint(anchorPoint);
	parent->addChild(m_Sprite);
	m_RenderTarget = parent;
}

void SpriteComponent::enter()
{
	m_Sprite->setVisible( true );
}

void SpriteComponent::exit()
{
	m_Sprite->setVisible( false );
}

void SpriteComponent::update( float dTime )
{
	CommonInfo* info = static_cast<CommonInfo*>(m_RenderTarget->getComponent(IT_COMMON));
	if (info != nullptr)
	{
		if (info->getInfo().dir == DIR_LEFT)
		{
			m_Sprite->setFlippedX(true);
		}
		else
		{
			m_Sprite->setFlippedX(false);
		}
	}
}

void SpriteComponent::addTransition(Transition addTransition)
{
	m_Transitions.push_back(addTransition);
}

void SpriteComponent::removeTransition(Transition remTranstion)
{
	for(auto& it = m_Transitions.begin(); it != m_Transitions.end();)
	{

		Transition transition = *it;
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

cocos2d::Sprite* SpriteComponent::getSprite()
{
	return m_Sprite;
}

void SpriteComponent::setSpriteVisible(bool visible)
{
	m_Sprite->setVisible(visible);
}

void SpriteComponent::setFlippedX(bool flip)
{
	m_Sprite->setFlippedX(flip);
}
