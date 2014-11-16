#include "pch.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "InputManager.h"
#include "KeyboardCommand.h"
#include "ObserverComponent.h"
#include "KeyboardTrigger.h"
#include "CommandTrigger.h"

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
		if (GET_INPUT_MANAGER()->getKeyState(KC_DOWN) == KS_HOLD &&
			GET_INPUT_MANAGER()->getKeyState(KC_JUMP) == KS_PRESS)
		{
			auto keyTrigger = (KeyboardTrigger*)GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();

			keyTrigger->initKeyCode(KC_DOWN_JUMP, KS_PRESS);
			observer->addTrigger(keyTrigger);
		}

		for(int keyCode = KC_NONE + 1; keyCode < MAX_KEY_NUM; ++keyCode)
		{
			auto keyState = GET_INPUT_MANAGER()->getKeyState((KeyCode) keyCode);
			auto keyTrigger = (KeyboardTrigger*) GET_TRIGGER_MANAGER()->createTrigger<KeyboardTrigger>();
			if(keyState != KS_NONE)
			{
				keyTrigger->initKeyCode((KeyCode)keyCode, keyState);
				observer->addTrigger(keyTrigger);
			}

			/*
			//커맨드 방식
			auto commandTrigger = (CommandTrigger*) GET_TRIGGER_MANAGER()->createTrigger<CommandTrigger>();
			CommandType command = keyToCommand((KeyCode)keyCode, keyState);
			if(command != CMD_NONE)
			{
				commandTrigger->initCmdTrigger(command);
				observer->addTrigger((Trigger*) commandTrigger);
			}
			*/
		}
	}
}

void Arthas::KeyboardCommand::enter()
{

}

void Arthas::KeyboardCommand::exit()
{

}

Arthas::CommandType Arthas::KeyboardCommand::keyToCommand(KeyCode keyCode, KeyState keyState)
{
	CommandType command = CMD_NONE;
	switch(keyCode)
	{
		case Arthas::KC_RIGHT:
			if(keyState == KS_NONE)
				break;
			else if(keyState & KS_HOLD)
				command = CMD_RIGHT_MOVING;
			else if(keyState & KS_PRESS)
				command = CMD_RIGHT_START;
			else if(keyState & KS_RELEASE)
				command = CMD_RIGHT_END;
			break;
		case Arthas::KC_LEFT:
			if(keyState == KS_NONE)
				break;
			else if(keyState & (KS_HOLD | KS_PRESS))
				command = CMD_LEFT_MOVING;
			else if(keyState & KS_PRESS)
				command = CMD_LEFT_START;
			else if(keyState & KS_RELEASE)
				command = CMD_LEFT_END;
			break;
		case Arthas::KC_ATTACK:
			if(keyState == KS_NONE)
				break;
			else if(keyState & (KS_HOLD | KS_PRESS))
				command = CMD_ATTACK;
			break;
		case Arthas::KC_JUMP:
			if(keyState == KS_NONE)
				break;
			else if(keyState & (KS_HOLD | KS_PRESS))
				command = CMD_JUMP;
			break;
		default:
			break;
	}
	return command;
}

