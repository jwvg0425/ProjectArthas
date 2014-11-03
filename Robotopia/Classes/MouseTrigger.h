/************************************************************************/
/*
CLASS			: MouseTrigger
Author			: 우재우
역할			: 특정한 마우스 움직임에 맞게 발생하는 트리거 클래스.
최종 수정일자	: 2014-11-04
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class Component;

class MouseTrigger : public Trigger
{
public:
	//void			initKeyCode(KeyCode keyCode, int keyState);
	//virtual bool	operator ==(Trigger& trigger);

	MouseTrigger();
	~MouseTrigger();

public:
// 	KeyCode			m_KeyCode;
// 	int				m_KeyState;
};

END_NS_AT