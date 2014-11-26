/************************************************************************/
/*
CLASS			: GameMenuLayer
Author			: 우재우
역할			: Game 중에 ESC를 누르면 나오는 메뉴
최종 수정일자	: 2014-11-22
최종 수정자		: 우재우
최종 수정사유	:신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "GameSceneUILayer.h"

class ButtonLayer;

class GameMenuLayer : public GameSceneUILayer
{
public:
	GameMenuLayer();
	~GameMenuLayer();

	OVERRIDE bool					init();
	OVERRIDE void					update(float dTime);

	CREATE_FUNC(GameMenuLayer);

	void							showGameMenu();
	void							hideGameMenu();

private:
	cocos2d::Sprite*				m_GameMenuBackGround = nullptr;
	cocos2d::Sprite*				m_GameMenuFrame = nullptr;
	std::vector<ButtonLayer*>		m_MenuItem;
	ButtonLayer*					m_Button1 = nullptr;
	ButtonLayer*					m_Button2 = nullptr;

};