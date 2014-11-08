#include "pch.h"
#include "GameSceneUILayer.h"
#include "MinimapLayer.h"

bool Arthas::GameSceneUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	//Member Create
	m_Minimap = Arthas::MinimapLayer::create();
	this->addChild(m_Minimap);

	return true;
}

void Arthas::GameSceneUILayer::update(float dTime)
{
	//Member update
	m_Minimap->update(dTime);



}

