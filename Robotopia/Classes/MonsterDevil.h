/************************************************************************/
/*
CLASS			: MonsterDevil
Author			: 김성연
역할				: DevilMonster class
최종 수정일자		: 2014-12-09
최종 수정자		:
최종 수정사유		:
Comment			: DevilMonster 동작 정의.
*/
/************************************************************************/
#pragma once
#include "Creature.h"
#include "Util.h"

class MonsterDevil : public Creature
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_MOVE,
		STAT_ATTACK,
		STAT_NUM,
	};

	virtual bool					init();
	virtual void					update(float dTime);
	virtual void					enter();
	virtual void					exit();

	virtual const AllStatus&		getInfo() const;

	void							move(Creature* target, double dTime, int idx);
	void							attack(Creature* target, double dTime, int idx);
	void							enterAttack(Creature* target, double dTime, int idx);

	void							idleTransition(Creature* target, double dTime, int idx);
	void							moveTransition(Creature* target, double dTime, int idx);
	void							attackTransition(Creature* target, double dTime, int idx);

	CREATE_FUNC(MonsterDevil);

private:
	AllStatus				m_Info;
	cocos2d::Point			m_FirstPos = cocos2d::Point::ZERO;
	int						m_MaxAttackRange = 200;
	int						m_MaxSightBound = 400;
	int						m_MaxMoveBound = 500;
	bool					m_IsAttacking = false;
	int						m_AttackStartTime = 0;
	cocos2d::Animation*		m_AttackArrow = nullptr;
};