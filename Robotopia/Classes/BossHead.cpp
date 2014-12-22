#include "pch.h"
#include "BossHead.h"
#include "GameManager.h"
#include "StageManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "MissileManager.h"
#include "AimingMissile.h"
#include "Corpse.h"

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

	initInfo();

	return true;
}

void BossHead::initInfo()
{
	m_Type = OT_MONSTER_BOSS_FIRST;
	m_PreDelay = PRE_DELAY;
	m_PostDelay = POST_DELAY;
	m_Info.m_MaxHp = MAX_HP;
	m_Info.m_CurrentHp = MAX_HP;
	m_Info.m_AttackRange = ATTACK_RANGE;
	m_LastCorpseNum = MAX_CORPSE_NUM;
	m_HpUnit = m_Info.m_MaxHp / MAX_CORPSE_NUM;
}


void BossHead::update(float dTime)
{
	Creature::update(dTime);
}


void BossHead::enter()
{
	m_Origin = getParent()->getPosition();
	m_Distance = getPosition().y;
}


void BossHead::exit()
{

}

bool BossHead::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*) bodyA->getNode();
	auto componentB = (BaseComponent*) bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;

	if(componentA->getType() == getType())
	{
		enemyComponent = componentB;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		isComponentA = false;
	}

	//¹Ì»çÀÏÀÌ¶û Ãæµ¹ Ã³¸®
	if(enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_MISSILE)
	{
		Missile* missile = static_cast<Missile*>( enemyComponent );

		//¼ö·ùÅºÀº µ© ¾È ÀÔÀ½
		if(missile->getType() == OT_MISSILE_GRENADE)
		{
			return false;
		}

		//¸÷ÀÌ ½ð °Ç ¾È ¸ÂÀ½.
		if(!missile->isPlayerMissile())
		{
			return false;
		}

		float damage = missile->getDamage();

		m_Info.m_CurrentHp -= damage * 100 / ( 100 + m_Info.m_DefensivePower );

		if(m_Info.m_CurrentHp / m_HpUnit < m_LastCorpseNum)
		{
			auto corpse = GET_COMPONENT_MANAGER()->createComponent<Corpse>();
			int roomNum = GET_STAGE_MANAGER()->getRoomNum();
			GET_STAGE_MANAGER()->addObject(corpse, roomNum, m_Origin, RoomZOrder::GAME_OBJECT);
			--m_LastCorpseNum;
		}

		//»ç¸Á
		if(m_Info.m_CurrentHp <= 0)
		{
			m_IsDead = true;
		}
	}
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
	auto rotating = cocos2d::RotateBy::create( 1.f , 40 );
	auto repeat = cocos2d::RepeatForever::create( rotating );
	runAction( repeat );
}

void BossHead::exitMove()
{
	m_IsMoving = false;
	stopAllActions();
}

void BossHead::attack(Creature* target, double dTime, int idx)
{

}

void BossHead::enterAttack()
{
	auto delay = cocos2d::DelayTime::create( m_PreDelay );
	auto launch = cocos2d::CallFuncN::create( CC_CALLBACK_1( BossHead::launch , this ) );
	auto postDelay = cocos2d::DelayTime::create( m_PostDelay );
	auto seizeFire = cocos2d::CallFuncN::create( CC_CALLBACK_1( BossHead::seizeFire , this ) );
	auto sequence = cocos2d::Sequence::create( delay , launch , postDelay, seizeFire, nullptr);
	runAction( sequence );
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
		exitMove();
		enterAttack();
		setState(0, STAT_ATTACK);
	}
}

void BossHead::attackTransition(Creature* target, double dTime, int idx)
{
	if(!m_IsAttacking)
	{
		exitAttack();
		setState(0, STAT_IDLE);
	}
}

void BossHead::launch( cocos2d::Node* ref )
{
	float rotation = getParent()->getRotation() - 90;
	int cicle = static_cast< int >( rotation ) / 180;
	float radian = MATH_PIOVER2 * rotation / 90;
	cocos2d::Point pos;
	pos.x = m_Distance * cos( radian );
	pos.y = -m_Distance * sin( radian );

	cocos2d::Point globalPosition = pos + m_Origin;
	switch( m_CurrentMode )
	{
		case MODE_WIDTH:
			GET_MISSILE_MANAGER()->launchMissile( OT_MISSILE_LINEAR , globalPosition , DIR_UP );
			break;
		case MODE_HEIGHT:
			GET_MISSILE_MANAGER()->launchMissile( OT_MISSILE_LINEAR , globalPosition , DIR_RIGHT );
			break;
		case MODE_MISSLE:
			radiateAttack(globalPosition);
			break;
		default:
			break;
	}
}

void BossHead::seizeFire( cocos2d::Node* ref )
{
	m_IsAttacking = false;
}

void BossHead::makeRadiateMissile( cocos2d::Node* ref , float startDegree ,cocos2d::Point startPos )
{
	for( int degree = startDegree; degree <= 360 + startDegree; degree += 30 )
	{
		auto missile = GET_MISSILE_MANAGER()->launchMissile( OT_MISSILE_AIMING , startPos, DIR_NONE, cocos2d::Size(HEAD_RADIUS, HEAD_RADIUS));
		static_cast< AimingMissile* >( missile )->setPlayerMissile( false );
		static_cast< AimingMissile* >( missile )->setDegree( degree );
		static_cast< AimingMissile* >( missile )->setMaxDistance( m_Info.m_AttackRange );
	}
}

void BossHead::radiateAttack(cocos2d::Point startPos)
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> attackQueue;
	for( int i = 0; i < 10; ++i )
	{
		auto radiate = cocos2d::CallFuncN::create( CC_CALLBACK_1( BossHead::makeRadiateMissile , this , i * 10 , startPos) );
		auto delay = cocos2d::DelayTime::create( 0.2f );
		attackQueue.pushBack( radiate );
		attackQueue.pushBack( delay );
	}
	auto sequence = cocos2d::Sequence::create( attackQueue );
	runAction( sequence );
}

void BossHead::dead()
{
	exit();
	removeFromParent();
}

