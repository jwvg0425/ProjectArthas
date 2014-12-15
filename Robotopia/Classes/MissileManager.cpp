#include "pch.h"
#include "Missile.h"
#include "MissileManager.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "StageManager.h"
#include "PunchMissile.h"
#include "AimingMissile.h"
#include "MissileThunder.h"

bool MissileManager::init()
{
	//매직넘버들을 바꾸자
	m_Missiles.reserve(50);

	for (int i = 0; i < 20; ++i)
	{
		Missile* punchMissile = GET_COMPONENT_MANAGER()->createComponent<PunchMissile>();
		punchMissile->initMissile();
		punchMissile->retain();
		m_Missiles.push_back(punchMissile);
	}

	for (int i = 0; i < 20; ++i)
	{
		Missile* aimingMissile = GET_COMPONENT_MANAGER()->createComponent<AimingMissile>();
		aimingMissile->initMissile();
		aimingMissile->retain();
		m_Missiles.push_back(aimingMissile);
	}


	for (int i = 0; i < 20; ++i)
	{
		Missile* thunderMissile = GET_COMPONENT_MANAGER()->createComponent<MissileThunder>();
		thunderMissile->initMissile();
		thunderMissile->retain();
		m_Missiles.push_back(thunderMissile);
	}


	return true;
}


Missile* MissileManager::launchMissile(ObjectType missileType, cocos2d::Point pos,
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

	//목록에 없는 경우 새로 생성.
	auto missile = createMissile(missileType);

	GET_STAGE_MANAGER()->addObject(missile, GET_STAGE_MANAGER()->getRoomNum(), pos, GAME_OBJECT);

	missile->setAttribute(pos, attackDir, damage, contentsSize, velocity, targetPos);

	return missile;
}

Missile* MissileManager::createMissile(ObjectType missileType)
{

	Missile* tmpMissile = nullptr;
	
	switch (missileType)
	{
	case OT_MISSILE_PUNCH:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<PunchMissile>();
		break;
	case OT_MISSILE_AIMING:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<AimingMissile>();
		break;
	case OT_MISSILE_THUNDER:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<MissileThunder>();
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


