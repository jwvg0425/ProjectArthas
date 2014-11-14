#include "pch.h"
#include "MinimapLayer.h"
#include "Player.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"

#define ROOM_SCALE 30
#define ROOM_MARGIN 2

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
	//init
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;
	initMarginSet();
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;

	//init Map Window
// 	m_MapWin = cocos2d::Sprite::create("Graphic/bg.png"); //R
// 	m_MapWin->setPosition(cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2));
// 	m_MapWin->setAnchorPoint(cocos2d::Point(0.5, 0.5));
//	this->addChild(m_MapWin);
	m_MapWinOn = false;

	m_MinimapFrame = cocos2d::Sprite::create("Graphic/circle2.png");
	setUIProperties(m_MinimapFrame, cocos2d::Point(0, 0), cocos2d::Point(m_WinWidth - 230, 30), 0.4f, true, 0);
	m_MinimapMask = cocos2d::Sprite::create("Graphic/circle.png");
	setUIProperties(m_MinimapMask, cocos2d::Point(0, 0), cocos2d::Point(m_WinWidth - 230, 30), 0.4f, true, 0);
	this->addChild(m_MinimapFrame);
	
	cocos2d::ClippingNode* clipper = cocos2d::ClippingNode::create();
	clipper->setInverted(false);
	clipper->setAlphaThreshold(0);
	//clipper->addChild(m_Minimap);

	Node *node = Node::create();
	node->addChild(m_MinimapMask);
	clipper->setStencil(node);

	this->addChild(clipper);


	m_StageData = GET_DATA_MANAGER()->getStageData(0);
	m_Map = drawMap(ROOM_MARGIN, ROOM_SCALE);
	setUpMap(); //연우가 나중에 호출해 줄것이야!!!
	m_Map->setPosition(cocos2d::Point(300, 50));
	m_Map->setScale(fitToWin());
	this->addChild(m_Map);
	return true;
}

void Arthas::MinimapLayer::setUpMap()
{
	//m_CurrentFloor = GET_STAGE_MANAGER()->getStageNum();
// 	if (m_CurrentFloor != -1)
// 	{	//m_Player = GET_STAGE_MANAGER()->getPlayer();

/*	}*/
}

void Arthas::MinimapLayer::update(float dTime)
{
	if (m_MapWinOn)
	{
		drawMapWin();
	}
	drawMiniMap();
// 	m_Player = GET_STAGE_MANAGER()->getPlayer();

}

cocos2d::DrawNode* Arthas::MinimapLayer::drawMap(int margin, int drawScale)
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

cocos2d::DrawNode* Arthas::MinimapLayer::makeRoomRect(int width, int height, int marginSize, MarginSet margin, cocos2d::Color4B fillColor)
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

void Arthas::MinimapLayer::roomBoundaryCheck(int roomCnt, int x, int y, int maxX, int maxY)
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

void Arthas::MinimapLayer::drawMapWin()
{
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

void Arthas::MinimapLayer::initMarginSet()
{
	m_MarginSet.mUp = false;
	m_MarginSet.mDown = false;
	m_MarginSet.mLeft = false;
	m_MarginSet.mRight = false;
}

int Arthas::MinimapLayer::getModulePlaceData(int roomCnt, int x, int y)
{
	int moduleX = m_StageData.Rooms[roomCnt].width / m_ModuleSize;
	return m_StageData.Rooms[roomCnt].modulePlaceData[moduleX * y + x];
}

float Arthas::MinimapLayer::fitToWin()
{
	float sizeX = 400.0f / ((m_StageData.height / m_ModuleSize) * ROOM_SCALE);
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




