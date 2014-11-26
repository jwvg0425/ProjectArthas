/************************************************************************/
/*
	CLASS			: GameScene
	Author			: 김연우
	역할				: 인 게임의 모든 레이어들을 담는 씬
	최종 수정일자	: 2014-10-29
	최종 수정자		: 
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/


#pragma once
#include "cocos2d.h"
#include "Util.h"



class GameLayer;
class UILayer;
class GameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene*	createScene();
	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );

	GameLayer*					getGameLayer();
	UILayer*					getUILayer();

	CREATE_FUNC( GameScene );

private:
	enum ZOrder
	{
		BACKGROUND,
		GAMELAYER,
		UILAYER,
	};

	void						setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld);

	cocos2d::Scene*				m_Scene = nullptr;
	cocos2d::PhysicsWorld*		m_PhysicsWorld = nullptr;
	GameLayer*					m_GameLayer = nullptr;
	UILayer*					m_UILayer = nullptr;
};

