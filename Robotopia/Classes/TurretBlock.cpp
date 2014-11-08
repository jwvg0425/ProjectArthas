#include "pch.h"
#include "TurretBlock.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"


bool Arthas::TurretBlock::init()
{
	if (!Tile::init())
	{
		return false;
	}

	return true;
}

void Arthas::TurretBlock::update(float dTime)
{
}

void Arthas::TurretBlock::enter()
{
}

void Arthas::TurretBlock::exit()
{
}

void Arthas::TurretBlock::initTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize)
{

}

