/************************************************************************/
/*
	CLASS			: TitleScene
	Author			: 김연우
	역할				: 타이틀 화면의 모든 레이어들을 담는 씬
	최종 수정일자	: 2014-10-29
	최종 수정자		: 우재우
	최종 수정사유	: AssemblyScene Test
	Comment			: 그냥 와꾸만 짜둠.
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"

class UILayer;
class ButtonLayer;

class TitleScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	virtual void			update(float dTime);
	virtual	void			onExit();
	void					menuCallback( Ref* sender );
	void					quitGame();

	CREATE_FUNC( TitleScene );

private:
	bool					m_IsStarted = false;
	UILayer*				m_UILayer = nullptr;
	cocos2d::Sprite*		m_TitleBackground = nullptr;
	ButtonLayer*			m_StartButton = nullptr;
	ButtonLayer*			m_QuitButton = nullptr;

	void					titleButtonInit();
};

