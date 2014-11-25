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



class View
{
public:

	///# 구조적인 조언: 전부 static 멤버 함수이고, *layer를 모두 넘긴다면, 사실 이 기능은 Layer에 들어가는게 맞다. (Layer를 상속해서 쓰던가...)

	// standardPoint로 기준점이 되는 점을 넘겨라, anchorPoint(0~1)
	static void setViewPort(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint);

	// Scene 중에 원하는 위치와 Width Height를 넘긴다 그러면 넘긴 위치를 중심으로 잘라낸 크기만큼의 
	//그림이 윈도우 창을 꽉차게 만든다
	static void setViewPortWithHighlight(cocos2d::Layer* layer, cocos2d::Rect standardRect);

	//뷰를 현재지점을 중심으로 힌들어라
	static void setViewPortShake(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint);
};

