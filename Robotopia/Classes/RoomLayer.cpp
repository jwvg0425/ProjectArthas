#include "pch.h"
#include "RoomLayer.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "Block.h"
#include "MovingBlock.h"
#include "TurretBlock.h"
#include "Floor.h"
#include "Portal.h"

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
	m_RoomData = roomData;
	m_RoomRect = cocos2d::Rect(m_RoomData.x* m_TileSize.width, m_RoomData.y* m_TileSize.height, 
							   m_RoomData.width*m_TileSize.width, m_RoomData.height*m_TileSize.height);
	setPosition(m_RoomRect.origin);
	makeTiles();

	//test
	auto movingBlock = Arthas::MovingBlock::create();
	movingBlock->initTile(cocos2d::Point(m_RoomRect.size.width / 3, m_RoomRect.size.height / 3), 
						  m_TileSize, cocos2d::Size(m_RoomRect.size.width / 3, m_TileSize.height));
	addChild(movingBlock);
}

void Arthas::RoomLayer::makeTiles()
{
	//sentinel 무시
	for(int yIdx = 0; yIdx < m_RoomData.height; ++yIdx)
	{
		makeTilesHorizontal(yIdx);
	}

	for(int xIdx = 0; xIdx < m_RoomData.width; ++xIdx)
	{
		makeTilesVertical(xIdx);
	}
}


//가로로 연결된 타일 생성
void Arthas::RoomLayer::makeTilesHorizontal(int yIdx)
{
	bool			isMaking = false;
	bool			isOnlySpriteMake = false;
	ComponentType	prevCompType = CT_NONE, currentCompType = CT_NONE;
	cocos2d::Size	physicalSize(0, m_TileSize.height), spriteSize(0, m_TileSize.height);
	cocos2d::Point	origin(0, yIdx*m_TileSize.height);

	for(int xIdx = 0; xIdx <= m_RoomData.width; ++xIdx)
	{
		prevCompType = currentCompType;
		currentCompType = getTypeByIndex(xIdx, yIdx);
		if(isHorizontalTile(xIdx, yIdx))
		{
			if(!isMaking)
			{
				isMaking = true;
				origin.x = xIdx*m_TileSize.width;
			}
			else if(prevCompType != currentCompType)
			{
				addTile(origin, physicalSize, spriteSize, prevCompType);
				origin.x = xIdx*m_TileSize.width;
				physicalSize.width = 0;
				spriteSize.width = 0;
			}
			else if(isOnlySpriteMake)
			{
				isOnlySpriteMake = false;
				addTile(origin, physicalSize, spriteSize, prevCompType);
				origin.x = xIdx*m_TileSize.width;
				physicalSize.width = 0;
				spriteSize.width = 0;
			}

			physicalSize.width += m_TileSize.width;
			spriteSize.width += m_TileSize.width;
		}
		else
		{
			if(isMaking)
			{
				if(currentCompType == CT_NONE)
				{
					isMaking = false;
					addTile(origin, physicalSize, spriteSize, prevCompType);
					origin.x = xIdx*m_TileSize.width;
					physicalSize.width = 0;
					spriteSize.width = 0;
				}
				else if(currentCompType == prevCompType)
				{
					isOnlySpriteMake = true;
					spriteSize.width += m_TileSize.width;
				}
			}
		}
	}
}

void Arthas::RoomLayer::makeTilesVertical(int xIdx)
{
	bool			isMaking = false;
	ComponentType	prevCompType = CT_NONE, currentCompType = CT_NONE;
	cocos2d::Size	physicalSize(m_TileSize.width, 0), spriteSize(m_TileSize.width, 0);
	cocos2d::Point	origin(xIdx*m_TileSize.height, 0);

	for(int yIdx = 0; yIdx <= m_RoomData.height; ++yIdx)
	{
		prevCompType = currentCompType;
		currentCompType = getTypeByIndex(xIdx, yIdx);
		if(isVerticalTile(xIdx, yIdx))
		{
			if(!isMaking)
			{
				isMaking = true;
				origin.y = yIdx*m_TileSize.height;
			}
			else if(prevCompType != currentCompType)
			{
				addTile(origin, physicalSize, spriteSize, prevCompType);
				origin.y = yIdx*m_TileSize.height;
				physicalSize.height = 0;
				spriteSize.height = 0;
			}

			physicalSize.height += m_TileSize.height;
			spriteSize.height += m_TileSize.height;
		}
		else
		{
			if(isMaking)
			{
				if(currentCompType == CT_NONE)
				{
					isMaking = false;
					addTile(origin, physicalSize, spriteSize, prevCompType);
					origin.y = yIdx*m_TileSize.height;
					physicalSize.height = 0;
					spriteSize.height = 0;
				}
			}
		}
	}
}

void Arthas::RoomLayer::setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld)
{
	m_PhysicsWorld = physicsWorld;
}

bool Arthas::RoomLayer::isHorizontalTile(int xIdx, int yIdx)
{
	bool ret = false;
	int maxContainerIdx = (signed) m_RoomData.data.size() - 1;
	if (isAvailableIndex(xIdx,yIdx) && //boundary check
	   m_RoomData.data[yIdx * m_RoomData.width + xIdx] > 0) //현재 데이터가 타일
	{
		//위나 아래 타일이 범위 바깥 타일인 경우 무조건 빈 타일로 취급
		int upTile = isAvailableIndex(xIdx, yIdx + 1) ? m_RoomData.data[(yIdx + 1)*m_RoomData.width + xIdx] : 0;
		int downTile = isAvailableIndex(xIdx, yIdx - 1) ? m_RoomData.data[(yIdx - 1)*m_RoomData.width + xIdx] : 0;

		if ( upTile == 0 || //윗칸 데이터가 빈칸
		   downTile == 0 ) //아래칸 데이터가 빈칸
		{
			ret = true;
		}
	}
	return ret;
}

bool Arthas::RoomLayer::isVerticalTile(int xIdx, int yIdx)
{
	bool ret = false;
	int maxContainerIdx = (signed) m_RoomData.data.size() - 1;
	if (isAvailableIndex(xIdx, yIdx) && //boundary check
	   m_RoomData.data[yIdx * m_RoomData.width + xIdx] > 0) //현재 데이터가 타일
	{ 
		//왼쪽이나 오른쪽 타일이 범위 바깥 타일인 경우 무조건 빈 타일로 취급
		int leftTile = getTypeByIndex(xIdx - 1, yIdx);
		int rightTile = getTypeByIndex(xIdx + 1, yIdx);

		if(!isHorizontalTile(xIdx, yIdx) && //Horizontal과 곂치치 않을 것
		   ( leftTile == 0 || //오른쪽 칸 데이터가 빈칸
		   rightTile == 0 )) //왼쪽 칸 데이터가 빈칸
		{
			ret = true;
		}
	}
	return ret;
}

void Arthas::RoomLayer::addTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize, ComponentType type)
{
	Tile* newTile = nullptr;
	switch(type)
	{
		case Arthas::OT_BLOCK:
			newTile = GET_COMPONENT_MANAGER()->createComponent<Block>();
			break;
		case Arthas::OT_BLOCK_MOVING:
			newTile = GET_COMPONENT_MANAGER()->createComponent<MovingBlock>();
			break;
		case Arthas::OT_BLOCK_TURRET:
			newTile = GET_COMPONENT_MANAGER()->createComponent<TurretBlock>();
			break;
		case Arthas::OT_FLOOR:
			newTile = GET_COMPONENT_MANAGER()->createComponent<Floor>();
			break;
		case Arthas::OT_PORTAL_CLOSED:
		case Arthas::OT_PORTAL_OPEN:
			newTile = GET_COMPONENT_MANAGER()->createComponent<Portal>();
			break;
		default:
			return;
	}
	addChild(newTile);
	newTile->initTile(origin, physicalSize, spriteSize);
}

bool Arthas::RoomLayer::isAvailableIndex(int xIdx, int yIdx)
{
	return xIdx >=0 && xIdx < m_RoomData.width &&
			yIdx >= 0 && yIdx < m_RoomData.height;
}

Arthas::ComponentType Arthas::RoomLayer::getTypeByIndex(int xIdx, int yIdx)
{
	return isAvailableIndex(xIdx, yIdx) ?
			m_RoomData.data[yIdx * m_RoomData.width + xIdx] : CT_NONE;
}

cocos2d::Rect Arthas::RoomLayer::getRoomRect()
{
	return m_RoomRect;
}

bool Arthas::RoomLayer::isOutOfRoom(cocos2d::Point pos)
{
	if(pos.x < 0 || pos.x > m_RoomRect.size.width ||
	   pos.y < 0 || pos.y > m_RoomRect.size.height)
	{
		return false;
	}
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	int moduleXIdx = pos.x / ( m_TileSize.width * moduleSize.width );
	int moduleYIdx = pos.y / ( m_TileSize.height * moduleSize.height );
	int index = moduleYIdx*( m_RoomData.width / moduleSize.width ) + moduleXIdx;
	return m_RoomData.modulePlaceData[index];
}

