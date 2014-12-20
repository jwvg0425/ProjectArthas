#include "pch.h"
#include "VendingMachine.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "InputManager.h"
#include "ComponentManager.h"
#include "StageManager.h"
#include "HPKit.h"

#define KITNUM 2
#define VENDING_WIDTH 100
#define VENDING_HEIGHT 140

bool VendingMachine::init()
{
	if (!NPC::init())
	{
		return false;
	}

	//타입을 vendingMachine으로 바꿔야 한다. 
	m_Type = OT_VENDING_MACHINE;
	m_Info.m_Size = cocos2d::Size(VENDING_WIDTH, VENDING_HEIGHT);

	//kitnum 초기화
	m_KitNum = KITNUM;

	//물리박스
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(m_Info.m_Size, meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_NPC);
	m_Body->setCollisionBitmask(PHYC_PLAYER);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);
	m_Body->retain();

	//애니메이션 초기화
	m_ContactAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_ContactAni->setAnimation(AT_VENDING_MACHINE_CONTACT, this, 1, false);
	m_SeperateAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_SeperateAni->setAnimation(AT_VENDING_MACHINE_SEPERATE, this, 1, false);

	return true;
}

void VendingMachine::update(float dTime)
{
	Creature::update(dTime);
}

void VendingMachine::enter()
{
	resume();
}

void VendingMachine::exit()
{
	removeFromParent();
}

bool VendingMachine::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*)bodyA->getNode();
	auto componentB = (BaseComponent*)bodyB->getNode();
	BaseComponent* enemyComponent;

	if (componentA->getType() == getType())
	{
		enemyComponent = componentB;
	}
	else
	{
		enemyComponent = componentA;
	}

	if (enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_PLAYER)
	{
		m_OnContact = true;
		m_MessageBox->enter();
	}


	if (GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_PRESS)
	{
		if (m_KitNum > 0)
		{
			--m_KitNum;
			//여기서 키트를 생성하자
			int roomNum = GET_STAGE_MANAGER()->getRoomNum();
			auto hpKit = HPKit::create();
			GET_STAGE_MANAGER()->addObject(hpKit, roomNum, getPosition(), GAME_OBJECT);

		}
		else
		{
			//여기서 exit로 가는 거야
			m_IsDead = true;
		}
	}
	




	return true;
}

void VendingMachine::onContactSeparate(cocos2d::PhysicsContact& contact)
{
	m_OnContact = false;
}

