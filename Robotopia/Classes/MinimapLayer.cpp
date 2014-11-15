#include "pch.h"
#include "MinimapLayer.h"
#include "ResourceManager.h"

#define ROOM_SCALE 15
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
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_MinimapRotate0 = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_ROTATE_00);
	m_MinimapRotate1 = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_ROTATE_01);
	m_MinimapRotate2 = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_ROTATE_02);
	m_MinimapMask = GET_RESOURCE_MANAGER()->createSprite(ST_MINIMAP_MASK);

	setUIProperties(m_MinimapRotate0, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_MinimapRotate1, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_MinimapRotate2, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_MinimapMask, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - (160 * RESOLUTION), 160 * RESOLUTION), 0.75f, true, 8);

	rotateSpriteForever(m_MinimapRotate0, 15, false);
	rotateSpriteForever(m_MinimapRotate1, 8, true);
	rotateSpriteForever(m_MinimapRotate2, 8, false);

	this->addChild(m_MinimapRotate0);
	this->addChild(m_MinimapRotate1);
	this->addChild(m_MinimapRotate2);
	this->addChild(m_MinimapMask);
	return true;
}

void Arthas::MinimapLayer::update(float dTime)
{
	drawMiniMap();
}

void Arthas::MinimapLayer::drawMiniMap()
{

}



