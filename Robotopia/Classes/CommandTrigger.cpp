#include "pch.h"
#include "CommandTrigger.h"

Arthas::CommandTrigger::CommandTrigger()
{
	m_Type = TT_COMMAND;
	m_CommandType = CMD_NONE;
	m_Argv = NULL;
}

void Arthas::CommandTrigger::initCmdTrigger(CommandType commandType, void* argv)
{
	m_CommandType = commandType;
	m_Argv = argv;
}

bool Arthas::CommandTrigger::operator==( const Trigger& trigger )
{
	if(!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	CommandTrigger& other = (CommandTrigger&) trigger;

	return ( m_CommandType == other.getCmdType() ) ? true : false;
}

Arthas::CommandType Arthas::CommandTrigger::getCmdType()
{
	return m_CommandType;
}

