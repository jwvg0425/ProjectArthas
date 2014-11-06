/************************************************************************/
/*
CLASS			: ToolLayer
Author			: 김성연
역할				: Tool에서 사용되는 Sprite를 띄우는 레이어
최종 수정일자		: 2014-11-05
최종 수정자		:
최종 수정사유		:
Comment			: 
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "Util.h"


BEGIN_NS_AT


class ToolLayer : public cocos2d::LayerColor
{
public:
	OVERRIDE bool					init();
	OVERRIDE void					update(float dTime);
	void							setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);

	CREATE_FUNC(ToolLayer);

private:
	cocos2d::PhysicsWorld*		m_PhysicsWorld;
	
	
};

END_NS_AT