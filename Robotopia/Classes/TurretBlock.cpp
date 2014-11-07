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

void Arthas::TurretBlock::initTile(cocos2d::Rect rect)
{
	Arthas::Tile::initTile(rect);
	//미사일과 부딪히게 할 것인지의 문제에 따라서 정해짐 
	//initPhysicsBody(rect);
	m_SpriteType = ST_BLOCK_TURRET;
	initSprite(rect.origin, rect.size);
}


