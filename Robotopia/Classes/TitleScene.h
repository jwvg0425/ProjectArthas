/************************************************************************/
/*
	CLASS			: TitleScene
	Author			: 김연우
	역할				: 타이틀 화면의 모든 레이어들을 담는 씬
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 그냥 와꾸만 짜둠.
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"

BEGIN_NS_AT

class TitleScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	OVERRIDE bool			init();
	void					menuCallback( Ref* sender );
	CREATE_FUNC( TitleScene );
private:
	bool					m_IsStarted;
};

END_NS_AT