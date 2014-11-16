#include "pch.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "InputManager.h"
#include "MouseCommand.h"
#include "ObserverComponent.h"
#include "MouseTrigger.h"

bool MouseCommand::init()
{
	if (!CommandComponent::init())
	{
		return false;
	}
	return true;
}

void MouseCommand::update(float dTime)
{
	auto observer = getObserverComponent();
	if (observer != nullptr)
	{
		auto mouseInfo = GET_INPUT_MANAGER()->getMouseInfo();
		if (mouseInfo.mouseState != MS_NONE)
		{
//			auto mouseTrigger = (MouseTrigger*)GET_TRIGGER_MANAGER()->createTrigger<MouseTrigger>();
//			keyTrigger->initKeyCode((KeyCode)keyCode, keyState);
//			observer->addTrigger((Trigger*)mouseTrigger);
			//resetMouseInfo 호출일 필요할 수 있음
		}
		if (mouseInfo.doubleClick)
		{
			//더블클릭에서 해야할 일들을 처리해야하는데 어떻게 할지 고민 중 다른 곳으로 옮길 수도 있음
			//resetMouseInfo 호출이 필요할 수 있음
		}
	}
}

void MouseCommand::enter()
{

}

void MouseCommand::exit()
{

}
