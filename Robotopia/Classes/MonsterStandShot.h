/************************************************************************/
/*
CLASS			: MonsterStandShot
Author			: 김성연
역할				: 서서 공격하는 몬스터 클래스
최종 수정일자		: 2014-11-22
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Thing.h"
#include "Util.h"

class MonsterStandShot : public Thing ///< 이것도 몬스터의 한 종류 아닌가? 그런데 네이밍이 동작 action을 상징하는 것 같다...
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_ATTACK,
		STAT_NUM,
	};

	struct MonsterStandShotInfo
	{
		float				coolTime;
		int					repeatAttackNum;
		Direction			dir;
		int					damage;
		int					maxHp;
		int					curHp;
		ComponentType		missileType;
		cocos2d::Size		size;
		float				attackDelay;
	};

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);
	OVERRIDE void			enter();
	OVERRIDE void			exit();

	CREATE_FUNC(MonsterStandShot);

	bool						onContactBegin(cocos2d::PhysicsContact& contact);
	void						onContactSeparate(cocos2d::PhysicsContact& contact);
	cocos2d::PhysicsBody*		getBody();

	//FSM
	static void				attack(Thing* target, double dTime, int idx);
	static void				enterAttack(Thing* target, double dTime, int idx);
	static void				exitAttack(Thing* target, double dTime, int idx);

	static void				idleTransition(Thing* target, double dTime, int idx);
	static void				attackTransition(Thing* target, double dTime, int idx);
	MonsterStandShotInfo&	getInfo();
	void					setInfo(float coolTime = 5, int repeatAttackNum = 2, Direction dir = DIR_RIGHT,
									int damage = 20, int maxHp = 100, int curHp = 100,
									ComponentType missileType = OT_MISSILE_PLAYER_LINEAR,
									cocos2d::Size size = cocos2d::Size(50, 50), float delay = 1.0f);

private:
	MonsterStandShotInfo		m_Info;
	int							m_CurAttackNum;
	float						m_AccTime;
	float						m_CurAttackDelay;
};