#include "pch.h"
#include "LinearMissile.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "ResourceManager.h"

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
	m_IsDead = false;
	m_IsUsable = true;
}

void LinearMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	m_Type = OT_MISSILE_LINEAR;
	m_IsDead = false;
	m_IsUsable = false;
	m_IsPlayerMissile = false;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_State = MST_KNOCKBACK;

	setPosition( pos );
	makeSprite( m_AttackDir );
	makePhysicalBody();
	launch();
}

bool LinearMissile::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return false;
}

void LinearMissile::setEnabled(bool enable)
{
	if( enable == true )
	{
		setPhysicsBody( m_Body );
	}
	else
	{
		setPhysicsBody( nullptr );
		if( m_Body != nullptr )
		{
			m_Body->removeFromWorld();
		}
	}
}

void LinearMissile::makeSprite( Direction dir )
{
	m_Sprite = cocos2d::Sprite::create();
	addChild( m_Sprite );

	auto roomData = GET_STAGE_MANAGER()->getCurrentRoomData();
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	float scale = 0.f;
	float rotation = 0.f;
	if( m_AttackDir & DIR_LEFT || m_AttackDir & DIR_RIGHT )
	{
		m_LaserSize.width = roomData.m_Width * tileSize.width * 2;
		m_LaserSize.height = LASER_MODULE_SIZE;
		scale = m_LaserSize.width / LASER_MODULE_SIZE;
		rotation = 0.f;
	}
	else if( m_AttackDir & DIR_UP || m_AttackDir & DIR_DOWN )
	{
		m_LaserSize.width = LASER_MODULE_SIZE;
		m_LaserSize.height = roomData.m_Height * tileSize.height * 2;
		scale = m_LaserSize.height / LASER_MODULE_SIZE;
		rotation = 90.f;
	}

	m_Sprite->setScaleX( scale );
	m_Sprite->setRotation( rotation );
}

void LinearMissile::makePhysicalBody()
{
	auto meterial = cocos2d::PhysicsMaterial( 0 , 0 , 0 );
	m_Body = cocos2d::PhysicsBody::createBox( m_LaserSize , meterial );
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
	setEnabled( false );
}

void LinearMissile::launch()
{
	auto animation = GET_RESOURCE_MANAGER()->createAnimation( AT_MISSILE_LINEAR );
	auto animate = cocos2d::Animate::create( animation );
	auto switchButton = cocos2d::CallFuncN::create( CC_CALLBACK_1( LinearMissile::turnSwitch , this ) );
	auto delay = cocos2d::DelayTime::create( m_Delay );
	auto sequence = cocos2d::Sequence::create( animate , switchButton , delay , switchButton , animate->reverse() , nullptr );
}

void LinearMissile::turnSwitch( cocos2d::Node* ref )
{
	m_Switch = !m_Switch;
	setEnabled( m_Switch );
	if( m_Switch == false )
	{
		m_IsDead = true;
	}
}
