#include "pch.h"
#include "GearLayer.h"
#include "Player.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "StageManager.h"

GearLayer::GearLayer()
{
}

GearLayer::~GearLayer()
{
}

bool GearLayer::init()
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
	
	m_CurrentGear = GEAR_MONKEY;
	m_GearBear = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_BEAR_ON);
	m_GearMonkey = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_MONKEY_OFF);
	m_GearEagle = GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_EAGLE_OFF);
	
	setUIProperties(m_GearFrame0, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearFrame1, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 8);
	setUIProperties(m_GearRotate0, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(m_GearRotate1, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(m_GearRotate2, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(m_GearBear, cocos2d::Point(0.5, 0.5), cocos2d::Point(170.3f, 123.1f), 1.0f, true, 9);
	setUIProperties(m_GearMonkey, cocos2d::Point(0.5, 0.5), cocos2d::Point(109.7f, 123.1f), 1.0f, true, 9);
	setUIProperties(m_GearEagle, cocos2d::Point(0.5, 0.5), cocos2d::Point(140.0f, 175.5f), 1.0f, true, 9);
	
	rotateGear(GEAR_BEAR, false);
	
	rotateSpriteForever(m_GearRotate0, 6, true);
	rotateSpriteForever(m_GearRotate1, 8, false);
	rotateSpriteForever(m_GearRotate2, 12, true);

	m_GearFrame1->addChild(m_GearMonkey);
	m_GearFrame1->addChild(m_GearEagle);
	m_GearFrame1->addChild(m_GearBear);

	this->addChild(m_GearFrame0);
	this->addChild(m_GearRotate0);
	this->addChild(m_GearRotate1);
	this->addChild(m_GearRotate2);
	this->addChild(m_GearFrame1);
	return true;
}

void GearLayer::update(float dTime)
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

	GearType newGear = GET_STAGE_MANAGER()->getPlayer()->getInfo().gear;

	if (m_GearFrame1->getNumberOfRunningActions() == 0)
	{
		if (newGear == GEAR_BEAR)
		{
			if (m_CurrentGear == GEAR_EAGLE)
			{
				rotateGear(GEAR_BEAR, false);
			}
			else if (m_CurrentGear == GEAR_MONKEY)
			{
				rotateGear(GEAR_BEAR, true);
			}
		}
		else if (newGear == GEAR_MONKEY)
		{
			if (m_CurrentGear == GEAR_BEAR)
			{
				rotateGear(GEAR_MONKEY, false);
			}
			else if (m_CurrentGear == GEAR_EAGLE)
			{
				rotateGear(GEAR_MONKEY, true);
			}
		}
		else if (newGear == GEAR_EAGLE)
		{
			if (m_CurrentGear == GEAR_MONKEY)
			{
				rotateGear(GEAR_EAGLE, false);
			}
			else if (m_CurrentGear == GEAR_BEAR)
			{
				rotateGear(GEAR_EAGLE, true);
			}
		}
	}

	m_CurrentGear = newGear;
}

void GearLayer::rotateGear(GearType swithGearTo, bool clockwise)
{
	//Chang Size and Position
	switch (swithGearTo)
	{
	case GEAR_EAGLE:
		m_GearEagle->setScale(1.1f);
		m_GearBear->setScale(0.70f);
		m_GearMonkey->setScale(0.70f);
		m_GearEagle->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_EAGLE_ON)->getTexture());
		m_GearBear->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_BEAR_OFF)->getTexture());
		m_GearMonkey->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_MONKEY_OFF)->getTexture());
		break;
	case GEAR_BEAR:
		m_GearEagle->setScale(0.70f);
		m_GearBear->setScale(1.1f);
		m_GearMonkey->setScale(0.70f);
		m_GearEagle->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_EAGLE_OFF)->getTexture());
		m_GearBear->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_BEAR_ON)->getTexture());
		m_GearMonkey->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_MONKEY_OFF)->getTexture());
		break;
	case GEAR_MONKEY:
		m_GearEagle->setScale(0.70f);
		m_GearBear->setScale(0.70f);
		m_GearMonkey->setScale(1.1f);
		m_GearEagle->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_EAGLE_OFF)->getTexture());
		m_GearBear->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_BEAR_OFF)->getTexture());
		m_GearMonkey->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GEAR_ICON_MONKEY_ON)->getTexture());
		break;
	}

	//Rotate
	cocos2d::RotateBy* rotateFrame;
	cocos2d::RotateBy* rotateIcon0;
	cocos2d::RotateBy* rotateIcon1;
	cocos2d::RotateBy* rotateIcon2;
	if (clockwise)
	{
		rotateFrame = cocos2d::RotateBy::create(0.3f, 120);
		rotateIcon0 = cocos2d::RotateBy::create(0.3f, -120);
		rotateIcon1 = cocos2d::RotateBy::create(0.3f, -120);
		rotateIcon2 = cocos2d::RotateBy::create(0.3f, -120);
	}
	else
	{
		rotateFrame = cocos2d::RotateBy::create(0.3f, -120);
		rotateIcon0 = cocos2d::RotateBy::create(0.3f, 120);
		rotateIcon1 = cocos2d::RotateBy::create(0.3f, 120);
		rotateIcon2 = cocos2d::RotateBy::create(0.3f, 120);
	}
	m_GearFrame1->runAction(rotateFrame);
	m_GearMonkey->runAction(rotateIcon0);
	m_GearBear->runAction(rotateIcon1);
	m_GearEagle->runAction(rotateIcon2);

	m_CurrentGear = swithGearTo;

}

