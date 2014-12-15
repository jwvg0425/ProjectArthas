/************************************************************************/
/*
CLASS			: Monster
Author			: 김성연
역할				: 몬스터전체의 추상클래스
최종 수정일자		: 2014-12-15
최종 수정자		: 김성연
최종 수정사유		: 몬스터의 다양한 공통 함수 지정하기 
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "Creature.h"


class Monster : public Creature
{
public:
	virtual bool			init();
	virtual void			update(float dTime);
	virtual void			enter();
	virtual void			exit();
	

protected:

};

