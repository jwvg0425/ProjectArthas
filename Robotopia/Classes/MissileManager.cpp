#include "pch.h"
#include "Missile.h"
#include "MissileManager.h"
#include "MissilePlayerMelee.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "StageManager.h"
#include "MissilePlayerLinear.h"

bool MissileManager::init()
{
	//매직넘버들을 바꾸자
	m_Missiles.reserve(50);

	for (int i = 0; i < 20; ++i)
	{
		Missile* PlayerMeleeMissile = GET_COMPONENT_MANAGER()->createComponent<MissilePlayerMelee>();
		PlayerMeleeMissile->initMissile();
		PlayerMeleeMissile->retain();
		m_Missiles.push_back(PlayerMeleeMissile);
	}

	for (int i = 0; i < 20; ++i)
	{
		Missile* PlayerLinearMissile = GET_COMPONENT_MANAGER()->createComponent<MissilePlayerLinear>();
		PlayerLinearMissile->initMissile();
		PlayerLinearMissile->retain();
		m_Missiles.push_back(PlayerLinearMissile);
	}


	return true;
}


Missile* MissileManager::launchMissile(ComponentType missileType, cocos2d::Point pos,
													Direction attackDir,
													cocos2d::Size contentsSize,
													float damage, cocos2d::Vec2 velocity, cocos2d::Point targetPos)
{
	for (auto& pMissile : m_Missiles)
	{
		if (pMissile->getType() == missileType && pMissile->isUsable())
		{
			
			GET_STAGE_MANAGER()->addObject(pMissile, GET_STAGE_MANAGER()->getRoomNum(), pos, GAME_OBJECT);
			
			pMissile->setAttribute(pos, attackDir, damage, contentsSize, velocity, targetPos);
			return pMissile;
		}
	}


	return createMissile(missileType);
}

Missile* MissileManager::createMissile(ComponentType missileType)
{

	Missile* tmpMissile;
	
	switch (missileType)
	{
	
	case OT_MISSILE_PLAYER_MELEE:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<MissilePlayerMelee>();
		break;
	case OT_MISSILE_PLAYER_LINEAR:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<MissilePlayerLinear>();
		break;
	default:
		tmpMissile = nullptr;
		break;
	}

	if (tmpMissile == nullptr)
	{
		return tmpMissile;
	}
	else
	{
		tmpMissile->initMissile();
		tmpMissile->retain();
		m_Missiles.push_back(tmpMissile);
		

		return tmpMissile;
	}
}

MissileManager::MissileManager()
{
}

MissileManager::~MissileManager()
{
	for (auto& pMissile : m_Missiles)
	{
		pMissile->release();
	}
}


