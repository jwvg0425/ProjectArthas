#include"pch.h"
#include "MonsterPlant.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "DataManager.h"
#include "StageManager.h"
#include "MissileManager.h"
#include "Player.h"
#include "AimingMissile.h"
#include "Corpse.h"

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
	m_AttackCount = 0;

	return true;
}

void MonsterPlant::idle(Creature* target, double dTime, int idx)
{
	if (getPositionX() < GET_STAGE_MANAGER()->getPlayer()->getPositionX())
	{
		m_Info.m_UpperDir = DIR_RIGHT;
	}
	else
	{
		m_Info.m_UpperDir = DIR_LEFT;
	}

	m_IdleTime += dTime;
}

void MonsterPlant::attack(Creature* target, double dTime, int idx)
{
	if (m_AttackTime > m_AttackCount * m_Info.m_MeleeAttackSpeed)
	{
		m_AttackCount++;
		cocos2d::Point launchPos1 = getPosition() + getContentSize() / 2;
		cocos2d::Point launchPos2 = getPosition() + getContentSize() / 2;
		cocos2d::Point targetPos1;
		cocos2d::Point targetPos2;

		launchPos1.y += m_Info.m_Size.height / 2;
		launchPos2.y -= m_Info.m_Size.height / 2;

		targetPos1 = launchPos1;
		targetPos2 = launchPos2;

		if (m_Info.m_UpperDir == DIR_LEFT)
		{
			targetPos1.x -= 20;
			targetPos2.x -= 20;
		}
		else
		{
			targetPos1.x += 20;
			targetPos2.x += 20;
		}

		auto missile = static_cast<AimingMissile*>(GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_AIMING, launchPos1, m_Info.m_UpperDir, 
												m_Info.m_Size, m_Info.m_MeleeDamage, cocos2d::Vect::ZERO, targetPos1));

		missile->setMaxDistance(m_Info.m_AttackRange);
		missile->setPlayerMissile(false);

		missile = static_cast<AimingMissile*>(GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_AIMING, launchPos2, m_Info.m_UpperDir,
			m_Info.m_Size, m_Info.m_MeleeDamage, cocos2d::Vect::ZERO, targetPos2));

		missile->setMaxDistance(m_Info.m_AttackRange);
		missile->setPlayerMissile(false);

	}

	m_AttackTime += dTime;
}

void MonsterPlant::idleTransition(Creature* target, double dTime, int idx)
{
	if (m_IdleTime > m_Info.m_MeleeAttackSpeed * 2)
	{
		m_AttackTime = 0;
		m_AttackCount = 0;
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
	if (m_Info.m_UpperDir == DIR_LEFT)
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

}

void MonsterPlant::enter()
{
	resume();
}

void MonsterPlant::exit()
{
}

bool MonsterPlant::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*)bodyA->getNode();
	auto componentB = (BaseComponent*)bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;

	if (componentA->getType() == getType())
	{
		enemyComponent = componentB;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		isComponentA = false;
	}

	//미사일이랑 충돌 처리
	if (enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_MISSILE)
	{
		Missile* missile = static_cast<Missile*>(enemyComponent);

		//수류탄은 뎀 안 입음
		if (missile->getType() == OT_MISSILE_GRENADE)
		{
			return false;
		}

		//몹이 쏜 건 안 맞음.
		if (!missile->isPlayerMissile())
		{
			return false;
		}

		float damage = missile->getDamage();

		m_Info.m_CurrentHp -= damage * 100 / (100 + m_Info.m_DefensivePower);

		//사망
		if (m_Info.m_CurrentHp <= 0)
		{
			m_IsDead = true;
		}
	}
	return true;
}

void MonsterPlant::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

const AllStatus& MonsterPlant::getInfo() const
{
	return m_Info;
}

void MonsterPlant::dead()
{
	auto corpse = GET_COMPONENT_MANAGER()->createComponent<Corpse>();
	int roomNum = GET_STAGE_MANAGER()->getRoomNum();
	GET_STAGE_MANAGER()->addObject(corpse, roomNum, getPosition(), RoomZOrder::GAME_OBJECT);
	removeFromParent();
}
