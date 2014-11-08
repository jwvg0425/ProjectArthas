#include "pch.h"
#include "RoomLayer.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "Block.h"
#include "MovingBlock.h"

bool Arthas::RoomLayer::init()
{
	m_TileSize = GET_DATA_MANAGER()->getTileSize();
	return true;
}

void Arthas::RoomLayer::update(float dTime)
{

}

void Arthas::RoomLayer::initRoom(const RoomData& roomData)
{
	setPosition(cocos2d::Point(roomData.x, roomData.y));
	makeTiles(roomData);

	//test
	auto movingBlock = Arthas::MovingBlock::create();
	movingBlock->initTile(roomData.width / 3, roomData.height / 3, roomData.width / 3, m_TileSize.height);
	addChild(movingBlock);
}

void Arthas::RoomLayer::makeTiles(const RoomData& roomData)
{
	int maxXIdx = roomData.width;
	int maxYIdx = roomData.height;
	//sentinel 무시
	for(int yIdx = 0; yIdx < maxYIdx; ++yIdx)
	{
		makeTilesHorizontal(roomData, yIdx, maxXIdx, maxYIdx);
	}

	for(int xIdx = 0; xIdx < maxXIdx; ++xIdx)
	{
		makeTilesVertical(roomData, xIdx, maxXIdx, maxYIdx);
	}
}


//가로로 연결된 타일 생성
void Arthas::RoomLayer::makeTilesHorizontal(const RoomData& roomData, int yIdx, int maxXIdx, int maxYIdx)
{
	//rect를 맞춘뒤에 그 rect에 맞는 타일을 만드는 형태로 구현
	cocos2d::Rect rect(0, yIdx*m_TileSize.height, 0, m_TileSize.height);
	bool isNewTile = true; //연속된 타일을 맞출때 새로 타일을 생성하는 플래그로 해야할 일을 구별한다.
	for(int xIdx = 0; xIdx < maxXIdx; ++xIdx)
	{
		//일단 현재 타일이 가로형 타일이라면
		if(isHorizontalTile(roomData, xIdx, yIdx, maxXIdx, maxYIdx))
		{
			//새로 만들때 최초 위치, rect의 origin값을 지정해준다.
			if(isNewTile)
			{
				isNewTile = false;
				rect.origin.x = xIdx*m_TileSize.width;
			}
			//새로 만들던 아니던 rect의 사이즈를 타일 한개 사이즈만큼 늘려준다.
			rect.size.width += m_TileSize.width;
		}
		//우리가 원한 타일이 아니면
		else
		{
			//타일 만들고 있던 상태가 아니라면
			if(isNewTile)
			{
				//rect 계속 초기화
				rect.size.width = 0;
				rect.origin.x = 0;
			}
			//타일을 만들고 있었다면
			else
			{
				//지금까지 만든 Rect로 타일 추가
				isNewTile = true;
				addTile(rect);
			}
		}
	}

	if(!isNewTile)
		addTile(rect);
}

//새로로 연결된 타일 만들기는 이하동문
void Arthas::RoomLayer::makeTilesVertical(const RoomData& roomData, int xIdx, int maxXIdx, int maxYIdx)
{
	cocos2d::Rect rect(xIdx*m_TileSize.width, 0, m_TileSize.width, 0);
	bool isNewTile = true;
	for(int yIdx = 0; yIdx < maxYIdx; ++yIdx)
	{
		if(isVerticalTile(roomData, xIdx, yIdx, maxXIdx, maxYIdx))
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
				addTile(rect);
			}
		}
	}
}

void Arthas::RoomLayer::setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld)
{
	m_PhysicsWorld = physicsWorld;
}

bool Arthas::RoomLayer::isHorizontalTile(const RoomData& roomData, int xIdx, int yIdx, int maxXIdx, int maxYIdx)
{
	bool ret = false;
	int maxContainerIdx = (signed) roomData.data.size() - 1;
	if (boundaryCheck(xIdx,yIdx,maxXIdx, maxYIdx) && //boundary check
	   roomData.data[yIdx * maxXIdx + xIdx] > 0) //현재 데이터가 타일
	{
		//위나 아래 타일이 범위 바깥 타일인 경우 무조건 빈 타일로 취급
		int upTile = boundaryCheck(xIdx, yIdx + 1, maxXIdx, maxYIdx) ?
						roomData.data[(yIdx + 1)*maxXIdx + xIdx] : 0;
		int downTile = boundaryCheck(xIdx, yIdx - 1, maxXIdx, maxYIdx) ?
			roomData.data[(yIdx - 1)*maxXIdx + xIdx] : 0;

		if ( upTile == 0 || //윗칸 데이터가 빈칸
		   downTile == 0 ) //아래칸 데이터가 빈칸
		{
			ret = true;
		}
	}
	return ret;
}

bool Arthas::RoomLayer::isVerticalTile(const RoomData& roomData, int xIdx, int yIdx, int maxXIdx, int maxYIdx)
{
	bool ret = false;
	int maxContainerIdx = (signed) roomData.data.size() - 1;
	if (boundaryCheck(xIdx, yIdx, maxXIdx, maxYIdx) && //boundary check
	   roomData.data[yIdx * maxXIdx + xIdx] > 0) //현재 데이터가 타일
	{ 
		//왼쪽이나 오른쪽 타일이 범위 바깥 타일인 경우 무조건 빈 타일로 취급
		int leftTile = boundaryCheck(xIdx - 1, yIdx, maxXIdx,maxYIdx) ?
			roomData.data[yIdx * maxXIdx + xIdx - 1] : 0;
		int rightTile = boundaryCheck(xIdx + 1, yIdx, maxXIdx,maxYIdx) ?
			roomData.data[yIdx * maxXIdx + xIdx + 1] : 0;

		if(!isHorizontalTile(roomData, xIdx, yIdx, maxXIdx, maxYIdx) && //Horizontal과 곂치치 않을 것
		   ( leftTile == 0 || //오른쪽 칸 데이터가 빈칸
		   rightTile == 0 )) //왼쪽 칸 데이터가 빈칸
		{
			ret = true;
		}
	}
	return ret;
}

void Arthas::RoomLayer::addTile(const cocos2d::Rect& rect)
{
	auto newTile = GET_COMPONENT_MANAGER()->createComponent<Block>();
	addChild(newTile);
	newTile->initTile(rect);
}

bool Arthas::RoomLayer::boundaryCheck(int xIdx, int yIdx, int maxXIdx,int maxYIdx)
{
	return xIdx >=0 && xIdx < maxXIdx &&
			yIdx >= 0 && yIdx < maxYIdx;
}

