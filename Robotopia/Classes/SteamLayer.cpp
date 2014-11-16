#include "pch.h"
#include "SteamLayer.h"
#include "Player.h"
#include "StageManager.h"
#include "ResourceManager.h"

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

	setClippingMask(m_Steam0, m_SteamMask0);
	setClippingMask(m_Steam1, m_SteamMask1);
	setClippingMask(m_Steam2, m_SteamMask2);
	setClippingMask(m_Steam3, m_SteamMask3);
	setClippingMask(m_Steam4, m_SteamMask4);
	setClippingMask(m_Steam5, m_SteamMask5);

	return true;
}

void SteamLayer::update(float dTime)
{
	const Player* player = GET_STAGE_MANAGER()->getPlayer();
	if (player)
	{
		m_Info = ((CommonInfo*)player->getComponent(IT_COMMON))->getInfo();
	}
}

void SteamLayer::setClippingMask(cocos2d::Sprite* steam, cocos2d::Sprite* steamMask)
{
	setUIProperties(steam, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	cocos2d::ClippingNode* clipper = cocos2d::ClippingNode::create();
	clipper->setInverted(true);
	clipper->setAlphaThreshold(0);
	clipper->addChild(steam);
	cocos2d::Node* node = cocos2d::Node::create();
	node->addChild(steamMask);
	clipper->setStencil(node);
	this->addChild(clipper);
}
