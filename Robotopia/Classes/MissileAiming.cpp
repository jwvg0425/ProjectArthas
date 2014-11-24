#include "pch.h"
#include "MissileAiming.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"



#define MISSILEAIMINGWIDHT 18
#define MISSILEAIMINGHEIGHT 16
#define PIE 3.141592


void MissileAiming::update(float dTime)
{

}

void MissileAiming::initMissile()
{
	m_IsUsable = true;
//	m_Type = OT_MISSILE_AIMING;
	
	setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);

	//¹°¸®
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(MISSILEAIMINGWIDHT, MISSILEAIMINGHEIGHT), 
											 meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_ALL);
	//m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_BLOCK);
	m_Body->setMass(10);
	m_Body->setRotationEnable(true);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);


	auto animation = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	addComponent(animation);
	//animation->setAnimation(AT_MISSILE_AIMING, this);


}

void MissileAiming::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, 
								 float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, 
								 cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, 
								 cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	
	float distance = sqrt((pos.x - targetPos.x)*(pos.x - targetPos.x) + (pos.y - targetPos.y) * (pos.y - targetPos.y));
	float degree = 0;

	if (distance != 0)
	{
		m_Velocity.x = ((targetPos.x - pos.x) / distance) * velocity.x;
		m_Velocity.y = ((targetPos.y - pos.y) / distance) * velocity.y;
		degree = acos((pos.x - targetPos.x) / distance) * 180 / PIE;

	}
	else
	{
		m_Velocity.x = velocity.x;
		m_Velocity.y = 0;
	}

	/*if (pos.y < targetPos.y)
	{
		m_MainSprite->setRotation(degree);
	}
	else
	{
		m_MainSprite->setRotation(-degree);

	}*/
}

bool MissileAiming::init()
{
	if (!MissileAiming::init())
	{
		return false;
	}

	return true;
}

void MissileAiming::enter()
{
}

void MissileAiming::exit()
{
}

