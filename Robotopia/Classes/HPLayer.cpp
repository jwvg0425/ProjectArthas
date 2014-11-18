#include "pch.h"
#include "HPLayer.h"
#include "Player.h"
#include "ResourceManager.h"

HPLayer::HPLayer()
{
}

HPLayer::~HPLayer()
{
}

bool HPLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_HPbar = GET_RESOURCE_MANAGER()->createSprite(ST_HP_BAR);
	m_HPMask = GET_RESOURCE_MANAGER()->createSprite(ST_HP_MASK);
	setHPMask(m_HPbar, m_HPMask);

	return true;
}

void HPLayer::update(float dTime)
{
	controlHP();
}

void HPLayer::controlHP()
{

}

void HPLayer::setHPMask(cocos2d::Sprite* hpBar, cocos2d::Sprite* hpMask)
{
	setUIProperties(hpBar, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(hpMask, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	cocos2d::ClippingNode* clipper = cocos2d::ClippingNode::create();
	clipper->setInverted(true);
	clipper->setAlphaThreshold(0);
	clipper->addChild(hpBar);
	cocos2d::Node* node = cocos2d::Node::create();
	node->addChild(hpMask);
	clipper->setStencil(node);
	this->addChild(clipper);
}
