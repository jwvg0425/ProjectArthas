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
#include "Missile.h"
#include "ComponentManager.h"
#include "PathFinder.h"
#include "Corpse.h"


#define DAMAGE 20
#define ATTACKAFTERDELAY 2000
#define SEARCHMOVEWAYTIME 3000

bool MonsterDevil::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Type = OT_MONSTER_DEVIL;
	m_PathFinder = new PathFinder();

	////info 설정
	auto data = GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_DEVIL);

	if (data != nullptr)
	{
		m_Info = *GET_DATA_MANAGER()->getMonsterInfo(OT_MONSTER_DEVIL);
	}

	m_Info.m_CurrentHp = m_Info.m_MaxHp;



	//물리 초기화

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(m_Info.m_Size.width, m_Info.m_Size.height), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_BLOCK | PHYC_PLAYER | PHYC_MISSILE | PHYC_FLOOR);
	m_Body->setCategoryBitmask(PHYC_MONSTER);
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_MISSILE);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(true);
	m_Body->setGravityEnable(false);
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
	((AnimationComponent*)m_Renders[0][STAT_ATTACK])->setAnimation(AT_DEVIL_ATTACK, this, 1, true);

	for (unsigned int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	//arrow 설정
	m_ArrowAniComponent = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_ArrowAniComponent->setAnimation(AT_DEVIL_ARROW, this, 2, true);
	addComponent(m_ArrowAniComponent);



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
		//readyAttack으로
		m_TargetPos = playerPos;
		enterReadyAttack();
		target->setState(idx, MonsterDevil::STAT_READYATTACK);
	}
	else if (distance <= m_MaxSightBound)
	{
		//move로

		enterMove();
		target->setState(idx, MonsterDevil::STAT_MOVE);

	}

}

void MonsterDevil::move(Creature* target, double dTime, int idx)
{
	if (getPositionX() < GET_STAGE_MANAGER()->getPlayer()->getPositionX())
	{
		m_Info.m_UpperDir = DIR_RIGHT;
	}
	else
	{
		m_Info.m_UpperDir = DIR_LEFT;
	}
}


void MonsterDevil::enterMove()
{
	m_IsArrived = false;
	m_MoveStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
	
	auto playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	auto myPos = getPosition();
	auto tileSize = GET_DATA_MANAGER()->getTileSize();

	int goalX = playerPos.x / tileSize.width;
	int goalY = playerPos.y / tileSize.height;
	int startX = myPos.x / tileSize.width;
	int startY = myPos.y / tileSize.height;

	if (m_PathFinder->initFinder(startX, startY, goalX, goalY))
	{

		m_PathFinder->getPath(&m_Path);

		m_DstPos.x = m_Path[0].x * tileSize.width + tileSize.width/2;
		m_DstPos.y = m_Path[0].y * tileSize.height + tileSize.height/2;

		float distance = sqrt((m_DstPos.x - myPos.x)*(m_DstPos.x - myPos.x) +
							  (m_DstPos.y - myPos.y)*(m_DstPos.y - myPos.y));

		cocos2d::Vec2 velocity;
		velocity.x = m_Info.m_Speed * (m_DstPos.x - myPos.x) / distance;
		velocity.y = m_Info.m_Speed * (m_DstPos.y - myPos.y) / distance;
		m_Body->setVelocity(velocity);
	}

}


void MonsterDevil::moveTransition(Creature* target, double dTime, int idx)
{
	cocos2d::Point playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	cocos2d::Point ownPos = this->getPosition();
	float distance = sqrt((playerPos.x - ownPos.x) * (playerPos.x - ownPos.x) + 
						  (playerPos.y - ownPos.y) * (playerPos.y - ownPos.y));

	if (distance < m_Info.m_AttackRange)
	{
		m_TargetPos = playerPos;
		exitMove();
		enterReadyAttack();
		target->setState(idx, MonsterDevil::STAT_READYATTACK);
	}
	else if (distance < m_MaxSightBound && checkArrived())
	{
		exitMove();
		enterMove();
		target->setState(idx, MonsterDevil::STAT_MOVE);

	}
	else if (distance > m_MaxSightBound)
	{
		exitMove();
		target->setState(idx, MonsterDevil::STAT_IDLE);
	}
	/*else if (!isMoving())
	{
		exitMove();
		enterMove();
		target->setState(idx, MonsterDevil::STAT_MOVE);
	}*/
	


}

void MonsterDevil::attack(Creature* target, double dTime, int idx)
{

	int arrowPosX = (m_ArrowAniComponent->getSprite())->getPosition().x;

	if (arrowPosX > 0)
	{
		m_Info.m_UpperDir = DIR_RIGHT;
	}
	else
	{
		m_Info.m_UpperDir = DIR_LEFT;
	}
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

	if (distance < m_Info.m_AttackRange && ((AnimationComponent*)m_Renders[0][STAT_ATTACK])->getAniExit())
	{
		m_TargetPos = playerPos;
		enterReadyAttack();
		target->setState(idx, MonsterDevil::STAT_READYATTACK);
	}
	else if (distance < m_MaxSightBound && ((AnimationComponent*)m_Renders[0][STAT_ATTACK])->getAniExit())
	{
		exitMove();
		enterMove();
		target->setState(idx, MonsterDevil::STAT_MOVE);
	}
	else if (distance > m_MaxSightBound && ((AnimationComponent*)m_Renders[0][STAT_ATTACK])->getAniExit())
	{
		target->setState(idx, MonsterDevil::STAT_IDLE);
	}

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

void MonsterDevil::enter()
{
	resume();
}

void MonsterDevil::exit()
{	
}

const AllStatus& MonsterDevil::getInfo() const
{
	return m_Info;
}

bool MonsterDevil::checkArrived()
{
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	if (!m_Path.size())
	{
		return true;
	}

	
	if (abs(m_DstPos.x - getPosition().x) < 3 &&
		abs(m_DstPos.y - getPosition().y) < 3)
	{
		return true;
	}


	return false;
}

void MonsterDevil::exitMove()
{
	m_Body->setVelocity(cocos2d::Vec2::ZERO);
}

bool MonsterDevil::isMoving()
{
	if (m_Body->getVelocity().x == 0 &&
	   m_Body->getVelocity().y == 0)
	{
		return false;
	}

	return true;
}

bool MonsterDevil::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*)bodyA->getNode();
	auto componentB = (BaseComponent*)bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;


	//어떤것 끼리 부딪혔는지는 안가르쳐주기 때문에
	//여기서 어느쪽이 monsterDevil인지 밝혀낸다.
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


	//FLOOR 충돌 무시 
	if (enemyComponent->getType() == OT_FLOOR)
	{
		return false;
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

void MonsterDevil::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

void MonsterDevil::dead()
{
	//화살표 컴포넌트 지우고
	if (m_ArrowAniComponent)
	{
		removeComponent(m_ArrowAniComponent);
	}

	//시체 만들고 
	auto corpse = GET_COMPONENT_MANAGER()->createComponent<Corpse>();
	int roomNum = GET_STAGE_MANAGER()->getRoomNum();
	GET_STAGE_MANAGER()->addObject(corpse, roomNum, getPosition(), RoomZOrder::GAME_OBJECT);

	//자신 없애고
	removeFromParent();
}
