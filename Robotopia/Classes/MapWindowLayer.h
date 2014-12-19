/************************************************************************/
/*
CLASS			: MapWindowLayer
Author			: 우재우
역할			: M키를 눌렀을 때 맵을 보여준다!
최종 수정일자	: 2014-11-14
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "MapLayer.h"



class MapWindowLayer : public MapLayer
{
public:
	MapWindowLayer();
	~MapWindowLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(MapWindowLayer);

	void					showMapWin();
	void					hideMapWin();
	void					setMapSprite(cocos2d::Node* mapSprite);

private:
	cocos2d::Sprite*		m_MapWinFrame = nullptr;
	cocos2d::Sprite*		m_MapWinTrigger = nullptr;
	cocos2d::Node*			m_MapSprite = nullptr;
	float					FitToWin();

};

