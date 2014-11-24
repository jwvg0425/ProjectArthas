#include "pch.h"
#include "MonsterStandShot.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "StageManager.h"
#include "ComponentManager.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "MissileManager.h"
#include "Player.h"

#define COOLTIME  5.f
#define REPEATEATTACKNUM 2

bool MonsterStandShot::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Body = nullptr;
	m_Type = OT_MONSTER_STAND_SHOT;
	setInfo(COOLTIME, REPEATEATTACKNUM);
	m_CurAttackNum = 0;
	m_AccTime = 0;
	m_CurAttackDelay = 0;
	
	//물리
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(58, 58), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_ALL);
	//m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_BLOCK);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->retain();
	setPhysicsBody(m_Body);
	m_Body->retain();

	//FSM 초기화
	initFSM(1);
	m_States[0] = STAT_IDLE;

	//0번은 attackFSM
	m_FSMs[0].resize(STAT_NUM);
	//attack에서 0번 함수는 IDLE인데 이때 할게 없다.
	m_FSMs[0][STAT_IDLE] = nullptr;
	//attack에서 1번 함수는  Attack인데 이때는 공격을 해야한다. 
	m_FSMs[0][STAT_ATTACK] = attack;

	//0번 즉 attackFSM에 대한 트랜지션
	m_Transitions[0].resize(STAT_NUM);
	//이 함수에는 idle에서 attack으로 넘어가는 경우가 있겠지
	m_Transitions[0][STAT_IDLE] = idleTransition;
	//attack에서 idle로 가는 경우 정의 
	m_Transitions[0][STAT_ATTACK] = attackTransition;

	//0번 fsm에 대한 그림을 어떻게 그릴 것인가. 
	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_IDLE])->setAnimation(AT_MONSTER_STAND_SHOT_IDLE, this);
	m_Renders[0][STAT_ATTACK] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_ATTACK])->setAnimation(AT_MONSTER_STAND_SHOT_ATTACK, this);

	for (int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}


	return true;

}



void MonsterStandShot::setInfo(float coolTime /*= 5*/, int repeatAttackNum /*= 2*/,
						   Direction dir /*= DIR_RIGHT*/, int damage /*= 20*/,
						   int maxHp /*= 100*/, int curHp /*= 100*/,
						   ComponentType missileType /*= OT_MISSILE_PLAYER_LINEAR*/,
						   cocos2d::Size size /*= cocos2d::Size(50,50)*/,
						   float delay/*= 1.0f*/)
{
	m_Info.coolTime = coolTime;
	m_Info.repeatAttackNum = repeatAttackNum;
	m_Info.dir = dir;
	m_Info.damage = damage;
	m_Info.maxHp = maxHp;
	m_Info.curHp = 100;
	m_Info.missileType = missileType;
	m_Info.size = size;
	m_Info.attackDelay = delay;
}





void MonsterStandShot::attack(Thing* target, double dTime, int idx)
{
	auto tmpInfo = ((MonsterStandShot*)target)->m_Info;
	((MonsterStandShot*)target)->m_CurAttackDelay += dTime;

	if (((MonsterStandShot*)target)->m_CurAttackDelay >= ((MonsterStandShot*)target)->m_Info.attackDelay)
	{
		cocos2d::Vec2 missileVec;
		missileVec.x = 200;
		missileVec.y = 0;


		GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_PLAYER_LINEAR, target->getPosition(),
											 tmpInfo.dir, tmpInfo.size,
											 20.f, missileVec);
		((MonsterStandShot*)target)->m_CurAttackNum++;
		((MonsterStandShot*)target)->m_CurAttackDelay = 0;
	}
}



void MonsterStandShot::attackTransition(Thing* target, double dTime, int idx)
{
	//=>idle
	if (((MonsterStandShot*)target)->m_CurAttackNum >= ((MonsterStandShot*)target)->m_Info.repeatAttackNum)
	{
		((MonsterStandShot*)target)->m_CurAttackNum = 0;
		exitAttack(target, dTime, idx);
		target->setState(idx, MonsterStandShot::STAT_IDLE);

	}
}

void MonsterStandShot::idleTransition(Thing* target, double dTime, int idx)
{
	//=>attack
	((MonsterStandShot*)target)->m_AccTime += dTime;
	if (((MonsterStandShot*)target)->m_AccTime > ((MonsterStandShot*)target)->m_Info.coolTime)
	{
		((MonsterStandShot*)target)->m_AccTime = 0;
		target->setState(idx, MonsterStandShot::STAT_ATTACK);
	}
}

void MonsterStandShot::update(float dTime)
{
	if (GET_STAGE_MANAGER()->getPlayer()->getPositionX() > getPositionX())
	{
		m_Info.dir = DIR_RIGHT;
	}
	else
	{
		m_Info.dir = DIR_LEFT;
	}


	if (m_Info.dir == DIR_LEFT)
	{
		for (int i = 0; i < m_Renders[0].size(); i++)
		{
			m_Renders[0][i]->setFlippedX(true);
		}
	}
	else
	{
		for (int i = 0; i < m_Renders[0].size(); i++)
		{
			m_Renders[0][i]->setFlippedX(false);
		}
	}

	Thing::update(dTime);
}

void MonsterStandShot::enter()
{
	resume();
}

void MonsterStandShot::exit()
{
}

void MonsterStandShot::enterAttack(Thing* target, double dTime, int idx)
{
}

void MonsterStandShot::exitAttack(Thing* target, double dTime, int idx)
{
}

bool MonsterStandShot::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void MonsterStandShot::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

cocos2d::PhysicsBody* MonsterStandShot::getBody()
{
	return m_Body;
}







