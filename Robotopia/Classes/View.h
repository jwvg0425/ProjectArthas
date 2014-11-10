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

BEGIN_NS_AT

class View
{
	// standardPoint로 기준점이 되는 점을 넘겨라, anchorPoint(0~1)
	static void setViewPort(cocos2d::Layer* layer, cocos2d::Point standardPoint, cocos2d::Point anchorPoint);

	// Scene 중에 원하는 위치와 Width Height를 넘긴다 그러면 넘긴 위치를 중심으로 잘라낸 크기만큼의 
	//그림이 윈도우 창을 꽉차게 만든다
	static void setViewPortWithHighlight(cocos2d::Layer* layer, cocos2d::Rect standardRect);

	//뷰를 현재지점을 중심으로 힌들어라
	static void setViewPortShake(cocos2d::Layer* layer, cocos2d::Point standardPoint, cocos2d::Point anchorPoint);
};

END_NS_AT