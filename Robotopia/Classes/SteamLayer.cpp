#include "pch.h"
#include "SteamLayer.h"
#include "Player.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

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
	m_Steam0 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_00);
	m_Steam1 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_01);
	m_Steam2 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_02);
	m_Steam3 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_03);
	m_Steam4 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_04);
	m_Steam5 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_05);

	m_SteamMask0 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MASK_HALF);
	m_SteamMask1 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MASK_PART);
	m_SteamMask2 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MASK_PART);
	m_SteamMask3 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MASK_PART);
	m_SteamMask4 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MASK_PART);
	m_SteamMask5 = GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MASK_PART);
	
	setSteamMask(m_Steam0, m_SteamMask0);
	setSteamMask(m_Steam1, m_SteamMask1);
	setSteamMask(m_Steam2, m_SteamMask2);
	setSteamMask(m_Steam3, m_SteamMask3);
	setSteamMask(m_Steam4, m_SteamMask4);
	setSteamMask(m_Steam5, m_SteamMask5);

	m_SteamMask1->setRotation(-144);
	m_SteamMask2->setRotation(-108);
	m_SteamMask3->setRotation(-72);
	m_SteamMask4->setRotation(-36);
	
	return true;
}

void SteamLayer::update(float dTime)
{
	//player member check
// 	const Player* player = GET_STAGE_MANAGER()->getPlayer();
// 	if (player)
// 	{
// 		m_Info = ((CommonInfo*)player->getComponent(IT_COMMON))->getInfo();
// 	}
// 	if (m_CurrentGear != /*playerGear*/)
// 	{
// 		changeSteamColor(/*playerGear*/);
// 		m_CurrentGear = /*playerGear*/;
// 	}
	//changeSteamColor(m_CurrentGear); 살릴 함수

	controlSteamColor(); //없어질 함수


}

void SteamLayer::setSteamMask(cocos2d::Sprite* steam, cocos2d::Sprite* steamMask)
{
	setUIProperties(steam, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(steamMask, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	cocos2d::ClippingNode* clipper = cocos2d::ClippingNode::create();
	clipper->setInverted(true);
	clipper->setAlphaThreshold(0);
	clipper->addChild(steam);
	cocos2d::Node* node = cocos2d::Node::create();
	node->addChild(steamMask);
	clipper->setStencil(node);
	this->addChild(clipper);
}

void SteamLayer::changeSteamColor(GearType gear)
{
	switch (gear)
	{
	case GEAR_EAGLE:
		m_Steam0->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_EAGLE_00)->getTexture());
		m_Steam1->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_EAGLE_01)->getTexture());
		m_Steam2->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_EAGLE_02)->getTexture());
		m_Steam3->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_EAGLE_03)->getTexture());
		m_Steam4->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_EAGLE_04)->getTexture());
		m_Steam5->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_EAGLE_05)->getTexture());
		break;
	case GEAR_BEAR:
		m_Steam0->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_00)->getTexture());
		m_Steam1->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_01)->getTexture());
		m_Steam2->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_02)->getTexture());
		m_Steam3->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_03)->getTexture());
		m_Steam4->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_04)->getTexture());
		m_Steam5->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_BEAR_05)->getTexture());
		break;
	case GEAR_MONKEY:
		m_Steam0->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MONKEY_00)->getTexture());
		m_Steam1->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MONKEY_01)->getTexture());
		m_Steam2->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MONKEY_02)->getTexture());
		m_Steam3->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MONKEY_03)->getTexture());
		m_Steam4->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MONKEY_04)->getTexture());
		m_Steam5->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_STEAM_MONKEY_05)->getTexture());
		break;
	}
}

void SteamLayer::controlSteam()
{
// 	auto act = cocos2d::RotateTo::create(0.2f, -30);
// 	m_SteamMask5->runAction(act);
// 
// 	auto act = cocos2d::RotateTo::create(0.2f, 0.5f);
// 	m_SteamMask5->runAction(act);
}

void SteamLayer::controlSteamColor()
{
	KeyState eagleKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_EAGLE);
	KeyState bearKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_BEAR);
	KeyState monkeyKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_MONKEY);

	GearType newGear = GET_STAGE_MANAGER()->getPlayer()->getInfo().gear;
	if (newGear == GEAR_EAGLE)
	{
		changeSteamColor(GEAR_EAGLE);
	}
	else if (newGear == GEAR_BEAR)
	{
		changeSteamColor(GEAR_BEAR);
	}
	else if (newGear == GEAR_MONKEY)
	{
		changeSteamColor(GEAR_MONKEY);
	}
}
