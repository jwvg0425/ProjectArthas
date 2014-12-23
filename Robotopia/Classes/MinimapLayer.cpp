#include "pch.h"
#include "MinimapLayer.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "Player.h"

#define ROOM_SCALE 15
#define ROOM_MARGIN 2

MinimapLayer::MinimapLayer()
{
}

MinimapLayer::~MinimapLayer()
{
}

bool MinimapLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_MinimapRotate0 = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_ROTATE_00);
	m_MinimapRotate1 = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_ROTATE_01);
	m_MinimapRotate2 = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_ROTATE_02);
	m_MinimapPlayer = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_PLAYER);
	m_MinimapNode = cocos2d::Node::create();

	setUIProperties(m_MinimapRotate0, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), RESOLUTION, true, 4);
	setUIProperties(m_MinimapRotate1, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), RESOLUTION, true, 8);
	setUIProperties(m_MinimapRotate2, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), RESOLUTION, true, 8);
	setUIProperties(m_MinimapPlayer, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), 1.0f, true, 10);

	rotateSpriteForever(m_MinimapRotate0, 15, false);
	rotateSpriteForever(m_MinimapRotate1, 8, false);
	rotateSpriteForever(m_MinimapRotate2, 8, true);
	
	m_MinimapRotate0->setGlobalZOrder(1);
	m_MinimapRotate1->setGlobalZOrder(3);
	m_MinimapRotate2->setGlobalZOrder(3);
	m_MinimapPlayer->setGlobalZOrder(5);

	this->addChild(m_MinimapRotate0);
	this->addChild(m_MinimapRotate1);
	this->addChild(m_MinimapRotate2);
	this->addChild(m_MinimapPlayer);
	return true;
}

void MinimapLayer::update(float dTime)
{
	if (m_MapSprite != nullptr)
	{
		auto moduleSize = GET_DATA_MANAGER()->getModuleSize().width * RESOLUTION * 2;
		auto playerPosition = GET_STAGE_MANAGER()->getPlayer()->getPosition();
		m_MapSprite->setPosition(cocos2d::Point(m_WinWidth - (160 * RESOLUTION) - m_MapXidx * moduleSize - (playerPosition.x - 640) * RESOLUTION / moduleSize, 160 * RESOLUTION - m_MapYidx * moduleSize - (playerPosition.y - 640) * RESOLUTION / moduleSize));

	}
}

void MinimapLayer::setMapSprite(cocos2d::Node* mapSprite)
{
	if (m_MapSprite != nullptr)
	{
		m_MapSprite->removeFromParentAndCleanup(true);
		m_MinimapNode->removeAllChildren();
	}
	auto moduleSize = GET_DATA_MANAGER()->getModuleSize().width * RESOLUTION * 2;
	m_MapSprite = mapSprite;
	m_MapSprite->setAnchorPoint(cocos2d::Point(0, 0));
//	m_MapSprite->setPosition(cocos2d::Point(m_WinWidth - (160 * RESOLUTION) - m_MapXidx * moduleSize, 160 * RESOLUTION - m_MapYidx * moduleSize));
	m_MapSprite->setScale(0.5f);
	setMapMask();
}

void MinimapLayer::setMapMask()
{
	m_MinimapMask = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_MASK);
	setUIProperties(m_MinimapMask, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), RESOLUTION, true, 5);

	cocos2d::ClippingNode *clipper = cocos2d::ClippingNode::create();
	clipper->setInverted(false);
	clipper->setAlphaThreshold(0);
	clipper->addChild(m_MapSprite);

	m_MinimapNode->addChild(m_MinimapMask);
	clipper->setStencil(m_MinimapNode);
	this->addChild(clipper);

}

void MinimapLayer::setCurrentMapCoordinate(int xidx, int yidx, int currentRoom)
{
	m_MapXidx = xidx;
	m_MapYidx = yidx;
	m_CurrentRoom = currentRoom;
}
