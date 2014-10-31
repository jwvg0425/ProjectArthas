#include "MoveState.h"
#include "PhysicsComponent.h"

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
	if (m_IsPhysics)
	{
		cocos2d::PhysicsBody* physicsBody = ((PhysicsComponent*)m_Parent->getComponent(CT_PHYSICS))->getBody();
		cocos2d::Vect speed = physicsBody->getVelocity();

		physicsBody->setVelocity(speed);
	}
}

void Arthas::MoveState::exit()
{
	if (m_IsPhysics)
	{
		cocos2d::PhysicsBody* physicsBody = ((PhysicsComponent*)m_Parent->getComponent(CT_PHYSICS))->getBody();
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
		auto parent = getParent()->getParent();
		auto parentPos = parent->getPosition();

		parent->setPosition(getMovedPos(parentPos, m_Direction, m_Speed*dTime));
	}
}

void Arthas::MoveState::setAttribute(Direction dir, float speed, bool isPhysics /*= true*/)
{
	m_Speed = speed;
	m_Direction = dir;
	m_IsPhysics = isPhysics;
}

cocos2d::Point Arthas::MoveState::getMovedPos(cocos2d::Point nowPos, Direction dir, float speed)
{
	cocos2d::Point movedPos = nowPos;

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

