#include "pch.h"
#include "GameMenuLayer.h"
#include "ResourceManager.h"

GameMenuLayer::GameMenuLayer()
{

}

GameMenuLayer::~GameMenuLayer()
{

}

bool GameMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_GameMenuBackGround = GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_BACKGROUND);
	m_GameMenuFrame = GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_FRAME);

	setUIProperties(m_GameMenuBackGround, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2), 0.75f, false, 50);
	setUIProperties(m_GameMenuFrame, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2), 0.75f, false, 51);

	this->addChild(m_GameMenuBackGround);
	this->addChild(m_GameMenuFrame);
	return true;
}

void GameMenuLayer::update(float dTime)
{

}

void GameMenuLayer::showGameMenu()
{
	m_GameMenuBackGround->setVisible(true);
	m_GameMenuFrame->setVisible(true);
}

void GameMenuLayer::hideGameMenu()
{
	m_GameMenuBackGround->setVisible(false);
	m_GameMenuFrame->setVisible(false);
}
