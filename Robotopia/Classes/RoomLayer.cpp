#include "pch.h"
#include "RoomLayer.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "ResourceManager.h"
#include "Block.h"
#include "MovingBlock.h"
#include "TurretBlock.h"
#include "Floor.h"
#include "Portal.h"
#include "PhysicsComponent.h"

bool Arthas::RoomLayer::init()
{
	m_TileSize = GET_DATA_MANAGER()->getTileSize();
	m_Block = nullptr;
	return true;
}

void Arthas::RoomLayer::update(float dTime)
{
	for(auto object : m_Objects)
	{
		object->update(dTime);
	}
}

void Arthas::RoomLayer::initRoom(const RoomData& roomData)
{
	m_RoomData = roomData;
	m_RoomRect = cocos2d::Rect(m_RoomData.x* m_TileSize.width, m_RoomData.y* m_TileSize.height, 
							   m_RoomData.width*m_TileSize.width, m_RoomData.height*m_TileSize.height);
	setPosition(m_RoomRect.origin);
	makeTiles();
	makeSprites();
}

bool Arthas::RoomLayer::addObject(Component* object, cocos2d::Point position, RoomZOrder zOrder)
{
	if(object == nullptr || isOutOfRoom(position))
	{
		return false;
	}

	addChild(object, zOrder);
	object->setPosition(position);
	m_Objects.push_back(object);
	return true;
}

void Arthas::RoomLayer::makeSprites()
{
	for(int yIdx = 0; yIdx < m_RoomData.height; ++yIdx)
	{
		for(int xIdx = 0; xIdx < m_RoomData.width; ++xIdx)
		{
			ComponentType cType = m_RoomData.data[xIdx + yIdx*m_RoomData.width];
			if(cType == OT_BLOCK || cType == OT_FLOOR)
			{
				ResourceType rType = ST_START;
				cocos2d::Point position;
				position.x = xIdx * m_TileSize.width;
				position.y = yIdx * m_TileSize.height;
				switch(cType)
				{
					case Arthas::OT_BLOCK:
						rType = ST_BLOCK;
						break;
					case Arthas::OT_FLOOR:
						rType = ST_FLOOR;
						break;
				}
				addSprite(rType, position);
			}
		}
	}
}

void Arthas::RoomLayer::makeTiles()
{
	m_Block = Arthas::Block::create();
	addChild(m_Block);
	m_Objects.push_back(m_Block);
	m_Block->initTile(cocos2d::Rect::ZERO);
	m_Block->retain();

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
	ComponentType	prevCompType = CT_NONE, currentCompType = CT_NONE;
	cocos2d::Rect	tileRect(0, yIdx*m_TileSize.height, 0, m_TileSize.height);

	for(int xIdx = 0; xIdx <= m_RoomData.width; ++xIdx)
	{
		prevCompType = currentCompType;
		currentCompType = getTypeByIndex(xIdx, yIdx);
		if(isHorizontalTile(xIdx, yIdx))
		{
			if(!isMaking)
			{
				isMaking = true;
				tileRect.origin.x = xIdx*m_TileSize.width;
			}
			else if(prevCompType != currentCompType)
			{
				addTile(tileRect, prevCompType);
				tileRect.origin.x = xIdx*m_TileSize.width;
				tileRect.size.width = 0;
			}
			tileRect.size.width += m_TileSize.width;
		}
		else
		{
			if(isMaking)
			{
				isMaking = false;
				addTile(tileRect, prevCompType);
				tileRect.origin.x = 0;
				tileRect.size.width = 0;
			}
			else
			{
				tileRect.origin.x = 0;
				tileRect.size.width = 0;
			}
		}
	}
}

void Arthas::RoomLayer::makeTilesVertical(int xIdx)
{
	bool			isMaking = false;
	ComponentType	prevCompType = CT_NONE, currentCompType = CT_NONE;
	cocos2d::Rect	tileRect(xIdx*m_TileSize.height, 0, m_TileSize.width, 0);

	for(int yIdx = 0; yIdx <= m_RoomData.height; ++yIdx)
	{
		prevCompType = currentCompType;
		currentCompType = getTypeByIndex(xIdx, yIdx);
		if(isVerticalTile(xIdx, yIdx))
		{
			if(!isMaking)
			{
				isMaking = true;
				tileRect.origin.y = yIdx*m_TileSize.height;
			}
			else if(prevCompType != currentCompType)
			{
				addTile(tileRect, prevCompType);
				tileRect.origin.y = yIdx*m_TileSize.height;
				tileRect.size.height = 0;
			}
			tileRect.size.height += m_TileSize.height;
		}
		else
		{
			if(isMaking)
			{
				isMaking = false;
				addTile(tileRect, prevCompType);
				tileRect.origin.y = 0;
				tileRect.size.height = 0;
			}
			else
			{
				tileRect.origin.y = 0;
				tileRect.size.height = 0;
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
	int currentTile = getTypeByIndex(xIdx, yIdx);
	if(currentTile > 0) //현재 데이터가 타일
	{
		//위나 아래 타일이 범위 바깥 타일인 경우 무조건 빈 타일로 취급
		int upTile = getTypeByIndex(xIdx, yIdx + 1);
		int downTile = getTypeByIndex(xIdx, yIdx - 1);

		if( upTile != currentTile || downTile != currentTile )
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
	int currentTile = getTypeByIndex(xIdx, yIdx);

	if(currentTile > 0 && !isHorizontalTile(xIdx, yIdx)) //현재 데이터가 타일
	{ 
		int leftTile = getTypeByIndex(xIdx - 1, yIdx);
		int rightTile = getTypeByIndex(xIdx + 1, yIdx);
		if(leftTile != currentTile || rightTile != currentTile)
		{
			ret = true;
		}
	}
	return ret;
}

void Arthas::RoomLayer::addTile(cocos2d::Rect tileRect, ComponentType type)
{
	Tile* newTile = nullptr;
	switch(type)
	{
		case Arthas::OT_BLOCK:
			m_Block->extendBlock(tileRect);
			return;
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
			((Portal*) newTile)->setRoom(this);
			break;
		default:
			return;
	}
	addChild(newTile);
	newTile->initTile(tileRect);
	m_Objects.push_back(newTile);
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
		return true;
	}
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	int moduleXIdx = pos.x / ( m_TileSize.width * moduleSize.width );
	int moduleYIdx = pos.y / ( m_TileSize.height * moduleSize.height );
	int index = moduleYIdx*( m_RoomData.width / moduleSize.width ) + moduleXIdx;
	bool isIn = m_RoomData.modulePlaceData[index];
	return !isIn;
}

Arthas::RoomData Arthas::RoomLayer::getRoomData()
{
	return m_RoomData;
}

void Arthas::RoomLayer::roomSwitch(bool isON)
{
	for(auto object : m_Objects)
	{
		if(isON)
		{
			object->pause();
		}
		else
		{
			object->resume();
		}
		((PhysicsComponent*)object->getComponent(CT_PHYSICS))->setEnabled(isON);
	}
}

void Arthas::RoomLayer::addSprite(ResourceType type, cocos2d::Point position)
{
	if(type != ST_START)
	{
		auto sprite = GET_RESOURCE_MANAGER()->createSprite(type);
		sprite->setPosition(position);
		sprite->setAnchorPoint(cocos2d::Point::ZERO);
		addChild(sprite, BACKGROUND);
	}
}

// void Arthas::RoomLayer::makeUnionBodies()
// {
// 
// 	for(int xIdx = 0; xIdx < m_RoomRect.size.width; ++xIdx)
// 	{
// 		for(int yIdx = 0; yIdx < m_RoomRect.size.height; ++yIdx)
// 		{
// 			
// 		}
// 	}
// 	block->extendBlock()
// }
// 

