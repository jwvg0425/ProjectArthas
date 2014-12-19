#include "pch.h"
#include "MapWindowLayer.h"
#include "Player.h"
#include "DataManager.h"
#include "ResourceManager.h"

bool MapWindowLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;
	m_MapWinFrame = GET_RESOURCE_MANAGER()->createSprite(ST_MAPWIN_FRAME);
	setUIProperties(m_MapWinFrame, cocos2d::Point(0, 0), cocos2d::Point(-902 * RESOLUTION, 70 * RESOLUTION), RESOLUTION, true, 10);
	m_MapWinTrigger = GET_RESOURCE_MANAGER()->createSprite(ST_MAPWIN_TRIGGER);
	setUIProperties(m_MapWinTrigger, cocos2d::Point(0.5, 0.5), cocos2d::Point(915, 275), RESOLUTION, true, 10);
	m_MapWinTrigger->setRotation(180);
	m_MapWinFrame->addChild(m_MapWinTrigger);
	this->addChild(m_MapWinFrame);
	return true;
}

void MapWindowLayer::update(float dTime)
{
}

void MapWindowLayer::showMapWin()
{
	if (m_MapWinFrame->getNumberOfRunningActions() == 0 && m_MapWinTrigger->getNumberOfRunningActions() == 0)
	{
		cocos2d::ActionInterval* action0 = cocos2d::MoveTo::create(0.5f, cocos2d::Point(-52 * RESOLUTION, 70 * RESOLUTION));
		cocos2d::Action* action1 = cocos2d::EaseBackIn::create(action0);
		m_MapWinFrame->runAction(action1);

		cocos2d::Action* action2 = cocos2d::RotateBy::create(0.5f, -180);
		m_MapWinTrigger->runAction(action2);
	}
}

void MapWindowLayer::hideMapWin()
{
	if (m_MapWinFrame->getNumberOfRunningActions() == 0 && m_MapWinTrigger->getNumberOfRunningActions() == 0)
	{
		cocos2d::ActionInterval* action0 = cocos2d::MoveTo::create(0.7f, cocos2d::Point(-902 * RESOLUTION, 70 * RESOLUTION));
		cocos2d::Action* action1 = cocos2d::EaseBounceOut::create(action0);
		m_MapWinFrame->runAction(action1);

		cocos2d::Action* action2 = cocos2d::RotateBy::create(0.5f, 180);
		m_MapWinTrigger->runAction(action2);
	}
}
float MapWindowLayer::fitToWin(StageData stageData)
{
	float sizeX = 600.0f * RESOLUTION / ((stageData.m_Height / m_ModuleSize) * ROOMRECT_SIZE);
	float sizeY = 400.0f * RESOLUTION / ((stageData.m_Width / m_ModuleSize) * ROOMRECT_SIZE);
	float fitScale = 0.0f;
	if (sizeX >= 1.0f && sizeY >= 1.0f)
	{
		fitScale = 1.0f;
	}
	else
	{
		fitScale = sizeX <= sizeY ? sizeX : sizeY;
	}
	return fitScale;
}

MapWindowLayer::MapWindowLayer()
{
}

MapWindowLayer::~MapWindowLayer()
{
}

void MapWindowLayer::setMapSprite(cocos2d::Node* mapSprite, float fitScale)
{
	if (m_MapSprite != nullptr)
	{
		m_MapWinFrame->removeChild(m_MapSprite, true);
	}
	m_MapSprite = mapSprite;
	m_MapSprite->setAnchorPoint(cocos2d::Point(0.5, 0.5));
	m_MapSprite->setPosition(cocos2d::Point(550 * RESOLUTION, 250 * RESOLUTION));
	m_MapSprite->setScale(fitScale);
	m_MapWinFrame->addChild(m_MapSprite);
}



