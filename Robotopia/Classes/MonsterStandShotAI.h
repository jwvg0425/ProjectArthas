/************************************************************************/
/*
CLASS			: MonsterStandShotAI
Author			: 김성연
역할				: 그림은 언제바꿀지 공격은 언제할지 결정하는 AI
최종 수정일자		: 2014-11-16
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "AICommand.h"

BEGIN_NS_AT

class Component;
class MonsterStandShotAI : public AICommand
{
public:

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	
	void						initAI(Component* ref, float coolTime = 5, int attackNum = 2);

	CREATE_FUNC(MonsterStandShotAI);

private:
	Component*		m_Ref;
	float			m_CoolTime;
	int				m_AttackNum;
	bool			m_IsAttackState;
};

END_NS_AT