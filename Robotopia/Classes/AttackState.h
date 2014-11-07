/************************************************************************/
/*
CLASS			: AttackState
Author			: 김성연
역할				: 공격 상태에 해당하는 클래스.
최종 수정일자		: 2014-11-07
최종 수정자		:
최종 수정사유		:
Comment			: 얘는 부모클래스고 이 얘를 상속받는 자식 클래스에서 melee라든가
				  원거리라든가 만들어야됨
*/
/************************************************************************/
#pragma once
#include "StateComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class AttackState : public StateComponent
{
public:
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();
	OVERRIDE void update(float dTime);

	void		  setAttribute(Component* ref);

private:
	//미사일 타입 멤버변수가 있어야 됨
	//선딜레이 
	//후딜레이
	int m_PreDelay;
	int m_AfterDelay;
	
};



END_NS_AT