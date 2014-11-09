/************************************************************************/
/*
	CLASS			: GameLayer
	Author			: 김연우
	역할				: 게임에 사용되는 모든 오브젝트들이 있는 레이어
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 그냥 클래스만 만들어둠, 데이터 받아서 룸레이어들 만들고 애드차일드까지, 플레이어 위치 생각좀
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "Util.h"
#define MAX_ROOM_LAYER_NUM 100

BEGIN_NS_AT

class Player;
class RoomLayer;
class View;
class GameLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool					init();
	OVERRIDE void					update( float dTime );
	void							initGameLayer( const StageData& data );
	void							setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld );
	const Player*					getPlayer();
	CREATE_FUNC( GameLayer );

private:
	cocos2d::PhysicsWorld*		m_PhysicsWorld;
	RoomLayer*					m_RoomLayers[MAX_ROOM_LAYER_NUM];
	Player*						m_Player;
	View*						m_View;
};

END_NS_AT