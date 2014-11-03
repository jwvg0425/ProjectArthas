#include "GameManager.h"
#include "TriggerManager.h"
#include "InputManager.h"
#include "MouseCommand.h"
#include "ObserverComponent.h"
#include "MouseTrigger.h"

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
//			auto mouseTrigger = (MouseTrigger*)GET_TRIGGER_MANAGER()->createTrigger<MouseTrigger>();
//			keyTrigger->initKeyCode((KeyCode)keyCode, keyState);
//			observer->addTrigger((Trigger*)mouseTrigger);
		}
	}
}

void Arthas::MouseCommand::enter()
{

}

void Arthas::MouseCommand::exit()
{

}
