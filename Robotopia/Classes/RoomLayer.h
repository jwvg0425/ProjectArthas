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
	OVERRIDE void					update( float dTime );
	void							initRoom( const RoomData& mData );
	void							makeTilesHorizontal( const RoomData& mData, int yIdx );
	void							makeTilesVertical( const RoomData& mData, int xIdx );
	void							setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);

	CREATE_FUNC( RoomLayer );

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

};

END_NS_AT