#include "SpriteComponent.h"

bool Arthas::SpriteComponent::init()
{
	if( !Component::init() )
	{
		return false;
	}
	m_Sprite = nullptr;
	m_Type = 0;
	return true;
}

void Arthas::SpriteComponent::setSprite( const char* spriteName , bool isFrameCache )
{
	if( isFrameCache )
	{
		m_Sprite = cocos2d::Sprite::createWithSpriteFrameName( spriteName );
	}
	else
	{
		m_Sprite = cocos2d::Sprite::create( spriteName );
	}
	m_Sprite->retain();
}

void Arthas::SpriteComponent::enter()
{
	m_Parent->addChild( m_Sprite );
}

void Arthas::SpriteComponent::exit()
{
	m_Parent->removeChild( m_Sprite );
}

void Arthas::SpriteComponent::update( float dTime )
{
}

