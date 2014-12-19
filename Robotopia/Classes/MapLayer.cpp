#include "pch.h"
#include "MapLayer.h"
#include "DataManager.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "MinimapLayer.h"
#include "MapWindowLayer.h"

#define ROOMRECT_SIZE 64

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

//	initMarginSet();
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;
//	m_StageData = GET_DATA_MANAGER()->getStageData(GET_STAGE_MANAGER()->getStageNum());
	m_StageData = GET_DATA_MANAGER()->getStageData(0);

	m_Minimap = MinimapLayer::create();
	m_MapWindow = MapWindowLayer::create();

	this->addChild(m_Minimap);
	this->addChild(m_MapWindow);
	return true;
}

void MapLayer::update(float dTime)
{
}

void MapLayer::setUpMap()
{
	m_StageData = GET_DATA_MANAGER()->getStageData(GET_STAGE_MANAGER()->getStageNum());
	m_MapWindow->setMapSprite(drawMap(RESOLUTION));
	//m_Minimap->setMapSprite()
}

void MapLayer::showMapWin()
{
	m_MapWindow->showMapWin();
}

void MapLayer::hideMapWin()
{
	m_MapWindow->hideMapWin();
}

cocos2d::Node* MapLayer::drawMap(float drawScale)
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
					cocos2d::Sprite* roomRect = GET_RESOURCE_MANAGER()->createSprite(ST_MAP_DEFAULT);
					SpriteType wall = static_cast<SpriteType>(static_cast<int>(ST_MAP_WALL_00) + roomWallCheck(roomCnt, x, y, moduleX, moduleY));
					cocos2d::Sprite* roomWall = GET_RESOURCE_MANAGER()->createSprite(wall);
					roomRect->setPosition(cocos2d::Point((posX + x) * ROOMRECT_SIZE * drawScale, (posY + y) * ROOMRECT_SIZE * drawScale));
					roomWall->setPosition(cocos2d::Point((posX + x) * ROOMRECT_SIZE * drawScale, (posY + y) * ROOMRECT_SIZE * drawScale));
					floorMap->addChild(roomRect);
					floorMap->addChild(roomWall);
				}
			}
		}
	}
	return floorMap;
}

// cocos2d::DrawNode* MapLayer::drawMap(int margin, int drawScale)
// {
// 	auto floorMap = cocos2d::DrawNode::create();
// 	int idxi = m_StageData.m_Height / m_ModuleSize;
// 	int idxj = m_StageData.m_Width / m_ModuleSize;
// 	initMarginSet();
// 	floorMap = makeRoomRect(idxi * drawScale, idxj * drawScale, margin, m_MarginSet, cocos2d::Color4B(0, 0, 125, 0)); //Data
// 
// 	for (int roomCnt = 0; roomCnt < (int)m_StageData.m_Rooms.size(); ++roomCnt)
// 	{
// 		//Data Converting to index
// 		int posX = m_StageData.m_Rooms[roomCnt].m_X / m_ModuleSize;
// 		int posY = m_StageData.m_Rooms[roomCnt].m_Y / m_ModuleSize;
// 		int moduleX = m_StageData.m_Rooms[roomCnt].m_Width / m_ModuleSize;
// 		int moduleY = m_StageData.m_Rooms[roomCnt].m_Height / m_ModuleSize;
// 
// 		for (int j = 0; j < moduleY; ++j)
// 		{
// 			for (int i = 0; i < moduleX; ++i)
// 			{
// 				if (getModulePlaceData(roomCnt, i, j) == 1)
// 				{
// 					roomWallCheck(roomCnt, i, j, moduleX, moduleY);
// 					cocos2d::DrawNode* roomRect = makeRoomRect(drawScale, drawScale, margin, m_MarginSet, cocos2d::Color4B(117, 198, 185, 120)); //Data
// 					roomRect->setPosition(cocos2d::Point((posX + i) * drawScale, (posY + j) * drawScale));
// 					floorMap->addChild(roomRect);
// 				}
// 			}
// 		}
// 	}
// 	return floorMap;
// }

void MapLayer::initMarginSet()
{
	m_MarginSet.m_Up = false;
	m_MarginSet.m_Down = false;
	m_MarginSet.m_Left = false;
	m_MarginSet.m_Right = false;
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
//		m_MarginSet.m_Up = true;
	}
	if (x == maxX - 1 || getModulePlaceData(roomCnt, x + 1, y) == 0)
	{
		dirValue |= DIR_RIGHT;
//		m_MarginSet.m_Right = true;
	}
	if (y == 0 || getModulePlaceData(roomCnt, x, y - 1) == 0)
	{
		dirValue |= DIR_DOWN;
//		m_MarginSet.m_Down = true;
	}
	if (x == 0 || getModulePlaceData(roomCnt, x - 1, y) == 0)
	{
		dirValue |= DIR_LEFT;
//		m_MarginSet.m_Left = true;
	}
	return dirValue;
}

cocos2d::DrawNode* MapLayer::makeRoomRect(int width, int height, int marginSize, MarginSet margin, cocos2d::Color4B fillColor)
{
	cocos2d::DrawNode* roomRect = cocos2d::DrawNode::create();

	cocos2d::Vec2 vertices1 = cocos2d::Vec2(0, 0);
	cocos2d::Vec2 vertices2 = cocos2d::Vec2(0, height);
	cocos2d::Vec2 vertices3 = cocos2d::Vec2(width, height);
	cocos2d::Vec2 vertices4 = cocos2d::Vec2(width, 0);
	if (margin.m_Up)
	{
		vertices2.y -= marginSize;
		vertices3.y -= marginSize;
	}
	if (margin.m_Left)
	{
		vertices1.x += marginSize;
		vertices2.x += marginSize;
	}
	if (margin.m_Down)
	{
		vertices1.y += marginSize;
		vertices4.y += marginSize;
	}
	if (margin.m_Right)
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

