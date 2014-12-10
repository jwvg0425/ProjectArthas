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
#define PLAYER_TAG 12



class Player;
class RoomLayer;
class View;
class GameLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool					init();
	OVERRIDE void					update( float dTime );
	void							initGameLayer( int stageNum );
	void							shakeRooms();
	const Player*					getPlayer();
	void							setPlayerState(int idx, int state);
	void							setPlayerInfo(const PlayerInfo& info);
	int								getCurrentRoomNum();
	RoomLayer*						getRoomLayer(int roomNum);
	void							setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);
	void							changeRoom(int roomNum, cocos2d::Point pos);

	bool							onContactBegin(cocos2d::PhysicsContact& contact);
	void							onContactSeparate(cocos2d::PhysicsContact& contact);

	CREATE_FUNC( GameLayer );

private:
	static void						setViewPort(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint);
	static void						setViewPortWithHighlight(cocos2d::Layer* layer, cocos2d::Rect standardRect);
	static void						setViewPortShake(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint);

	void							checkIn();
	cocos2d::Point					findFirstPoint(int roomNum);
	void							testCode();

	cocos2d::PhysicsWorld*			m_PhysicsWorld = nullptr;
	RoomLayer*						m_RoomLayers[MAX_ROOM_LAYER_NUM];
	Player*							m_Player = nullptr;
	int								m_StageNum = 0;
	int								m_CurrentRoomNum = 0;
	int								m_RoomCount = 0;
};

