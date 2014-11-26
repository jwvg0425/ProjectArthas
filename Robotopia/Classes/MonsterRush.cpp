#include "pch.h"
#include "MonsterRush.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "DataManager.h"
#include "StageManager.h"
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
						 PHYC_BLOCK, PHYC_MONSTER, PHYC_BLOCK | PHYC_FLOOR);
	physics->addIgnoreCollision(OT_FLOOR, DIR_UP);

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(RUSH_WIDTH, RUSH_HEIGHT), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_BLOCK);
	m_Body->setCategoryBitmask(PHYC_MONSTER);
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(true);
	m_Body->retain();
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

void MonsterRush::idleTransition(Creature* target, double dTime, int idx)
{
	enterMove(target, dTime, DIR_RIGHT);
	target->setState(idx, MonsterRush::STAT_MOVE);
}

void MonsterRush::move(Creature* target, double dTime, int idx)
{
	auto pos = target->getPosition();
	auto velocity = ( (MonsterRush*) target )->getBody()->getVelocity();
	pos += velocity*dTime;
	target->setPosition(pos);
}

void MonsterRush::enterMove(Creature* target, double dTime, Direction dir)
{
	auto monster = (MonsterRush*) target;
	auto velocity = monster->getBody()->getVelocity();
	monster->setDirection(dir);

	//속도 임시로 지정.
	if(dir == DIR_LEFT)
	{
		velocity.x = -100;
	}
	else if(dir == DIR_RIGHT)
	{
		velocity.x = 100;
	}
	monster->getBody()->setVelocity(velocity);
}

void MonsterRush::exitMove(Creature* target, double dTime)
{
	auto monster = (MonsterRush*) target;
	auto velocity = monster->getBody()->getVelocity();

	velocity.x = 0;

	monster->getBody()->setVelocity(velocity);
}

void MonsterRush::moveTransition(Creature* target, double dTime, int idx)
{
	auto monster = (MonsterRush*) target;
	//->move
	if( !monster->isStepForwardable() )
	{
		auto info = monster->getInfo();
		auto dir = ( info.dir == DIR_LEFT ) ? DIR_RIGHT : DIR_LEFT;
		enterMove(target, dTime, dir);
	}
}

bool MonsterRush::onContactBegin(cocos2d::PhysicsContact& contact)
{
// 	auto bodyA = contact.getShapeA()->getBody();
// 	auto bodyB = contact.getShapeB()->getBody();
// 	auto componentA = (BaseComponent*) bodyA->getNode();
// 	auto componentB = (BaseComponent*) bodyB->getNode();
// 	BaseComponent* other;
// 	if(componentA->getType() == getType())
// 	{
// 		other = componentB;
// 	}
// 	else
// 	{
// 		other = componentA;
// 	}
// 
// 	if(contact.getContactData()->normal.y == 0)
// 	{
// 		if(contact.getContactData()->normal.x > 0)
// 		{
// 			if(other->getPhysicsBody()->getCategoryBitmask() & PHYC_MONSTER )
// 			{
// 				enterMove(this, 0, DIR_RIGHT);
// 			}
// 		}
// 		else if(contact.getContactData()->normal.x < 0)
// 		{
// 			if( other->getPhysicsBody()->getCategoryBitmask() & PHYC_MONSTER )
// 			{
// 				enterMove(this, 0, DIR_LEFT);
// 			}
// 		}
// 	}
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
	Creature::update(dTime);
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

}

void MonsterRush::setDirection(Direction dir)
{
	m_Info.dir = dir;
}


bool MonsterRush::isStepForwardable()
{
	cocos2d::Point currentPosition = getPosition();
	cocos2d::Point nextBelowPosition;
	cocos2d::Point nextStepPosition;
	cocos2d::Vec2 velocityComplement = m_Body->getVelocity()*0.3f;
	float addSize = ( m_Info.dir == DIR_RIGHT ) ? m_Info.size.width : -m_Info.size.width;
	
	nextBelowPosition.x = currentPosition.x + addSize + velocityComplement.x;
	nextBelowPosition.y = currentPosition.y - m_Info.size.height + velocityComplement.y;

	nextStepPosition.x = currentPosition.x + addSize + velocityComplement.x;
	nextStepPosition.y = currentPosition.y + velocityComplement.y;
	
	int stageNum = GET_STAGE_MANAGER()->getStageNum();
	int roomNum = GET_STAGE_MANAGER()->getRoomNum();

	int nextBelowTile = GET_DATA_MANAGER()->getTileData(stageNum, roomNum, nextBelowPosition);
	int nextStepTile = GET_DATA_MANAGER()->getTileData(stageNum, roomNum, nextStepPosition);
	bool forwardable =  ( nextBelowTile == OT_BLOCK || nextBelowTile == OT_FLOOR ) && 
						(nextStepTile != OT_BLOCK && nextStepTile != OT_FLOOR) 
						? true : false;

	return forwardable;
}
