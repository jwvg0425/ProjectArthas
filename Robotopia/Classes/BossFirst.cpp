#include "pch.h"
#include "BossFirst.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "DataManager.h"
#include "SpriteComponent.h"
#include "BossHead.h"

bool BossFirst::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}

	m_Type = OT_MONSTER_RUSH;
	auto rotate = cocos2d::RotateBy::create(ROTATE_DURATION, ROTATE_ANGLE);
	auto callback = cocos2d::CallFuncN::create(CC_CALLBACK_1(BossFirst::endModule, this));
	m_RotateModule = cocos2d::Sequence::create(rotate, callback, NULL);
	m_RotateModule->retain();
	//물리 초기화
	m_Head = BossHead::create();
	addChild(m_Head);
	m_Head->setPosition(cocos2d::Point(0, RAIL_RADIUS));
	//FSM 초기화
	initFSM(1);
	m_States[0] = STAT_MOVE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = FSM_CALLBACK(BossFirst::move, this); 
	m_FSMs[0][STAT_ATTACK] = FSM_CALLBACK(BossFirst::attack, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(BossFirst::idleTransition, this);
	m_Transitions[0][STAT_MOVE] = FSM_CALLBACK(BossFirst::moveTransition, this);
	m_Transitions[0][STAT_ATTACK] = FSM_CALLBACK(BossFirst::attackTransition, this);


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
	Creature::update(dTime);
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
	timeval time = GET_GAME_MANAGER()->getTime();
	m_Mode = time.tv_usec % MODE_NUM;
}
void BossFirst::enterMove()
{
	m_RotateNum = MIN_ROTATE_NUM + rand() % MAX_ROTATE_NUM;
	auto act = cocos2d::Repeat::create(m_RotateModule, m_RotateNum);
	runAction(act);
}

void BossFirst::exitMove()
{
	m_RotateNum = 0;
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
	if(m_RotateNum < 1)
	{
		exitMove();
		enterAttack();
		setState(idx, STAT_ATTACK);
	}
}

void BossFirst::attackTransition(Creature* target, double dTime, int idx)
{

}

bool BossFirst::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void BossFirst::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

const AllStatus& BossFirst::getInfo() const
{
	return m_Info;
}

void BossFirst::endModule(Ref* ref)
{
	m_RotateNum--;
}

