#include "pch.h"
#include "MonsterRush.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "ObserverComponent.h"
#include "PhysicsComponent.h"
#include "CommonInfo.h"
#include "PhysicsInfo.h"
#include "ResourceManager.h"
#include "AnimationComponent.h"

bool MonsterRush::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}

	auto info = GET_COMPONENT_MANAGER()->createComponent<CommonInfo>();
	addComponent(info);

	CommonInfo::Info tmp;
	tmp.dir = DIR_RIGHT;
	tmp.speed = 200;
	tmp.jumpSpeed = 500;
	tmp.size.width = RUSH_WIDTH;
	tmp.size.height = RUSH_HEIGHT;
	tmp.maxHp = 100;
	tmp.maxSteam = 100;
	tmp.currentHp = 100;
	tmp.currentSteam = 100;

	info->setInfo(tmp);

	m_Type = OT_MONSTER_RUSH;

	//물리 초기화
	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, RUSH_WIDTH, RUSH_HEIGHT), true, 0, 0, 0,
						 PHYC_PLAYER | PHYC_BLOCK, PHYC_MONSTER, PHYC_BLOCK | PHYC_FLOOR);
	physics->addIgnoreCollision(OT_FLOOR, DIR_UP);

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(RUSH_WIDTH, RUSH_HEIGHT), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_PLAYER|PHYC_BLOCK);
	m_Body->setCategoryBitmask(PHYC_MONSTER);
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MonsterRush::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(MonsterRush::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//FSM 초기화
	initFSM(1);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = move;

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = idleTransition;
	m_Transitions[0][STAT_MOVE] = moveTransition;

	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	( (AnimationComponent*) m_Renders[0][STAT_IDLE] )->setAnimation(AT_MONSTER_RUSH_IDLE, this);
	m_Renders[0][STAT_MOVE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	( (AnimationComponent*) m_Renders[0][STAT_MOVE] )->setAnimation(AT_MONSTER_RUSH_MOVE, this);

	for(int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	//info 설정

	m_Info.speed = 200;
	m_Info.jumpSpeed = 500;
	m_Info.dir = DIR_RIGHT;
	m_Info.size = cocos2d::Size(32, 32);

	return true;
}

void MonsterRush::enter()
{
	resume();
}

void MonsterRush::exit()
{
}

void MonsterRush::idleTransition(Thing* target, double dTime, int idx)
{

}

void MonsterRush::move(Thing* target, double dTime, int idx)
{
}

void MonsterRush::enterMove(Thing* target, double dTime, Direction dir)
{
	auto velocity = ( (MonsterRush*) target )->getBody()->getVelocity();

	( (MonsterRush*) target )->setDirection(dir);

	//속도 임시로 지정.
	if(dir == DIR_LEFT)
	{
		velocity.x = -200;
	}
	else if(dir == DIR_RIGHT)
	{
		velocity.x = 200;
	}

	( (MonsterRush*) target )->getBody()->setVelocity(velocity);
}

void MonsterRush::exitMove(Thing* target, double dTime)
{
	auto velocity = ( (MonsterRush*) target )->getBody()->getVelocity();

	velocity.x = 0;

	( (MonsterRush*) target )->getBody()->setVelocity(velocity);
}

void MonsterRush::moveTransition(Thing* target, double dTime, int idx)
{
	
}

bool MonsterRush::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}


void MonsterRush::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

cocos2d::PhysicsBody* MonsterRush::getBody()
{
	return m_Body;
}

const PlayerInfo& MonsterRush::getInfo()
{
	return m_Info;
}

void MonsterRush::update(float dTime)
{
	if(m_Info.dir == DIR_LEFT)
	{
		for(int i = 0; i < m_Renders[0].size(); i++)
		{
			m_Renders[0][i]->setFlippedX(true);
		}
	}
	else
	{
		for(int i = 0; i < m_Renders[0].size(); i++)
		{
			m_Renders[0][i]->setFlippedX(false);
		}
	}

	Thing::update(dTime);
}

void MonsterRush::setDirection(Direction dir)
{
	m_Info.dir = dir;
}
