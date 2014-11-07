#include "pch.h"
#include "SimpleRoaming.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "TriggerManager.h"
#include "MoveState.h"
#include "PositionTrigger.h"

bool Arthas::SimpleRoamingFSM::init()
{
	if(!FSMComponent::init())
		return false;

	m_Type = FSMT_SIMPLE_ROAMING;
	return true;
}

void Arthas::SimpleRoamingFSM::initRoaming(const cocos2d::Point& leftPoint, const cocos2d::Point& rightPoint, float speed)
{
	m_LeftPoint = leftPoint;
	m_RightPoint = rightPoint;
	m_Speed = speed;

	MoveState* leftMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	leftMove->setAttribute(m_Parent, DIR_LEFT, m_Speed, false);

	MoveState* rightMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
	rightMove->setAttribute(m_Parent, DIR_RIGHT, m_Speed, false);

	PositionTrigger* leftPointTrigger = GET_TRIGGER_MANAGER()->createTrigger<PositionTrigger>();
	leftPointTrigger->initPositionTrigger(m_LeftPoint);

	PositionTrigger* rightPointTrigger = GET_TRIGGER_MANAGER()->createTrigger<PositionTrigger>();
	rightPointTrigger->initPositionTrigger(m_RightPoint);


	addComponent(leftMove);
	leftMove->addTransition(std::make_pair(leftPointTrigger, rightMove));
	addComponent(rightMove);
	rightMove->addTransition(std::make_pair(rightPointTrigger, leftMove));

	m_NowState = rightMove;
}

void Arthas::SimpleRoamingFSM::enter()
{

	
}

void Arthas::SimpleRoamingFSM::exit()
{

}

