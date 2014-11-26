	/************************************************************************/
/*
CLASS			: Player
Author			: 김연우
역할				: Player class
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			: Player 동작 정의.
*/
/************************************************************************/
#pragma once
#include "Creature.h"
#include "Util.h"


class CommonInfo;
class Player : public Creature
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_MOVE,
		STAT_JUMP,
		STAT_JUMP_DOWN,
		STAT_FLY,
		STAT_NUM,
	};

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC( Player );

	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);

	//FSM
	static void					move(Creature* target, double dTime, int idx);
	static void					jump(Creature* target, double dTime, int idx);
	static void					fly(Creature* target, double dTime, int idx);

	static void					enterMove(Creature* target, double dTime, Direction dir);
	static void					exitMove(Creature* target, double dTime);

	static void					enterJump(Creature* target, double dTime, bool isFall);
	static void					enterDownJump(Creature* target, double dTime);

	static void					idleTransition(Creature* target, double dTime, int idx);
	static void					idleTransitionInEagle(Creature* target, double dTime, int idx);
	static void					moveTransition(Creature* target, double dTime, int idx);
	static void					jumpTransition(Creature* target, double dTime, int idx);
	static void					downJumpTransition(Creature* target, double dTime, int idx);
	static void					flyTransition(Creature* target, double dTime, int idx);

	//get,set 함수
	const PlayerInfo&			getInfo() const;
	void						setDirection(Direction dir);

protected:
	PlayerInfo						m_Info;
	int								m_FSMNum;
};

