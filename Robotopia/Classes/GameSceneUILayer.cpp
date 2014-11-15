#include "pch.h"
#include "StageManager.h"
#include "Player.h"
#include "GameSceneUILayer.h"
#include "MinimapLayer.h"
#include "GearLayer.h"
#include "SteamLayer.h"

bool Arthas::GameSceneUILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	//Member Create & init
	m_Player = GET_STAGE_MANAGER()->getPlayer();
	m_Gear = Arthas::GearLayer::create();
	m_SteamBar = Arthas::SteamLayer::create();
	m_Map = Arthas::MapLayer::create();
	
	this->addChild(m_Gear);
	this->addChild(m_SteamBar);
	this->addChild(m_Map);
	return true;
}

void Arthas::GameSceneUILayer::update(float dTime)
{
	//Member update
	m_Gear->update(dTime);
	m_SteamBar->update(dTime);
	m_Map->update(dTime);
}

