/************************************************************************/
/*
CLASS			: PlantMonster
Author			: 남현욱
역할				: 식물형 몬스터
최종 수정일자	: 2014-12-10
최종 수정자		:
최종 수정사유	:
Comment			: RushMonster 동작 정의.
*/
/************************************************************************/
#pragma once
#include "Creature.h"
#include "Util.h"

#define RUSH_WIDTH 60
#define RUSH_HEIGHT 50

class MonsterPlant : public Creature
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_ATTACK,
		STAT_NUM,
	};

	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();

	CREATE_FUNC(MonsterPlant);

	virtual bool				onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void				onContactSeparate(cocos2d::PhysicsContact& contact);

	virtual const AllStatus&	getInfo() const;
	void						setDirection(Direction dir);

	void						idle(Creature* target, double dTime, int idx);
	void						attack(Creature* target, double dTime, int idx);

	void						idleTransition(Creature* target, double dTime, int idx);
	void						attackTransition(Creature* target, double dTime, int idx);

protected:
	AllStatus				m_Info;
	double					m_AttackTime = 0.0f;
	double					m_IdleTime = 0.0f;
	int						m_AttackCount = 0;
};
