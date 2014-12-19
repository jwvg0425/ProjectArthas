/************************************************************************/
/*
CLASS			: BossFirst
Author			: 김연우
역할				: 첫번째 보스 class
최종 수정일자		: 2014-12-19
최종 수정자		:
최종 수정사유		:
Comment			: 빙글빙글 돌아가며 춤을춥시다.
*/
/************************************************************************/
#pragma once
#include "Creature.h"
#include "Util.h"
#define RAIL_RADIUS 350
#define ROTATE_ANGLE 20
#define ROTATE_DURATION 1.f
#define MAX_ROTATE_NUM 40
#define MIN_ROTATE_NUM 5

class AnimationComponent;
class BossHead;
class BossFirst : public Creature
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_MOVE,
		STAT_ATTACK,
		STAT_NUM,
	};

	enum Mode
	{
		MODE_WIDTH,
		MODE_HEIGHT,
		MODE_MISSLE,
		MODE_NUM,
	};

	virtual bool					init();
	virtual void					update(float dTime);
	virtual void					enter();
	virtual void					exit();
	virtual void					dead();

	virtual const AllStatus&		getInfo() const;

	void							move(Creature* target, double dTime, int idx);
	void							enterMove();
	void							exitMove();

	void							attack(Creature* target, double dTime, int idx);
	void							enterAttack();
	void							exitAttack();

	void							idleTransition(Creature* target, double dTime, int idx);
	void							moveTransition(Creature* target, double dTime, int idx);
	void							attackTransition(Creature* target, double dTime, int idx);
	//void							endModule(cocos2d::Ref ref);
	void							endModule(Ref* ref);
	virtual bool					onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void					onContactSeparate(cocos2d::PhysicsContact& contact);

	CREATE_FUNC(BossFirst);

private:
	bool						m_IsArrived = false;
	int							m_Mode;
	int							m_RotateNum;
	cocos2d::Sequence*			m_RotateModule;
	BossHead*					m_Head;
	AllStatus					m_Info;
};