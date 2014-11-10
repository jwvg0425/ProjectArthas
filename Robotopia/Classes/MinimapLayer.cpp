#include "pch.h"
#include "MinimapLayer.h"
#include "Player.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"

#define ROOM_SCALE 30
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
	//init
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	//init Map Data
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;

	//init Map Window
	m_MapWin = cocos2d::Sprite::create("Graphic/bg.png"); //R
	m_MapWin->setPosition(cocos2d::Point(m_WinWidth / 2, m_WinHeight / 2));
	m_MapWin->setAnchorPoint(cocos2d::Point(0.5, 0.5));
	//this->addChild(m_MapWin);
	m_MapWinOn = false;

	m_MinimapFrame = cocos2d::Sprite::create("Graphic/circle2.png");
	setUIProperties(m_MinimapFrame, cocos2d::Point(0, 0), cocos2d::Point(m_WinWidth - 230, 30), 0.4f, true, 0);
	m_MinimapMask = cocos2d::Sprite::create("Graphic/circle.png");
	setUIProperties(m_MinimapMask, cocos2d::Point(0, 0), cocos2d::Point(m_WinWidth - 230, 30), 0.4f, true, 0);
	this->addChild(m_MinimapFrame);
	
	cocos2d::ClippingNode* clipper = cocos2d::ClippingNode::create();
	clipper->setInverted(false);
	clipper->setAlphaThreshold(0);
	clipper->addChild(m_Minimap);

	Node *node = Node::create();
	node->addChild(m_MinimapMask);
	clipper->setStencil(node);

	this->addChild(clipper);

	setUpMap(); //연우가 나중에 호출해 줄것이야!!!
	this->addChild(m_Map);
	return true;
}

void Arthas::MinimapLayer::setUpMap()
{
	//m_CurrentFloor = GET_STAGE_MANAGER()->getStageNum();
// 	if (m_CurrentFloor != -1)
// 	{
		m_StageData = GET_DATA_MANAGER()->getStageData(0);
		m_Map = drawMap(ROOM_MARGIN, ROOM_SCALE);
		m_Map->setPosition(cocos2d::Point(100, 100));
		//m_Player = GET_STAGE_MANAGER()->getPlayer();

/*	}*/
}

void Arthas::MinimapLayer::update(float dTime)
{
	if (m_MapWinOn)
	{
		drawMapWin();
	}
	drawMiniMap();
// 	if (m_Player == nullptr)
// 	{
// 		return;
// 	}
// 	m_Player = GET_STAGE_MANAGER()->getPlayer();

}

cocos2d::DrawNode* Arthas::MinimapLayer::drawMap(int margin, int drawScale)
{
	auto floorMap = cocos2d::DrawNode::create();
	int idxj = m_StageData.height / m_ModuleSize;
	int idxi = m_StageData.width / m_ModuleSize;
	floorMap = makeRect(0, -250, 0, 0, 0, 0); //Data

	for (auto room : m_StageData.Rooms)
	{
		//Data Converting to index
		int posX = room.x / m_ModuleSize;
		int posY = room.y / m_ModuleSize;
		int moduleX = room.width / m_ModuleSize;
		int moduleY = room.height / m_ModuleSize;

		for (int j = 0; j < moduleY; ++j)
		{
			for (int i = 0; i < moduleX; ++i)
			{
				if (room.modulePlaceData[moduleX * j + i] == 1)
				{
					//boundary check implement!!!!!!!!!!!!
					auto roomRect = makeRect(margin, drawScale, 117, 198, 185, 120); //Data
					roomRect->setPosition(cocos2d::Point((posX + i) * drawScale, (posY + j) * drawScale));
					floorMap->addChild(roomRect);
				}
			}
		}
	}
	return floorMap;
}

cocos2d::DrawNode* Arthas::MinimapLayer::makeRect(int margin, int drawScale, int colorR, int colorG, int colorB, int colorOpacity)
{
	auto roomRect = cocos2d::DrawNode::create();
	cocos2d::Vec2 vertices1 = cocos2d::Vec2(0 + margin, 0 + margin);
	cocos2d::Vec2 vertices2 = cocos2d::Vec2(0 + margin, drawScale - margin);
	cocos2d::Vec2 vertices3 = cocos2d::Vec2(drawScale - margin, drawScale - margin);
	cocos2d::Vec2 vertices4 = cocos2d::Vec2(drawScale - margin, 0 + margin);
	cocos2d::Vec2 points[] =
	{
		vertices1,
		vertices2,
		vertices3,
		vertices4
	};
	roomRect->drawPolygon(points, 4, cocos2d::Color4F(cocos2d::Color4B(colorR, colorG, colorB, colorOpacity)), 0, cocos2d::Color4F(0.0f, 0.0f, 0.0f, 0));
	return roomRect;
}

void Arthas::MinimapLayer::drawMapWin()
{
	//m_MapWin->addChild(m_Map);
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




