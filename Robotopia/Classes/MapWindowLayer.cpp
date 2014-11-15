#include "pch.h"
#include "MapWindowLayer.h"
#include "Player.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"


#define ROOM_SCALE 30

bool Arthas::MapWindowLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_StageData = GET_DATA_MANAGER()->getStageData(0);
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;

	auto test = cocos2d::Sprite::create("Graphic/circle2.png");
	setUIProperties(test, cocos2d::Point(0, 0), cocos2d::Point(m_WinWidth - 230, 30), 0.4f, true, 0);
	this->addChild(test);
	return true;
}

void Arthas::MapWindowLayer::update(float dTime)
{

}

void Arthas::MapWindowLayer::showMapWIn()
{

}

void Arthas::MapWindowLayer::hideMapWin()
{

}
float Arthas::MapWindowLayer::FitToWin()
{
	float sizeX = 400.0f / ((m_StageData.height / m_ModuleSize) * ROOM_SCALE);
	float sizeY = 400.0f / ((m_StageData.width / m_ModuleSize) * ROOM_SCALE);
	float fitScale;
	if (sizeX < 1 && sizeY < 1)
	{
		fitScale = sizeX >= sizeY ? sizeX : sizeY;
	}
	else
	{
		fitScale = sizeX < sizeY ? sizeX : sizeY;
	}
	return fitScale;
}

Arthas::MapWindowLayer::MapWindowLayer()
{
}

Arthas::MapWindowLayer::~MapWindowLayer()
{
}



