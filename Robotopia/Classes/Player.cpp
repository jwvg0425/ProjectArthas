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
#include "CommonState.h"
#include "MissileManager.h"
#include "AssemblyScene.h"

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
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR | PHYC_MONSTER | PHYC_MISSILE);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);
	m_Body->retain();

	//info 설정
	m_Info.m_MaxHp = 100;
	m_Info.m_CurrentHp = 100;
	m_Info.m_MaxSteam = 100;
	m_Info.m_CurrentSteam = 100;
	m_Info.m_Speed = 350;
	m_Info.m_Jump = 750;
	m_Info.m_UpperDir = DIR_LEFT;
	m_Info.m_LowerDir = DIR_LEFT;
	m_Info.m_Size = cocos2d::Size(PLAYER_WIDTH, PLAYER_HEIGHT);
	m_Info.m_Gear = GEAR_BEAR;
	m_Info.m_MeleeDamage = 10.0f;
	m_Info.m_MeleeAttackSpeed = 1.3f;

	//FSM 초기화
	initFSMAndTransition();
	gearSetting();

	m_PlayerRenderer = PlayerRenderer::create();
	m_PlayerRenderer->retain();
	addChild(m_PlayerRenderer);

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
	cocos2d::Rect rect = cocos2d::Rect(getPosition().x, getPosition().y,
									getInfo().m_Size.width, getInfo().m_Size.height);

	//->move
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD ||
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
		{
			enterMove(DIR_LEFT);
		}
		else
		{
			enterMove(DIR_RIGHT);
		}

		setState(idx, Player::STAT_MOVE);
		return;
	}

	//->downJump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS &&
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD &&
		GET_GAME_MANAGER()->getContactComponentType(this,rect,DIR_DOWN) == OT_FLOOR)
	{
		enterDownJump();
		setState(idx, Player::STAT_JUMP_DOWN);
		return;
	}

	//->jump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS)
	{
		enterJump(false);
		setState(idx, Player::STAT_JUMP);
		return;
	}

	//->fall
	if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) == CT_NONE)
	{
		enterJump(true);
		setState(idx, Player::STAT_JUMP);
		return;
	}
}

void Player::move(Creature* target, double dTime, int idx)
{
	cocos2d::Rect rect = cocos2d::Rect(getPosition().x, getPosition().y,
						getInfo().m_Size.width, getInfo().m_Size.height);
	
	auto velocity = getPhysicsBody()->getVelocity();

	if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_LEFT) == CT_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
	{
		velocity.x = -m_Info.m_Speed;
	}
	else if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_RIGHT) == CT_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		velocity.x = m_Info.m_Speed;
	}
	else
	{
		velocity.x = 0;
	}

	getPhysicsBody()->setVelocity(velocity);
}

void Player::jump(Creature* target, double dTime, int idx)
{
	move(target, dTime, idx);
}

void Player::enterMove(Direction dir)
{
	auto velocity = getPhysicsBody()->getVelocity();

	setDirection(dir);

	//속도 임시로 지정.
	if (dir == DIR_LEFT)
	{
		velocity.x = -m_Info.m_Speed;
	}
	else if (dir == DIR_RIGHT)
	{
		velocity.x = m_Info.m_Speed;
	}

	getPhysicsBody()->setVelocity(velocity);
}

void Player::enterJump(bool isFall)
{
	auto velocity = getPhysicsBody()->getVelocity();

	//속도 임시로 지정.
	if (!isFall)
	{
		velocity.y = m_Info.m_Jump;
	}

	getPhysicsBody()->setVelocity(velocity);
}

void Player::moveTransition(Creature* target, double dTime, int idx)
{
	//->idle
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_NONE)
	{
		exitMove();
		setState(idx, Player::STAT_IDLE);
	}

	//->jump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS)
	{
		exitMove();
		enterJump(false);
		setState(idx, Player::STAT_JUMP);
	}

	//->fall
	cocos2d::Rect rect = cocos2d::Rect(getPositionX(), getPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT);
	if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) == CT_NONE)
	{
		exitMove();
		enterJump(true);
		setState(idx, Player::STAT_JUMP);
	}
}

void Player::jumpTransition(Creature* target, double dTime, int idx)
{
	//->idle
	cocos2d::Rect rect = cocos2d::Rect(getPositionX(), getPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT);
	if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) != CT_NONE)
	{
		auto body = getPhysicsBody();

		setState(idx, Player::STAT_IDLE);
	}
}

void Player::exitMove()
{
	auto velocity = getPhysicsBody()->getVelocity();

	velocity.x = 0;

	getPhysicsBody()->setVelocity(velocity);
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


	//몬스터랑 충돌은 무조건 false 취급. 단, 충돌이 일어난 거 검사는 해야하므로 그건 실행시킴.
	if (enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_MONSTER ||
		enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_MISSILE)
	{
		auto enemyBody = enemyComponent->getPhysicsBody();
		auto enemyVelocity = enemyBody->getVelocity();

		//무적 상태일 때는 무조건 생략.
		if (m_IsInvincible)
		{
			return false;
		}

		if (enemyVelocity.x == 0)
		{
			if (m_Info.m_LowerDir == DIR_LEFT)
			{
				m_Info.m_LowerDir = DIR_RIGHT;
			}
			else
			{
				m_Info.m_LowerDir = DIR_LEFT;
			}
		}
		else if (enemyVelocity.x > 0)
		{
			m_Info.m_LowerDir = DIR_RIGHT;
		}
		else
		{
			m_Info.m_LowerDir = DIR_LEFT;
		}
		m_KnockbackStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
		m_IsInvincible = true;
		m_InvincibleStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
		CommonState::enterKnockback(this, m_Info.m_LowerDir);
		m_States[0] = STAT_KNOCKBACK;
		m_States[1] = AS_KNOCKBACK;

		//데미지 적용
		if (enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_MONSTER)
		{
			auto monster = static_cast<Creature*>(enemyComponent);
			int damage = monster->getInfo().m_MeleeDamage * 100 / (100 + m_Info.m_DefensivePower);

			m_Info.m_CurrentHp -= damage;
		}
		else
		{
			//임시로 트랩 뎀 5로 잡음.
			m_Info.m_CurrentHp -= 5;
		}

		//사망. 일단 임시로 0으로 만듬
		if (m_Info.m_CurrentHp <= 0)
		{
			GET_GAME_MANAGER()->changeScene(AssemblyScene::create(), ASSEMBLY_SCENE);
		}

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

	//방향 설정

	float mouseX = GET_INPUT_MANAGER()->getMouseInfo().m_MouseMove.x;

	cocos2d::log("layerX : %f, posX : %f", GET_STAGE_MANAGER()->getViewPosition().x, getPositionX());
	if (mouseX < GET_STAGE_MANAGER()->getViewPosition().x + getPositionX())
	{
		m_Info.m_UpperDir = DIR_LEFT;
	}
	else
	{
		m_Info.m_UpperDir = DIR_RIGHT;
	}

	for(auto& BaseComponent : getChildren())
	{
		BaseComponent->update(dTime);
	}

	updateFSM(dTime);

	for(int i = 0; i < m_States.size(); i++)
	{
		if(m_States[0] != m_PrevStates[0])
		{
			m_PlayerRenderer->changeState(static_cast<Player::State>( m_States[0] ));
		}
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

	auto player = const_cast<Player*>(this);

	if (m_Info.m_Gear != prevGear)
	{
		gearSetting();
		
		prevGear = m_Info.m_Gear;
	}

	//무적 해제
	if (m_IsInvincible)
	{
		
		int time = GET_GAME_MANAGER()->getMicroSecondTime();

		if (time - m_InvincibleStartTime > TIME_INVINCIBLE)
		{
			m_IsInvincible = false;
		}
	}
}

void Player::setDirection(Direction dir)
{
	m_Info.m_LowerDir = dir;
}

void Player::enterDownJump()
{
	auto velocity = getPhysicsBody()->getVelocity();

	//속도 임시로 지정.
	velocity.y = 100;

	getPhysicsBody()->setVelocity(velocity);
}

void Player::downJumpTransition(Creature* target, double dTime, int idx)
{
	//->idle
	cocos2d::Rect rect = cocos2d::Rect(getPositionX(), getPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT);
	if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) == OT_BLOCK)
	{
		setState(idx, Player::STAT_IDLE);
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
		setState(idx, Player::STAT_FLY);
		return;
	}
}

void Player::fly(Creature* target, double dTime, int idx)
{
	cocos2d::Rect rect = cocos2d::Rect(getPosition().x, getPosition().y,
		getInfo().m_Size.width, getInfo().m_Size.height);

	auto velocity = getPhysicsBody()->getVelocity();

	if ((GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_LEFT) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_LEFT) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_HOLD)
	{
		setDirection(DIR_LEFT);
		velocity.x = -m_Info.m_Speed;
	}
	else if ((GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_RIGHT) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_RIGHT) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		setDirection(DIR_RIGHT);
		velocity.x = m_Info.m_Speed;
	}
	else
	{
		velocity.x = 0;
	}

	if ((GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_UP) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_UP) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_HOLD)
	{
		velocity.y = m_Info.m_Speed;
	}
	else if ((GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) == CT_NONE ||
		GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) == OT_FLOOR) &&
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD)
	{
		velocity.y = -m_Info.m_Speed;
	}
	else
	{
		velocity.y = 0;
	}

	getPhysicsBody()->setVelocity(velocity);
}

void Player::flyTransition(Creature* target, double dTime, int idx)
{
	//->idle
	if (GET_INPUT_MANAGER()->getKeyState(KC_LEFT) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_NONE)
	{
		setState(idx, Player::STAT_IDLE);
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
	if (GET_INPUT_MANAGER()->getMouseInfo().m_MouseState == MS_LEFT_DOWN)
	{
		GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_PUNCH , getPosition(), m_Info.m_UpperDir, m_Info.m_Size, m_Info.m_MeleeDamage);
		m_MeleeAttackStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
		m_States[idx] = AS_ATTACK;
	}
}

void Player::meleeAttackTransition(Creature* target, double dTime, int idx)
{
	int time = GET_GAME_MANAGER()->getMicroSecondTime();

	if (time - m_MeleeAttackStartTime > 1000 / (m_Info.m_MeleeAttackSpeed))
	{
		m_States[idx] = AS_ATK_IDLE;
	}
}

void Player::knockbackTransition(Creature* target, double dTime, int idx)
{
	int time = GET_GAME_MANAGER()->getMicroSecondTime();

	int knockbackDelay = TIME_KNOCKBACK * 100 / (100 + getInfo().m_Resistance);

	if (time - m_KnockbackStartTime >= knockbackDelay)
	{
		switch (idx)
		{
		case 0:
			m_States[idx] = STAT_IDLE;
			break;
		case 1:
			m_States[idx] = AS_ATK_IDLE;
			break;
		}
	}
}

void Player::attackIdleTransitionInEagle(Creature* target, double dTIme, int idx)
{
	//비행 모드일 땐 공격 불가!
}

void Player::gearSetting()
{
	auto velocity = getPhysicsBody()->getVelocity();

	switch (m_Info.m_Gear)
	{
	case GEAR_BEAR:
		m_Body->setGravityEnable(true);
		m_States[0] = STAT_IDLE;
		m_States[1] = AS_ATK_IDLE;
		break;

	case GEAR_MONKEY:
		m_Body->setGravityEnable(true);
		m_States[0] = STAT_IDLE;
		m_States[1] = AS_ATK_IDLE;
		break;

	case GEAR_EAGLE:
		m_Body->setGravityEnable(false);
		velocity.x = 0;
		velocity.y = 0;
		getPhysicsBody()->setVelocity(velocity);
		m_States[0] = STAT_IDLE;
		m_States[1] = AS_ATK_IDLE;
		setPosition(getPositionX(), getPositionY() + 10);
		break;
	}

	//각 기어에 맞는 fsm으로 교체.
	for (int fsm = 0; fsm < m_FSMNum; fsm++)
	{
		for (int state = 0; state < m_FSMs[fsm].size(); state++)
		{
			m_FSMs[fsm][state] = m_GearFSMs[m_Info.m_Gear][fsm][state];
			m_Transitions[fsm][state] = m_GearTransitions[m_Info.m_Gear][fsm][state];
		}
	}
}

void Player::attackIdleTransitionInMonkey(Creature* target, double dTime, int idx)
{

}

void Player::rangeAttackTransition(Creature* target, double dTime, int idx)
{

}

void Player::rangeAttack(Creature* target, double dTime, int idx)
{

}

void Player::initFSMAndTransition()
{
	initFSM(m_FSMNum);
	m_FSMs[0].resize(STAT_NUM);
	m_FSMs[1].resize(AS_NUM);
	
	m_Transitions[0].resize(STAT_NUM);
	m_Transitions[1].resize(AS_NUM);

	m_States[0] = STAT_IDLE;
	m_States[1] = AS_ATK_IDLE;

	//전체 FSM 종류 초기화
	m_GearFSMs[GEAR_BEAR].resize(m_FSMNum);
	m_GearFSMs[GEAR_EAGLE].resize(m_FSMNum);
	m_GearFSMs[GEAR_MONKEY].resize(m_FSMNum);

	m_GearTransitions[GEAR_BEAR].resize(m_FSMNum);
	m_GearTransitions[GEAR_EAGLE].resize(m_FSMNum);
	m_GearTransitions[GEAR_MONKEY].resize(m_FSMNum);

	//bear 상태 fsm 초기화
	
	m_GearFSMs[GEAR_BEAR][0].resize(STAT_NUM);
	m_GearFSMs[GEAR_BEAR][0][STAT_IDLE] = nullptr;
	m_GearFSMs[GEAR_BEAR][0][STAT_MOVE] = FSM_CALLBACK(Player::move, this);
	m_GearFSMs[GEAR_BEAR][0][STAT_JUMP] = FSM_CALLBACK(Player::jump, this);
	m_GearFSMs[GEAR_BEAR][0][STAT_JUMP_DOWN] = FSM_CALLBACK(Player::jump, this);
	m_GearFSMs[GEAR_BEAR][0][STAT_FLY] = nullptr;
	m_GearFSMs[GEAR_BEAR][0][STAT_KNOCKBACK] = CommonState::knockback;

	m_GearTransitions[GEAR_BEAR][0].resize(STAT_NUM);
	m_GearTransitions[GEAR_BEAR][0][STAT_IDLE] = FSM_CALLBACK(Player::idleTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_MOVE] = FSM_CALLBACK(Player::moveTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_JUMP] = FSM_CALLBACK(Player::jumpTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_JUMP_DOWN] = FSM_CALLBACK(Player::downJumpTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_FLY] = nullptr;
	m_GearTransitions[GEAR_BEAR][0][STAT_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);

	m_GearFSMs[GEAR_BEAR][1].resize(AS_NUM);
	m_GearFSMs[GEAR_BEAR][1][AS_ATK_IDLE] = nullptr;
	m_GearFSMs[GEAR_BEAR][1][AS_ATTACK] = FSM_CALLBACK(Player::meleeAttack, this);
	m_GearFSMs[GEAR_BEAR][1][AS_KNOCKBACK] = CommonState::knockback;

	m_GearTransitions[GEAR_BEAR][1].resize(AS_NUM);
	m_GearTransitions[GEAR_BEAR][1][AS_ATK_IDLE] = FSM_CALLBACK(Player::attackIdleTransition, this);
	m_GearTransitions[GEAR_BEAR][1][AS_ATTACK] = FSM_CALLBACK(Player::meleeAttackTransition, this);
	m_GearTransitions[GEAR_BEAR][1][AS_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);

	//monkey 상태 fsm 초기화
	m_GearFSMs[GEAR_MONKEY][0].resize(STAT_NUM);
	m_GearFSMs[GEAR_MONKEY][0][STAT_IDLE] = nullptr;
	m_GearFSMs[GEAR_MONKEY][0][STAT_MOVE] = FSM_CALLBACK(Player::move, this);
	m_GearFSMs[GEAR_MONKEY][0][STAT_JUMP] = FSM_CALLBACK(Player::jump, this);
	m_GearFSMs[GEAR_MONKEY][0][STAT_JUMP_DOWN] = FSM_CALLBACK(Player::jump, this);
	m_GearFSMs[GEAR_MONKEY][0][STAT_FLY] = nullptr;
	m_GearFSMs[GEAR_MONKEY][0][STAT_KNOCKBACK] = CommonState::knockback;

	m_GearTransitions[GEAR_MONKEY][0].resize(STAT_NUM);
	m_GearTransitions[GEAR_MONKEY][0][STAT_IDLE] = FSM_CALLBACK(Player::idleTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_MOVE] = FSM_CALLBACK(Player::moveTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_JUMP] = FSM_CALLBACK(Player::jumpTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_JUMP_DOWN] = FSM_CALLBACK(Player::downJumpTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_FLY] = nullptr;
	m_GearTransitions[GEAR_MONKEY][0][STAT_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);

	m_GearFSMs[GEAR_MONKEY][1].resize(AS_NUM);
	m_GearFSMs[GEAR_MONKEY][1][AS_ATK_IDLE] = nullptr;
	m_GearFSMs[GEAR_MONKEY][1][AS_ATTACK] = FSM_CALLBACK(Player::rangeAttack, this);
	m_GearFSMs[GEAR_MONKEY][1][AS_KNOCKBACK] = CommonState::knockback;

	m_GearTransitions[GEAR_MONKEY][1].resize(AS_NUM);
	m_GearTransitions[GEAR_MONKEY][1][AS_ATK_IDLE] = FSM_CALLBACK(Player::attackIdleTransitionInMonkey, this);
	m_GearTransitions[GEAR_MONKEY][1][AS_ATTACK] = FSM_CALLBACK(Player::rangeAttackTransition, this);
	m_GearTransitions[GEAR_MONKEY][1][AS_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);

	//eagle 상태 fsm 초기화
	m_GearFSMs[GEAR_EAGLE][0].resize(STAT_NUM);
	m_GearFSMs[GEAR_EAGLE][0][STAT_IDLE] = nullptr;
	m_GearFSMs[GEAR_EAGLE][0][STAT_MOVE] = FSM_CALLBACK(Player::move, this);
	m_GearFSMs[GEAR_EAGLE][0][STAT_JUMP] = nullptr;
	m_GearFSMs[GEAR_EAGLE][0][STAT_JUMP_DOWN] = nullptr;
	m_GearFSMs[GEAR_EAGLE][0][STAT_FLY] = FSM_CALLBACK(Player::fly, this);
	m_GearFSMs[GEAR_EAGLE][0][STAT_KNOCKBACK] = CommonState::knockback;

	m_GearTransitions[GEAR_EAGLE][0].resize(STAT_NUM);
	m_GearTransitions[GEAR_EAGLE][0][STAT_IDLE] = FSM_CALLBACK(Player::idleTransitionInEagle, this);
	m_GearTransitions[GEAR_EAGLE][0][STAT_MOVE] = FSM_CALLBACK(Player::moveTransition, this);
	m_GearTransitions[GEAR_EAGLE][0][STAT_JUMP] = nullptr;
	m_GearTransitions[GEAR_EAGLE][0][STAT_JUMP_DOWN] = nullptr;
	m_GearTransitions[GEAR_EAGLE][0][STAT_FLY] = FSM_CALLBACK(Player::flyTransition, this);
	m_GearTransitions[GEAR_EAGLE][0][STAT_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);

	m_GearFSMs[GEAR_EAGLE][1].resize(AS_NUM);
	m_GearFSMs[GEAR_EAGLE][1][AS_ATK_IDLE] = nullptr;
	m_GearFSMs[GEAR_EAGLE][1][AS_ATTACK] = nullptr;
	m_GearFSMs[GEAR_EAGLE][1][AS_KNOCKBACK] = CommonState::knockback;

	m_GearTransitions[GEAR_EAGLE][1].resize(AS_NUM);
	m_GearTransitions[GEAR_EAGLE][1][AS_ATK_IDLE] = FSM_CALLBACK(Player::attackIdleTransitionInEagle, this);
	m_GearTransitions[GEAR_EAGLE][1][AS_ATTACK] = nullptr;
	m_GearTransitions[GEAR_EAGLE][1][AS_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);
}
