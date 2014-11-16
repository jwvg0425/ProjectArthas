#include "pch.h"
#include "GoToState.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "PhysicsComponent.h"
#include "CommonInfo.h"
#include "PositionTrigger.h"
#include "ObserverComponent.h"

bool GoToState::init()
{
	if(!StateComponent::init())
	{
		return false;
	}

	m_RequiredTime = 0.f;
	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;
	m_Type = STAT_GOTO;

	return true;
}

void GoToState::enter()
{
	m_Velocity = getMovingVelocity(m_Ref->getPosition(), m_Destination, m_RequiredTime);
}

void GoToState::exit()
{
	m_Velocity.x = 0.f;
	m_Velocity.y = 0.f;
}

void GoToState::update(float dTime)
{
	cocos2d::Point position = m_Ref->getPosition();
	if(isAlmostThere(position))
	{
		auto arriveTrigger = GET_TRIGGER_MANAGER()->createTrigger<PositionTrigger>();
		arriveTrigger->initPositionTrigger(m_Destination);
		auto observer = (ObserverComponent*) m_Ref->getComponent(CT_OBSERVER);
		observer->addTrigger(arriveTrigger);
	}
	else
	{
		position.x += m_Velocity.x*dTime;
		position.y += m_Velocity.y*dTime;
		m_Ref->setPosition(position);
	}
}



void GoToState::initState(BaseComponent* subject, cocos2d::Point dstPos, float requiredTime)
{
	m_RequiredTime = requiredTime;
	m_Destination = dstPos;
	m_Ref = subject;
	m_Velocity = getMovingVelocity(m_Ref->getPosition(), m_Destination, m_RequiredTime);
}

cocos2d::Point GoToState::getMovingVelocity(cocos2d::Point srcPos, cocos2d::Point dstPos, float requiredTime)
{
	m_Velocity.x = ( dstPos.x - srcPos.x ) / requiredTime;
	m_Velocity.y = ( dstPos.y - srcPos.y ) / requiredTime;
	return m_Velocity;
}

bool GoToState::isAlmostThere(cocos2d::Point currentPos)
{
	float almost = 0.1f;
	if(abs(currentPos.x - m_Destination.x) <= almost &&
	   abs(currentPos.y - m_Destination.y) <= almost)
	{
		return true;
	}
	return false;
}

