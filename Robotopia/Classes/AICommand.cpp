#include "pch.h"
#include "AICommand.h"

bool Arthas::AICommand::init()
{
	if (!CommandComponent::init())
	{
		return false;
	}

	return true;
}

void Arthas::AICommand::update(float dTime)
{
}

void Arthas::AICommand::enter()
{
}

void Arthas::AICommand::exit()
{
}

