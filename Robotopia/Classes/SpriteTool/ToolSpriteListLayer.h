/************************************************************************/
/*
CLASS			: ToolSpriteListLayer
Author			: 김성연
역할				: 현재 저장된 Sprite의 list 및 정보를 보여주는 레이어
최종 수정일자		: 2014-11-08
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"
#include <vector>

BEGIN_NS_AT

class ToolSpriteListLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool init();
	

private:
	std::vector<AnimationInfo*> m_SpriteList;
	
};

END_NS_AT

//
//struct AnimationInfo
//{
//	ResourceType type;
//	char animationName[MAX_FRAME][MAX_LEN];
//	int frameNum;
//	float delay;
//};