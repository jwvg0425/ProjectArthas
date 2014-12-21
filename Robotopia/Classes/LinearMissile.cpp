#include "pch.h"
#include "LinearMissile.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"

bool LinearMissile::init()
{
	if(!Missile::init())
	{
		return false;
	}
	return true;
}

void LinearMissile::update(float dTime)
{

}

void LinearMissile::enter()
{

}

void LinearMissile::exit()
{
	setEnabled( false );
	removeChild( m_Sprite );
	m_IsUsable = true;
	removeFromParent();
}

void LinearMissile::initMissile()
{

}

void LinearMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	m_Type = OT_MISSILE_LINEAR;
	m_IsDead = false;
	m_IsUsable = false;
	m_IsPlayerMissile = true;
	m_Damage = damage;

	auto roomData = GET_STAGE_MANAGER()->getCurrentRoomData();
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	auto meterial = cocos2d::PhysicsMaterial( 0 , 0 , 0 );
	cocos2d::Size laserSize;
	float scale = 0.f;
	float rotation = 0.f;

	setPosition( pos );

	if( attackDir & DIR_LEFT || attackDir & DIR_RIGHT )
	{
		laserSize.width = roomData.m_Width * tileSize.width* 2;
		laserSize.height = LASER_SIZE;
		scale = laserSize.width / LASER_SIZE;
	}
	else if( attackDir & DIR_UP || attackDir & DIR_DOWN )
	{
		laserSize.width = LASER_SIZE;
		laserSize.height = roomData.m_Height * tileSize.height * 2;
		scale = laserSize.height / LASER_SIZE;
		rotation = 90;
	}
	m_Sprite->setScaleX( scale );
	m_Sprite->setRotation( rotation );

	m_Body = cocos2d::PhysicsBody::createBox( laserSize , meterial );
	m_Body->setContactTestBitmask( PHYC_MONSTER | PHYC_BLOCK | PHYC_PLAYER );
	m_Body->setCategoryBitmask( PHYC_MISSILE );
	m_Body->setCollisionBitmask( PHYC_MONSTER | PHYC_BLOCK | PHYC_PLAYER );
	m_Body->setTag( static_cast< int >( getType() ) );
	m_Body->setGravityEnable( false );
	m_Body->setMass( 10 );
	m_Body->setRotationEnable( false );
	m_Body->setVelocity( m_Velocity );
	m_Body->retain();
	setPhysicsBody( m_Body );
}

bool LinearMissile::onContactBegin(cocos2d::PhysicsContact& contact)
{

	return true;
}

void LinearMissile::setEnabled(bool enable)
{

}
