#include "GameManager.h"
#include "InputManager.h"
#include "GameLayer.h"
#include "Player.h"

bool Arthas::GameLayer::init()
{
	if( !Layer::init() )
	{
		return false;
	}
	
	GET_INPUT_MANAGER()->receiveKeyboardData( this );
	m_Player = Player::create();
	m_Player->setPosition( 100 , 100 );
	addChild( m_Player );
	
	return true;
}

void Arthas::GameLayer::update( float dTime )
{
	
}
