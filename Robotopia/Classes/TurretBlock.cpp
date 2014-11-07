#include "TurretBlock.h"


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

void Arthas::TurretBlock::initTile(cocos2d::Rect rect, int missileGateDir)
{
	m_BoxRect.setRect(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	m_SpriteType = ST_BLOCK_TURRET;

	

}

void Arthas::TurretBlock::initTile(float x, float y, float width, float height, int missileGateDir)
{
	cocos2d::Rect tmpRect;
	tmpRect.setRect(x, y, width, height);
	initTile(tmpRect, missileGateDir);
}
