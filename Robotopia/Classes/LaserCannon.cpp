#include "pch.h"
#include "LaserCannon.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "cocos2d.h"

bool LaserCannon::init()
{
	if (!Tile::init())
	{
		return false;
	}
	m_Type = OT_LASER;
	m_SpriteType = ST_START; // 임시
	scheduleUpdate();
	return true;
}

void LaserCannon::update(float dTime)
{

}

void LaserCannon::enter()
{
}

void LaserCannon::exit()
{
}

void LaserCannon::initTile(cocos2d::Rect tileRect)
{
	setPosition(tileRect.origin);
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	auto lower = GET_RESOURCE_MANAGER()->createSprite(ST_LASER_LOWER);
	auto upper = GET_RESOURCE_MANAGER()->createSprite(ST_LASER_UPPER);
	addChild(lower);
	addChild(upper);
	lower->setPosition(cocos2d::Point(0, 0));
	upper->setPosition(cocos2d::Point(0, tileRect.size.height - tileSize.height));

	m_Laser = cocos2d::Sprite::create();
	addChild(m_Laser);
	for(float height = 0.f; height < tileRect.size.height; height += tileSize.height)
	{
		auto laser = GET_RESOURCE_MANAGER()->createSprite(ST_LASER_RELEASE);
		m_Laser->addChild(laser);
		laser->setPosition(cocos2d::Point(0, height));
	}
	initPhysicsBody(tileRect, PHYC_ALL);
}

