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
#include "SpriteComponent.h"

#define KITNUM 2
#define VENDING_WIDTH 50
#define VENDING_HEIGHT 90

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
	m_Body->setContactTestBitmask(PHYC_PLAYER);
	m_Body->setCategoryBitmask(PHYC_NPC);
	m_Body->setCollisionBitmask(PHYC_PLAYER | PHYC_BLOCK);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);
	m_Body->retain();

	//스프라이트 초기화
	m_FirstSprite = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_FirstSprite->initSprite(ST_VENDING_MACHINE, this);
	m_FirstSprite->retain();
	m_FirstSprite->enter();
	

	//애니메이션 초기화
	m_ContactAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_ContactAni->setAnimation(AT_VENDING_MACHINE_CONTACT, this, 1, false);
	m_ContactAni->retain();
	m_SeperateAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_SeperateAni->setAnimation(AT_VENDING_MACHINE_SEPERATE, this, 1, false);
	m_SeperateAni->retain();

	return true;
}

void VendingMachine::update(float dTime)
{
	Creature::update(dTime);
	if (m_OnContact)
	{

		if (GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_PRESS)
		{
			if (m_KitNum > 0)
			{
				--m_KitNum;
				//여기서 플레이어 돈을 줄여야 되는데 


				//여기서 키트를 생성하자
				int roomNum = GET_STAGE_MANAGER()->getRoomNum();
				auto hpKit = HPKit::create();
				GET_STAGE_MANAGER()->addObject(hpKit, roomNum, getPosition(), GAME_OBJECT);

				if (m_KitNum <= 0)
				{
					m_IsDead = true;
				}
			}
		}
	}
}

void VendingMachine::enter()
{
	resume();
	m_FirstSprite->enter();
}

void VendingMachine::exit()
{
	removeFromParent();
}


void VendingMachine::dead()
{
	exit();
}

bool VendingMachine::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*)bodyA->getNode();
	auto componentB = (BaseComponent*)bodyB->getNode();
	BaseComponent* enemyComponent;
	BaseComponent* myComponent;

	bool isComponentA = true;

	if (componentA->getType() == getType())
	{
		enemyComponent = componentB;
		myComponent = componentA;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		myComponent = componentB;
		isComponentA = false;
	}

	if ((m_LockOwner == nullptr || m_LockOwner == myComponent)
		&& enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_PLAYER)
	{
		m_LockOwner = myComponent;
		m_OnContact = true;
		m_MessageBox->enter();
	}


	m_SeperateAni->exit();
	m_FirstSprite->exit();
	m_ContactAni->enter();

	return true;
}

void VendingMachine::onContactSeparate(cocos2d::PhysicsContact& contact)
{
	m_ContactAni->exit();
	m_FirstSprite->exit();
	m_SeperateAni->enter();
}


