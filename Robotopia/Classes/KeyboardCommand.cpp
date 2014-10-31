#include "GameManager.h"
#include "TriggerManager.h"
#include "InputManager.h"
#include "KeyboardCommand.h"
#include "ObserverComponent.h"
#include "KeyboardTrigger.h"

#define MAX_KEY_CODE 128

bool Arthas::KeyboardCommand::init()
{
	if(!CommandComponent::init())
	{
		return false;
	}
	return true;
}

void Arthas::KeyboardCommand::update( float dTime )
{
	auto observer = getObserverComponent();
	if(observer != nullptr)
	{
		for(int keyCode = KC_NONE + 1; keyCode < KC_END; ++keyCode)
		{
			auto keyState = GET_INPUT_MANAGER()->getKeyState( (KeyCode) keyCode );
			if(keyState != KS_NONE)
			{
				auto keyTrigger = (KeyboardTrigger*) GET_TRIGGER_MANAGER()->createTrigger( TT_KEYBOARD );
				keyTrigger->initKeyCode((KeyCode)keyCode, keyState);
				observer->addTrigger( (Trigger*)keyTrigger );
			}
		}
	}
}

void Arthas::KeyboardCommand::enter()
{

}

void Arthas::KeyboardCommand::exit()
{

}

