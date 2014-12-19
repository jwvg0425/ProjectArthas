/************************************************************************/
/*
CLASS			: MapLayer
Author			: 우재우
역할			: MapData를 받아와서 맵을 그리는 함수를 제공하는 맵 상위 클래스,
Minimap과 MapWindow를 가지고 있다.
최종 수정일자	: 2014-11-14
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "GameSceneUILayer.h"


class MinimapLayer;
class MapWindowLayer;

class MapLayer : public GameSceneUILayer
{
public:
	MapLayer();
	virtual ~MapLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(MapLayer);

	void					setUpMap(int stageNum, int roomNum);
	void					showMapWin();
	void					hideMapWin();

protected:
	int						m_ModuleSize = 0;
	StageData				m_StageData = StageData();
	cocos2d::Node*			drawMap(float drawScale, int currentRoom);

private:
	MinimapLayer*			m_Minimap = nullptr;
	MapWindowLayer*			m_MapWindow = nullptr;
	std::vector<int>		m_VisitedRoom;

	int						getModulePlaceData(int roomCnt, int x, int y);
	int						roomWallCheck(int roomCnt, int x, int y, int maxX, int maxY);
};
