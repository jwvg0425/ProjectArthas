#include "pch.h"
#include "CharWindowLayer.h"
#include "Player.h"
#include "ResourceManager.h"

Arthas::CharWindowLayer::CharWindowLayer()
{
}

Arthas::CharWindowLayer::~CharWindowLayer()
{
}

bool Arthas::CharWindowLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_CharWinFrame = GET_RESOURCE_MANAGER()->createSprite(ST_CHARWIN_FRAME);
	setUIProperties(m_CharWinFrame, cocos2d::Point(1, 0), cocos2d::Point(m_WinWidth + (412 * RESOLUTION), 70 * RESOLUTION), 0.75, true, 10);
	m_CharWinTrigger = GET_RESOURCE_MANAGER()->createSprite(ST_CHARWIN_TRIGGER);
	setUIProperties(m_CharWinTrigger, cocos2d::Point(0.5, 0.5), cocos2d::Point(20, 275), 0.75f, true, 11);
	m_CharWinFrame->addChild(m_CharWinTrigger);

	this->addChild(m_CharWinFrame);
	return true;
}

void Arthas::CharWindowLayer::update(float dTime)
{

}

void Arthas::CharWindowLayer::showCharWin()
{
	if (m_CharWinFrame->getNumberOfRunningActions() == 0)
	{
		cocos2d::ActionInterval* action0 = cocos2d::MoveTo::create(0.5f, cocos2d::Point(m_WinWidth + (50 * RESOLUTION), 70 * RESOLUTION));
		cocos2d::Action* action1 = cocos2d::EaseBackIn::create(action0);
		m_CharWinFrame->runAction(action1);

		cocos2d::Action* action2 = cocos2d::RotateBy::create(0.5f, 180);
		m_CharWinTrigger->runAction(action2);
	}
}

void Arthas::CharWindowLayer::hideCharWin()
{
	if (m_CharWinFrame->getNumberOfRunningActions() == 0)
	{
		cocos2d::ActionInterval* action0 = cocos2d::MoveTo::create(0.7f, cocos2d::Point(m_WinWidth + (412 * RESOLUTION), 70 * RESOLUTION));
		cocos2d::Action* action1 = cocos2d::EaseBounceOut::create(action0);
		m_CharWinFrame->runAction(action1);

		cocos2d::Action* action2 = cocos2d::RotateBy::create(0.5f, -180);
		m_CharWinTrigger->runAction(action2);
	}
}

