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
#include "ResourceManager.h"
#include "AnimationComponent.h"

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

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(32, 32), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_PLAYER);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);

	//FSM 초기화
	initFSM(1);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = move;
	m_FSMs[0][STAT_JUMP] = jump;
	m_FSMs[0][STAT_JUMP_DOWN] = jump;

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = idleTransition;
	m_Transitions[0][STAT_MOVE] = moveTransition;
	m_Transitions[0][STAT_JUMP] = jumpTransition;
	m_Transitions[0][STAT_JUMP_DOWN] = nullptr;

	m_Renders[0].resize(STAT_NUM);
	m_Renders[0][STAT_IDLE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_IDLE])->setAnimation(AT_PLAYER_IDLE, this);
	m_Renders[0][STAT_MOVE] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_MOVE])->setAnimation(AT_PLAYER_MOVE, this);
	m_Renders[0][STAT_JUMP] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_JUMP])->setAnimation(AT_PLAYER_JUMP, this);
	m_Renders[0][STAT_JUMP_DOWN] = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	((AnimationComponent*)m_Renders[0][STAT_JUMP_DOWN])->setAnimation(AT_PLAYER_JUMP, this);

	for (int i = 0; i < m_Renders[0].size(); i++)
	{
		addComponent(m_Renders[0][i]);
	}

	//info 설정

	m_Info.speed = 200;
	m_Info.jumpSpeed = 500;
	m_Info.dir = DIR_LEFT;
	m_Info.size = cocos2d::Size(32, 32);

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
		return;
	}

	//->downJump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS &&
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD)
	{
		enterJump(target, dTime, false);
		target->setState(idx, Player::STAT_JUMP_DOWN);
		return;
	}

	//->jump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS)
	{
		enterJump(target, dTime, false);
		target->setState(idx, Player::STAT_JUMP);
		return;
	}
}

void Player::move(Thing* target, double dTime, int idx)
{
	cocos2d::Rect rect = cocos2d::Rect(target->getPosition().x, target->getPosition().y,
						((Player*)target)->getInfo().size.width, ((Player*)target)->getInfo().size.height);
	
	auto velocity = ((Player*)target)->getBody()->getVelocity();

	//왼쪽 방향이고 왼쪽에 아무것도 없음.
	cocos2d::log("left : %d right : %d up : %d down : %d", GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_LEFT),
		GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_RIGHT),
		GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_UP),
		GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN));

	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_LEFT) == CT_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
	{
		((Player*)target)->setDirection(DIR_LEFT);
		velocity.x = -200;
	}
	else if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_RIGHT) == CT_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		((Player*)target)->setDirection(DIR_RIGHT);
		velocity.x = 200;
	}
	else
	{
		velocity.x = 0;
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

	((Player*)target)->setDirection(dir);

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

	if (m_States[0] == STAT_JUMP_DOWN)
	{
		m_States[0] = STAT_IDLE;
		return false;
	}

	if (contact.getContactData()->normal.y < 0)
	{
		if (enemyComponent->getType() == OT_FLOOR)
		{
			return false;
		}
	}
	return true;
}


void Player::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

cocos2d::PhysicsBody* Player::getBody()
{
	return m_Body;
}

const PlayerInfo& Player::getInfo()
{
	return m_Info;
}

void Player::update(float dTime)
{
	Thing::update(dTime);

	if (m_Info.dir == DIR_LEFT)
	{
		for (int i = 0; i < m_Renders[0].size(); i++)
		{
			m_Renders[0][i]->setFlippedX(true);
		}
	}
	else
	{
		for (int i = 0; i < m_Renders[0].size(); i++)
		{
			m_Renders[0][i]->setFlippedX(false);
		}
	}
}

void Player::setDirection(Direction dir)
{
	m_Info.dir = dir;
}
