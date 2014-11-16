/************************************************************************/
/*
CLASS			: MinimapLayer
Author			: 우재우
역할			: Minimap을 보여주고, M키를 눌렀을 때 확대 뷰까지 보여준다!
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "MapLayer.h"



class MinimapLayer : public MapLayer
{
public:
	MinimapLayer();
	~MinimapLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(MinimapLayer);

private:
	cocos2d::Sprite*		m_MinimapRotate0;
	cocos2d::Sprite*		m_MinimapRotate1;
	cocos2d::Sprite*		m_MinimapRotate2;
	cocos2d::Sprite*		m_MinimapMask;

	void					drawMiniMap();

};





