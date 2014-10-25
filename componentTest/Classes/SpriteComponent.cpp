#include "SpriteComponent.h"
#include "Object.h"


SpriteComponent::SpriteComponent(Object* parent, char* name, cocos2d::Point pos, bool isFromCache)
{
	if (isFromCache)
	{
		m_MainSprite = cocos2d::Sprite::createWithSpriteFrameName(name);
	}
	else
	{
		m_MainSprite = cocos2d::Sprite::create(name);
	}

	m_MainSprite->setPosition(pos);
	parent->addChild(m_MainSprite);
}

void SpriteComponent::update(float dTime)
{

}

void SpriteComponent::enter()
{

}

void SpriteComponent::exit()
{

}

SpriteComponent::~SpriteComponent()
{
	m_MainSprite->removeFromParent();
}
