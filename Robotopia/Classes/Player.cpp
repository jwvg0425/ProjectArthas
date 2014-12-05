#include "pch.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "StageManager.h"
#include "ComponentManager.h"
#include "PhysicsComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "AnimationComponent.h"
#include "GameScene.h"
#include "PlayerRenderer.h"

bool Player::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Type = OT_PLAYER;
	m_FSMNum = 2;

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(PLAYER_WIDTH, PLAYER_HEIGHT), meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_PLAYER);
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);
	m_Body->retain();

	//FSM 초기화
	initFSM(m_FSMNum);
	m_States[0] = STAT_IDLE;

	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[0][STAT_IDLE] = nullptr;
	m_FSMs[0][STAT_MOVE] = move;
	m_FSMs[0][STAT_JUMP] = jump;
	m_FSMs[0][STAT_JUMP_DOWN] = jump;
	m_FSMs[0][STAT_FLY] = fly;

	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[0][STAT_IDLE] = idleTransition;
	m_Transitions[0][STAT_MOVE] = moveTransition;
	m_Transitions[0][STAT_JUMP] = jumpTransition;
	m_Transitions[0][STAT_JUMP_DOWN] = downJumpTransition;
	m_Transitions[0][STAT_FLY] = flyTransition;

	m_States[1] = AS_ATK_IDLE;

	m_FSMs[1].resize(AS_NUM);
	m_FSMs[1][AS_ATK_IDLE] = nullptr;
	m_FSMs[1][AS_MELEE_ATTACK] = meleeAttack;

	m_Transitions[1].resize(AS_NUM);
	m_Transitions[1][AS_ATK_IDLE] = attackIdleTransition;
	m_Transitions[1][AS_MELEE_ATTACK] = meleeAttackTransition;

	m_PlayerRenderer = PlayerRenderer::create();
	m_PlayerRenderer->retain();
	addChild(m_PlayerRenderer);

	//info 설정

	m_Info.m_Speed = 200;
	m_Info.m_JumpSpeed = 500;
	m_Info.m_UpperDir = DIR_LEFT;
	m_Info.m_LowerDir = DIR_LEFT;
	m_Info.m_Size = cocos2d::Size(PLAYER_WIDTH, PLAYER_HEIGHT);
	m_Info.m_Gear = GEAR_BEAR;

	return true;
}

void Player::enter()
{
	resume();
}

void Player::exit()
{
	removeFromParentAndCleanup(false);
}

void Player::idleTransition(Creature* target, double dTime, int idx)
{
	cocos2d::Rect rect = cocos2d::Rect(target->getPosition().x, target->getPosition().y,
		static_cast<Player*>(target)->getInfo().m_Size.width, static_cast<Player*>(target)->getInfo().m_Size.height);

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
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD &&
		GET_GAME_MANAGER()->getContactComponentType(target,rect,DIR_DOWN) == OT_FLOOR)
	{
		enterDownJump(target, dTime);
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

	//->fall
	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) == CT_NONE)
	{
		enterJump(target, dTime, true);
		target->setState(idx, Player::STAT_JUMP);
		return;
	}
}

void Player::move(Creature* target, double dTime, int idx)
{
	cocos2d::Rect rect = cocos2d::Rect(target->getPosition().x, target->getPosition().y,
						static_cast<Player*>(target)->getInfo().m_Size.width, static_cast<Player*>(target)->getInfo().m_Size.height);
	
	auto velocity = static_cast<Player*>(target)->getPhysicsBody()->getVelocity();

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
	else
	{
		velocity.x = 0;
	}

	target->getPhysicsBody()->setVelocity(velocity);
}

void Player::jump(Creature* target, double dTime, int idx)
{
	move(target, dTime, idx);
}

void Player::enterMove(Creature* target, double dTime,Direction dir)
{
	auto velocity = target->getPhysicsBody()->getVelocity();

	static_cast<Player*>(target)->setDirection(dir);

	//속도 임시로 지정.
	if (dir == DIR_LEFT)
	{
		velocity.x = -200;
	}
	else if (dir == DIR_RIGHT)
	{
		velocity.x = 200;
	}

	target->getPhysicsBody()->setVelocity(velocity);
}

void Player::enterJump(Creature* target, double dTime, bool isFall)
{
	auto velocity = target->getPhysicsBody()->getVelocity();

	//속도 임시로 지정.
	if (!isFall)
	{
		velocity.y = 500;
	}

	target->getPhysicsBody()->setVelocity(velocity);
}

void Player::moveTransition(Creature* target, double dTime, int idx)
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
	cocos2d::Rect rect = cocos2d::Rect(target->getPositionX(), target->getPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT);
	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) == CT_NONE)
	{
		exitMove(target, dTime);
		enterJump(target, dTime, true);
		target->setState(idx, Player::STAT_JUMP);
	}
}

void Player::jumpTransition(Creature* target, double dTime, int idx)
{
	auto player = (Player*)target;

	//->idle
	cocos2d::Rect rect = cocos2d::Rect(target->getPositionX(), target->getPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT);
	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) != CT_NONE)
	{
		auto body = target->getPhysicsBody();

		body->setVelocity(cocos2d::Vect(body->getVelocity().x, 0));
		target->setState(idx, Player::STAT_IDLE);
	}
}

void Player::exitMove(Creature* target, double dTime)
{
	auto velocity = target->getPhysicsBody()->getVelocity();

	velocity.x = 0;

	target->getPhysicsBody()->setVelocity(velocity);
}

bool Player::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*)bodyA->getNode();
	auto componentB = (BaseComponent*)bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;

	if (componentA->getType() == getType())
	{
		enemyComponent = componentB;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		isComponentA = false;
	}


	if (m_States[0] == STAT_JUMP_DOWN && enemyComponent->getType() == OT_FLOOR)
	{
		m_States[0] = STAT_JUMP;
		return false;
	}

	if ((contact.getContactData()->normal.y > 0 && isComponentA) ||
		(contact.getContactData()->normal.y < 0 && !isComponentA))
	{
		if (enemyComponent->getType() == OT_FLOOR)
		{
			return false;
		}
	}

	//eagle 상태일땐 floor와의 충돌 무시.
	if (m_Info.m_Gear == GEAR_EAGLE && enemyComponent->getType() == OT_FLOOR)
	{
		return false;
	}

	return true;
}


void Player::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

const PlayerInfo& Player::getInfo() const
{
	return m_Info;
}

void Player::update(float dTime)
{
	//기본 업데이트
//	Creature::update(dTime);
	for(auto& BaseComponent : getChildren())
	{
		BaseComponent->update(dTime);
	}

	for(int i = 0; i < m_States.size(); i++)
	{
		int state = m_States[i];
		if(m_FSMs[i][state] != nullptr)
		{
			m_FSMs[i][state](this, dTime, i);
		}

		if(m_Transitions[i][state] != nullptr)
		{
			m_Transitions[i][state](this, dTime, i);
		}

		if(m_States[0] != m_PrevStates[0])
		{
			m_PlayerRenderer->changeState(static_cast<Player::State>( m_States[0] ));
		}
	}

	//방향 설정

	float mouseX = GET_INPUT_MANAGER()->getMouseInfo().m_MouseMove.x;

	if (mouseX < GET_STAGE_MANAGER()->getGameLayerPosition().x + getPositionX())
	{
		m_Info.m_UpperDir = DIR_LEFT;
	}
	else
	{
		m_Info.m_UpperDir = DIR_RIGHT;
	}

	//방향에 따른 뒤집기
	if (m_Info.m_UpperDir == DIR_LEFT)
	{
		m_PlayerRenderer->flipUpperBody(true);
	}
	else
	{
		m_PlayerRenderer->flipUpperBody(false);
	}
	if(m_Info.m_LowerDir == DIR_LEFT)
	{
		m_PlayerRenderer->flipLowerBody(true);
	}
	else
	{
		m_PlayerRenderer->flipLowerBody(false);
	}

	//기어 변환
	KeyState eagleKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_EAGLE);
	KeyState bearKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_BEAR);
	KeyState monkeyKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_MONKEY);
	float scrollValue = GET_INPUT_MANAGER()->getMouseInfo().m_ScollValue;
	GearType prevGear = m_Info.m_Gear;
	if (m_GearDelay > 0.6f)
	{
		if (prevGear == GEAR_BEAR)
		{
			if (eagleKey == KS_PRESS || scrollValue < 0)
			{
				m_Info.m_Gear = GEAR_EAGLE;
				m_GearDelay = 0;
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
			else if (monkeyKey == KS_PRESS || scrollValue > 0)
			{
				m_Info.m_Gear = GEAR_MONKEY;
				m_GearDelay = 0;
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
		}
		else if (prevGear == GEAR_MONKEY)
		{
			if (eagleKey == KS_PRESS || scrollValue > 0)
			{
				m_Info.m_Gear = GEAR_EAGLE;
				m_GearDelay = 0;
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
			else if (bearKey == KS_PRESS || scrollValue < 0)
			{
				m_Info.m_Gear = GEAR_BEAR;
				m_GearDelay = 0;
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
		}
		else if (prevGear == GEAR_EAGLE)
		{
			if (bearKey == KS_PRESS || scrollValue > 0)
			{
				m_Info.m_Gear = GEAR_BEAR;
				m_GearDelay = 0;
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
			else if (monkeyKey == KS_PRESS || scrollValue < 0)
			{
				m_Info.m_Gear = GEAR_MONKEY;
				m_GearDelay = 0;
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
		}
	}
	else
	{
		m_GearDelay += dTime;
	}

	if (m_Info.m_Gear != prevGear)
	{
		if (m_Info.m_Gear == GEAR_EAGLE)
		{
			m_Body->setGravityEnable(false);
			m_Transitions[0][STAT_IDLE] = idleTransitionInEagle;

			auto velocity = getPhysicsBody()->getVelocity();

			velocity.x = 0;
			velocity.y = 0;

			getPhysicsBody()->setVelocity(velocity);
			m_States[0] = STAT_IDLE;
			setPosition(getPositionX(), getPositionY() + 10);
		}
		else
		{
			m_Body->setGravityEnable(true);
			m_Transitions[0][STAT_IDLE] = idleTransition;
			m_States[0] = STAT_IDLE;
		}
		
		prevGear = m_Info.m_Gear;
	}
}

void Player::setDirection(Direction dir)
{
	m_Info.m_LowerDir = dir;
}

void Player::enterDownJump(Creature* target, double dTime)
{
	auto velocity = target->getPhysicsBody()->getVelocity();

	//속도 임시로 지정.
	velocity.y = 100;

	target->getPhysicsBody()->setVelocity(velocity);
}

void Player::downJumpTransition(Creature* target, double dTime, int idx)
{
	auto player = static_cast<Player*>(target);

	//->idle
	cocos2d::Rect rect = cocos2d::Rect(target->getPositionX(), target->getPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT);
	if (GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) == OT_BLOCK)
	{
		target->setState(idx, Player::STAT_IDLE);
	}
}

void Player::idleTransitionInEagle(Creature* target, double dTime, int idx)
{
	//->fly
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD ||
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD ||
		GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_HOLD ||
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD)
	{
		target->setState(idx, Player::STAT_FLY);
		return;
	}
}

void Player::fly(Creature* target, double dTime, int idx)
{
	cocos2d::Rect rect = cocos2d::Rect(target->getPosition().x, target->getPosition().y,
		static_cast<Player*>(target)->getInfo().m_Size.width, static_cast<Player*>(target)->getInfo().m_Size.height);

	auto velocity = (static_cast<Player*>(target))->getPhysicsBody()->getVelocity();

	if ((GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_LEFT) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_LEFT) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
	{
		static_cast<Player*>(target)->setDirection(DIR_LEFT);
		velocity.x = -200;
	}
	else if ((GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_RIGHT) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_RIGHT) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		static_cast<Player*>(target)->setDirection(DIR_RIGHT);
		velocity.x = 200;
	}
	else
	{
		velocity.x = 0;
	}

	if ((GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_UP) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_UP) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_HOLD)
	{
		velocity.y = 200;
	}
	else if ((GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(target, rect, DIR_DOWN) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD)
	{
		velocity.y = -200;
	}
	else
	{
		velocity.y = 0;
	}

	target->getPhysicsBody()->setVelocity(velocity);
}

void Player::flyTransition(Creature* target, double dTime, int idx)
{
	//->idle
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_NONE)
	{
		target->setState(idx, Player::STAT_IDLE);
		return;
	}
}

Player::Player()
{

	//임시로 데이터 지정
	m_Info.m_MeleeAttackSpeed = 1.0f;
}

Player::~Player()
{
	m_Body->release();
	m_PlayerRenderer->release();
}

void Player::setInfo(PlayerInfo info)
{
	m_Info = info;
}

void Player::meleeAttack(Creature* target, double dTime, int idx)
{

}

void Player::attackIdleTransition(Creature* target, double dTime, int idx)
{

}

void Player::meleeAttackTransition(Creature* target, double dTime, int idx)
{

}
