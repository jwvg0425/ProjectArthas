#include "pch.h"
#include "SteamDeathEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "Player.h"

bool SteamDeathEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_StartTime = GET_GAME_MANAGER()->getMicroSecondTime();
	GET_SOUND_MANAGER()->allStopSound();
	GET_SOUND_MANAGER()->createSound(SoundManager::PLAYER_DEAD, false);

	return true;
}

void SteamDeathEffect::enter()
{
	
}

void SteamDeathEffect::exit()
{

}

void SteamDeathEffect::update(float dTime)
{
	if (GET_GAME_MANAGER()->getMicroSecondTime() - m_StartTime < 2000)
	{
		auto player = GET_STAGE_MANAGER()->getPlayer();

		int randNum = 20 - (GET_GAME_MANAGER()->getMicroSecondTime() - m_StartTime) / 100;
		int createNum = 1 + (GET_GAME_MANAGER()->getMicroSecondTime() - m_StartTime) / 400;

		if (rand() % randNum == 0)
		{

			for (int i = 0; i < createNum; i++)
			{
				float xPos = rand() % 20;

				if (player->getInfo().m_UpperDir == DIR_RIGHT)
				{
					xPos -= 30;
				}
				else
				{
					xPos += 10;
				}

				cocos2d::Point randPos(xPos, static_cast<float>(player->getInfo().m_Size.height / 2 - rand() % 10));

				GET_EFFECT_MANAGER()->createEffect(ET_SMOKE, player->getPosition() + randPos)->enter();
			}
		}
	}
	else if (GET_GAME_MANAGER()->getMicroSecondTime() - m_StartTime < 4000)
	{
		if (!m_MakeParalysis)
		{
			GET_EFFECT_MANAGER()->createEffect(ET_PARALYSIS, getPosition())->enter();
			m_MakeParalysis = true;
		}
	}
	else
	{
		m_IsDead = true;
	}
}

void SteamDeathEffect::dead()
{
	GET_STAGE_MANAGER()->playerDead();
}

