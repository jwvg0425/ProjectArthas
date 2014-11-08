#include "pch.h"
#include "GameSceneUILayer.h"
#include "MinimapLayer.h"

bool Arthas::GameSceneUILayer::init()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;
	return true;
}

void Arthas::GameSceneUILayer::update(float dTime)
{
	//Member update
	m_Minimap->update(dTime);



}

