#include "pch.h"
#include "MonsterStandShot.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "ObserverComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "MissileManager.h"
#include "CommonInfo.h"
#include "TriggerManager.h"
#include "StateChangeTrigger.h"

#define MONSTERSTANDWIDHT 68
#define MONSTERSTANDHEIGHT 85
#define ATTACKCOOLTIME 0.3f
#define TOTALCOOLTIME 5


bool Arthas::MonsterStandShot::init()
{
	if (!Monster::init())
	{
		return false;
	}

	return true;
}

bool Arthas::MonsterStandShot::initMosnter()
{
	m_IsAttacking = false;
	m_AttackCoolTime = ATTACKCOOLTIME;
	m_MissileCount = MISSILECOUNT;
	
	auto info = GET_COMPONENT_MANAGER()->createComponent<CommonInfo>();
	CommonInfo::Info tmpInfo;
	tmpInfo.dir = DIR_RIGHT;
	tmpInfo.jumpSpeed = 0.f;
	tmpInfo.size.width = MONSTERSTANDWIDHT;
	tmpInfo.size.height = MONSTERSTANDHEIGHT;
	tmpInfo.speed = 0.f;
	info->setInfo(tmpInfo);

	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);



	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	physics->initPhysics(cocos2d::Rect(0, 0, MONSTERSTANDWIDHT, MONSTERSTANDHEIGHT),
						true, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);

	

	return true;
}


void Arthas::MonsterStandShot::update(float dTime)
{
	static float attackTime = 0;
	static float missileInterval = 1.;

	for (auto &pChild : getChildren())
	{
		pChild->update(dTime);
	}

	

	attackTime += dTime;
	if (attackTime > m_TotalCoolTime)
	{
		m_IsAttacking = true;
		auto observer = (ObserverComponent*)getComponent(CT_OBSERVER);
		if (observer)
		{
			auto attackStartTrigger = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
			attackStartTrigger->initChangingStates(CT_NONE, STAT_ATTACK);
			observer->addTrigger(attackStartTrigger);
		}
	}

	if (m_IsAttacking)
	{
		attackTime = 0;
		missileInterval += dTime;

		if (missileInterval > m_AttackCoolTime)
		{
			auto observer = (ObserverComponent*)getComponent(CT_OBSERVER);
			if (observer)
			{
				auto tmpTriggers = observer->getTriggers();
				auto aniEndTrigger = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
				aniEndTrigger->initChangingStates(CT_ANIMATION, CT_NONE);
				for (auto& pTriger : tmpTriggers)
				{
					if (*aniEndTrigger == *pTriger)
					{
						static int curMissileCount = 0;
						missileInterval = 0;
						CommonInfo* tmpInfo = (CommonInfo*)(getComponent(IT_COMMON));
						auto info = tmpInfo->getInfo();
						GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_PLAYER_LINEAR, getPosition(),
															 info.dir, info.size);
						++curMissileCount;
						if (curMissileCount > m_MissileCount)
						{
							auto observer = (ObserverComponent*)getComponent(CT_OBSERVER);
							if (observer)
							{
								auto attackEndTrigger = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
								attackEndTrigger->initChangingStates(CT_NONE, STAT_IDLE);
								observer->addTrigger(attackEndTrigger);
							}
							m_IsAttacking = false;
						}
					}
				}
			}
		}
	}


	
}

void Arthas::MonsterStandShot::enter()
{
}
void Arthas::MonsterStandShot::exit()
{
}

void Arthas::MonsterStandShot::setMonster(Direction dir, float damage, float speed, float jumpSpeed, int missileCount)
{
	CommonInfo* tmpInfo = (CommonInfo*)(getComponent(IT_COMMON));
	auto info = tmpInfo->getInfo();
	info.dir = dir;
	info.jumpSpeed = jumpSpeed;
	tmpInfo->setInfo(info);
	m_MissileCount = missileCount;

}
