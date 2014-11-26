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

	void					setUpMap(); //플로어가 바뀔 때, 흔들릴 때 커맨드 받아서 호출해야 할 함수

	void					showMapWin();
	void					hideMapWin();

protected:
	//Draw Map
	StageData				m_StageData = StageData();
	int						m_ModuleSize = 0;
	cocos2d::DrawNode*		m_MapPaper = nullptr;
	
	cocos2d::DrawNode*		drawMap(int margin, int drawScale);

private:
	MinimapLayer*			m_Minimap = nullptr;
	MapWindowLayer*			m_MapWindow = nullptr;

	int						m_CurrentFloor = 0;
	std::vector<int>		m_VisitedRoom;

	//members for drawing map
	struct MarginSet
	{
		bool mUp = false;
		bool mRight = false;
		bool mDown = false;
		bool mLeft = false;
	};
	MarginSet				m_MarginSet = MarginSet();

	void					initMarginSet();
	int						getModulePlaceData(int roomCnt, int x, int y);
	void					roomBoundaryCheck(int roomCnt, int x, int y, int maxX, int maxY);
	cocos2d::DrawNode*		makeRoomRect(int width, int height, int marginSize, MarginSet margin, cocos2d::Color4B fillColor);
};
