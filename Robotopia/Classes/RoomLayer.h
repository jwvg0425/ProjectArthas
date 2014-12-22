/************************************************************************/
/*
	CLASS			: RoomLayer
	Author			: 김연우
	역할				: 한방에 있는 모든 오브젝트들이 있는 레이어
	최종 수정일자	: 2014-11-08
	최종 수정자		: 남현욱
	최종 수정사유	: sentinel 무시하는 부분을 바꿔야 맵 알고리즘 만들 수 있어서 그 부분 수정.
	Comment			: 그냥 클래스만 만들어둠
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "Util.h"
#include <hash_map>

class Block;
class Floor;
class RoomLayer : public cocos2d::Layer
{
public:
	RoomLayer();
	~RoomLayer();

	OVERRIDE bool					init();
	OVERRIDE void					update(float dTime);
	void							initRoom(const RoomData& mData);
	bool							addObject(BaseComponent* object, cocos2d::Point position, RoomZOrder zOrder);
	void							setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);
	cocos2d::Rect					getRoomRect();
	RoomData						getRoomData();
	bool							isOutOfRoom(cocos2d::Point pos);
	void							roomSwitch(bool isON);
	void							enter();
	void							exit();

	CREATE_FUNC(RoomLayer);

private:
	void							makeUnionBodies();
	void							makeObjectsByData();
	void							makeBackGroundTileSprites();
	void							makeObjectsHorizontal(int yIdx);
	void							makeObjectsVertical(int xIdx);
	void							makeTile(cocos2d::Rect tileRect, ObjectType type);
	void							makeCreature(cocos2d::Rect rect, ObjectType type);
	bool							isHorizontal(int xIdx, int yIdx);
	bool							isVertical(int xIdx, int yIdx);
	bool							isAvailableIndex(int xIdx, int yIdx);
	ObjectType						getTypeByIndex(int xIdx, int yIdx);
	void							addObjectByData(cocos2d::Rect tileRect, ObjectType type);
	void							addSprite(SpriteType type, cocos2d::Point position);
	int								findNeighbor(int xIdx, int yIdx);

	cocos2d::Size					m_TileSize;
	cocos2d::Rect					m_RoomRect;
	RoomData						m_RoomData;
	std::list<BaseComponent*>		m_Objects;
	cocos2d::PhysicsWorld*			m_PhysicsWorld = nullptr;
	Block*							m_Block = nullptr;
	Floor*							m_Floor = nullptr;
};

