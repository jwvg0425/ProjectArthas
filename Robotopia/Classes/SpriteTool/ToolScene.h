/************************************************************************/
/*
CLASS			: SpriteToolScene
Author			: 김성연
역할				: Sprite를 실험해 볼 수 있는 Scene
최종 수정일자		: 2014-11-03
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"

BEGIN_NS_AT

class ToolLayer;
class ToolScene : cocos2d::Layer
{
public:
	static cocos2d::Scene*	    createScene();
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);

	CREATE_FUNC(ToolScene);

private:
	enum ZOrder
	{
		BACKGROUND,
		TOOLLAYER,
		UILAYER,
	};
	void						setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);
	cocos2d::PhysicsWorld*		m_PhysicsWorld;
	ToolLayer*					m_ToolLayer;

};

END_NS_AT