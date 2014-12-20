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
	m_RotateModule = cocos2d::RotateBy::create(ROTATE_DURATION, ROTATE_ANGLE);
	m_RotateModule->retain();
	//물리 초기화
	m_Rail = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	( (SpriteComponent*) m_Rail )->initSprite(ST_BOSS_RAIL, this);
	addComponent(m_Rail);
	m_Rail->enter();

	m_Head = BossHead::create();
	addChild(m_Head);
	m_Head->setPosition(cocos2d::Point(0, RAIL_RADIUS));
	return true;
}

void BossFirst::update(float dTime)
{
	if(m_Head->getState(0) == BossHead::STAT_IDLE)
	{
		enterMove();
		m_Head->setMoving(true);
	}
	m_Head->update(dTime);
}

void BossFirst::enter()
{

}

void BossFirst::exit()
{

}

void BossFirst::enterMove()
{
	cocos2d::log("dd");
	m_IsMoving = true;
	m_RotateNum = MIN_ROTATE_NUM + rand() % MAX_ROTATE_NUM;
	auto repeat = cocos2d::Repeat::create(m_RotateModule, m_RotateNum);
	auto endMove = cocos2d::CallFuncN::create(CC_CALLBACK_1(BossFirst::exitMove, this));
	auto sequence = cocos2d::Sequence::create(repeat, endMove, nullptr);
	runAction(sequence);
}

void BossFirst::exitMove(cocos2d::Node* ref)
{
	m_IsMoving = false;
	m_Head->setAttacking(true);  
}
