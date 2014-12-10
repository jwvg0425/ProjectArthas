#include "pch.h"
#include "Computer.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "InputManager.h"
#include "SpriteComponent.h"
#include "GaugeBarContainer.h"

bool Computer::init()
{
	if(!NPC::init())
	{
		return false;
	}
	m_Type = OT_COMPUTER;
	m_Info.m_Size = cocos2d::Size(COMPUTER_WIDTH, COMPUTER_HEIGHT);
	bodyInit(m_Info.m_Size);

	initFSM(1);
	m_States[0] = STAT_IDLE;

	//0¹øÀº attackFSM
	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_AVAILABLE] = FSM_CALLBACK(Computer::available, this);
	m_FSMs[0][STAT_LOADING] = FSM_CALLBACK(Computer::loading, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = nullptr;
	m_Transitions[0][STAT_AVAILABLE] = FSM_CALLBACK(Computer::availableTransition, this);
	m_Transitions[0][STAT_LOADING] = FSM_CALLBACK(Computer::loadingTransition, this);


	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_IDLE]->initSprite(ST_COMPUTER_NORMAL, this);

	m_Renders[0][STAT_AVAILABLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_AVAILABLE]->initSprite(ST_COMPUTER_HEATED_01, this);

	m_Renders[0][STAT_LOADING] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_LOADING]->initSprite(ST_COMPUTER_HEATED_02, this);


	for(int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	m_Bar->initBarContainer(this, ST_BAR_CONTAINER, ST_BAR, cocos2d::Point(0, LOADING_BAR_HEIGHT));
	addComponent(m_Bar);

	return true;
}

void Computer::update(float dTime)
{
}

void Computer::exit()
{

}

void Computer::enter()
{

}

void Computer::available(Creature* target, double dTime, int idx)
{

}

void Computer::loading(Creature* target, double dTime, int idx)
{

}

void Computer::idleTransition(Creature* target, double dTime, int idx)
{
	if(m_OnContact)
	{
		availableEnter(dTime, idx);
		setState(idx, Computer::STAT_AVAILABLE);
	}
}

void Computer::availableTransition(Creature* target, double dTime, int idx)
{
	if(!m_OnContact)
	{
		availableExit(dTime, idx);
		setState(idx, Computer::STAT_IDLE);
	}
	else if(GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_PRESS)
	{
		availableExit(dTime, idx);
		loadingEnter(dTime, idx);
		setState(idx, Computer::STAT_AVAILABLE);
	}
}

void Computer::loadingTransition(Creature* target, double dTime, int idx)
{
	if(!m_OnContact)
	{
		availableExit(dTime, idx);
		setState(idx, Computer::STAT_IDLE);
	}
}

void Computer::availableEnter(double dTime, int idx)
{
}

void Computer::availableExit(double dTime, int idx)
{
}

void Computer::loadingEnter(double dTime, int idx)
{
	m_Bar->enter();
}

void Computer::loadingExit(double dTime, int idx)
{

}
