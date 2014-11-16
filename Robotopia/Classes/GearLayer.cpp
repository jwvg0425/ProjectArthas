#include "pch.h"
#include "GearLayer.h"
#include "Player.h"
#include "ResourceManager.h"
#include "InputManager.h"

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
	setUIProperties(m_GearRotate0, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(m_GearRotate1, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(m_GearRotate2, cocos2d::Point(0.5, 0.5), cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION), 0.75f, true, 7);
	setUIProperties(m_GearMonkey, cocos2d::Point(0.5, 0.5), cocos2d::Point(140.0f, 175.5f), 1.0f, true, 9);
	setUIProperties(m_GearEagle, cocos2d::Point(0.5, 0.5), cocos2d::Point(109.7f, 123.1f), 1.0f, true, 9);
	setUIProperties(m_GearBear, cocos2d::Point(0.5, 0.5), cocos2d::Point(170.3f, 123.1f), 1.0f, true, 9);

	rotateSpriteForever(m_GearRotate0, 6, true);
	rotateSpriteForever(m_GearRotate1, 8, false);
	rotateSpriteForever(m_GearRotate2, 12, true);

	this->addChild(m_GearFrame0);
	this->addChild(m_GearRotate0);
	this->addChild(m_GearRotate1);
	this->addChild(m_GearRotate2);
	this->addChild(m_GearFrame1);
	m_GearFrame1->addChild(m_GearMonkey);
	m_GearFrame1->addChild(m_GearEagle);
	m_GearFrame1->addChild(m_GearBear);
	m_CurrentGear = GEAR_MONKEY;
	return true;
}

void Arthas::GearLayer::update(float dTime)
{
	KeyState eagleKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_EAGLE);
	KeyState bearKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_BEAR);
	KeyState monkeyKey = GET_INPUT_MANAGER()->getKeyState(KC_GEAR_MONKEY);

	if (m_GearFrame1->getNumberOfRunningActions() == 0)
	{
		if (eagleKey == KS_PRESS)
		{
			if (m_CurrentGear == GEAR_MONKEY)
			{
				rotateGear(true);
			}
			else if (m_CurrentGear == GEAR_BEAR)
			{
				rotateGear(false);
			}
			m_CurrentGear = GEAR_EAGLE;
		}
		else if (bearKey == KS_PRESS)
		{
			if (m_CurrentGear == GEAR_EAGLE)
			{
				rotateGear(true);
			}
			else if (m_CurrentGear == GEAR_MONKEY)
			{
				rotateGear(false);
			}
			m_CurrentGear = GEAR_BEAR;
		}
		else if (monkeyKey == KS_PRESS)
		{
			if (m_CurrentGear == GEAR_BEAR)
			{
				rotateGear(true);
			}
			else if (m_CurrentGear == GEAR_EAGLE)
			{
				rotateGear(false);
			}
			m_CurrentGear = GEAR_MONKEY;
		}
	}
}

void Arthas::GearLayer::rotateGear(bool clockwise)
{
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
}

