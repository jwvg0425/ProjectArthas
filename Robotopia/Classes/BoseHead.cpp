#include "pch.h"
#include "BossHead.h"

bool BossHead::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createCircle(HEAD_RADIUS, meterial);
	m_Body->setContactTestBitmask(PHYC_BLOCK | PHYC_PLAYER | PHYC_MISSILE);
	m_Body->setCategoryBitmask(PHYC_MONSTER);
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR | PHYC_MISSILE);
	m_Body->setMass(10);
	m_Body->setRotationEnable(true);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(false);
	m_Body->retain();
	setPhysicsBody(m_Body);
	return true;
}


void BossHead::update(float dTime)
{

}


void BossHead::enter()
{

}


void BossHead::exit()
{

}

void BossHead::setEnabled(bool enable)
{

}

bool BossHead::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void BossHead::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}
 