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

BEGIN_NS_AT

class GameLayer;
class UILayer;
class GameScene : public cocos2d::Scene
{
public:
	static GameScene*			createScene();
	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	void						onEnter();

	GameLayer*					getGameLayer(){return m_GameLayer;}
	UILayer*					getUILayer(){return m_UILayer;}

	CREATE_FUNC( GameScene );

private:
	enum ZOrder
	{
		BACKGROUND ,
		GAMELAYER ,
		UILAYER ,
	};

	GameLayer*			m_GameLayer;
	UILayer*			m_UILayer;
};

END_NS_AT