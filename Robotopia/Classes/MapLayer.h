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
	~MapLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(MapLayer);

	void					setUpMap(); //플로어가 바뀔 때, 흔들릴 때 커맨드 받아서 호출해야 할 함수

	void					showMapWin();
	void					hideMapWin();

protected:
	//Draw Map
	StageData				m_StageData;
	int						m_ModuleSize;
	cocos2d::DrawNode*		m_MapPaper;
	
	cocos2d::DrawNode*		drawMap(int margin, int drawScale);

private:
	MinimapLayer*			m_Minimap;
	MapWindowLayer*			m_MapWindow;

	int						m_CurrentFloor;
	std::vector<int>		m_VisitedRoom;

	//members for drawing map
	struct MarginSet
	{
		bool mUp;
		bool mRight;
		bool mDown;
		bool mLeft;
	};
	MarginSet				m_MarginSet;

	void					initMarginSet();
	int						getModulePlaceData(int roomCnt, int x, int y);
	void					roomBoundaryCheck(int roomCnt, int x, int y, int maxX, int maxY);
	cocos2d::DrawNode*		makeRoomRect(int width, int height, int marginSize, MarginSet margin, cocos2d::Color4B fillColor);
};
