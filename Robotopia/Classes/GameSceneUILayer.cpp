#include "pch.h"
#include "StageManager.h"
#include "GameSceneUILayer.h"
#include "MinimapLayer.h"
#include "GearLayer.h"
#include "SteamLayer.h"
#include "InputManager.h"
#include "CharWindowLayer.h"

bool GameSceneUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	//Member Create & init
	m_GearLayer = GearLayer::create();
	m_SteamBarLayer = SteamLayer::create();
	m_MapLayer = MapLayer::create();
	m_CharWInLayer = CharWindowLayer::create();
	
	m_MenuWindowOn = false;
	m_MapWindowOn = false;
	m_CharWindowOn = false;

	this->addChild(m_GearLayer);
	this->addChild(m_SteamBarLayer);
	this->addChild(m_MapLayer);
	this->addChild(m_CharWInLayer);
	return true;
}

void GameSceneUILayer::update(float dTime)
{
	//Member update
	m_GearLayer->update(dTime);
	m_SteamBarLayer->update(dTime);
	m_MapLayer->update(dTime);
	m_CharWInLayer->update(dTime);
	UIInputControl();
}

void GameSceneUILayer::UIInputControl()
{
	KeyState mapKey1 = GET_INPUT_MANAGER()->getKeyState(KC_MAP);
	KeyState mapKey2 = GET_INPUT_MANAGER()->getKeyState(KC_TAB);
	KeyState escKey = GET_INPUT_MANAGER()->getKeyState(KC_ESC);
	KeyState charKey = GET_INPUT_MANAGER()->getKeyState(KC_CHARACTER);
	KeyState enterKey = GET_INPUT_MANAGER()->getKeyState(KC_RETURN);

	//위치에 문제 있음
	if (escKey == KS_PRESS)
	{
		if (m_MenuWindowOn)
		{
			//close menu
		}
		else
		{
			//여기를 수정할 것!!!
			if (m_MapWindowOn)
			{
				m_MapLayer->hideMapWin();
				m_MapWindowOn = false;
			}
			else if (m_CharWindowOn)
			{
				m_CharWInLayer->hideCharWin();
				m_CharWindowOn = false;
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
				m_MapLayer->hideMapWin();
				m_MapWindowOn = false;
			}
			else
			{
				m_MapLayer->showMapWin();
				m_MapWindowOn = true;
			}
		}
	}
	if (charKey == KS_PRESS)
	{
		if (!m_MenuWindowOn)
		{
			if (m_CharWindowOn)
			{
				m_CharWInLayer->hideCharWin();
				m_CharWindowOn = false;
			}
			else
			{
				m_CharWInLayer->showCharWin();
				m_CharWindowOn = true;
			}
		}
	}
}

void GameSceneUILayer::setMapUI(int stageNum, int roomNum)
{
	//stage 전환 or map shaking or room change
}

