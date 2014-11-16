/************************************************************************/
/*
CLASS			: AttackState
Author			: 김성연
역할				: 공격 상태에 해당하는 클래스.
최종 수정일자	: 2014-11-07
최종 수정자		:
최종 수정사유	:
Comment			: 얘는 부모클래스고 이 얘를 상속받는 자식 클래스에서 melee라든가
				  원거리라든가 만들어야됨
*/
/************************************************************************/
#pragma once
#include "StateComponent.h"
#include "cocos2d.h"



class AttackState : public StateComponent
{
public:
	OVERRIDE bool	init();
	OVERRIDE void	enter();
	OVERRIDE void	exit();
	OVERRIDE void	update(float dTime);

	void			setAttribute(BaseComponent* ref, float preDelay, float afterDelay, 
								 ComponentType missleType, int attackPoint);
	CREATE_FUNC(AttackState);

private:
	ComponentType	m_MissileType;
	timeval			m_InitTime;
	float			m_PreDelay;
	float			m_AfterDelay;
	int				m_AttackPoint;
	bool			m_IsAttacked;
};

