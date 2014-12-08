#include "pch.h"
#include "SteamLayer.h"
#include "Player.h"
#include "StageManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "EquipmentSteamContainer.h"

SteamLayer::SteamLayer()
{
}

SteamLayer::~SteamLayer()
{
}

bool SteamLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_SteamSprite = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_00);
	m_SteamBar = cocos2d::ProgressTimer::create(m_SteamSprite);
	m_SteamBar->setScale(RESOLUTION);
	m_SteamBar->setPosition(cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION));
	m_SteamBar->setPercentage(0);
	m_SteamBar->setBarChangeRate(cocos2d::Point(0, 1));
	m_SteamBar->setType(cocos2d::ProgressTimer::Type::RADIAL);
	this->addChild(m_SteamBar);

	int steamContainer = static_cast<int>(GET_DATA_MANAGER()->getEquipmentItem().m_Steam);
	m_SteamLevel = (GET_DATA_MANAGER()->getEquipmentInfo(EMT_STEAMCONTAINER, steamContainer)->m_Level) % 5;
	if (m_SteamLevel < 0)
	{
		m_SteamLevel = 0;
	}
	else if (m_SteamLevel > 5)
	{
		m_SteamLevel = 5;
	}
	m_SteamLevel = 2;
	m_SteamMaxPercent = 10.0f * m_SteamLevel + 50;
	return true;
}

void SteamLayer::update(float dTime)
{
	const PlayerInfo player = GET_STAGE_MANAGER()->getPlayer()->getInfo();
	GearType newGear = player.m_Gear;
	changeSteamColor(newGear);
	controlSteam(player.m_MaxSteam, player.m_CurrentSteam);
}

void SteamLayer::changeSteamColor(GearType gear)
{
	switch (gear)
	{
	case GEAR_EAGLE:
		m_SteamSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_EAGLE_00)->getTexture());
		break;
	case GEAR_BEAR:
		m_SteamSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_00)->getTexture());
		break;
	case GEAR_MONKEY:
		m_SteamSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MONKEY_00)->getTexture());
		break;
	}
}

void SteamLayer::controlSteam(int MaxSteam, int CurrentSteam)
{
	if (m_PrevSteam != CurrentSteam)
	{
		if (CurrentSteam < 0)
		{
			CurrentSteam = 0;
		}

		float steamRatio = m_SteamMaxPercent * CurrentSteam / MaxSteam;
		float duration = steamRatio / 100.0f;
		cocos2d::ProgressTo* act = cocos2d::ProgressTo::create(duration, steamRatio);
		m_SteamBar->runAction(act);
		m_PrevSteam = CurrentSteam;
	}
}
