/************************************************************************/
/*
	CLASS			: RoomLayer
	Author			: 김연우
	역할				: 한방에 있는 모든 오브젝트들이 있는 레이어
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
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
	void							makeTiles(const RoomData& roomData);
	void							makeTilesHorizontal(const RoomData& roomData, int yIdx, int maxXIdx, int maxYIdx);
	void							makeTilesVertical(const RoomData& roomData, int xIdx, int maxXIdx, int maxYIdx);
	bool							isHorizontalTile(const RoomData& roomData, int xIdx, int yIdx, int maxXIdx, int maxYIdx);
	bool							isVerticalTile(const RoomData& roomData, int xIdx, int yIdx, int maxXIdx, int maxYIdx);

	void							addTile(const cocos2d::Rect& rect);
	void							setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);

	CREATE_FUNC(RoomLayer);

private:

	enum ZOrder
	{
		BACKGROUND ,
		LAND_OBJECT ,
		GAME_OBJECT ,
		EFFECT ,
	};
	cocos2d::Size					m_TileSize;
	cocos2d::PhysicsWorld*			m_PhysicsWorld;

	bool							boundaryCheck(int xIdx,int yIdx,int maxXIdx,int maxContainerIdx);

};

END_NS_AT