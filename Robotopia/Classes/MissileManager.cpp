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
		m_Missiles.push_back(PlayerMeleeMissile);
	
	}

	return true;
}


Arthas::Missile* Arthas::MissileManager::getMissile(Arthas::ComponentType missileType, cocos2d::Point pos,
													Arthas::Direction attackDir, 
													float damage, cocos2d::Vec2 velocity)
{
	for (auto pMissile : m_Missiles)
	{
		if (pMissile->getType() == missileType && pMissile->isUsable())
		{
			pMissile->setAttribute(pos, attackDir, damage, velocity);
			
			GET_STAGE_MANAGER()->addObject(pMissile, GET_STAGE_MANAGER()->getRoomNum(), pos, GAME_OBJECT);
			return pMissile;
		}
	}

	//여기까지 왔다면 앞에서 조건에 맞는 미사일이 없었다는 뜻이고
	//미사일을 새로 생성해서 넣어줘야 한다. 
	//다른 여러 미사일은 어떻게 넣어주지
	Missile* playerMeleeMissile = GET_COMPONENT_MANAGER()->createComponent<MissilePlayerMelee>();
	m_Missiles.push_back(playerMeleeMissile);


	//사실 이러면 안되지만 일단은
	return playerMeleeMissile;
}


