#include "pch.h"
#include "Corpse.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "InputManager.h"
#include "Player.h"
#include "GaugeBarContainer.h"
#include "SoundManager.h"
#define CORPSE_SUSTAINMENT_TIME 30000 //시체 유지 시간
#define ABSORB_VALUE 20

bool Corpse::init()
{
	if (!NPC::init())
	{
		return false;
	}

	m_Type = OT_CORPSE;

	m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_CORPSE);
	addChild(m_Sprite);

	m_Time = GET_GAME_MANAGER()->getMicroSecondTime();
	bodyInit(cocos2d::Size(81, 41));

	m_Bar = GaugeBarContainer::create();
	m_Bar->initBarContainer(this, ST_BAR_CONTAINER, ST_BAR, cocos2d::Point(0, LOADING_BAR_HEIGHT));
	addComponent(m_Bar);

	initFSM(1);
	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_ABSORB] = FSM_CALLBACK(Corpse::absorb, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(Corpse::idleTransition, this);
	m_Transitions[0][STAT_ABSORB] = FSM_CALLBACK(Corpse::absorbTransition, this);

	return true;
}

void Corpse::update(float dTime)
{
	int time = GET_GAME_MANAGER()->getMicroSecondTime();

	//지속 시간 다 됨.
	if (time - m_Time > CORPSE_SUSTAINMENT_TIME)
	{
		m_IsDead = true;
	}

	updateFSM(dTime);
}

void Corpse::exit()
{
}

void Corpse::enter()
{

}

void Corpse::absorb(Creature* target, double dTime, int idx)
{
	m_AbsorbTime += dTime;

	m_Bar->setBarPercent(m_AbsorbTime / ABSORB_TIME* 100);

	if (m_AbsorbTime > ABSORB_TIME)
	{
		GET_SOUND_MANAGER()->createSound(SoundManager::CORPSE_LAST_GET, false);
		GET_STAGE_MANAGER()->getPlayer()->produceSteam(20);
		m_IsDead = true;
	}
}

void Corpse::idleTransition(Creature* target, double dTime, int idx)
{
	//->absorb
	if(m_OnContact && GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_HOLD)
	{
		GET_SOUND_MANAGER()->createSound(SoundManager::CORPSE_GET, false);
		m_Bar->enter();
		setState(idx, STAT_ABSORB);
	}
}

void Corpse::absorbTransition(Creature* target, double dTime, int idx)
{
	//->idle
	
	if (!m_OnContact || GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_NONE )
	{
		m_AbsorbTime = 0;
		m_Bar->exit();
		m_Bar->setBarPercent(0.f);
		setState(idx, STAT_IDLE);
	}
}

void Corpse::dead()
{
	removeFromParent();
}
