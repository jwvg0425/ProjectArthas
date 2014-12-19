#include "pch.h"
#include "MapLayer.h"
#include "DataManager.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "MinimapLayer.h"
#include "MapWindowLayer.h"

MapLayer::MapLayer()
{
}

MapLayer::~MapLayer()
{
}

bool MapLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	//init
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;
	m_Minimap = MinimapLayer::create();
	m_MapWindow = MapWindowLayer::create();

	this->addChild(m_Minimap);
	this->addChild(m_MapWindow);
	return true;
}

void MapLayer::update(float dTime)
{
	m_Minimap->update(dTime);
}

void MapLayer::setUpMap(int stageNum, int roomNum)
{
	m_StageData = GET_DATA_MANAGER()->getStageData(stageNum);
	m_MapWindow->setMapSprite(drawMap(RESOLUTION, roomNum), m_MapWindow->fitToWin(m_StageData));
	m_Minimap->setMapSprite(drawMap(RESOLUTION, roomNum));
}

void MapLayer::showMapWin()
{
	m_MapWindow->showMapWin();
}

void MapLayer::hideMapWin()
{
	m_MapWindow->hideMapWin();
}

cocos2d::Node* MapLayer::drawMap(float drawScale, int currentRoom)
{
	cocos2d::Node* floorMap = cocos2d::Node::create();
	int xIdx = m_StageData.m_Height / m_ModuleSize;
	int yIdx = m_StageData.m_Width / m_ModuleSize;
	floorMap->setContentSize(cocos2d::Size(xIdx * ROOMRECT_SIZE, yIdx * ROOMRECT_SIZE));
	for (int roomCnt = 0; roomCnt < static_cast<int>(m_StageData.m_Rooms.size()); ++roomCnt)
	{
		int posX = m_StageData.m_Rooms[roomCnt].m_X / m_ModuleSize;
		int posY = m_StageData.m_Rooms[roomCnt].m_Y / m_ModuleSize;
		int moduleX = m_StageData.m_Rooms[roomCnt].m_Width / m_ModuleSize;
		int moduleY = m_StageData.m_Rooms[roomCnt].m_Height / m_ModuleSize;

		for (int y = 0; y < moduleY; ++y)
		{
			for (int x = 0; x < moduleX; ++x)
			{
				if (getModulePlaceData(roomCnt, x, y) == 1)
				{
					cocos2d::Sprite* roomRect = nullptr;
					if (roomCnt == currentRoom)
					{
						roomRect = GET_RESOURCE_MANAGER()->createSprite(ST_MAP_IN);
					}
					else
					{
						roomRect = GET_RESOURCE_MANAGER()->createSprite(ST_MAP_DEFAULT);
					}
					SpriteType wall = static_cast<SpriteType>(static_cast<int>(ST_MAP_WALL_00) + roomWallCheck(roomCnt, x, y, moduleX, moduleY));
					cocos2d::Sprite* roomWall = GET_RESOURCE_MANAGER()->createSprite(wall);
					roomRect->setPosition(cocos2d::Point((posX + x) * ROOMRECT_SIZE, (posY + y) * ROOMRECT_SIZE));
					roomWall->setPosition(cocos2d::Point((posX + x) * ROOMRECT_SIZE, (posY + y) * ROOMRECT_SIZE));
					floorMap->addChild(roomRect);
					floorMap->addChild(roomWall);
				}
			}
		}
	}
	return floorMap;
}

int MapLayer::getModulePlaceData(int roomCnt, int x, int y)
{
	int moduleX = m_StageData.m_Rooms[roomCnt].m_Width / m_ModuleSize;
	return m_StageData.m_Rooms[roomCnt].m_ModulePlaceData[moduleX * y + x];
}

int MapLayer::roomWallCheck(int roomCnt, int x, int y, int maxX, int maxY)
{
	int dirValue = 0;
	if (y == maxY - 1 || getModulePlaceData(roomCnt, x, y + 1) == 0)
	{
		dirValue |= DIR_UP;
	}
	if (x == maxX - 1 || getModulePlaceData(roomCnt, x + 1, y) == 0)
	{
		dirValue |= DIR_RIGHT;
	}
	if (y == 0 || getModulePlaceData(roomCnt, x, y - 1) == 0)
	{
		dirValue |= DIR_DOWN;
	}
	if (x == 0 || getModulePlaceData(roomCnt, x - 1, y) == 0)
	{
		dirValue |= DIR_LEFT;
	}
	return dirValue;
}
