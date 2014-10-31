#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "DataType.h"

BEGIN_NS_AT

class GameScene;
class StageManager
{
public:
	StageManager();
	~StageManager();

	bool			init();
	void			getStageData(int stageNum);

private:
	ModuleData		m_StageData;
	GameScene*		m_GameScene;

};

END_NS_AT