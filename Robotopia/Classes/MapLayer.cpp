#include "pch.h"
#include "MapLayer.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "MinimapLayer.h"
#include "MapWindowLayer.h"

bool Arthas::MapLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	return true;
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	//init
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	initMarginSet();
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;
	m_MapWindowOn = false;
	m_StageData = GET_DATA_MANAGER()->getStageData(0);

	m_Minimap = Arthas::MinimapLayer::create();
	m_MapWindow = Arthas::MapWindowLayer::create();

	this->addChild(m_Minimap);
	this->addChild(m_MapWindow);
	return true;
}

void Arthas::MapLayer::update(float dTime)
{
}

void Arthas::MapLayer::setUpMap()
{

}

void Arthas::MapLayer::showMapWin()
{
	m_MapWindow->showMapWIn();
}

void Arthas::MapLayer::hideMapWin()
{
	m_MapWindow->hideMapWin();
}

bool Arthas::MapLayer::getMapWinOn()
{
	return m_MapWindowOn;
}

cocos2d::DrawNode* Arthas::MapLayer::drawMap(int margin, int drawScale)
{
	auto floorMap = cocos2d::DrawNode::create();
	int idxj = m_StageData.height / m_ModuleSize;
	int idxi = m_StageData.width / m_ModuleSize;
	initMarginSet();
	floorMap = makeRoomRect(idxi * drawScale, idxj * drawScale, margin, m_MarginSet, cocos2d::Color4B(0, 0, 125, 0)); //Data

	for (int roomCnt = 0; roomCnt < (int)m_StageData.Rooms.size(); ++roomCnt)
	{
		//Data Converting to index
		int posX = m_StageData.Rooms[roomCnt].x / m_ModuleSize;
		int posY = m_StageData.Rooms[roomCnt].y / m_ModuleSize;
		int moduleX = m_StageData.Rooms[roomCnt].width / m_ModuleSize;
		int moduleY = m_StageData.Rooms[roomCnt].height / m_ModuleSize;

		for (int j = 0; j < moduleY; ++j)
		{
			for (int i = 0; i < moduleX; ++i)
			{
				if (getModulePlaceData(roomCnt, i, j) == 1)
				{
					roomBoundaryCheck(roomCnt, i, j, moduleX, moduleY);
					cocos2d::DrawNode* roomRect = makeRoomRect(drawScale, drawScale, margin, m_MarginSet, cocos2d::Color4B(117, 198, 185, 120)); //Data
					roomRect->setPosition(cocos2d::Point((posX + i) * drawScale, (posY + j) * drawScale));
					floorMap->addChild(roomRect);
				}
			}
		}
	}
	return floorMap;
}

void Arthas::MapLayer::initMarginSet()
{
	m_MarginSet.mUp = false;
	m_MarginSet.mDown = false;
	m_MarginSet.mLeft = false;
	m_MarginSet.mRight = false;
}

int Arthas::MapLayer::getModulePlaceData(int roomCnt, int x, int y)
{
	int moduleX = m_StageData.Rooms[roomCnt].width / m_ModuleSize;
	return m_StageData.Rooms[roomCnt].modulePlaceData[moduleX * y + x];
}

void Arthas::MapLayer::roomBoundaryCheck(int roomCnt, int x, int y, int maxX, int maxY)
{
	initMarginSet();
	if (x == 0 || getModulePlaceData(roomCnt, x - 1, y) == 0)
		m_MarginSet.mLeft = true;
	if (y == 0 || getModulePlaceData(roomCnt, x, y - 1) == 0)
		m_MarginSet.mDown = true;
	if (x == maxX - 1 || getModulePlaceData(roomCnt, x + 1, y) == 0)
		m_MarginSet.mRight = true;
	if (y == maxY - 1 || getModulePlaceData(roomCnt, x, y + 1) == 0)
		m_MarginSet.mUp = true;
}

cocos2d::DrawNode* Arthas::MapLayer::makeRoomRect(int width, int height, int marginSize, MarginSet margin, cocos2d::Color4B fillColor)
{
	cocos2d::DrawNode* roomRect = cocos2d::DrawNode::create();

	cocos2d::Vec2 vertices1 = cocos2d::Vec2(0, 0);
	cocos2d::Vec2 vertices2 = cocos2d::Vec2(0, height);
	cocos2d::Vec2 vertices3 = cocos2d::Vec2(width, height);
	cocos2d::Vec2 vertices4 = cocos2d::Vec2(width, 0);
	if (margin.mUp)
	{
		vertices2.y -= marginSize;
		vertices3.y -= marginSize;
	}
	if (margin.mLeft)
	{
		vertices1.x += marginSize;
		vertices2.x += marginSize;
	}
	if (margin.mDown)
	{
		vertices1.y += marginSize;
		vertices4.y += marginSize;
	}
	if (margin.mRight)
	{
		vertices3.x -= marginSize;
		vertices4.x -= marginSize;
	}
	cocos2d::Vec2 points[] =
	{
		vertices1,
		vertices2,
		vertices3,
		vertices4
	};
	roomRect->drawPolygon(points, 4, cocos2d::Color4F(fillColor), 0, cocos2d::Color4F(0.0f, 0.0f, 0.0f, 0));
	return roomRect;
}

Arthas::MapLayer::MapLayer()
{
}

Arthas::MapLayer::~MapLayer()
{
}