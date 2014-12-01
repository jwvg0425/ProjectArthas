#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "DataType.h"


class Player;
class GameScene;
class CommonInfo;
class StageManager
{
public:
	StageManager();
	~StageManager();

	bool					init();
	void					initStage(int stageNum);
	void					start();
	void					pause();
	cocos2d::Scene*			getGameScene();
	const Player*			getPlayer();
	int						getStageNum();
	int						getRoomNum();
	StageData				getCurrentStageData();
	RoomData				getCurrentRoomData();
	cocos2d::Point			getGameLayerPosition();
	bool					changeRoom(int roomNum, cocos2d::Point pos);
	bool					shakeRoom();
	bool					addObject(BaseComponent* object, int roomNum, cocos2d::Point position, RoomZOrder zOrder);

private:
	StageData				m_StageData;
	GameScene*				m_GameScene = nullptr;
	int						m_CurrentStageNum = -1;
};

