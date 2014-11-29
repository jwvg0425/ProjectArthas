#include "pch.h"
#include "StageManager.h"
#include "GameSceneUILayer.h"
#include "HPLayer.h"
#include "GearLayer.h"
#include "SteamLayer.h"
#include "MinimapLayer.h"
#include "InputManager.h"
#include "GameMenuLayer.h"
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
	m_HPLayer = HPLayer::create();
	m_MapLayer = MapLayer::create();
	m_GearLayer = GearLayer::create();
	m_SteamBarLayer = SteamLayer::create();
	m_GameMenuLayer = GameMenuLayer::create();
	m_CharWInLayer = CharWindowLayer::create();
	
	m_MenuWindowOn = false;
	m_MapWindowOn = false;
	m_CharWindowOn = false;

	m_MapWinRect.setRect(0 * RESOLUTION, 315 * RESOLUTION, 30 * RESOLUTION, 60 * RESOLUTION);
	m_CharWinRect.setRect(m_WinWidth - 30 * RESOLUTION, 315 * RESOLUTION, 30 * RESOLUTION, 60 * RESOLUTION);

	this->addChild(m_HPLayer);
	this->addChild(m_MapLayer);
	this->addChild(m_GearLayer);
	this->addChild(m_CharWInLayer);
	this->addChild(m_SteamBarLayer);
	this->addChild(m_GameMenuLayer);
	return true;
}

void GameSceneUILayer::update(float dTime)
{
	//Member update
	m_HPLayer->update(dTime);
	m_MapLayer->update(dTime);
	m_GearLayer->update(dTime);
	m_CharWInLayer->update(dTime);
	m_GameMenuLayer->update(dTime);
	m_SteamBarLayer->update(dTime);

	controlUIKeyboard();
	controlUIMouse();
}

void GameSceneUILayer::controlUIKeyboard()
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
			closeGameMenu();
		}
		else
		{
			if (m_MapWindowOn)
			{
				closeMapWindow();
			}
			else if (m_CharWindowOn)
			{
				closeCharWindow();
			}
			else
			{
				openGameMenu();
			}
		}
	}
	if (mapKey1 == KS_PRESS || mapKey2 == KS_PRESS)
	{
		if (!m_MenuWindowOn)
		{
			if (m_MapWindowOn)
			{
				closeMapWindow();
			}
			else
			{
				openMapWindow();
			}
		}
	}
	if (charKey == KS_PRESS)
	{
		if (!m_MenuWindowOn)
		{
			if (m_CharWindowOn)
			{
				closeCharWindow();
			}
			else
			{
				openCharWindow();
			}
		}
	}
}

void GameSceneUILayer::controlUIMouse()
{
	MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
	if (m_MapWinRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
	{
		if (!m_MapWindowOn)
		{
			openMapWindow();
		}
		else if (m_MapWindowOn)
		{
			closeMapWindow();
		}
	}
	if (m_CharWinRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
	{
		if (!m_CharWindowOn)
		{
			openCharWindow();
		}
		else if (m_CharWindowOn)
		{
			closeCharWindow();
		}
	}
	if (mouseInput.m_MouseState == MS_RIGHT_UP)
	{
		if (m_MenuWindowOn)
		{
			closeGameMenu();
		}
		else if (m_MapWindowOn)
		{
			closeMapWindow();
		}
		else if (m_CharWindowOn)
		{
			closeCharWindow();
		}
	}
}

void GameSceneUILayer::setMapUI(int stageNum, int roomNum)
{
	//stage 전환 or map shaking or room change
}

void GameSceneUILayer::openMapWindow()
{
	m_MapLayer->showMapWin();
	m_MapWindowOn = true;
	m_MapWinRect.setRect(850 * RESOLUTION, 315 * RESOLUTION, 30 * RESOLUTION, 60 * RESOLUTION);
	GET_INPUT_MANAGER()->resetMousePoints();
}

void GameSceneUILayer::closeMapWindow()
{
	m_MapLayer->hideMapWin();
	m_MapWindowOn = false;
	m_MapWinRect.setRect(0, 315 * RESOLUTION, 30 * RESOLUTION, 60 * RESOLUTION);
	GET_INPUT_MANAGER()->resetMousePoints();
}

void GameSceneUILayer::openCharWindow()
{
	m_CharWInLayer->showCharWin();
	m_CharWindowOn = true;
	m_CharWinRect.setRect(m_WinWidth - 390 * RESOLUTION, 315 * RESOLUTION, 30 * RESOLUTION, 60 * RESOLUTION);
	GET_INPUT_MANAGER()->resetMousePoints();
}

void GameSceneUILayer::closeCharWindow()
{
	m_CharWInLayer->hideCharWin();
	m_CharWindowOn = false;
	m_CharWinRect.setRect(m_WinWidth - 30 * RESOLUTION, 315 * RESOLUTION, 30 * RESOLUTION, 60 * RESOLUTION);
	GET_INPUT_MANAGER()->resetMousePoints();
}

void GameSceneUILayer::openGameMenu()
{
	m_GameMenuLayer->showGameMenu();
	m_MenuWindowOn = true;
	GET_INPUT_MANAGER()->resetMousePoints();
}

void GameSceneUILayer::closeGameMenu()
{
	m_GameMenuLayer->hideGameMenu();
	m_MenuWindowOn = false;
	GET_INPUT_MANAGER()->resetMousePoints();
}
