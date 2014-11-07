#include "pch.h"
#include "GoToState.h"
#include "PhysicsComponent.h"
#include "CommonInfo.h"

bool Arthas::GoToState::init()
{
	if(!StateComponent::init())
	{
		return false;
	}

	m_RequiredTime = 0.f;
	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;
	m_Type = STAT_MOVE;

	return true;
}

void Arthas::GoToState::enter()
{
	m_Velocity = getMovingVelocity(m_Ref->getPosition(), m_Destination, m_RequiredTime);
}

void Arthas::GoToState::exit()
{
	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;
}

void Arthas::GoToState::update(float dTime)
{
	cocos2d::Point position = m_Ref->getPosition();
	if(isAlmostThere(position))
	{

	}
	else
	{ 
		position.x += m_Velocity.x*dTime;
		position.y += m_Velocity.y*dTime;
		m_Ref->setPosition(position);
	}
}



void Arthas::GoToState::initState(Component* subject, cocos2d::Point dstPos, float requiredTime)
{
	m_RequiredTime = requiredTime;
	m_Destination = dstPos;
	m_Ref = subject;
}

cocos2d::Point Arthas::GoToState::getMovingVelocity(cocos2d::Point srcPos, cocos2d::Point dstPos, float requiredTime)
{
	m_Velocity.x = ( srcPos.x - dstPos.x ) / requiredTime;
	m_Velocity.y = ( srcPos.y - dstPos.y ) / requiredTime;
	return m_Velocity;
}

bool Arthas::GoToState::isAlmostThere(cocos2d::Point currentPos)
{
	int almost = 0.01f;
	if(abs(currentPos.x - m_Destination.x) < almost &&
	   abs(currentPos.y - m_Destination.y) < almost)
	{
		return true;
	}
	return false;
}

