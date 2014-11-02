#include "RoomLayer.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "Block.h"

bool Arthas::RoomLayer::init()
{
	m_TileSize = GET_DATA_MANAGER()->getTileSize();
	return true;
}

void Arthas::RoomLayer::update( float dTime )
{

}

void Arthas::RoomLayer::initRoom( const RoomData& mData )
{
	setPosition( cocos2d::Point( mData.x, mData.y ) );
	int maxXIdx = mData.width / m_TileSize.width;
	int maxYIdx = mData.height / m_TileSize.height;
	//sentinel 무시
	for(int yIdx = 1; yIdx < maxYIdx - 1; ++yIdx)
	{
		makeTilesHorizontal( mData , yIdx );
	}

	for(int xIdx = 1; xIdx < maxXIdx - 1; ++xIdx)
	{
		makeTilesVertical( mData , xIdx);
	}

}

//가로로 연결된 타일 생성
void Arthas::RoomLayer::makeTilesHorizontal( const RoomData& mData, int yIdx )
{
	//rect를 맞춘뒤에 그 rect에 맞는 타일을 만드는 형태로 구현
	cocos2d::Rect rect( 0, yIdx*m_TileSize.height, 0, m_TileSize.height );

	bool isNewTile = true;
	int maxXIdx = mData.width / m_TileSize.width;
	for(int xIdx = 0; xIdx < maxXIdx; ++xIdx)
	{
		if(mData.data[yIdx*maxXIdx + xIdx] > 0 && 
			(mData.data[(yIdx + 1)*maxXIdx + xIdx] == 0 || mData.data[(yIdx - 1)*maxXIdx + xIdx] == 0))
		{
			if(isNewTile)
			{
				isNewTile = false;
				rect.origin.x = xIdx*m_TileSize.width;
			}
			rect.size.width += m_TileSize.width;
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
				this->addChild( newTile );
				newTile->initTile( rect );
			}
		}
	}
}

void Arthas::RoomLayer::makeTilesVertical( const RoomData& mData, int xIdx )
{
	cocos2d::Rect rect( xIdx*m_TileSize.width, 0, m_TileSize.width, 0 );
	bool isNewTile = true;
	int maxYIdx = mData.height / m_TileSize.height;
	int maxXIdx = mData.width / m_TileSize.width;
	for(int yIdx = 0; yIdx < maxYIdx; ++yIdx)
	{
		if(mData.data[yIdx * maxXIdx + xIdx] > 0 &&
			(mData.data[yIdx*maxXIdx + xIdx + 1] == 0|| mData.data[yIdx*maxXIdx + xIdx-1] == 0))
		{
			if(isNewTile)
			{
				isNewTile = false;
				rect.origin.y = yIdx*m_TileSize.height;
			}
			rect.size.height += m_TileSize.height;
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
				this->addChild( newTile );
				newTile->initTile( rect );
			}
		}
	}
}

void Arthas::RoomLayer::setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld )
{
	m_PhysicsWorld = physicsWorld;
}

