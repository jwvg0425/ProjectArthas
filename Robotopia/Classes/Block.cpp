#include "pch.h"
#include "Block.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

bool Arthas::Block::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_BLOCK;
	m_SpriteType = ST_BLOCK;

	return true;
}

void Arthas::Block::update( float dTime )
{

}

void Arthas::Block::enter()
{
}

void Arthas::Block::exit()
{
}

void Arthas::Block::initTile( float x, float y, float width, float height )
{
	Tile::initTile( x, y, width, height);
	initPhysicsBody(m_BoxRect);
	
	for(int xIdx = 0; xIdx < width; xIdx += GET_DATA_MANAGER()->getTileSize().width)
	{
		for(int yIdx = 0; yIdx < height; yIdx += GET_DATA_MANAGER()->getTileSize().height)
		{
			initSprite(cocos2d::Point(xIdx, yIdx));
		}
	}
}

void Arthas::Block::initTile( cocos2d::Rect rect)
{
	initTile( rect.origin.x, rect.origin.y, rect.size.width, rect.size.height );
}
