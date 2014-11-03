#include "GameManager.h"
#include "TriggerManager.h"
#include "InputManager.h"
#include "MouseCommand.h"
#include "ObserverComponent.h"
#include "KeyboardTrigger.h"

bool Arthas::MouseCommand::init()
{
	if (!CommandComponent::init())
	{
		return false;
	}
	return true;
}

void Arthas::MouseCommand::update(float dTime)
{
	auto observer = getObserverComponent();
	if (observer != nullptr)
	{
		auto mouseState = GET_INPUT_MANAGER()->getMouseInfo();
		if (mouseState.mouseState != MS_NONE)
		{

		}
	}
}

void Arthas::MouseCommand::enter()
{

}

void Arthas::MouseCommand::exit()
{

}
