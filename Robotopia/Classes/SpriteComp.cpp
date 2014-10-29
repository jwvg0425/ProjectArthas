#include "SpriteComp.h"

USING_NS_CC;

bool SpriteComp::init()
{
	if( !Component::init() )
	{
		return false;
	}
	m_Sprite = nullptr;
	m_Type = 0;
	return true;
}

void SpriteComp::setSprite( const char* spriteName , bool isFrameCache )
{
	if( isFrameCache )
	{
		m_Sprite = Sprite::createWithSpriteFrameName( spriteName );
	}
	else
	{
		m_Sprite = Sprite::create( spriteName );
	}
	m_Sprite->retain();
}

void SpriteComp::enter()
{
	m_Parent->addChild( m_Sprite );
}

void SpriteComp::exit()
{
	m_Parent->removeChild( m_Sprite );
}

void SpriteComp::update( float dTime )
{

}

