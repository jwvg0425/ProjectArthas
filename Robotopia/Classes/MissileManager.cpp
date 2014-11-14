#include "pch.h"
#include "Missile.h"
#include "MissileManager.h"
#include "MissilePlayerMelee.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "StageManager.h"

bool Arthas::MissileManager::init()
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

	return true;
}


Arthas::Missile* Arthas::MissileManager::launchMissile(Arthas::ComponentType missileType, cocos2d::Point pos,
													Arthas::Direction attackDir,
													cocos2d::Size contentsSize,
													float damage, cocos2d::Vec2 velocity, cocos2d::Point targetPos)
{
	for (auto& pMissile : m_Missiles)
	{
		if (pMissile->getType() == missileType && pMissile->isUsable())
		{
			pMissile->setAttribute(pos, attackDir, damage, contentsSize, velocity, targetPos);
			
			GET_STAGE_MANAGER()->addObject(pMissile, GET_STAGE_MANAGER()->getRoomNum(), pos, GAME_OBJECT);
			return pMissile;
		}
	}


	return createMissile(missileType);
}

Arthas::Missile* Arthas::MissileManager::createMissile(ComponentType missileType)
{

	Missile* tmpMissile;
	
	switch (missileType)
	{
	
	case Arthas::OT_MISSILE_PLAYER_MELEE:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<MissilePlayerMelee>();
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

Arthas::MissileManager::MissileManager()
{
}

Arthas::MissileManager::~MissileManager()
{
	for (auto& pMissile : m_Missiles)
	{
		pMissile->release();
	}
}


