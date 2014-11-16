#include "pch.h"
#include "AICommand.h"

bool AICommand::init()
{
	if (!CommandComponent::init())
	{
		return false;
	}

	return true;
}

void AICommand::update(float dTime)
{
}

void AICommand::enter()
{
}

void AICommand::exit()
{
}

