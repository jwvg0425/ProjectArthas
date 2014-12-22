#include "pch.h"
#include "Missile.h"
#include "MissileManager.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "StageManager.h"
#include "PunchMissile.h"
#include "AimingMissile.h"
#include "MissileThunder.h"
#include "PenerateMissile.h"
#include "BindMissile.h"
#include "BombMissile.h"
#include "GrenadeMissile.h"
#include "LinearMissile.h"
#include "BladeMissile.h"

bool MissileManager::init()
{
	//매직넘버들을 바꾸자
	m_Missiles.reserve(200);

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

	for (int i = 0; i < 20; ++i)
	{
		Missile* penerateMissile = GET_COMPONENT_MANAGER()->createComponent<PenerateMissile>();
		penerateMissile->initMissile();
		penerateMissile->retain();
		m_Missiles.push_back(penerateMissile);
	}

	for (int i = 0; i < 20; ++i)
	{
		Missile* bindMissile = GET_COMPONENT_MANAGER()->createComponent<BindMissile>();
		bindMissile->initMissile();
		bindMissile->retain();
		m_Missiles.push_back(bindMissile);
	}

	for (int i = 0; i < 20; ++i)
	{
		Missile* grenadeMissile = GET_COMPONENT_MANAGER()->createComponent<GrenadeMissile>();
		grenadeMissile->initMissile();
		grenadeMissile->retain();
		m_Missiles.push_back(grenadeMissile);
	}

	for (int i = 0; i < 20; ++i)
	{
		Missile* bombMissile = GET_COMPONENT_MANAGER()->createComponent<BombMissile>();
		bombMissile->initMissile();
		bombMissile->retain();
		m_Missiles.push_back(bombMissile);
	}

	for( int i = 0; i < 20; ++i )
	{
		Missile* linearMissile = GET_COMPONENT_MANAGER()->createComponent<LinearMissile>();
		linearMissile->initMissile();
		linearMissile->retain();
		m_Missiles.push_back( linearMissile );
	}

	for (int i = 0; i < 20; ++i)
	{
		Missile* bladeMissile = GET_COMPONENT_MANAGER()->createComponent<BladeMissile>();
		bladeMissile->initMissile();
		bladeMissile->retain();
		m_Missiles.push_back(bladeMissile);
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
	missile->initMissile();

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
	case OT_MISSILE_PLAYER_LINEAR:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<PenerateMissile>();
		break;
	case OT_MISSILE_BIND:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<BindMissile>();
		break;
	case OT_MISSILE_GRENADE:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<GrenadeMissile>();
		break;
	case OT_MISSILE_BOMB:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<BombMissile>();
		break;
	case OT_MISSILE_LINEAR:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<LinearMissile>();
		break;
	case OT_MISSILE_BLADE:
		tmpMissile = GET_COMPONENT_MANAGER()->createComponent<BladeMissile>();
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


