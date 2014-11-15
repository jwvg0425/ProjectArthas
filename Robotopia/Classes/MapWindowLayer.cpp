#include "pch.h"
#include "MapWindowLayer.h"
#include "Player.h"
#include "DataManager.h"
#include "ResourceManager.h"

#define WIN_ROOM_SCALE 30
#define WIN_ROOM_MARGIN 5

bool Arthas::MapWindowLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_StageData = GET_DATA_MANAGER()->getStageData(0);
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;

	m_MapWinFrame = GET_RESOURCE_MANAGER()->createSprite(ST_MAPWIN_FRAME);
	setUIProperties(m_MapWinFrame, cocos2d::Point(0, 0), cocos2d::Point(-902 * RESOLUTION, 70 * RESOLUTION), 0.75, true, 10);
	m_MapWinTrigger = GET_RESOURCE_MANAGER()->createSprite(ST_MAPWIN_TRIGGER);
	setUIProperties(m_MapWinTrigger, cocos2d::Point(0.5, 0.5), cocos2d::Point(915, 275), 0.75, true, 10);
	m_MapWinTrigger->setRotation(180);
	m_MapWinFrame->addChild(m_MapWinTrigger);
	
	this->addChild(m_MapWinFrame);
	return true;
}

void Arthas::MapWindowLayer::update(float dTime)
{
}

void Arthas::MapWindowLayer::showMapWIn()
{
	if (m_MapWinFrame->getNumberOfRunningActions() == 0)
	{
		m_MapPaper = drawMap(WIN_ROOM_MARGIN, WIN_ROOM_SCALE);
		m_MapPaper->setScale(FitToWin());
		m_MapPaper->setAnchorPoint(cocos2d::Point(0, 0));
		m_MapPaper->setPosition(cocos2d::Point(200 * RESOLUTION, 50 * RESOLUTION));
		m_MapWinFrame->addChild(m_MapPaper);

		cocos2d::ActionInterval* action0 = cocos2d::MoveTo::create(0.5f, cocos2d::Point(-52 * RESOLUTION, 70 * RESOLUTION));
		cocos2d::Action* action1 = cocos2d::EaseBackIn::create(action0);
		m_MapWinFrame->runAction(action1);

		cocos2d::Action* action2 = cocos2d::RotateBy::create(0.5f, -180);
		m_MapWinTrigger->runAction(action2);
	}
}

void Arthas::MapWindowLayer::hideMapWin()
{
	if (m_MapWinFrame->getNumberOfRunningActions() == 0)
	{
		cocos2d::ActionInterval* action0 = cocos2d::MoveTo::create(0.7f, cocos2d::Point(-902 * RESOLUTION, 70 * RESOLUTION));
		cocos2d::Action* action1 = cocos2d::EaseBounceOut::create(action0);
		m_MapWinFrame->runAction(action1);

		cocos2d::Action* action2 = cocos2d::RotateBy::create(0.5f, 180);
		m_MapWinTrigger->runAction(action2);
		m_MapWinFrame->removeChild(m_MapPaper, true);
	}
}
float Arthas::MapWindowLayer::FitToWin()
{
	float sizeX = 600.0f / ((m_StageData.height / m_ModuleSize) * WIN_ROOM_SCALE);
	float sizeY = 400.0f / ((m_StageData.width / m_ModuleSize) * WIN_ROOM_SCALE);
	float fitScale;
	if (sizeX < 1 && sizeY < 1)
	{
		fitScale = sizeX >= sizeY ? sizeX : sizeY;
	}
	else
	{
		fitScale = sizeX < sizeY ? sizeX : sizeY;
	}
	return fitScale;
}

Arthas::MapWindowLayer::MapWindowLayer()
{
}

Arthas::MapWindowLayer::~MapWindowLayer()
{
}



