#include "pch.h"
#include "MonsterDevil.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "DataManager.h"

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
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_MISSILE);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(true);
	m_Body->retain();
	setPhysicsBody(m_Body);

	initFSM(1);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = FSM_CALLBACK(move, this);
	m_FSMs[0][STAT_ATTACK] = FSM_CALLBACK(attack, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(idleTransition, this);
	m_Transitions[0][STAT_MOVE] = FSM_CALLBACK(moveTransition, this);
	m_Transitions[0][STAT_ATTACK] = FSM_CALLBACK(attackTransition, this);


	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_MOVE])->setAnimation(AT_DEVIL_IDLE, this);
	m_Renders[0][STAT_MOVE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_MOVE])->setAnimation(AT_DEVIL_MOVE, this);
	m_Renders[0][STAT_ATTACK] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_MOVE])->setAnimation(AT_DEVIL_ATTACK, this);

	for (int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	////info 설정
	auto data = GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_RUSH);

	//if (data != nullptr)
	//{
	//	m_Info = *GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_RUSH);
	//}

	//m_Info.m_CurrentHp = m_Info.m_MaxHp;


	return true;
}

void MonsterDevil::move()
{

}

void MonsterDevil::attack()
{

}

void MonsterDevil::idleTransition()
{

}

void MonsterDevil::moveTransition()
{

}

void MonsterDevil::attackTransition()
{

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



