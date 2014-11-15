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


	m_MinimapFrame = cocos2d::Sprite::create("Graphic/circle2.png");
	setUIProperties(m_MinimapFrame, cocos2d::Point(0, 0), cocos2d::Point(m_WinWidth - 230, 30), 0.4f, true, 0);
	m_MinimapMask = cocos2d::Sprite::create("Graphic/circle.png");
	setUIProperties(m_MinimapMask, cocos2d::Point(0, 0), cocos2d::Point(m_WinWidth - 230, 30), 0.4f, true, 0);
	
	cocos2d::ClippingNode* clipper = cocos2d::ClippingNode::create();
	clipper->setInverted(false);
	clipper->setAlphaThreshold(0);
	clipper->addChild(m_MinimapFrame);

	Node *node = Node::create();
	node->addChild(m_MinimapMask);
	clipper->setStencil(node);
	this->addChild(clipper);

	m_StageData = GET_DATA_MANAGER()->getStageData(0);
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;

	return true;
}

void Arthas::MinimapLayer::update(float dTime)
{
	drawMiniMap();
}

void Arthas::MinimapLayer::drawMiniMap()
{

}



