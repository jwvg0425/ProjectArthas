#include "pch.h"
#include "MonsterStandShotAI.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "TriggerManager.h"
#include "StateChangeTrigger.h"
#include <crtdbg.h>
#include "BaseComponent.h"
#include "MonsterStandShot.h"
#include "ObserverComponent.h"
#include "AnimationEndTrigger.h"
#include "MissileManager.h"
#include "CommonInfo.h"
#include "GameManager.h"
#include "StageManager.h"
#include "Player.h"

bool MonsterStandShotAI::init()
{
	if (!AICommand::init())
	{
		return false;
	}

	return true;
}

void MonsterStandShotAI::update(float dTime)
{
	static float totalCoolTime = 0;
	static int missileLaunchCount = 0;

	//미사일 발사 AI

	if (!m_IsAttackState)
	{
		totalCoolTime += dTime;

		auto commonInfo = (CommonInfo*)m_Ref->getComponent(IT_COMMON);
		auto info = commonInfo->getInfo();

		if (getParent()->getPositionX() < GET_STAGE_MANAGER()->getPlayer()->getPositionX())
		{
			info.dir = DIR_RIGHT;
		}
		else
		{
			info.dir = DIR_LEFT;
		}

		commonInfo->setInfo(info);
	}

	if (totalCoolTime >= m_CoolTime) m_IsAttackState = true;

	if (m_IsAttackState)
	{
		auto observer = (ObserverComponent*)m_Ref->getComponent(CT_OBSERVER);
		if (observer)
		{
			auto triggers = observer->getTriggers();
			auto attackState = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
			attackState->initChangingStates(STAT_IDLE, STAT_ATTACK);

			auto attackRender = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
			attackRender->initChangingStates(CT_NONE, STAT_ATTACK);

			observer->addTrigger(attackState);
			observer->addTrigger(attackRender);

			auto animationEndTrigger = GET_TRIGGER_MANAGER()->createTrigger<AnimationEndTrigger>();
			animationEndTrigger->initTrigger(AT_MONSTER_STAND_SHOT_ATTACK);

			for (auto& pTrigger : triggers)
			{
				if (*animationEndTrigger == *pTrigger)
				{
					auto info = (CommonInfo*)m_Ref->getComponent(IT_COMMON);
					CommonInfo::Info tmpInfo;

					tmpInfo.size.width = info->getInfo().size.width;
					tmpInfo.size.height = info->getInfo().size.height;
					tmpInfo.dir = info->getInfo().dir;
					
					GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_PLAYER_LINEAR, m_Ref->getPosition(), tmpInfo.dir, tmpInfo.size,
														 20.f, cocos2d::Vec2(200, 0));

					auto idleRender = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
					idleRender->initChangingStates(CT_NONE, STAT_IDLE);

					observer->addTrigger(idleRender);

					++missileLaunchCount;
				}

			}

			if (missileLaunchCount >= m_AttackNum)
			{
				totalCoolTime = 0;
				missileLaunchCount = 0;
				auto idleState = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
				idleState->initChangingStates(STAT_ATTACK, STAT_IDLE);
				auto idleRender = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
				idleRender->initChangingStates(CT_NONE, STAT_IDLE);

				observer->addTrigger(idleState);
				observer->addTrigger(idleRender);

				m_IsAttackState = false;
			}
		}
	}

}

void MonsterStandShotAI::enter()
{
}

void MonsterStandShotAI::exit()
{
}



void MonsterStandShotAI::initAI(BaseComponent* ref, float coolTime /*= 5*/, int attackNum /*= 2*/)
{
	_ASSERT(ref != nullptr);

	m_Ref = ref;
	m_CoolTime = coolTime;
	m_AttackNum = attackNum;
	m_IsAttackState = false;
}


