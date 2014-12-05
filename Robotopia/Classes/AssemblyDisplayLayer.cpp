#include "pch.h"
#include "AssemblyDisplayLayer.h"
#include "ResourceManager.h"

bool AssemblyDisplayLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_DisplayScanBar = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_SCAN_BAR);
	setUIProperties(m_DisplayScanBar, cocos2d::Point(0.5, 0.5), cocos2d::Point(1055, 200), 1.0f, false, 2);
	this->addChild(m_DisplayScanBar);
	return true;
}

void AssemblyDisplayLayer::update(float dTime)
{
	moveScanBar();
	if (m_DisplayScanBar->getPosition().y >= 650)
	{
		m_DisplayScanBar->setVisible(false);
		m_DisplayScanBar->setPosition(cocos2d::Point(1055, 200));
	}
}

void AssemblyDisplayLayer::moveScanBar()
{
	m_DisplayScanBar->setPosition(cocos2d::Point(1055, 200));
	m_DisplayScanBar->setVisible(true);
	auto moveAction = cocos2d::MoveTo::create(1.0f, cocos2d::Point(1055, 650));
	m_DisplayScanBar->runAction(moveAction);
}