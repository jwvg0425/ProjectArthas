/************************************************************************/
/*
CLASS			: View
Author			: 김성연
역할				: 
최종 수정일자		: 2014-11-09
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/

#pragma once

#include "Util.h"

BEGIN_NS_AT

class View : public cocos2d::extension::ScrollView
{
public:
	OVERRIDE bool init();
	//인자로 뷰의 대상이 되는 레이어를 넣으시오
	void		  initView(cocos2d::Layer* scrollingLayer);
	//인자로 현재 플레이어 위치값을 넣으시오
	void		  setViewPort(cocos2d::Point pivotPoint);

	CREATE_FUNC(View);
private:
	cocos2d::extension::ScrollView* m_Scroll;
};

END_NS_AT
