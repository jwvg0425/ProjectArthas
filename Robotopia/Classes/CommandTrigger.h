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



class BaseComponent;

class CommandTrigger : public Trigger
{
public:
	void			initCmdTrigger(CommandType commandType, void* argv = NULL);
	virtual bool	operator ==( const Trigger& trigger );
	CommandType		getCmdType();

	CommandTrigger();
	~CommandTrigger();

public:
	CommandType		m_CommandType;
	void*			m_Argv;
};

