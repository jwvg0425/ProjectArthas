#include"pch.h"
#include "MonsterPlant.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "DataManager.h"
#include "StageManager.h"
#include "Player.h"


bool MonsterPlant::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Type = OT_MONSTER_STAND_SHOT;

	//FSM 초기화
	initFSM(1);

	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = FSM_CALLBACK(MonsterPlant::idle, this);
	m_FSMs[0][STAT_ATTACK] = FSM_CALLBACK(MonsterPlant::attack, this);
	
	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(MonsterPlant::idleTransition, this);
	m_Transitions[0][STAT_ATTACK] = FSM_CALLBACK(MonsterPlant::attackTransition, this);

	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_IDLE])->setAnimation(AT_MONSTER_STAND_SHOT_IDLE, this);
	m_Renders[0][STAT_ATTACK] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_ATTACK])->setAnimation(AT_MONSTER_STAND_SHOT_ATTACK, this);

	for (int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	//info 설정
	auto data = GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_STAND_SHOT);

	if (data != nullptr)
	{
		m_Info = *data;
	}

	m_Info.m_CurrentHp = m_Info.m_MaxHp;

	//물리 초기화
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(m_Info.m_Size, meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_MONSTER);
	m_Body->setCollisionBitmask(PHYC_ALL);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->retain();
	setPhysicsBody(m_Body);
	m_Body->retain();

	m_IdleTime = 0;
	m_AttackTime = 0;

	return true;
}

void MonsterPlant::idle(Creature* target, double dTime, int idx)
{
	if (getPositionX() < GET_STAGE_MANAGER()->getPlayer()->getPositionX())
	{
		m_Info.m_LowerDir = DIR_LEFT;
	}
	else
	{
		m_Info.m_LowerDir = DIR_RIGHT;
	}

	m_IdleTime += dTime;
}

void MonsterPlant::attack(Creature* target, double dTime, int idx)
{
	m_AttackTime += dTime;
}

void MonsterPlant::idleTransition(Creature* target, double dTime, int idx)
{
	if (m_IdleTime > m_Info.m_MeleeAttackSpeed * 2)
	{
		m_AttackTime = 0;
		m_States[0] = STAT_ATTACK;
	}
}

void MonsterPlant::attackTransition(Creature* target, double dTime, int idx)
{
	if (m_AttackTime > m_Info.m_MeleeAttackSpeed * 4)
	{
		m_IdleTime = 0;
		m_States[0] = STAT_IDLE;
	}
}

void MonsterPlant::update(float dTime)
{
	Creature::update(dTime);
}

void MonsterPlant::enter()
{

}

void MonsterPlant::exit()
{

}

bool MonsterPlant::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void MonsterPlant::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

const AllStatus& MonsterPlant::getInfo() const
{
	return m_Info;
}
