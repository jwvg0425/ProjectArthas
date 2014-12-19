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

	void					setMapSprite(cocos2d::Node* mapSprite);

private:
	cocos2d::Sprite*		m_MinimapRotate0 = nullptr;
	cocos2d::Sprite*		m_MinimapRotate1 = nullptr;
	cocos2d::Sprite*		m_MinimapRotate2 = nullptr;
	cocos2d::Sprite*		m_MinimapMask = nullptr;
	cocos2d::Sprite*		m_MinimapPlayer = nullptr;
	cocos2d::Node*			m_MapSprite = nullptr;
	cocos2d::Node*			m_MinimapNode = nullptr;

	void					setMapMask();
};





