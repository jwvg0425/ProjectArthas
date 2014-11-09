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

class View
{
public:

	void initView(cocos2d::Layer* scrollingLayer);
	void setViewPort(cocos2d::Point pivotPoint);

private:
	cocos2d::extension::ScrollView* m_Scroll;
};

END_NS_AT
