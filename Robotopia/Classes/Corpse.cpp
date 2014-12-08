#include "pch.h"
#include "Corpse.h"
#include "GameManager.h"
#include "ResourceManager.h"
#define CORPSE_SUSTAINMENT_TIME 30000 //시체 유지 시간

bool Corpse::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_CORPSE);
	addChild(m_Sprite);

	m_Time = GET_GAME_MANAGER()->getMicroSecondTime();

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
