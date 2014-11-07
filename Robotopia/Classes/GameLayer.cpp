#include "pch.h"
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
	m_PhysicsWorld = nullptr;
	m_Player = nullptr;

	return true;
}

void Arthas::GameLayer::update( float dTime )
{
	m_Player->update(dTime);
}

void Arthas::GameLayer::initGameLayer( const StageData& data )
{
	for(size_t idx = 0; idx < data.Rooms.size(); idx++)
	{
		m_RoomLayers[idx] = RoomLayer::create();
		m_RoomLayers[idx]->initRoom( data.Rooms[idx] );
		m_RoomLayers[idx]->setPhysicsWorld( m_PhysicsWorld );
		addChild( m_RoomLayers[idx] );
	}

	m_Player = Player::create();
	m_Player->setPosition( 100, 100 );
	addChild( m_Player );
}

void Arthas::GameLayer::setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld )
{
	if(physicsWorld != nullptr)
	{
		m_PhysicsWorld = physicsWorld;
	}
}

const Arthas::Player* Arthas::GameLayer::getPlayer()
{
	return m_Player;
}

