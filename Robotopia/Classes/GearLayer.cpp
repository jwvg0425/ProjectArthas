#include "pch.h"
#include "GearLayer.h"
#include "Player.h"
#include "ResourceManager.h"

Arthas::GearLayer::GearLayer()
{
}

Arthas::GearLayer::~GearLayer()
{
}

bool Arthas::GearLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_GearFrame0 = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_FIXED_00);
	m_GearFrame1 = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_FIXED_01);
	m_GearRotate0 = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ROTATE_00);
	m_GearRotate1 = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ROTATE_01);
	m_GearRotate2 = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ROTATE_02);
	m_GearMonkey = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_MONKEY);
	m_GearEagle = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_EAGLE);
	m_GearBear = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_BEAR);
	
	setUIProperties(m_GearFrame0, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearFrame1, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearRotate0, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearRotate1, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearRotate2, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearMonkey, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearEagle, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearBear, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);

	this->addChild(m_GearFrame0);
	this->addChild(m_GearFrame1);
	this->addChild(m_GearRotate0);
	this->addChild(m_GearRotate1);
	this->addChild(m_GearRotate2);
	this->addChild(m_GearMonkey);
	this->addChild(m_GearEagle);
	this->addChild(m_GearBear);
	return true;
}

void Arthas::GearLayer::update(float dTime)
{

}

