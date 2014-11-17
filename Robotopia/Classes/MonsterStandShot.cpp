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
#include "MonsterStandShotRender.h"
#include "MonsterStandAttackFSM.h"
#include "MonsterStandShotAI.h"

#define MONSTERSTANDWIDHT 68
#define MONSTERSTANDHEIGHT 85
#define ATTACKCOOLTIME 0.3f
#define TOTALCOOLTIME 5


bool MonsterStandShot::init()
{
	if (!Monster::init())
	{
		return false;
	}

	return true;
}

bool MonsterStandShot::initMosnter()
{
	m_Type = OT_MONSTER_STAND_SHOT;
	
	CommonInfo::Info tmpInfo;
	tmpInfo.dir = DIR_RIGHT;
	tmpInfo.jumpSpeed = 0.f;
	tmpInfo.size.width = MONSTERSTANDWIDHT;
	tmpInfo.size.height = MONSTERSTANDHEIGHT;
	tmpInfo.speed = 0.f;

	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);

	auto info = GET_COMPONENT_MANAGER()->createComponent<CommonInfo>();
	addComponent(info);
	info->setInfo(tmpInfo);

	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, MONSTERSTANDWIDHT, MONSTERSTANDHEIGHT),
						true, 0, 0, 0, PHYC_ALL, PHYC_MONSTER, PHYC_ALL);
	
	auto render = GET_COMPONENT_MANAGER()->createComponent<MonsterStandShotRender>();
	addComponent(render);
	render->initRender();

	auto attackFSM = GET_COMPONENT_MANAGER()->createComponent<MonsterStandAttackFSM>();
	addComponent(attackFSM);
	attackFSM->initFSM();

	auto AI = GET_COMPONENT_MANAGER()->createComponent<MonsterStandShotAI>();
	addComponent(AI);
	AI->initAI(this);

	return true;
}


void MonsterStandShot::update(float dTime)
{
	for (auto& pChild : getChildren())
	{
		pChild->update(dTime);
	}
}

void MonsterStandShot::enter()
{
}
void MonsterStandShot::exit()
{
}

