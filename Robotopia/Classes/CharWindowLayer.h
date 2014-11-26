/************************************************************************/
/*
CLASS			: CharWindowLayer
Author			: 우재우
역할			: C키를 눌렀을 때 캐릭터 창을 보여준다!
최종 수정일자	: 2014-11-15
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "GameSceneUILayer.h"



class CharWindowLayer : public GameSceneUILayer
{
public:
	CharWindowLayer();
	~CharWindowLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(CharWindowLayer);

	void					showCharWin();
	void					hideCharWin();

private:
	cocos2d::Sprite*		m_CharWinFrame = nullptr;
	cocos2d::Sprite*		m_CharWinTrigger = nullptr;
};
