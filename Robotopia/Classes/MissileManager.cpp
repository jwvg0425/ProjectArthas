#include "pch.h"
#include "Missile.h"
#include "MissileManager.h"
#include "MissilePlayerMelee.h"
#include "GameManager.h"
#include "ComponentManager.h"

bool Arthas::MissileManager::init()
{

	//매직넘버들을 바꾸자
	m_Missiles.reserve(20);

	for (int i = 0; i < 5; ++i)
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
			
			return pMissile;
		}
	}

	//여기까지 왔다면 앞에서 조건에 맞는 미사일이 없었다는 뜻이고
	//미사일을 새로 생성해서 넣어줘야 한다. 
	/*Missile* PlayerMeleeMissile = GET_COMPONENT_MANAGER()->createComponent<missileType>();
	m_Missiles.push_back(PlayerMeleeMissile);*/


	//사실 이러면 안되지만 일단은
	return nullptr;
}


