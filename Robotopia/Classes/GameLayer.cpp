#include "GameManager.h"
#include "InputManager.h"
#include "GameLayer.h"
#include "RoomLayer.h"
#include "Player.h"

bool Arthas::GameLayer::init()
{
	if( !Layer::init() )
	{
		return false;
	}
	
	GET_INPUT_MANAGER()->receiveKeyboardData( this );

	return true;
}

void Arthas::GameLayer::update( float dTime )
{
	m_Player->update(dTime);
}

void Arthas::GameLayer::initGameLayer( const ModuleData& data )
{
	int size = 1;
	for(int idx = 0; idx < size; idx++)
	{
		m_RoomLayers[idx] = RoomLayer::create();
		m_RoomLayers[idx]->initRoom( data );
		addChild( m_RoomLayers[idx] );
	}

	m_Player = Player::create();
	m_Player->setPosition( 100, 100 );
	addChild( m_Player );
}
