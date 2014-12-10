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
	virtual bool					init();
	virtual void					update(float dTime);
	virtual void					updateFSM(float dTime);
	virtual void					updateRender(float dTime);
	virtual void					enter();
	virtual void					exit();


private:

};