#include "pch.h"
#include "GameMenuLayer.h"
#include "ResourceManager.h"
#include "ButtonLayer.h"

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

	m_Button1 = ButtonLayer::create();
	m_Button1->setButtonProperties(GAMEMENU_BUTTON, cocos2d::Point(m_GameMenuFrame->getBoundingBox().getMinX(), m_GameMenuFrame->getBoundingBox().getMinY()), cocos2d::Point(m_GameMenuFrame->getContentSize().width / 2, m_GameMenuFrame->getContentSize().height / 2), "abc", 1);
	m_Button2 = ButtonLayer::create();
	m_Button2->setButtonProperties(GAMEMENU_BUTTON, cocos2d::Point(m_GameMenuFrame->getBoundingBox().getMinX(), m_GameMenuFrame->getBoundingBox().getMinY()), cocos2d::Point(m_GameMenuFrame->getContentSize().width / 2, m_GameMenuFrame->getContentSize().height / 2 - 55), "abc", 1);

	//add Children
	m_GameMenuFrame->addChild(m_Button1);
	m_GameMenuFrame->addChild(m_Button2);
	this->addChild(m_GameMenuBackGround);
	this->addChild(m_GameMenuFrame);
	return true;
}

void GameMenuLayer::update(float dTime)
{
	m_Button1->update(dTime);
	m_Button2->update(dTime);

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
