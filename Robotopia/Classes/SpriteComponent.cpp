#include "SpriteComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"

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

void Arthas::SpriteComponent::initSprite( ResourceType resourceType, Component* parent, 
										  cocos2d::Point position /*= cocos2d::Point(0.f, 0.f)*/, 
										  cocos2d::Point anchorPoint /*= cocos2d::Point(0.f, 0.f)*/ )
{
	m_Sprite = GET_RESOURCE_MANAGER()->createSprite( resourceType );
	m_Sprite->setPosition( position );
	m_Sprite->setAnchorPoint( anchorPoint );
	parent->addChild( m_Sprite );
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

