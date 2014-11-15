#include "pch.h"
#include "StageManager.h"
#include "Player.h"
#include "GameSceneUILayer.h"
#include "MinimapLayer.h"
#include "GearLayer.h"
#include "SteamLayer.h"
#include "InputManager.h"

bool Arthas::GameSceneUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	//Member Create & init
	m_Player = GET_STAGE_MANAGER()->getPlayer();
	m_Gear = Arthas::GearLayer::create();
	m_SteamBar = Arthas::SteamLayer::create();
	m_Map = Arthas::MapLayer::create();
	
	m_MenuWindowOn = false;
	m_MapWindowOn = false;
	m_CharWindowOn = false;

	this->addChild(m_Gear);
	this->addChild(m_SteamBar);
	this->addChild(m_Map);
	return true;
}

void Arthas::GameSceneUILayer::update(float dTime)
{
	//Member update
	m_Gear->update(dTime);
	m_SteamBar->update(dTime);
	m_Map->update(dTime);
	UIInputControl();
}

void Arthas::GameSceneUILayer::UIInputControl()
{
	KeyState mapKey1 = GET_INPUT_MANAGER()->getKeyState(KC_MAP);
	KeyState mapKey2 = GET_INPUT_MANAGER()->getKeyState(KC_TAB);
	KeyState escKey = GET_INPUT_MANAGER()->getKeyState(KC_ESC);
	KeyState charKey = GET_INPUT_MANAGER()->getKeyState(KC_CHARACTER);
	KeyState enterKey = GET_INPUT_MANAGER()->getKeyState(KC_RETURN);

	if (escKey == KS_PRESS)
	{
		if (m_MenuWindowOn)
		{
			//close menu
		}
		else
		{
			if (m_MapWindowOn)
			{
				m_Map->hideMapWin();
				m_MapWindowOn = false;
			}
			else if (m_CharWindowOn)
			{
				//close character window
			}
			else
			{
				//open menu
			}
		}
	}
	if (mapKey1 == KS_PRESS || mapKey2 == KS_PRESS)
	{
		if (!m_MenuWindowOn)
		{
			if (m_MapWindowOn)
			{
				m_Map->hideMapWin();
				m_MapWindowOn = false;
			}
			else
			{
				m_Map->showMapWin();
				m_MapWindowOn = true;
			}
		}
	}
	if (charKey == KS_PRESS)
	{
		if (!m_MenuWindowOn && !m_MapWindowOn)
		{
			if (m_CharWindowOn)
			{
				//close character Window
			}
			else
			{
				//open character Window
			}
		}
	}
}

