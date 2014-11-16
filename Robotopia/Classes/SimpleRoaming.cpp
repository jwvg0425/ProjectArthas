#include "pch.h"
#include "SimpleRoaming.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "TriggerManager.h"
#include "MoveState.h"
#include "PositionTrigger.h"
#include "GoToState.h"

bool SimpleRoamingFSM::init()
{
	if(!FSMComponent::init())
		return false;

	m_Type = FSMT_SIMPLE_ROAMING;
	return true;
}

void SimpleRoamingFSM::initRoaming(BaseComponent* parent, cocos2d::Point leftPoint, cocos2d::Point rightPoint, float time)
{
	GoToState* goToLeft = GET_COMPONENT_MANAGER()->createComponent<GoToState>();
	goToLeft->initState(parent, leftPoint, time);
	GoToState* goToRight = GET_COMPONENT_MANAGER()->createComponent<GoToState>();
	goToRight->initState(parent, rightPoint, time);

	PositionTrigger* leftPointTrigger = GET_TRIGGER_MANAGER()->createTrigger<PositionTrigger>();
	leftPointTrigger->initPositionTrigger(leftPoint);
	PositionTrigger* rightPointTrigger = GET_TRIGGER_MANAGER()->createTrigger<PositionTrigger>();
	rightPointTrigger->initPositionTrigger(rightPoint);


	addComponent(goToLeft);
	goToLeft->addTransition(std::make_pair(leftPointTrigger, goToRight));
	addComponent(goToRight);
	goToRight->addTransition(std::make_pair(rightPointTrigger, goToLeft));

	m_NowState = goToRight;
}

void SimpleRoamingFSM::enter()
{

	
}

void SimpleRoamingFSM::exit()
{

}

