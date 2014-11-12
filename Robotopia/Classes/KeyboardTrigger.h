/************************************************************************/
/*
CLASS			: KeyboardTrigger
Author			: 남현욱
역할				: 특정한 키가 눌렸을 때 발생하는 트리거 클래스.
최종 수정일자	: 2014-10-31
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class Component;

class KeyboardTrigger : public Trigger
{
public:
	void			initKeyCode(KeyCode keyCode, int keyState);
	virtual bool	operator ==( const Trigger& trigger );

	KeyboardTrigger();
	~KeyboardTrigger();

public:
	KeyCode			m_KeyCode;
	int				m_KeyState;
};

END_NS_AT