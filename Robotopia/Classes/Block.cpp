#include "Block.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool Arthas::Block::init()
{
	m_Sprite = GET_RESOURCE_MANAGER()->createSprite( ST_BLOCK );
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
