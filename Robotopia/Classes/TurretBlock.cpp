#include "pch.h"
#include "TurretBlock.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"


bool TurretBlock::init()
{
	if (!Tile::init())
	{
		return false;
	}

	return true;
}

void TurretBlock::update(float dTime)
{
}

void TurretBlock::enter()
{
}

void TurretBlock::exit()
{
}

void TurretBlock::initTile(cocos2d::Rect tileRect)
{

}

