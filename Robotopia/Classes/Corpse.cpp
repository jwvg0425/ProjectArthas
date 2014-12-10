#include "pch.h"
#include "Corpse.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "InputManager.h"
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

	return true;
}

void Corpse::update(float dTime)
{
	int time = GET_GAME_MANAGER()->getMicroSecondTime();



	//지속 시간 다 됨.
	if (time - m_Time > CORPSE_SUSTAINMENT_TIME)
	{
		m_IsExit = true;
	}
}

void Corpse::exit()
{
	removeFromParent();
}

void Corpse::enter()
{

}
