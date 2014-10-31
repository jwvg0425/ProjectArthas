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

void Arthas::SpriteComponent::initSprite( ResourceType resourceType , Component* parent)
{
	m_Sprite = GET_RESOURCE_MANAGER()->createSprite( resourceType );
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

