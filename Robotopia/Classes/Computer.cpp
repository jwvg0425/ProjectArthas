#include "pch.h"
#include "Computer.h"
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

bool Computer::init()
{
	if(!NPC::init())
	{
		return false;
	}
	m_Type = OT_COMPUTER;
	m_Info.m_Size = cocos2d::Size(COMPUTER_WIDTH, COMPUTER_HEIGHT);
	bodyInit(m_Info.m_Size);
	initFSMAndTransition();
	m_Bar = GaugeBarContainer::create();
	m_Bar->initBarContainer(this, ST_BAR_CONTAINER, ST_BAR, cocos2d::Point(0, LOADING_BAR_HEIGHT));
	addComponent(m_Bar);
	setLoadingTime(3.f);
	return true;
}

void Computer::update(float dTime)
{
	Creature::update(dTime);
}

void Computer::exit()
{
	//removeFromParent();
}

void Computer::enter()
{

}

void Computer::dead()
{
	setEnabled(false);
	m_Body->release();
}

void Computer::available(Creature* target, double dTime, int idx)
{

}

void Computer::loading(Creature* target, double dTime, int idx)
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

void Computer::complete(Creature* target, double dTime, int idx)
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
	else if(GET_INPUT_MANAGER()->getKeyState(KC_INTERACT) == KS_PRESS)
	{
		GET_SOUND_MANAGER()->createSound(SoundManager::CHARGEGAGE, false);
		availableExit(dTime, idx);
		loadingEnter(dTime, idx);
		setState(idx, Computer::STAT_LOADING);
	}
}

void Computer::loadingTransition(Creature* target, double dTime, int idx)
{
	if(!m_OnContact)
	{
		loadingExit(dTime, idx);
		setState(idx, Computer::STAT_IDLE);
	}
	else if(GET_INPUT_MANAGER()->getKeyState(KC_INTERACT) == KS_RELEASE)
	{
		loadingExit(dTime, idx);
		availableEnter(dTime, idx);
		setState(idx, Computer::STAT_AVAILABLE);
	}
	else if(m_IsComplete)
	{
		loadingExit(dTime, idx);
		GET_SOUND_MANAGER()->createSound(SoundManager::GETMONEY, false);
		completeEnter(dTime, idx);
		setState(idx, Computer::STAT_COMPLETE);
	}
}

void Computer::completeTransition(Creature* target, double dTime, int idx)
{
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
	m_Bar->exit();
	m_Bar->setBarPercent(0.f);
}

void Computer::completeEnter(double dTime, int idx)
{
	UpMoveEffect* effect = static_cast<UpMoveEffect*>
		(GET_EFFECT_MANAGER()->createEffect(ET_UP_MOVE, getPosition() + cocos2d::Point(0, m_Info.m_Size.height / 2)));

	auto player = GET_STAGE_MANAGER()->getPlayer();
	auto info = player->getInfo();
	int randomValue = rand() % 100;
	if(randomValue < 10 && GET_DATA_MANAGER()->getLockSkillNum() > 0)
	//10% 확률로 내가 갖고 있지 않은 스킬 하나 획득.
	{
		SkillType category;
		int type;
		
		do
		{
			category = static_cast<SkillType>(rand() %SKILL_NUM);
			type = rand() % 2/*GET_DATA_MANAGER()->getSkillNum(category)*/;
		} while (!GET_DATA_MANAGER()->getSkillInfo(category, type)->m_IsLock);

		GET_DATA_MANAGER()->setSkillLock(category, type, false);
		effect->setAnimation(AT_EFFECT_SKILL);
	}
	else if (randomValue < 30 && GET_DATA_MANAGER()->getLockItemNum()>0)
	//20% 확률로 내가 갖고 있지 않은 아이템 하나 획득.
	{
		EquipmentType category;
		int type;

		do
		{
			category = static_cast<EquipmentType>(rand() % EMT_NUM);
			type = rand() % 2/*GET_DATA_MANAGER()->getItemNum(category)*/;
		} while (!GET_DATA_MANAGER()->getEquipmentInfo(category, type)->m_IsLock);

		GET_DATA_MANAGER()->setItemLock(category, type, false);
		effect->setAnimation(AT_EFFECT_BLUEPRINT);
	}
	else
	//그 외의 경우 비트코인 획득.
	{
		info.m_BitCoin += 100;
		player->setInfo(info);
		effect->setAnimation(AT_EFFECT_COIN);
	}

	effect->enter();

	//뭔가 획득하면 바로바로 저장
	GET_DATA_MANAGER()->saveGameData();

	m_IsDead = true;
}

void Computer::completeExit(double dTime, int idx)
{

}
void Computer::initFSMAndTransition()
{
	initFSM(1);
	m_States[0] = STAT_IDLE;

	//0번은 attackFSM
	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_AVAILABLE] = FSM_CALLBACK(Computer::available, this);
	m_FSMs[0][STAT_LOADING] = FSM_CALLBACK(Computer::loading, this);
	m_FSMs[0][STAT_COMPLETE] = FSM_CALLBACK(Computer::complete, this);

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = FSM_CALLBACK(Computer::idleTransition, this);
	m_Transitions[0][STAT_AVAILABLE] = FSM_CALLBACK(Computer::availableTransition, this);
	m_Transitions[0][STAT_LOADING] = FSM_CALLBACK(Computer::loadingTransition, this);
	m_Transitions[0][STAT_COMPLETE] = FSM_CALLBACK(Computer::completeTransition, this);

	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_IDLE]->initSprite(ST_COMPUTER_NORMAL, this);

	m_Renders[0][STAT_AVAILABLE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_AVAILABLE]->initSprite(ST_COMPUTER_HEATED_01, this);

	m_Renders[0][STAT_LOADING] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_LOADING]->initSprite(ST_COMPUTER_HEATED_01, this);

	m_Renders[0][STAT_COMPLETE] = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_Renders[0][STAT_COMPLETE]->initSprite(ST_COMPUTER_EMPTY, this);


	for(int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

}

void Computer::setLoadingTime(float sec)
{
	m_LoadingSpeed = ( sec != 0 ) ? 100 / sec : 0.f;
}



