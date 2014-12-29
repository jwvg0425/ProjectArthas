#include "pch.h"
#include "Lever.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "InputManager.h"
#include "SpriteComponent.h"
#include "GaugeBarContainer.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "StageManager.h"
#include "Player.h"
#include "DataManager.h"
#include "EquipmentAbstract.h"
#include "UpMoveEffect.h"

bool Lever::init()
{
	if(!NPC::init())
	{
		return false;
	}
	m_Type = OT_LEVER;
	m_Info.m_Size = cocos2d::Size(LEVER_WIDTH, LEVER_HEIGHT);
	bodyInit(m_Info.m_Size);
	initFSMAndTransition();
	m_Bar = GaugeBarContainer::create();
	m_Bar->initBarContainer(this, ST_BAR_CONTAINER, ST_BAR, cocos2d::Point(0, LOADING_BAR_HEIGHT));
	addComponent(m_Bar);
	setLoadingTime(3.f);

	return true;
}

void Lever::update(float dTime)
{
	Creature::update(dTime);
}

void Lever::exit()
{
	//removeFromParent();
}

void Lever::enter()
{

}

void Lever::dead()
{
	setEnabled(false);
	m_Body->release();
}

void Lever::available(Creature* target, double dTime, int idx)
{

}

void Lever::loading(Creature* target, double dTime, int idx)
{
	if(GET_INPUT_MANAGER()->getKeyState(KC_INTERACT) == KS_HOLD)
	{
		float curPercent = m_Bar->getBarPercent();
		if(curPercent < 100)
		{
			m_Bar->setBarPercent(curPercent + dTime * m_LoadingSpeed);
		}
		else
		{
			m_IsComplete = true;
		}
	}
}

void Lever::complete(Creature* target, double dTime, int idx)
{

}

void Lever::idleTransition(Creature* target, double dTime, int idx)
{
	if(m_OnContact)
	{
		availableEnter(dTime, idx);
		setState(idx, Lever::STAT_OFF);
	}
}

void Lever::availableTransition(Creature* target, double dTime, int idx)
{
	if(!m_OnContact)
	{
		availableExit(dTime, idx);
		setState(idx, Lever::STAT_IDLE);
	}
	else if(GET_INPUT_MANAGER()->getKeyState(KC_INTERACT) == KS_PRESS)
	{
		GET_SOUND_MANAGER()->createSound(SoundManager::CHARGEGAGE, false);
		availableExit(dTime, idx);
		loadingEnter(dTime, idx);
		setState(idx, Lever::STAT_MID);
	}
}

void Lever::loadingTransition(Creature* target, double dTime, int idx)
{
	if(!m_OnContact)
	{
		loadingExit(dTime, idx);
		setState(idx, Lever::STAT_IDLE);
	}
	else if(GET_INPUT_MANAGER()->getKeyState(KC_INTERACT) == KS_RELEASE)
	{
		loadingExit(dTime, idx);
		availableEnter(dTime, idx);
		setState(idx, Lever::STAT_OFF);
	}
	else if(m_IsComplete)
	{
		loadingExit(dTime, idx);
		GET_SOUND_MANAGER()->createSound(SoundManager::GETMONEY, false);
		completeEnter(dTime, idx);
		setState(idx, Lever::STAT_ON);
	}
}

void Lever::completeTransition(Creature* target, double dTime, int idx)
{
}

void Lever::availableEnter(double dTime, int idx)
{
}

void Lever::availableExit(double dTime, int idx)
{
}

void Lever::loadingEnter(double dTime, int idx)
{
	m_Bar->enter();
}

void Lever::loadingExit(double dTime, int idx)
{
	m_Bar->exit();
	m_Bar->setBarPercent(0.f);
}

void Lever::completeEnter(double dTime, int idx)
{
	UpMoveEffect* effect = static_cast<UpMoveEffect*>
		( GET_EFFECT_MANAGER()->createEffect(ET_UP_MOVE, getPosition() + cocos2d::Point(0, m_Info.m_Size.height / 2)) );
	effect->setAnimation(AT_EFFECT_KEY);
	effect->enter();
	GET_STAGE_MANAGER()->portalOpen();
	m_IsDead = true;
}

void Lever::completeExit(double dTime, int idx)
{

}
void Lever::initFSMAndTransition()
{
	initFSM(1);
	m_States[0] = STAT_IDLE;

	//0¹øÀº attackFSM
	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_OFF] = FSM_CALLBACK(Lever::available, this);
	m_FSMs[0][STAT_MID] = FSM_CALLBACK(Lever::loading, this);
	m_FSMs[0][STAT_ON] = FSM_CALLBACK(Lever::complete, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(Lever::idleTransition, this);
	m_Transitions[0][STAT_OFF] = FSM_CALLBACK(Lever::availableTransition, this);
	m_Transitions[0][STAT_MID] = FSM_CALLBACK(Lever::loadingTransition, this);
	m_Transitions[0][STAT_ON] = FSM_CALLBACK(Lever::completeTransition, this);

	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_IDLE]->initSprite(ST_LEVER_OFF, this);

	m_Renders[0][STAT_OFF] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_OFF]->initSprite(ST_LEVER_OFF, this);

	m_Renders[0][STAT_MID] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_MID]->initSprite(ST_LEVER_MID, this);

	m_Renders[0][STAT_ON] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_ON]->initSprite(ST_LEVER_ON, this);


	for(int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

}

void Lever::setLoadingTime(float sec)
{
	m_LoadingSpeed = ( sec != 0 ) ? 100 / sec : 0.f;
}



