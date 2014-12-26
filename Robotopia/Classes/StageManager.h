#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "DataType.h"


class Player;
class GameScene;
class CommonInfo;
class Portal;
class StageManager
{
public:
	StageManager();
	~StageManager();

	bool					init();
	void					initStage(int stageNum);
	void					start();
	void					pause();

	Player*					getPlayer();
	void					setPlayerState(int idx, int state);
	void					setPlayerInfo(const PlayerInfo& info);

	int						getStageNum();
	int						getRoomNum();
	StageData				getCurrentStageData();
	RoomData				getCurrentRoomData();
	cocos2d::Point			getGameLayerPosition();
	cocos2d::Point			getViewPosition();
	cocos2d::Scene*			getGameScene();
	void					setPortal(Portal* portal);
	void					portalOpen();

	bool					changeRoom(int roomNum, cocos2d::Point pos);
	bool					shakeRoom();
	bool					addObject(BaseComponent* object, int roomNum, cocos2d::Point position, RoomZOrder zOrder);
	void					playerDead();

private:
	StageData				m_StageData;
	Portal*					m_StagePortal = nullptr;
	GameScene*				m_GameScene = nullptr;
	int						m_CurrentStageNum = -1;
};

