/************************************************************************/
/*
CLASS			: View
Author			: 김성연
역할				: 플레이어 위치에 따른 뷰 
최종 수정일자		: 2014-11-09
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/

#pragma once

#include "Util.h"
#include "cocos-ext.h"
#include "cocos2d.h"

class View : public cocos2d::extension::ScrollView
{
public:
	OVERRIDE bool init();
	void		  initScroll(cocos2d::Layer* scrollingLayer);
	void		  setViewPort(cocos2d::Point pivotPoint);

	CREATE_FUNC(View);

private:
	cocos2d::extension::ScrollView* m_Scroll;
};