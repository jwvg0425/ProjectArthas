#include "pch.h"
#include "LaserCannon.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"


bool LaserCannon::init()
{
	if (!Tile::init())
	{
		return false;
	}

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

}

