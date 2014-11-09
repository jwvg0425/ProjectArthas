/************************************************************************/
/*
CLASS			: View
Author			: 김성연
역할				: State들의 추상 클래스
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
public:
	static void initView(cocos2d::Layer* scrollingLayer);
	static void setViewPort(cocos2d::Point pivotPoint);

private:
	//static cocos2d::extension::ScrollView* m_Scroll;
};

END_NS_AT
