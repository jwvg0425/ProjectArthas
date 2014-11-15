#include "pch.h"
#include "MapWindowLayer.h"
#include "Player.h"
#include "DataManager.h"
#include "ResourceManager.h"

#define ROOM_SCALE 35
#define ROOM_MARGIN 4
#define RESOLUTION 0.75f

bool Arthas::MapWindowLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_StageData = GET_DATA_MANAGER()->getStageData(0);
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;
	m_MapWinFrame = GET_RESOURCE_MANAGER()->createSprite(ST_MAPWIN_FRAME);
	setUIProperties(m_MapWinFrame, cocos2d::Point(0, 0), cocos2d::Point(-905 * RESOLUTION, 70 * RESOLUTION), 0.75, true, 10);
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
		m_MapPaper = drawMap(ROOM_MARGIN, ROOM_SCALE);
		m_MapPaper->setScale(FitToWin());
		m_MapPaper->setAnchorPoint(cocos2d::Point(0, 0));
		m_MapPaper->setPosition(cocos2d::Point(200 * RESOLUTION, 50 * RESOLUTION));
		m_MapWinFrame->addChild(m_MapPaper);

		auto action0 = cocos2d::MoveTo::create(0.5f, cocos2d::Point(-50 * RESOLUTION, 70 * RESOLUTION));
		auto action1 = cocos2d::EaseBackIn::create(action0);
		m_MapWinFrame->runAction(action1);
	}
}

void Arthas::MapWindowLayer::hideMapWin()
{
	if (m_MapWinFrame->getNumberOfRunningActions() == 0)
	{
		auto action0 = cocos2d::MoveTo::create(0.7f, cocos2d::Point(-905 * RESOLUTION, 70 * RESOLUTION));
		auto action1 = cocos2d::EaseBounceOut::create(action0);
		m_MapWinFrame->runAction(action1);

		m_MapWinFrame->removeChild(m_MapPaper, true);
	}
}
float Arthas::MapWindowLayer::FitToWin()
{
	float sizeX = 600.0f / ((m_StageData.height / m_ModuleSize) * ROOM_SCALE);
	float sizeY = 400.0f / ((m_StageData.width / m_ModuleSize) * ROOM_SCALE);
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



