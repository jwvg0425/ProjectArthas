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
#include "Monster.h"
#include "MonsterStandShot.h"
#include "Creature.h"
#include "MonsterRush.h"

bool RoomLayer::init()
{
	m_TileSize = GET_DATA_MANAGER()->getTileSize();
	m_Block = nullptr;
	m_Floor = nullptr;
	return true;
}

void RoomLayer::update(float dTime)
{
	for(auto object : m_Objects)
	{
		object->update(dTime);
	}
}

void RoomLayer::initRoom(const RoomData& roomData)
{
	m_RoomData = roomData;
	m_RoomRect = cocos2d::Rect(m_RoomData.m_X* m_TileSize.width, m_RoomData.m_Y* m_TileSize.height, 
							   m_RoomData.m_Width*m_TileSize.width, m_RoomData.m_Height*m_TileSize.height);
	setPosition(m_RoomRect.origin);
	makeObjectsByData();
	makeBackGroundTileSprites();
}

bool RoomLayer::addObject(BaseComponent* object, cocos2d::Point position, RoomZOrder zOrder)
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

void RoomLayer::makeBackGroundTileSprites()
{
	for(int yIdx = 0; yIdx < m_RoomData.m_Height; ++yIdx)
	{
		for(int xIdx = 0; xIdx < m_RoomData.m_Width; ++xIdx)
		{
			ObjectType cType = (ObjectType)m_RoomData.m_Data[xIdx + yIdx*m_RoomData.m_Width];
			if(cType == OT_BLOCK || cType == OT_FLOOR)
			{
				SpriteType rType = ST_START;
				cocos2d::Point position;
				position.x = xIdx * m_TileSize.width;
				position.y = yIdx * m_TileSize.height;
				switch(cType)
				{
					case OT_BLOCK:
						rType = ST_BLOCK;
						break;
					case OT_FLOOR:
						rType = ST_FLOOR;
						break;
				}
				addSprite(rType, position);
			}
		}
	}
}

void RoomLayer::makeObjectsByData()
{
	m_Block = Block::create();
	m_Floor = Floor::create();
	addChild(m_Block);
	addChild(m_Floor);
	m_Objects.push_back(m_Block);
	m_Objects.push_back(m_Floor);
	m_Block->initTile(cocos2d::Rect::ZERO);
	m_Floor->initTile(cocos2d::Rect::ZERO);

	for(int yIdx = 0; yIdx < m_RoomData.m_Height; ++yIdx)
	{
		makeObjectsHorizontal(yIdx);
	}

	for(int xIdx = 0; xIdx < m_RoomData.m_Width; ++xIdx)
	{
		makeObjectsVertical(xIdx);
	}
}


//가로로 연결된 타일 생성
void RoomLayer::makeObjectsHorizontal(int yIdx)
{
	bool			isMaking = false;
	ObjectType	prevCompType = OT_START, currentCompType = OT_START;
	cocos2d::Rect	tileRect(0, yIdx*m_TileSize.height, 0, m_TileSize.height);

	for(int xIdx = 0; xIdx <= m_RoomData.m_Width; ++xIdx)
	{
		prevCompType = currentCompType;
		currentCompType = getTypeByIndex(xIdx, yIdx);
		if(isHorizontal(xIdx, yIdx))
		{
			if(!isMaking)
			{
				isMaking = true;
				tileRect.origin.x = xIdx*m_TileSize.width;
			}
			else if(prevCompType != currentCompType)
			{
				addObjectByData(tileRect, prevCompType);
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
				addObjectByData(tileRect, prevCompType);
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

void RoomLayer::makeObjectsVertical(int xIdx)
{
	bool			isMaking = false;
	ObjectType	prevCompType = OT_START, currentCompType = OT_START;
	cocos2d::Rect	tileRect(xIdx*m_TileSize.height, 0, m_TileSize.width, 0);

	for(int yIdx = 0; yIdx <= m_RoomData.m_Height; ++yIdx)
	{
		prevCompType = currentCompType;
		currentCompType = getTypeByIndex(xIdx, yIdx);
		if(isVertical(xIdx, yIdx))
		{
			if(!isMaking)
			{
				isMaking = true;
				tileRect.origin.y = yIdx*m_TileSize.height;
			}
			else if(prevCompType != currentCompType)
			{
				addObjectByData(tileRect, prevCompType);
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
				addObjectByData(tileRect, prevCompType);
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



bool RoomLayer::isHorizontal(int xIdx, int yIdx)
{
	bool ret = false;
	int maxContainerIdx = (signed) m_RoomData.m_Data.size() - 1;
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

bool RoomLayer::isVertical(int xIdx, int yIdx)
{
	bool ret = false;
	int maxContainerIdx = (signed) m_RoomData.m_Data.size() - 1;
	int currentTile = getTypeByIndex(xIdx, yIdx);

	if(currentTile > 0 && !isHorizontal(xIdx, yIdx)) //현재 데이터가 타일
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

void RoomLayer::addObjectByData(cocos2d::Rect rect, ObjectType type)
{
	_ASSERT(OT_START < type && type < OT_END);

	if(OT_TILE_START < type && type < OT_TILE_END)
	{
		makeTile(rect, type);
	}
	else if(OT_MONTER_START < type &&  type < OT_MONSTER_END)
	{
		makeMonster(rect, type);
	}
}

bool RoomLayer::isAvailableIndex(int xIdx, int yIdx)
{
	return xIdx >=0 && xIdx < m_RoomData.m_Width &&
			yIdx >= 0 && yIdx < m_RoomData.m_Height;
}

ObjectType RoomLayer::getTypeByIndex(int xIdx, int yIdx)
{
	return isAvailableIndex(xIdx, yIdx) ? 
		(ObjectType)m_RoomData.m_Data[yIdx * m_RoomData.m_Width + xIdx] : OT_START;
}

cocos2d::Rect RoomLayer::getRoomRect()
{
	return m_RoomRect;
}

bool RoomLayer::isOutOfRoom(cocos2d::Point pos)
{
	if(pos.x < 0 || pos.x > m_RoomRect.size.width ||
	   pos.y < 0 || pos.y > m_RoomRect.size.height)
	{
		return true;
	}
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	int moduleXIdx = pos.x / ( m_TileSize.width * moduleSize.width );
	int moduleYIdx = pos.y / ( m_TileSize.height * moduleSize.height );
	int index = moduleYIdx*( m_RoomData.m_Width / moduleSize.width ) + moduleXIdx;
	bool isIn = m_RoomData.m_ModulePlaceData[index];
	return !isIn;
}


void RoomLayer::roomSwitch(bool isON)
{
	for(auto object : m_Objects)
	{
// 		if(isON)
// 		{
// 			object->resume();
// 		}
// 		else
// 		{
// 			object->pause();
// 		}
		object->setEnabled(isON);
	}
}

void RoomLayer::addSprite(SpriteType type, cocos2d::Point position)
{
	if(type != ST_START)
	{
		auto sprite = GET_RESOURCE_MANAGER()->createSprite(type);
		sprite->setPosition(position);
		sprite->setAnchorPoint(cocos2d::Point::ZERO);
		addChild(sprite, BACKGROUND);
	}
}

void RoomLayer::makeTile(cocos2d::Rect rect, ObjectType type)
{
	Tile* newTile = nullptr;
	switch(type)
	{
		case OT_BLOCK:
			m_Block->extendBlock(rect);
			return;
		case OT_FLOOR:
			m_Floor->extendBlock(rect);
			return;
		case OT_PORTAL:
			newTile = GET_COMPONENT_MANAGER()->createComponent<Portal>();
			break;
		default:
			return;
	}
	addChild(newTile);
	newTile->initTile(rect);
	m_Objects.push_back(newTile);
}

RoomData RoomLayer::getRoomData()
{
	return m_RoomData;
}

void RoomLayer::setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld)
{
	m_PhysicsWorld = physicsWorld;
}

void RoomLayer::makeMonster(cocos2d::Rect rect, ObjectType type)
{
	Creature* newMonster = nullptr;
	switch(rand()%2/*type*/)
	{
		//case OT_MONSTER_STAND_SHOT:
		case 0:
			newMonster = GET_COMPONENT_MANAGER()->createComponent<MonsterStandShot>();
			break;
		//case OT_MONSTER_RUSH:
		case 1:
			newMonster = GET_COMPONENT_MANAGER()->createComponent<MonsterRush>();
			break;
		default:
			return;
	}
	newMonster->setPosition(rect.origin);
	addChild(newMonster);
	m_Objects.push_back(newMonster);
}
