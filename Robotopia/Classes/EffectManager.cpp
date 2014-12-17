#include "pch.h"
#include "GameManager.h"
#include "EffectManager.h"
#include "DataManager.h"
#include "StageManager.h"
#include "FlyRoundEffect.h"



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
	}

	int roomNum = GET_STAGE_MANAGER()->getRoomNum();

	GET_STAGE_MANAGER()->addObject(newEffect, roomNum, position, RoomZOrder::EFFECT);

	return newEffect;
}

