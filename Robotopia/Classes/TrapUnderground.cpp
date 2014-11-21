#include "pch.h"
#include "TrapUnderground.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "ResourceManager.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"


bool TrapUnderground::init()
{
	if (!Tile::init())
	{
		return false;
	}

	return true;
}

void TrapUnderground::update(float dTime)
{

	if (m_AccumulatedTime - m_StartTime > m_Duration)
	{
		((PhysicsComponent*)getComponent(CT_PHYSICS))->setEnabled(true);
		((AnimationComponent*)getComponent(CT_ANIMATION))->enter();

		m_AccumulatedTime = GET_GAME_MANAGER()->getTime().tv_sec;
		m_StartTime = GET_GAME_MANAGER()->getTime().tv_sec;

	}
	else
	{
		m_AccumulatedTime += GET_GAME_MANAGER()->getTime().tv_sec;
		//이거 매번하는거 이상한데
		((PhysicsComponent*)getComponent(CT_PHYSICS))->setEnabled(false);
		((AnimationComponent*)getComponent(CT_ANIMATION))->exit();
	}

}


void TrapUnderground::initTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize)
{
	//3초에 한번 공격하게
	m_Duration = 5;
	m_AccumulatedTime = 0;
	m_StartTime = 0;
	m_IsPrevTimeCheck = true;


	auto sprComponent = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	sprComponent->initSprite(ST_TRAP_UNDERGROUND, this);
	sprComponent->enter();



	auto aniComponent = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	addComponent(aniComponent);
	aniComponent->setAnimation(AT_TRAP_UNDERGROUND, this, 2);
	
	//애니메이션 킬 때만 프레임에 맞춰서 물리 충돌이 일어나게 하려면 어떻게 해야지?
	initPhysicsBody(cocos2d::Rect(origin.x, origin.y , 69, 60));
	((PhysicsComponent*)getComponent(CT_PHYSICS))->setEnabled(false);
	
}

void TrapUnderground::enter()
{
}

void TrapUnderground::exit()
{
}
