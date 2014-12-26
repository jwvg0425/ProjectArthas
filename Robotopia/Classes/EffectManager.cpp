#include "pch.h"
#include "GameManager.h"
#include "EffectManager.h"
#include "DataManager.h"
#include "StageManager.h"
#include "FlyRoundEffect.h"
#include "AimingEffect.h"
#include "DashEffect.h"
#include "LandingEffect.h"
#include "PunchEffect.h"
#include "ParalysisEffect.h"
#include "UpMoveEffect.h"
#include "SmokeEffect.h"
#include "SteamDeathEffect.h"
#include "ExplosionEffect.h"
#include "HealthDeathEffect.h"


EffectManager::EffectManager()
{
	
}

EffectManager::~EffectManager()
{

}

bool EffectManager::init()
{
	return true;
}

Effect* EffectManager::createEffect(EffectType effectType, cocos2d::Point position)
{
	Effect* newEffect = nullptr;

	switch (effectType)
	{
	case ET_FLYING_SMOKE:
		newEffect = FlyRoundEffect::create();
		break;
	case ET_AIMING_MISSILE:
		newEffect = AimingEffect::create();
		break;
	case ET_DASH:
		newEffect = DashEffect::create();
		break;
	case ET_LANDING:
		newEffect = LandingEffect::create();
		break;
	case ET_PUNCH_MISSILE:
		newEffect = PunchEffect::create();
		break;
	case ET_PARALYSIS:
		newEffect = ParalysisEffect::create();
		break;
	case ET_UP_MOVE:
		newEffect = UpMoveEffect::create();
		break;
	case ET_SMOKE:
		newEffect = SmokeEffect::create();
		break;
	case ET_STEAM_DEATH:
		newEffect = SteamDeathEffect::create();
		break;
	case ET_EXPLOSION:
		newEffect = ExplosionEffect::create();
		break;
	case ET_HEALTH_DEATH:
		newEffect = HealthDeathEffect::create();
		break;
	}

	int roomNum = GET_STAGE_MANAGER()->getRoomNum();

	GET_STAGE_MANAGER()->addObject(newEffect, roomNum, position, RoomZOrder::EFFECT);

	return newEffect;
}

