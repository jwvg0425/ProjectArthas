#include "pch.h"
#include "MonsterDevil.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "DataManager.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "MissileManager.h"
#include "Player.h"
#include "ComponentManager.h"


#define DEVIL_WIDTH 30
#define DEVIL_HEIGHT 30
#define DAMAGE 20
#define ATTACKAFTERDELAY 2000

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
	m_FSMs[0][STAT_MOVE] = FSM_CALLBACK(MonsterDevil::move, this);
	m_FSMs[0][STAT_READYATTACK] = FSM_CALLBACK(MonsterDevil::readyAttack, this);
	m_FSMs[0][STAT_ATTACK] = FSM_CALLBACK(MonsterDevil::attack, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(MonsterDevil::idleTransition, this);
	m_Transitions[0][STAT_MOVE] = FSM_CALLBACK(MonsterDevil::moveTransition, this);
	m_Transitions[0][STAT_READYATTACK] = FSM_CALLBACK(MonsterDevil::readyAttackTransition, this);
	m_Transitions[0][STAT_ATTACK] = FSM_CALLBACK(MonsterDevil::attackTransition, this);


	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_IDLE])->setAnimation(AT_DEVIL_IDLE, this);
	m_Renders[0][STAT_MOVE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_MOVE])->setAnimation(AT_DEVIL_MOVE, this);
	m_Renders[0][STAT_READYATTACK] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_READYATTACK])->setAnimation(AT_DEVIL_IDLE, this);
	m_Renders[0][STAT_ATTACK] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_ATTACK])->setAnimation(AT_DEVIL_ATTACK, this);

	for (unsigned int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	//arrow 설정
	m_ArrowAniComponent = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_ArrowAniComponent->setAnimation(AT_DEVIL_ARROW, this, 2, true);
	addComponent(m_ArrowAniComponent);

	////info 설정
	auto data = GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_DEVIL);

	if (data != nullptr)
	{
		m_Info = *GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_DEVIL);
	}

	m_Info.m_CurrentHp = m_Info.m_MaxHp;


	return true;
}




void MonsterDevil::idleTransition(Creature* target, double dTime, int idx)
{
	cocos2d::Point playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	cocos2d::Point ownPos = this->getPosition();
	float distance = sqrt((playerPos.x - ownPos.x) * (playerPos.x - ownPos.x) +
						  (playerPos.y - ownPos.y) * (playerPos.y - ownPos.y));
	
	if (distance <= m_Info.m_AttackRange)
	{
		m_TargetPos = playerPos;
		enterReadyAttack();
		target->setState(idx, MonsterDevil::STAT_READYATTACK);
	}

}

void MonsterDevil::move(Creature* target, double dTime, int idx)
{

}


void MonsterDevil::moveTransition(Creature* target, double dTime, int idx)
{
	cocos2d::Point playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	cocos2d::Point ownPos = this->getPosition();
	float distance = sqrt((playerPos.x - ownPos.x) * (playerPos.x - ownPos.x) + 
						  (playerPos.y - ownPos.y) * (playerPos.y - ownPos.y));


}

void MonsterDevil::attack(Creature* target, double dTime, int idx)
{
}

void MonsterDevil::enterAttack()
{
	GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_THUNDER, cocos2d::Point::ZERO,
										 DIR_NONE, cocos2d::Size::ZERO, m_Info.m_MeleeDamage,
										 cocos2d::Vec2::ZERO, m_TargetPos);
}

void MonsterDevil::attackTransition(Creature* target, double dTime, int idx)
{
	cocos2d::Point playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	cocos2d::Point ownPos = this->getPosition();
	float distance = sqrt((playerPos.x - ownPos.x) * (playerPos.x - ownPos.x) +
						  (playerPos.y - ownPos.y) * (playerPos.y - ownPos.y));

	if (distance <= m_Info.m_AttackRange)
	{
		m_TargetPos = playerPos;
		enterReadyAttack();
		target->setState(idx, MonsterDevil::STAT_READYATTACK);
	}

	/*else
	{
		target->setState(idx, MonsterDevil::STAT_MOVE);
	}
*/
}

void MonsterDevil::readyAttack(Creature* target, double dTime, int idx)
{
	

}

void MonsterDevil::enterReadyAttack()
{
	//상대좌표
	
	m_ArrowAniComponent->getSprite()->setPosition(m_TargetPos - getPosition());
	m_ArrowAniComponent->enter();

}

void MonsterDevil::readyAttackTransition(Creature* target, double dTime, int idx)
{
	if (m_ArrowAniComponent->getAniExit())
	{
		enterAttack();
		target->setState(idx, MonsterDevil::STAT_ATTACK);
	}
}

void MonsterDevil::update(float dTime)
{
	Creature::update(dTime);

	int nowTime = GET_GAME_MANAGER()->getMicroSecondTime();

	
}

void MonsterDevil::enter()
{
}

void MonsterDevil::exit()
{
	m_IsExit = true;

	//시체 만들고 
}

const AllStatus& MonsterDevil::getInfo() const
{
	return m_Info;
}







