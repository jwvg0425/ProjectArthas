#include "pch.h"
#include "MinimapLayer.h"

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

	return true;
}

void Arthas::MinimapLayer::update(float dTime)
{

}




