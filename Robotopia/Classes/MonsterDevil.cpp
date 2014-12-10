#include "pch.h"
#include "MonsterDevil.h"

#define DEVIL_WIDTH 30
#define DEVIL_HEIGHT 30

bool MonsterDevil::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Type = OT_MONSTER_DEVIL;

	//물리 초기화

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(DEVIL_WIDTH, DEVIL_HEIGHT), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_BLOCK | PHYC_PLAYER | PHYC_MISSILE);
	m_Body->setCategoryBitmask(PHYC_MONSTER);
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR | PHYC_MISSILE);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(true);
	m_Body->retain();
	setPhysicsBody(m_Body);

	return true;
}

void MonsterDevil::update(float dTime)
{

}

void MonsterDevil::updateFSM(float dTime)
{

}

void MonsterDevil::updateRender(float dTime)
{

}

void MonsterDevil::enter()
{

}

void MonsterDevil::exit()
{

}
