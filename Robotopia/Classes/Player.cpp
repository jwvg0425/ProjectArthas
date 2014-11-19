#include "pch.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "PlayerMoveFSM.h"
#include "PlayerJumpFSM.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "KeyboardCommand.h"
#include "ObserverComponent.h"
#include "PhysicsComponent.h"
#include "PlayerRender.h"
#include "CommonInfo.h"
#include "PlayerAttackFSM.h"
#include "PhysicsInfo.h"
#include "InputManager.h"

bool Player::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	auto info = GET_COMPONENT_MANAGER()->createComponent<CommonInfo>();
	addComponent(info);

	CommonInfo::Info tmp;
	tmp.dir = DIR_RIGHT;
	tmp.speed = 200;
	tmp.jumpSpeed = 500;
	tmp.size.width = 32.f;
	tmp.size.height = 32.f;
	tmp.maxHp = 100;
	tmp.maxSteam = 100;
	tmp.currentHp = 100;
	tmp.currentSteam = 100;

	info->setInfo(tmp);

	m_Type = OT_PLAYER;

	//물리 초기화
	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, 32, 32), true, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);
	physics->addIgnoreCollision(OT_FLOOR, DIR_UP);

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(32, 32), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_PLAYER);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(Player::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//FSM 초기화
	initFSM(1);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = move;
	m_FSMs[0][STAT_JUMP] = jump;

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = idleTransition;
	m_Transitions[0][STAT_MOVE] = moveTransition;
	m_Transitions[0][STAT_JUMP] = jumpTransition;

	return true;
}

void Player::enter()
{
	resume();
}

void Player::exit()
{
}

void Player::idleTransition(Thing* target, double dTime, int idx)
{
	//->move
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD ||
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
		{
			enterMove(target, dTime, DIR_LEFT);
		}
		else
		{
			enterMove(target, dTime, DIR_RIGHT);
		}

		target->setState(idx, Player::STAT_MOVE);
	}

	//->jump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS)
	{
		enterJump(target, dTime, false);
		target->setState(idx, Player::STAT_JUMP);
	}
}

void Player::move(Thing* target, double dTime, int idx)
{
	cocos2d::Rect rect = cocos2d::Rect(target->getPositionX(), target->getPositionY(), 32, 32);
	
	auto velocity = ((Player*)target)->getBody()->getVelocity();

	//왼쪽 방향이고 왼쪽에 아무것도 없음.
	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_LEFT) == CT_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
	{
		velocity.x = -200;
	}
	else if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_RIGHT) == CT_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		velocity.x = 200;
	}

	((Player*)target)->getBody()->setVelocity(velocity);
}

void Player::jump(Thing* target, double dTime, int idx)
{
	move(target, dTime, idx);
}

void Player::enterMove(Thing* target, double dTime,Direction dir)
{
	auto velocity = ((Player*)target)->getBody()->getVelocity();

	//속도 임시로 지정.
	if (dir == DIR_LEFT)
	{
		velocity.x = -200;
	}
	else if (dir == DIR_RIGHT)
	{
		velocity.x = 200;
	}

	((Player*)target)->getBody()->setVelocity(velocity);
}

void Player::enterJump(Thing* target, double dTime, bool isFall)
{
	auto velocity = ((Player*)target)->getBody()->getVelocity();

	//속도 임시로 지정.
	if (!isFall)
	{
		velocity.y = 500;
	}

	((Player*)target)->getBody()->setVelocity(velocity);
}

void Player::moveTransition(Thing* target, double dTime, int idx)
{
	//->idle
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_NONE)
	{
		exitMove(target, dTime);
		target->setState(idx, Player::STAT_IDLE);
	}

	//->jump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS)
	{
		exitMove(target, dTime);
		enterJump(target, dTime, false);
		target->setState(idx, Player::STAT_JUMP);
	}

	//->fall
	cocos2d::Rect rect = cocos2d::Rect(target->getPositionX(), target->getPositionY(), 32, 32);
	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) == CT_NONE)
	{
		exitMove(target, dTime);
		enterJump(target, dTime, true);
		target->setState(idx, Player::STAT_JUMP);
	}
}

void Player::jumpTransition(Thing* target, double dTime, int idx)
{
	auto player = (Player*)target;

	//->idle
	cocos2d::Rect rect = cocos2d::Rect(target->getPositionX(), target->getPositionY(), 32, 32);
	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) != CT_NONE)
	{
		target->setState(idx, Player::STAT_IDLE);
	}
}

void Player::exitMove(Thing* target, double dTime)
{
	auto velocity = ((Player*)target)->getBody()->getVelocity();

	velocity.x = 0;

	((Player*)target)->getBody()->setVelocity(velocity);
}

bool Player::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}


void Player::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

cocos2d::PhysicsBody* Player::getBody()
{
	return m_Body;
}