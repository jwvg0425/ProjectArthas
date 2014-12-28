#include "pch.h"
#include "HealthDeathEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "Player.h"
#include "Effect.h"

bool HealthDeathEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_StartTime = GET_GAME_MANAGER()->getMicroSecondTime();
	GET_SOUND_MANAGER()->allStopSound();

	return true;
}

void HealthDeathEffect::enter()
{

}

void HealthDeathEffect::exit()
{
	GET_STAGE_MANAGER()->playerDead();
}

void HealthDeathEffect::update(float dTime)
{

	if (GET_GAME_MANAGER()->getMicroSecondTime() - m_StartTime > 3000)
	{
		m_IsDead = true;
	}
	else if (GET_GAME_MANAGER()->getMicroSecondTime() - m_StartTime > 1000)
	{
		if (!m_MakeExplosion)
		{
			GET_STAGE_MANAGER()->getPlayer()->setVisible(false);
			GET_SOUND_MANAGER()->createSound(SoundManager::GREANADE_EXPLOSION, false);
			auto effect = GET_EFFECT_MANAGER()->createEffect(ET_EXPLOSION, getPosition());
			effect->setChasingPlayer(true);
			effect->enter();

			
			m_MakeExplosion = true;
		}
	}
}

void HealthDeathEffect::dead()
{
	GET_STAGE_MANAGER()->playerDead();
}

