#include "pch.h"
#include "MinimapLayer.h"
#include "Player.h"
#include "StageManager.h"
#include "DataManager.h"

#define MAP_SCALE 20
#define ROOM_MARGIN 3

Arthas::MinimapLayer::MinimapLayer()
{
}

Arthas::MinimapLayer::~MinimapLayer()
{
}

bool Arthas::MinimapLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_MapWinOn = false;
	m_MapWin = cocos2d::Sprite::create("bg.png");
// 	auto test = cocos2d::Sprite::create("block.png");
// 	test->setPosition(cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2));
// 	test->setAnchorPoint(cocos2d::Point(0.5, 0.5));
// 	test->setScale(2.3f);
// 	this->addChild(test);

	m_MapWin->setPosition(cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2));
	m_MapWin->setAnchorPoint(cocos2d::Point(0.5, 0.5));
	this->addChild(m_MapWin);

	setUpMap();
	return true;
}

void Arthas::MinimapLayer::setUpMap()
{
	m_CurrentFloor = 0;
	m_StageData = GET_DATA_MANAGER()->getStageData(m_CurrentFloor);
	//m_Map = drawMap(MAP_SCALE);
}

void Arthas::MinimapLayer::update(float dTime)
{
	//m_Player = GET_STAGE_MANAGER()->getPlayer();
	if (m_MapWinOn)
	{
		drawMapWin();
	}
	drawMiniMap();
}

cocos2d::Sprite* Arthas::MinimapLayer::drawMap(int drawScale)
{
	auto floorMap = cocos2d::Sprite::create();

// 	int currentRoom = GET_STAGE_MANAGER()->getCurStageNum();
// 	int transmitterRoom = GET_STAGE_MANAGER()->getTransmitterStageNum();

	for (int j = 0; j < m_StageData.height; ++j)
	{
		for (int i = 0; i < m_StageData.width; ++i)
		{

		}
	}


	return floorMap;
}

void Arthas::MinimapLayer::drawMapWin()
{
	m_MapWin->addChild(m_Map);
}

void Arthas::MinimapLayer::drawMiniMap()
{
}

void Arthas::MinimapLayer::showMapWin()
{
	m_MapWin->setVisible(true);
	m_MapWinOn = true;
}

void Arthas::MinimapLayer::hideMapWin()
{
	m_MapWin->setVisible(false);
	m_MapWinOn = false;
}

bool Arthas::MinimapLayer::getMapWinOn()
{
	return m_MapWinOn;
}




