/************************************************************************/
/*
	CLASS			: FSMComponent
	Author			: 남현욱
	역할				: 모든 FSM 컴포넌트들의 최상위 클래스.
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "Component.h"

BEGIN_NS_AT

class FSMComponent : public Component
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	ABSTRACT void				enter() = 0;
	ABSTRACT void				exit() = 0;

	FSMComponent();
	~FSMComponent();
private:
	Component* m_NowState;
};

END_NS_AT