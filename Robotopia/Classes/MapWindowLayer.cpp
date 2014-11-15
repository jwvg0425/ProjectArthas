#include "pch.h"
#include "MapWindowLayer.h"
#include "Player.h"
#include "DataManager.h"

#define ROOM_SCALE 35
#define ROOM_MARGIN 4

bool Arthas::MapWindowLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_StageData = GET_DATA_MANAGER()->getStageData(0);
	m_ModuleSize = GET_DATA_MANAGER()->getModuleSize().width;	
	return true;
}

void Arthas::MapWindowLayer::update(float dTime)
{
}

void Arthas::MapWindowLayer::showMapWIn()
{
	m_MapPaper = drawMap(ROOM_MARGIN, ROOM_SCALE);
	this->addChild(m_MapPaper);
}

void Arthas::MapWindowLayer::hideMapWin()
{
	this->removeChild(m_MapPaper, true);
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



