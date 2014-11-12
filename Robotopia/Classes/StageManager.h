#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "DataType.h"

BEGIN_NS_AT
class Player;
class GameScene;
class StageManager
{
public:
	StageManager();
	~StageManager();

	bool					init();
	void					initStage(int stageNum);
	const Player*			getPlayer();
	int						getStageNum();
	int						getRoomNum();
	StageData				getCurrentStageData();
	RoomData				getCurrentRoomData();
	bool					addObject(Component* object, int roomNum, cocos2d::Point position, RoomZOrder zOrder);

private:
	StageData				m_StageData;
	GameScene*				m_GameScene;
	int						m_CurrentStageNum;
};

END_NS_AT