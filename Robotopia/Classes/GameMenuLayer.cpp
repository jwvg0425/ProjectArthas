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

	setUIProperties(m_GameMenuBackGround, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2), RESOLUTION, false, 50);
	setUIProperties(m_GameMenuFrame, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2), RESOLUTION, false, 51);

	m_Button1 = ButtonLayer::create();
	m_Button2 = ButtonLayer::create();
	m_Button1->setButtonProperties(BUTTON_GAMEMENU, cocos2d::Point(m_GameMenuFrame->getBoundingBox().getMinX(), m_GameMenuFrame->getBoundingBox().getMinY()),
									cocos2d::Point(m_GameMenuFrame->getContentSize().width / 2, m_GameMenuFrame->getContentSize().height / 2), "Resume", 35);
	m_Button2->setButtonProperties(BUTTON_GAMEMENU, cocos2d::Point(m_GameMenuFrame->getBoundingBox().getMinX(), m_GameMenuFrame->getBoundingBox().getMinY()),
									cocos2d::Point(m_GameMenuFrame->getContentSize().width / 2, m_GameMenuFrame->getContentSize().height / 2 - 55), "Save and Quit", 35);

	//temporary buttons
	m_Button1->setButtonFunc(std::bind(&GameMenuLayer::quitGame, this));
	m_Button2->setButtonFunc(std::bind(&GameMenuLayer::quitGame, this));
	hideGameMenu();
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

void GameMenuLayer::resumeGame()
{

}

void GameMenuLayer::quitGame()
{
	exit(0);
}

void GameMenuLayer::showGameMenu()
{
	m_GameMenuBackGround->setVisible(true);
	m_GameMenuFrame->setVisible(true);
	m_Button1->setButtonRect(cocos2d::Point(m_GameMenuFrame->getBoundingBox().getMinX(), m_GameMenuFrame->getBoundingBox().getMinY()));
	m_Button2->setButtonRect(cocos2d::Point(m_GameMenuFrame->getBoundingBox().getMinX(), m_GameMenuFrame->getBoundingBox().getMinY()));
}

void GameMenuLayer::hideGameMenu()
{
	m_GameMenuBackGround->setVisible(false);
	m_GameMenuFrame->setVisible(false);
	m_Button1->setButtonRect(cocos2d::Point(m_WinWidth, m_WinHeight));
	m_Button2->setButtonRect(cocos2d::Point(m_WinWidth, m_WinHeight));

}
