#include "pch.h"
#include "BossHead.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"

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
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(false);
	m_Body->retain();
	setPhysicsBody(m_Body);

	initFSM(1);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = FSM_CALLBACK(BossHead::move, this);
	m_FSMs[0][STAT_ATTACK] = FSM_CALLBACK(BossHead::attack, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(BossHead::idleTransition, this);
	m_Transitions[0][STAT_MOVE] = FSM_CALLBACK(BossHead::moveTransition, this);
	m_Transitions[0][STAT_ATTACK] = FSM_CALLBACK(BossHead::attackTransition, this);


	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = NULL;
	m_Renders[0][STAT_MOVE] = NULL;
	m_Renders[0][STAT_ATTACK] = NULL;



	m_ModeRender[MODE_WIDTH] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_ModeRender[MODE_WIDTH]->initSprite(ST_BOSS_MODE_WIDTH, this);
	m_ModeRender[MODE_HEIGHT] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_ModeRender[MODE_HEIGHT]->initSprite(ST_BOSS_MODE_HEIGHT, this);
	m_ModeRender[MODE_MISSLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_ModeRender[MODE_MISSLE]->initSprite(ST_BOSS_MODE_MISSILE, this);
	for(unsigned int i = 0; i < MODE_NUM; i++)
	{
		addComponent(m_ModeRender[i]);
	}
	m_ModeRender[MODE_WIDTH]->enter();

	return true;
}


void BossHead::update(float dTime)
{
	Creature::update(dTime);
}


void BossHead::enter()
{

}


void BossHead::exit()
{

}

bool BossHead::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void BossHead::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

void BossHead::setAttacking(bool isAttack) 
{
	m_IsAttacking = isAttack;
}

void BossHead::setMoving(bool isMoving)
{
	m_IsMoving = isMoving;
}

const AllStatus& BossHead::getInfo() const
{
	return m_Info;
}

void BossHead::move(Creature* target, double dTime, int idx)
{
	timeval time = GET_GAME_MANAGER()->getTime();
	int checkValue = (time.tv_sec) % MODE_NUM;
	if(m_CurrentMode != checkValue)
	{
		m_ModeRender[m_CurrentMode]->exit();
		m_CurrentMode = checkValue;
		m_ModeRender[m_CurrentMode]->enter();
	}
}

void BossHead::enterMove()
{

}

void BossHead::exitMove()
{

}

void BossHead::attack(Creature* target, double dTime, int idx)
{

}

void BossHead::enterAttack()
{

}

void BossHead::exitAttack()
{

}

void BossHead::idleTransition(Creature* target, double dTime, int idx)
{
	if(m_IsMoving)
	{
		enterMove();
		setState(0, STAT_MOVE);
	}
}

void BossHead::moveTransition(Creature* target, double dTime, int idx)
{
	if(m_IsAttacking)
	{
		enterAttack();
		setState(0, STAT_ATTACK);
	}
}

void BossHead::attackTransition(Creature* target, double dTime, int idx)
{
	if(!m_IsAttacking)
	{
		enterAttack();
		setState(0, STAT_IDLE);
	}
}
