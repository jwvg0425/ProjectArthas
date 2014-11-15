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

BEGIN_NS_AT


class RoomLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool					init();
	OVERRIDE void					update(float dTime);
	void							initRoom(const RoomData& mData);
	bool							addObject(Component* object, cocos2d::Point position, RoomZOrder zOrder);
	void							setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);
	cocos2d::Rect					getRoomRect();
	RoomData						getRoomData();
	bool							isOutOfRoom(cocos2d::Point pos);
	void							roomSwitch(bool isON);

	CREATE_FUNC(RoomLayer);

private:
	void							makeTiles();
	void							makeSprites();
	void							makeTilesHorizontal(int yIdx);
	void							makeTilesVertical(int xIdx);
	bool							isHorizontalTile(int xIdx, int yIdx);
	bool							isVerticalTile(int xIdx, int yIdx);
	bool							isAvailableIndex(int xIdx, int yIdx);
	Arthas::ComponentType			getTypeByIndex(int xIdx, int yIdx);
	void							addTile(cocos2d::Rect tileRect, ComponentType type);
	void							addSprite(ResourceType type, cocos2d::Point position);

	cocos2d::Size					m_TileSize;
	cocos2d::Rect					m_RoomRect;
	cocos2d::PhysicsWorld*			m_PhysicsWorld;
	RoomData						m_RoomData;
	std::vector<Component*>			m_Objects;

	
};

END_NS_AT