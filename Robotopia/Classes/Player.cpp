#include "pch.h"
#include "Player.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "StageManager.h"
#include "ComponentManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "AnimationComponent.h"
#include "GameScene.h"
#include "PlayerRenderer.h"
#include "CommonState.h"
#include "MissileManager.h"
#include "AssemblyScene.h"
#include "AimingMissile.h"
#include "DataManager.h"
#include "Floor.h"
#include "Missile.h"
#include "NPC.h"
#include "PenerateMissile.h"

#define FLY_STEAM_PER_SECOND 5

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
	m_Body->setCollisionBitmask(PHYC_BLOCK | PHYC_FLOOR | PHYC_MONSTER | PHYC_MISSILE | PHYC_NPC);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);
	m_Body->retain();

	//info 설정

	m_Info = GET_DATA_MANAGER()->getPlayerInfo();

	m_Info.m_MaxHp = 100;
	m_Info.m_CurrentHp = m_Info.m_MaxHp;
	m_Info.m_CurrentSteam = m_Info.m_MaxSteam;
	m_Info.m_Gear = GEAR_BEAR;
	m_Info.m_UpperDir = DIR_LEFT;
	m_Info.m_LowerDir = DIR_LEFT;
	m_Info.m_Size = cocos2d::Size(PLAYER_WIDTH, PLAYER_HEIGHT);

	//FSM 초기화:
	initSkillFSM();
	initFSMAndTransition();
	gearSetting();

	m_PlayerRenderer = PlayerRenderer::create();
	m_PlayerRenderer->retain();
	addChild(m_PlayerRenderer);
	m_FlyTime = 0;

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

	//dash 중에는 이동 불가.
	if (m_Dashing)
	{
		return;
	}

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

		setState(idx, STAT_MOVE);
		return;
	}

	//->downJump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS &&
		GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD &&
		GET_GAME_MANAGER()->getContactComponentType(this,rect,DIR_DOWN) == OT_FLOOR)
	{
		enterDownJump();
		setState(idx, STAT_JUMP_DOWN);
		return;
	}

	//->jump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS)
	{
		enterJump(false);
		setState(idx, STAT_JUMP);
		return;
	}

	//->fall
	if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) == CT_NONE)
	{
		enterJump(true);
		setState(idx, STAT_JUMP);
		return;
	}

	//->processing
	if (GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_HOLD && m_IsContactingNPC)
	{
		setState(idx, STAT_PROCESSING);
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
		setDirection(DIR_LEFT);
		velocity.x = -m_Info.m_Speed;
	}
	else if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_RIGHT) == CT_NONE &&
		GET_INPUT_MANAGER()->getKeyState(KC_RIGHT) == KS_HOLD)
	{
		setDirection(DIR_RIGHT);
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
	static int jumpValue = 0;

	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_RELEASE)
	{
		m_Jumping = false;
		jumpValue = 0;
	}

	if (m_Jumping && GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_HOLD)
	{
		//0.1초이상 누르면 발동
		if (GET_GAME_MANAGER()->getMicroSecondTime() - m_JumpTime > 200)
		{
			float nowJump = dTime*m_Info.m_Jump;
			jumpValue += nowJump;

			if (jumpValue >= m_Info.m_Jump / 2)
			{
				m_Jumping = false;
				jumpValue = 0;
			}

			auto velocity = getPhysicsBody()->getVelocity();

			getPhysicsBody()->setVelocity(cocos2d::Vect(velocity.x, velocity.y - GRAVITY*dTime));
		}
		else
		{
			auto velocity = getPhysicsBody()->getVelocity();

			getPhysicsBody()->setVelocity(cocos2d::Vect(velocity.x, velocity.y - GRAVITY*dTime * 0.5));
		}
	}
	move(target, dTime, idx);
}

void Player::enterMove(Direction dir)
{
	auto velocity = getPhysicsBody()->getVelocity();

	setDirection(dir);

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

	if (!isFall)
	{
		velocity.y = m_Info.m_Jump / 1.5;
		m_Jumping = true;
		m_JumpTime = GET_GAME_MANAGER()->getMicroSecondTime();
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

	//종류에 따른 처리
	switch (enemyComponent->getPhysicsBody()->getCategoryBitmask())
	{
	case PHYC_FLOOR:
		return contactFloor(contact, static_cast<Floor*>(enemyComponent), isComponentA);
	case PHYC_MONSTER:
		return contactMonster(contact, static_cast<Creature*>(enemyComponent));
	case PHYC_MISSILE:
		return contactMissile(contact, static_cast<Missile*>(enemyComponent));
	case PHYC_TRAP:
		return contactTrap(contact, static_cast<BaseComponent*>(enemyComponent));
	case PHYC_NPC:
		return contactNPC(contact, static_cast<NPC*>(enemyComponent));
	}

	//default 처리
	return true;
}


void Player::onContactSeparate(cocos2d::PhysicsContact& contact)
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


	//종류에 따른 처리
	switch (enemyComponent->getPhysicsBody()->getCategoryBitmask())
	{
	case PHYC_NPC:
		m_IsContactingNPC = false;
		break;
	}

	//default 처리
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
	actSkill(dTime);

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
	if (m_IsInvincible && m_SkillStartTime[SKILL_BEAR] == 0)
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
	//->processing
	if (GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_HOLD && m_IsContactingNPC)
	{
		setState(idx, STAT_PROCESSING);
		return;
	}

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

	m_FlyTime += dTime;
	consumeFlySteam();
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
		consumeMeleeAttackSteam();
		GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_PUNCH , getPosition(), m_Info.m_UpperDir, m_Info.m_Size, m_Info.m_MeleeDamage);
		m_AttackStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
		m_States[idx] = AS_ATTACK;
	}
}

void Player::meleeAttackTransition(Creature* target, double dTime, int idx)
{
	int time = GET_GAME_MANAGER()->getMicroSecondTime();

	if (time - m_AttackStartTime > 1000 / (m_Info.m_MeleeAttackSpeed))
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
	if (GET_INPUT_MANAGER()->getMouseInfo().m_MouseState == MS_LEFT_DOWN)
	{
		if (m_States[0] == STAT_IDLE || m_States[0] == STAT_MOVE)
		{
			exitMove();
			m_AttackStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
			m_States[0] = STAT_IDLE;
			m_States[idx] = AS_ATTACK;
		}
	}
}

void Player::rangeAttackTransition(Creature* target, double dTime, int idx)
{
	static bool isLaunched = false;
	int time = GET_GAME_MANAGER()->getMicroSecondTime();

	if (time - m_AttackStartTime > 500 / (m_Info.m_RangeAttackSpeed) && !isLaunched)
	{
		auto mousePoint = GET_INPUT_MANAGER()->getMouseInfo().m_MouseMove;

		mousePoint -= GET_STAGE_MANAGER()->getViewPosition();
		consumeRangeAttackSteam();
		auto missile = GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_PLAYER_LINEAR, getPosition(), m_Info.m_UpperDir, m_Info.m_Size,
			m_Info.m_RangeDamage, cocos2d::Vec2::ZERO, mousePoint);

		static_cast<PenerateMissile*>(missile)->setMaxDistance(m_Info.m_AttackRange);
		isLaunched = true;
	}

	if (time - m_AttackStartTime > 1000 / (m_Info.m_RangeAttackSpeed))
	{
		m_States[idx] = AS_ATK_IDLE;
		isLaunched = false;
	}
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
	m_GearFSMs[GEAR_BEAR][0][STAT_PROCESSING] = nullptr;

	m_GearTransitions[GEAR_BEAR][0].resize(STAT_NUM);
	m_GearTransitions[GEAR_BEAR][0][STAT_IDLE] = FSM_CALLBACK(Player::idleTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_MOVE] = FSM_CALLBACK(Player::moveTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_JUMP] = FSM_CALLBACK(Player::jumpTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_JUMP_DOWN] = FSM_CALLBACK(Player::downJumpTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_FLY] = nullptr;
	m_GearTransitions[GEAR_BEAR][0][STAT_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);
	m_GearTransitions[GEAR_BEAR][0][STAT_PROCESSING] = FSM_CALLBACK(Player::processingTransition, this);

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
	m_GearFSMs[GEAR_MONKEY][0][STAT_PROCESSING] = nullptr;

	m_GearTransitions[GEAR_MONKEY][0].resize(STAT_NUM);
	m_GearTransitions[GEAR_MONKEY][0][STAT_IDLE] = FSM_CALLBACK(Player::idleTransitionInMonkey, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_MOVE] = FSM_CALLBACK(Player::moveTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_JUMP] = FSM_CALLBACK(Player::jumpTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_JUMP_DOWN] = FSM_CALLBACK(Player::downJumpTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_FLY] = nullptr;
	m_GearTransitions[GEAR_MONKEY][0][STAT_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);
	m_GearTransitions[GEAR_MONKEY][0][STAT_PROCESSING] = FSM_CALLBACK(Player::processingTransition, this);

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
	m_GearFSMs[GEAR_EAGLE][0][STAT_IDLE] = FSM_CALLBACK(Player::idleInEagle, this);
	m_GearFSMs[GEAR_EAGLE][0][STAT_MOVE] = FSM_CALLBACK(Player::move, this);
	m_GearFSMs[GEAR_EAGLE][0][STAT_JUMP] = nullptr;
	m_GearFSMs[GEAR_EAGLE][0][STAT_JUMP_DOWN] = nullptr;
	m_GearFSMs[GEAR_EAGLE][0][STAT_FLY] = FSM_CALLBACK(Player::fly, this);
	m_GearFSMs[GEAR_EAGLE][0][STAT_KNOCKBACK] = CommonState::knockback;
	m_GearFSMs[GEAR_EAGLE][0][STAT_PROCESSING] = nullptr;

	m_GearTransitions[GEAR_EAGLE][0].resize(STAT_NUM);
	m_GearTransitions[GEAR_EAGLE][0][STAT_IDLE] = FSM_CALLBACK(Player::idleTransitionInEagle, this);
	m_GearTransitions[GEAR_EAGLE][0][STAT_MOVE] = FSM_CALLBACK(Player::moveTransition, this);
	m_GearTransitions[GEAR_EAGLE][0][STAT_JUMP] = nullptr;
	m_GearTransitions[GEAR_EAGLE][0][STAT_JUMP_DOWN] = nullptr;
	m_GearTransitions[GEAR_EAGLE][0][STAT_FLY] = FSM_CALLBACK(Player::flyTransition, this);
	m_GearTransitions[GEAR_EAGLE][0][STAT_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);
	m_GearTransitions[GEAR_EAGLE][0][STAT_PROCESSING] = FSM_CALLBACK(Player::processingTransition, this);

	m_GearFSMs[GEAR_EAGLE][1].resize(AS_NUM);
	m_GearFSMs[GEAR_EAGLE][1][AS_ATK_IDLE] = nullptr;
	m_GearFSMs[GEAR_EAGLE][1][AS_ATTACK] = nullptr;
	m_GearFSMs[GEAR_EAGLE][1][AS_KNOCKBACK] = CommonState::knockback;

	m_GearTransitions[GEAR_EAGLE][1].resize(AS_NUM);
	m_GearTransitions[GEAR_EAGLE][1][AS_ATK_IDLE] = FSM_CALLBACK(Player::attackIdleTransitionInEagle, this);
	m_GearTransitions[GEAR_EAGLE][1][AS_ATTACK] = nullptr;
	m_GearTransitions[GEAR_EAGLE][1][AS_KNOCKBACK] = FSM_CALLBACK(Player::knockbackTransition, this);

	//스킬로 인해 변경되는 FSM 적용.
	applySkillToFSM();
}

void Player::idleTransitionInMonkey(Creature* target, double dTime, int idx)
{
	//원거리는 공격중에 다른 행동 불가
	if (m_States[1] == AS_ATTACK)
	{
		return;
	}

	//그 외에는 그냥이랑 똑같애
	idleTransition(target, dTime, idx);
}

void Player::idleInEagle(Creature* target, double dTime, int idx)
{
	m_FlyTime += dTime;
	consumeFlySteam();
}

void Player::consumeFlySteam()
{
	//1초에 한번씩 플라이 스팀 깜. 
	const double CONSUME_SECOND = 1;

	while (m_FlyTime > CONSUME_SECOND)
	{
		m_FlyTime -= CONSUME_SECOND;
		consumeSteam(FLY_STEAM_PER_SECOND);
	}
}

void Player::consumeMeleeAttackSteam()
{
	const int MELEE_STEAM = 3;

	consumeSteam(MELEE_STEAM);
}

void Player::consumeRangeAttackSteam()
{
	const int RANGE_STEAM = 5;

	consumeSteam(RANGE_STEAM);
}

bool Player::contactMonster(cocos2d::PhysicsContact& contact, Creature* monster)
{
	auto monsterBody = monster->getPhysicsBody();
	auto monsterVelocity = monsterBody->getVelocity();

	//무적 상태일 때는 무조건 생략.
	if (m_IsInvincible)
	{
		return false;
	}

	if (monsterVelocity.x == 0)
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
	else if (monsterVelocity.x > 0)
	{
		m_Info.m_LowerDir = DIR_RIGHT;
	}
	else
	{
		m_Info.m_LowerDir = DIR_LEFT;
	}
	
	setKnockbackState();
	hit(monster->getInfo().m_MeleeDamage);
	return false;
}

void Player::hit(float damage)
{
	m_Info.m_CurrentHp -= damage * 100 / (100 + m_Info.m_DefensivePower);

	if (m_Info.m_CurrentHp <= 0)
	{
		GET_GAME_MANAGER()->changeScene(AssemblyScene::create(), ASSEMBLY_SCENE);
	}
}

bool Player::contactTrap(cocos2d::PhysicsContact& contact, BaseComponent* trap)
{
	//무적 상태일 때는 무조건 생략.
	if (m_IsInvincible)
	{
		return false;
	}

	if (m_Info.m_LowerDir == DIR_LEFT)
	{
		m_Info.m_LowerDir = DIR_RIGHT;
	}
	else
	{
		m_Info.m_LowerDir = DIR_LEFT;
	}

	setKnockbackState();

	//임시 지정
	hit(5);
	return false;
}

bool Player::contactFloor(cocos2d::PhysicsContact& contact, Floor* floor, bool isComponentA)
{
	if (m_States[0] == STAT_JUMP_DOWN)
	{
		m_States[0] = STAT_JUMP;
		return false;
	}

	if ((contact.getContactData()->normal.y > 0 && isComponentA) ||
		(contact.getContactData()->normal.y < 0 && !isComponentA))
	{
		return false;
	}

	//eagle 상태일땐 floor와의 충돌 무시.
	if (m_Info.m_Gear == GEAR_EAGLE)
	{
		return false;
	}

	//그 외에는 충돌 인정
	return true;
}

bool Player::contactMissile(cocos2d::PhysicsContact& contact, Missile* missile)
{
	//자기가 쏜 건 안 맞음.
	if (missile->isPlayerMissile())
	{
		return false;
	}

	auto missileBody = missile->getPhysicsBody();
	auto missileVelocity = missileBody->getVelocity();

	//무적 상태일 때는 무조건 생략.
	if (m_IsInvincible)
	{
		return false;
	}

	if (missileVelocity.x == 0)
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
	else if (missileVelocity.x > 0)
	{
		m_Info.m_LowerDir = DIR_RIGHT;
	}
	else
	{
		m_Info.m_LowerDir = DIR_LEFT;
	}

	setKnockbackState();

	hit(missile->getDamage());
	return false;
}

void Player::doubleJumpTransition(Creature* target, double dTime, int idx)
{
	static int jumpNum = 0;

	//->jump
	if (GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS && jumpNum == 0)
	{
		auto skillSet = GET_DATA_MANAGER()->getSkillSet();
		auto skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_COMMON, skillSet.m_CommonSkill);

		enterJump(false);
		setState(idx, Player::STAT_JUMP);
		consumeSteam(skillInfo->m_SteamCost);
		jumpNum = 1;
		return;
	}

	//->idle
	cocos2d::Rect rect = cocos2d::Rect(getPositionX(), getPositionY(), PLAYER_WIDTH, PLAYER_HEIGHT);
	if (GET_GAME_MANAGER()->getContactComponentType(this, rect, DIR_DOWN) != CT_NONE)
	{
		auto body = getPhysicsBody();

		setState(idx, Player::STAT_IDLE);
		jumpNum = 0;
	}
}

void Player::initSkillFSM()
{
	m_SkillStartTime[SKILL_BEAR] = 0;
	m_SkillStartTime[SKILL_MONKEY] = 0;
	m_SkillStartTime[SKILL_EAGLE] = 0;
	m_SkillStartTime[SKILL_COMMON] = 0;

	m_SkillFSMs[SKILL_BEAR].resize(BEAR_END);
	m_SkillFSMs[SKILL_MONKEY].resize(MONKEY_END);
	m_SkillFSMs[SKILL_EAGLE].resize(EAGLE_END);
	m_SkillFSMs[SKILL_COMMON].resize(COMMON_END);

	//슈퍼 아머
	auto& superArmor = m_SkillFSMs[SKILL_BEAR][BEAR_SUPER_ARMOR];
	superArmor.m_FSMChanges.push_back
		(FSMChange(GEAR_BEAR, 0, FSMChange::STAT_SKILL, false, FSM_CALLBACK(Player::actSuperArmor, this)));

	//순간 무적
	auto& zhonya = m_SkillFSMs[SKILL_BEAR][BEAR_JONYA];
	zhonya.m_FSMChanges.push_back
		(FSMChange(GEAR_BEAR, 0, FSMChange::STAT_SKILL, false, FSM_CALLBACK(Player::actZhonya, this)));

	//비행 공격.
	auto& flyingAttack = m_SkillFSMs[SKILL_EAGLE][EAGLE_FLYING_ATTACK];
	flyingAttack.m_FSMChanges.push_back
		(FSMChange(GEAR_EAGLE, 1, AS_ATK_IDLE, true, FSM_CALLBACK(Player::flyAttackIdleTransition, this)));
	flyingAttack.m_FSMChanges.push_back
		(FSMChange(GEAR_EAGLE, 1, AS_ATTACK, true, FSM_CALLBACK(Player::flyAttackTransition, this)));

	//방사 공격
	auto& radiationAttack = m_SkillFSMs[SKILL_EAGLE][EAGLE_MISSILE_RADIATION];
	radiationAttack.m_FSMChanges.push_back
		(FSMChange(GEAR_EAGLE, 1, AS_ATK_IDLE, true, FSM_CALLBACK(Player::flyAttackIdleTransition, this)));
	radiationAttack.m_FSMChanges.push_back
		(FSMChange(GEAR_EAGLE, 1, AS_ATTACK, true, FSM_CALLBACK(Player::radiationAttackTransition, this)));

	//2단 점프.
	auto& doubleJump = m_SkillFSMs[SKILL_COMMON][COMMON_DOUBLE_JUMP];
	doubleJump.m_FSMChanges.push_back
		(FSMChange(GEAR_BEAR, 0, STAT_JUMP, true, FSM_CALLBACK(Player::doubleJumpTransition, this)));
	doubleJump.m_FSMChanges.push_back
		(FSMChange(GEAR_MONKEY, 0, STAT_JUMP, true, FSM_CALLBACK(Player::doubleJumpTransition, this)));
}

void Player::changeGearFSMBySkill(const SkillFSM& skill)
{
	auto& fsmChanges = skill.m_FSMChanges;
	for (int i = 0; i < fsmChanges.size(); i++)
	{
		auto& fsmChange = fsmChanges[i];
		
		//스킬로 따로 사용하는 경우 FSM 바꾸지 않음.
		if (fsmChange.m_State == FSMChange::STAT_SKILL)
		{
			continue;
		}

		if (fsmChange.m_IsTransition)
		{
			m_GearTransitions[fsmChange.m_Gear][fsmChange.m_Idx][fsmChange.m_State]
				= fsmChange.m_Function;
		}
		else
		{
			m_GearFSMs[fsmChange.m_Gear][fsmChange.m_Idx][fsmChange.m_State]
				= fsmChange.m_Function;
		}
	}
}

void Player::flyAttackIdleTransition(Creature* target, double dTime, int idx)
{
	if (GET_INPUT_MANAGER()->getMouseInfo().m_MouseState == MS_LEFT_DOWN)
	{
		m_AttackStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
		m_States[idx] = AS_ATTACK;
	}
}

void Player::flyAttackTransition(Creature* target, double dTIme, int idx)
{
	static bool isLaunch = false;
	int time = GET_GAME_MANAGER()->getMicroSecondTime();
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();
	auto skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_EAGLE, skillSet.m_EagleSkill);
	auto attackCoolTime = skillInfo->m_CoolTime;

	if (!isLaunch)
	{
		auto mousePoint = GET_INPUT_MANAGER()->getMouseInfo().m_MouseMove;

		mousePoint -= GET_STAGE_MANAGER()->getViewPosition();
		consumeSteam(skillInfo->m_SteamCost);
		auto missile = GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_AIMING, getPosition(), m_Info.m_UpperDir, m_Info.m_Size,
			skillInfo->m_Value, cocos2d::Vec2::ZERO, mousePoint);

		static_cast<AimingMissile*>(missile)->setMaxDistance(m_Info.m_AttackRange);
		isLaunch = true;
	}

	if (time - m_AttackStartTime > attackCoolTime*1000)
	{
		isLaunch = false;
		setState(idx, AS_ATK_IDLE);
	}
}

void Player::consumeSteam(float steam)
{
	m_Info.m_CurrentSteam -= steam * 100 / (100 + m_Info.m_SteamEffectiveness);
}

void Player::applySkillToFSM()
{
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();

	if (skillSet.m_BearSkill != BEAR_START)
		changeGearFSMBySkill(m_SkillFSMs[SKILL_BEAR][skillSet.m_BearSkill]);

	if (skillSet.m_MonkeySkill != MONKEY_START)
		changeGearFSMBySkill(m_SkillFSMs[SKILL_MONKEY][skillSet.m_MonkeySkill]);

	if (skillSet.m_EagleSkill != EAGLE_START)
		changeGearFSMBySkill(m_SkillFSMs[SKILL_EAGLE][skillSet.m_EagleSkill]);

	if (skillSet.m_CommonSkill != COMMON_START)
		changeGearFSMBySkill(m_SkillFSMs[SKILL_COMMON][skillSet.m_CommonSkill]);
}

void Player::processingTransition(Creature* target, double dTIme, int idx)
{
	if (!m_IsContactingNPC)
	{
		setState(idx, STAT_IDLE);
	}

	if (GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_NONE)
	{
		setState(idx, STAT_IDLE);
	}
}

bool Player::contactNPC(cocos2d::PhysicsContact& contact, NPC* npc)
{
	m_IsContactingNPC = true;

	return false;
}

void Player::produceSteam(float steam)
{
	m_Info.m_CurrentSteam += steam * 100 / (100 + m_Info.m_AbsorbEffectiveness);

	if (m_Info.m_CurrentSteam > m_Info.m_MaxSteam)
	{
		m_Info.m_CurrentSteam = m_Info.m_MaxSteam;
	}
}

void Player::actSkill(double dTime)
{
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();
	auto time = GET_GAME_MANAGER()->getMicroSecondTime();

	skillStateProc();

	if (GET_INPUT_MANAGER()->getKeyState(KC_DASH) == KS_HOLD)
	{
		const SkillInfo* skillInfo;

		skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_COMMON, skillSet.m_CommonSkill);

		//스킬 있는 경우
		if (skillInfo != nullptr)
		{
				//dash 스킬이면 dash 수행.
			if (skillInfo != nullptr && skillInfo->m_Skill == COMMON_DASH)
			{
				actDash();
			}
		}
	}

	if (GET_INPUT_MANAGER()->getKeyState(KC_SKILL) == KS_HOLD)
	{
		const SkillInfo* skillInfo;
		int skill;

		switch (m_Info.m_Gear)
		{
		case GEAR_BEAR:
			skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, skillSet.m_BearSkill);
			skill = SKILL_BEAR;
			break;
		case GEAR_MONKEY:
			skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_MONKEY, skillSet.m_MonkeySkill);
			skill = SKILL_MONKEY;
			break;
		case GEAR_EAGLE:
			skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_EAGLE, skillSet.m_EagleSkill);
			skill = SKILL_EAGLE;
			break;
		}

		auto& skillFSM = m_SkillFSMs[skill][skillInfo->m_Skill];

		if (skillFSM.m_FSMChanges.empty())
		{
			return;
		}
		
		auto& fsmChange = m_SkillFSMs[skill][skillInfo->m_Skill].m_FSMChanges[0];

		//act류 스킬이 아니면 동작 X.
		if (skillInfo == nullptr || fsmChange.m_State != FSMChange::STAT_SKILL)
		{
			return;
		}

		
		//cooltime 처리.
		if (time - m_SkillStartTime[skill] > skillInfo->m_CoolTime * 1000)
		{
			//act
			fsmChange.m_Function(this, dTime, 0);
		}
	}
}

void Player::setKnockbackState()
{
	m_IsInvincible = true;
	m_InvincibleStartTime = GET_GAME_MANAGER()->getMicroSecondTime();

	//슈퍼 아머 발동중일 땐 넉백 안 당함.
	if (!m_IsSuperArmor)
	{
		m_KnockbackStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
		CommonState::enterKnockback(this, m_Info.m_LowerDir);
		m_States[0] = STAT_KNOCKBACK;
		m_States[1] = AS_KNOCKBACK;
	}
}

void Player::actDash()
{
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();
	auto skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_COMMON, skillSet.m_CommonSkill);
	int time = GET_GAME_MANAGER()->getMicroSecondTime();

	if(!m_Dashing)
	{
		//cooltime 처리.
		if (time - m_SkillStartTime[SKILL_COMMON] <= skillInfo->m_CoolTime * 1000)
		{
			return;
		}

		//일반적인 이동상황 중에는 대쉬 가능.
		if (m_States[0] == STAT_IDLE || m_States[0] == STAT_MOVE || m_States[0] == STAT_JUMP ||
			m_States[0] == STAT_JUMP_DOWN || m_States[0] == STAT_FLY)
		{
			auto body = getPhysicsBody();
			auto velocity = body->getVelocity();

			//이동하던 방향으로 대쉬. 대쉬 속도는 일반 속도의 3배(임시).
			if (m_Info.m_LowerDir == DIR_RIGHT)
			{
				velocity.x = m_Info.m_Speed * 3;
			}
			else
			{
				velocity.x = -m_Info.m_Speed * 3;
			}
			velocity.y = 0;

			consumeSteam(skillInfo->m_SteamCost);
			body->setVelocity(velocity);
			m_Dashing = true;
			m_States[0] = STAT_IDLE;
			body->setGravityEnable(false);
			m_SkillStartTime[SKILL_COMMON] = GET_GAME_MANAGER()->getMicroSecondTime();
		}
	}
}

void Player::skillStateProc()
{
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();
	auto skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_COMMON, skillSet.m_CommonSkill);
	int time = GET_GAME_MANAGER()->getMicroSecondTime();

	if (m_Dashing)
	{
		if (time - m_SkillStartTime[SKILL_COMMON] > skillInfo->m_Value * 1000)
		{
			auto body = getPhysicsBody();

			body->setGravityEnable(true);
			exitMove();
			m_Dashing = false;
		}
	}

	skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, skillSet.m_BearSkill);
	if (m_IsSuperArmor)
	{
		if (time - m_SkillStartTime[SKILL_BEAR] > skillInfo->m_Value * 1000)
		{
			m_IsSuperArmor = false;
		}
	}

	if (m_IsInvincible && m_SkillStartTime[SKILL_BEAR] != 0)
	{
		if (time - m_SkillStartTime[SKILL_BEAR] > skillInfo->m_Value * 1000)
		{
			m_IsInvincible = false;
			m_SkillStartTime[SKILL_BEAR] = 0;
		}
	}
}

void Player::actSuperArmor(Creature* target, double dTime, int idx)
{
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();
	auto skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, skillSet.m_BearSkill);

	if (!m_IsSuperArmor)
	{
		consumeSteam(skillInfo->m_SteamCost);
		m_SkillStartTime[SKILL_BEAR] = GET_GAME_MANAGER()->getMicroSecondTime();
		m_IsSuperArmor = true;
	}
}

void Player::actZhonya(Creature* target, double dTime, int idx)
{
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();
	auto skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, skillSet.m_BearSkill);

	if (!m_IsInvincible)
	{
		consumeSteam(skillInfo->m_SteamCost);
		m_SkillStartTime[SKILL_BEAR] = GET_GAME_MANAGER()->getMicroSecondTime();
		m_IsInvincible = true;
	}
}

void Player::radiationAttackTransition(Creature* target, double dTime, int idx)
{
	static bool isLaunch = false;
	int time = GET_GAME_MANAGER()->getMicroSecondTime();
	auto skillSet = GET_DATA_MANAGER()->getSkillSet();
	auto skillInfo = GET_DATA_MANAGER()->getSkillInfo(SKILL_EAGLE, skillSet.m_EagleSkill);
	auto attackCoolTime = skillInfo->m_CoolTime;

	if (!isLaunch)
	{
		auto mousePoint = GET_INPUT_MANAGER()->getMouseInfo().m_MouseMove;

		mousePoint -= GET_STAGE_MANAGER()->getViewPosition();
		consumeSteam(skillInfo->m_SteamCost);
		for (int degree = 0; degree <= 360; degree += 30)
		{
			auto missile = GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_AIMING, getPosition(), m_Info.m_UpperDir, m_Info.m_Size,
				skillInfo->m_Value, cocos2d::Vec2::ZERO, mousePoint);

			static_cast<AimingMissile*>(missile)->setDegree(degree);
			static_cast<AimingMissile*>(missile)->setMaxDistance(m_Info.m_AttackRange);
		}
		isLaunch = true;
	}

	if (time - m_AttackStartTime > attackCoolTime * 1000)
	{
		isLaunch = false;
		setState(idx, AS_ATK_IDLE);
	}
}
