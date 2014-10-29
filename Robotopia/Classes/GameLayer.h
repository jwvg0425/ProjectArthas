/************************************************************************/
/*
	CLASS			: GameLayer
	Author			: 김연우
	역할				: 게임에 사용되는 모든 오브젝트들이 있는 레이어
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 그냥 클래스만 만들어둠
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "Util.h"

class GameLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene*			createScene();

	OVERRIDE bool					init();
	OVERRIDE void					update( float dTime );

	CREATE_FUNC( GameLayer );

private:

	enum ZOrder
	{
		BACKGROUND ,
		LAND_OBJECT ,
		GAME_OBJECT ,
		EFFECT ,
	};

};

