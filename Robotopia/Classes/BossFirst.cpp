#include "pch.h"
#include "BossFirst.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "DataManager.h"
#include "SpriteComponent.h"

bool BossFirst::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}

	m_Type = OT_MONSTER_RUSH;

	//물리 초기화

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
	m_Head->setPhysicsBody(m_Body);

	//FSM 초기화
	initFSM(1);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = move;
	m_FSMs[0][STAT_ATTACK] = attack;

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = idleTransition;
	m_Transitions[0][STAT_MOVE] = moveTransition;
	m_Transitions[0][STAT_ATTACK] = attackTransition;


	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	( (SpriteComponent*) m_Renders[0][STAT_IDLE] )->initSprite(ST_BOSS_RAIL, this);
	m_Renders[0][STAT_MOVE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	( (SpriteComponent*) m_Renders[0][STAT_MOVE] )->initSprite(ST_BOSS_RAIL, this);
	m_Renders[0][STAT_ATTACK] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	( (SpriteComponent*) m_Renders[0][STAT_ATTACK] )->initSprite(ST_BOSS_RAIL, this);

	for(int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	//info 설정
	auto data = GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_RUSH);

	if(data != nullptr)
	{
		m_Info = *GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_RUSH);
	}

	m_Info.m_CurrentHp = m_Info.m_MaxHp;

	return true;
}

void BossFirst::update(float dTime)
{

}

void BossFirst::enter()
{

}

void BossFirst::exit()
{

}

void BossFirst::dead()
{

}

void BossFirst::move(Creature* target, double dTime, int idx)
{

}

void BossFirst::enterMove()
{
	auto action = cocos2d::RotateBy::create(1.0, 30.f);

}

void BossFirst::exitMove()
{

}

void BossFirst::attack(Creature* target, double dTime, int idx)
{

}

void BossFirst::enterAttack()
{

}

void BossFirst::exitAttack()
{

}

void BossFirst::idleTransition(Creature* target, double dTime, int idx)
{

}

void BossFirst::moveTransition(Creature* target, double dTime, int idx)
{

}

void BossFirst::attackTransition(Creature* target, double dTime, int idx)
{

}

bool BossFirst::onContactBegin(cocos2d::PhysicsContact& contact)
{

}

void BossFirst::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

