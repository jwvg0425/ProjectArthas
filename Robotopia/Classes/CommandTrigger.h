/************************************************************************/
/*
	CLASS			: CommandTrigger
	Author			: 김연우
	역할				: 커맨드를전gksms xmflrj달
	최종 수정일자	: 2014-11-14
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class Component;

class CommandTrigger : public Trigger
{
public:
	void			initKeyCode(CommandType commandType);
	virtual bool	operator ==( const Trigger& trigger );

	CommandTrigger();
	~CommandTrigger();

public:
	CommandType		m_CommandType;
};

END_NS_AT