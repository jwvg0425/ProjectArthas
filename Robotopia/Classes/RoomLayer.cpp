#include "RoomLayer.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "Block.h"

#define BOX_SIZE_WIDTH 32
#define BOX_SIZE_HEIGHT 32
bool Arthas::RoomLayer::init()
{
	return true;
}

void Arthas::RoomLayer::update( float dTime )
{

}

void Arthas::RoomLayer::initRoom( const ModuleData& mData )
{
	for(int yIdx = 0; yIdx < mData.height; ++yIdx)
	{
		makeTilesHorizontal( mData, yIdx );
	}

	for(int xIdx = 0; xIdx < mData.width; ++xIdx)
	{
		makeTilesVertical( mData , xIdx);
	}

}

void Arthas::RoomLayer::makeTilesHorizontal( const ModuleData& data, int yIdx )
{
	cocos2d::Rect rect(0, yIdx, 0, BOX_SIZE_HEIGHT);
	bool isNewTile = true;

	for(int xIdx = 0; xIdx < data.width; ++xIdx)
	{
		if(data.data[yIdx*data.width + xIdx] > 0)
		{
			if(isNewTile)
			{
				isNewTile = false;
				rect.origin.x = xIdx;
			}
			rect.size.width += BOX_SIZE_WIDTH;
		}
		else
		{
			if(isNewTile)
			{
				rect.size.width = 0;
				rect.origin.x = 0;
			}
			else
			{
				isNewTile = true;
				auto newTile = GET_COMPONENT_MANAGER()->createComponent<Block>();
				newTile->initTile( rect );
				this->addChild( newTile );
			}
		}
	}
}

void Arthas::RoomLayer::makeTilesVertical( const ModuleData& data, int xIdx )
{
	cocos2d::Rect rect( xIdx, 0, BOX_SIZE_WIDTH, 0 );
	bool isNewTile = true;

	for(int yIdx = 0; yIdx < data.height; ++yIdx)
	{
		if(data.data[yIdx * data.width + xIdx] > 0)
		{
			if(isNewTile)
			{
				isNewTile = false;
				rect.origin.y = yIdx;
			}
			rect.size.height += BOX_SIZE_HEIGHT;
		}
		else
		{
			if(isNewTile)
			{
				rect.size.height = 0;
				rect.origin.y = 0;
			}
			else
			{
				isNewTile = true;
				auto newTile = GET_COMPONENT_MANAGER()->createComponent<Block>();
				newTile->initTile( rect );
				this->addChild( newTile );
			}
		}
	}
}

