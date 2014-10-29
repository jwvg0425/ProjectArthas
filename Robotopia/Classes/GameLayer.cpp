
#include "GameManager.h"
#include "GameLayer.h"
#include "Player.h"

bool Arthas::GameLayer::init()
{
	if( !Layer::init() )
	{
		return false;
	}
	m_Player = Player::create();
	m_Player->setPosition( 100 , 100 );
	addChild( m_Player );
	return true;
}

void Arthas::GameLayer::update( float dTime )
{
	
}
