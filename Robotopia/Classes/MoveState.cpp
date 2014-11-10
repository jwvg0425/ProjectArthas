#include "pch.h"
#include "MoveState.h"
#include "PhysicsComponent.h"
#include "CommonInfo.h"

bool Arthas::MoveState::init()
{
	if (!StateComponent::init())
	{
		return false;
	}

	m_Speed = 0;
	m_Direction = 0;
	m_Type = STAT_MOVE;

	return true;
}

void Arthas::MoveState::enter()
{
	CommonInfo* infoComponent = (CommonInfo*)m_Ref->getComponent(IT_COMMON);

	if (infoComponent)
	{
		CommonInfo::Info info = infoComponent->getInfo();
		info.dir = m_Direction;
		infoComponent->setInfo(info);
	}

	if (m_IsPhysics)
	{
		cocos2d::PhysicsBody* physicsBody = ((PhysicsComponent*)m_Ref->getComponent(CT_PHYSICS))->getBody();
		cocos2d::Vect speed = physicsBody->getVelocity();
		speed.x = 0;

		physicsBody->setVelocity(getMovedPos(speed, m_Direction, m_Speed));
	}
}

void Arthas::MoveState::exit()
{
	if (m_IsPhysics)
	{
		cocos2d::PhysicsBody* physicsBody = ((PhysicsComponent*)m_Ref->getComponent(CT_PHYSICS))->getBody();
		cocos2d::Vect speed = physicsBody->getVelocity();

		if (m_Direction & DIR_UP || m_Direction & DIR_DOWN)
		{
			speed.y = 0;
		}
		if (m_Direction & DIR_LEFT || m_Direction & DIR_RIGHT)
		{
			speed.x = 0;
		}
		physicsBody->setVelocity(speed);
	}
}

void Arthas::MoveState::update(float dTime)
{
	if (!m_IsPhysics)
	{
		auto refPos = m_Ref->getPosition();

		m_Ref->setPosition(getMovedPos(refPos, m_Direction, m_Speed*dTime));
	}
}

void Arthas::MoveState::setAttribute(Component* ref, Direction dir, float speed, bool isPhysics /*= true*/)
{
	m_Ref = ref;
	m_Speed = speed;
	m_Direction = dir;
	m_IsPhysics = isPhysics;
	if (dir == DIR_LEFT)
		m_Type = STAT_MOVE_LEFT;
	else if (dir == DIR_RIGHT)
		m_Type = STAT_MOVE_RIGHT;
}

cocos2d::Point Arthas::MoveState::getMovedPos(cocos2d::Point nowPos, Direction dir, float speed)
{
	cocos2d::Point movedPos = nowPos;

	CommonInfo* infoComponent = (CommonInfo*)m_Ref->getComponent(IT_COMMON);

	if (infoComponent)
	{
		speed = infoComponent->getInfo().speed;
	}

	//현재 4방향만 지원.
	switch (dir)
	{
	case DIR_UP:
		movedPos.y += speed;
		break;
	case DIR_RIGHT:
		movedPos.x += speed;
		break;
	case DIR_DOWN:
		movedPos.y -= speed;
		break;
	case DIR_LEFT:
		movedPos.x -= speed;
		break;
	}

	return movedPos;
}

