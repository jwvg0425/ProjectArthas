#include "pch.h"
#include "MinimapLayer.h"
#include "ResourceManager.h"

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
	setUIProperties(m_MinimapPlayer, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), RESOLUTION, true, 10);

	rotateSpriteForever(m_MinimapRotate0, 15, false);
	rotateSpriteForever(m_MinimapRotate1, 8, false);
	rotateSpriteForever(m_MinimapRotate2, 8, true);

	this->addChild(m_MinimapRotate0);
	this->addChild(m_MinimapRotate1);
	this->addChild(m_MinimapRotate2);
	this->addChild(m_MinimapPlayer);
	return true;
}

void MinimapLayer::update(float dTime)
{
}

void MinimapLayer::setMapSprite(cocos2d::Node* mapSprite)
{
	if (m_MapSprite != nullptr)
	{
		m_MapSprite->removeFromParentAndCleanup(true);
		m_MinimapNode->removeAllChildren();
	}
	m_MapSprite = mapSprite;
	m_MapSprite->setAnchorPoint(cocos2d::Point(0.5, 0.5));
	m_MapSprite->setPosition(cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION));
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
