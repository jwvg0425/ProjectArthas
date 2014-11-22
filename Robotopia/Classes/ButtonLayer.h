/************************************************************************/
/*
CLASS			: ButtonLayer
Author			: 우재우
역할			: UI에 필요한 버튼
최종 수정일자	: 2014-11-22
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			: Button을 만들면 반드시 setButtonProperties를 해야 쓸 수 있음.
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "UILayer.h"

class ButtonLayer : public UILayer
{
public:
	ButtonLayer();
	~ButtonLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(ButtonLayer);

	void					setButtonProperties(ButtonType buttonType, cocos2d::Point buttonPosition, std::string buttonLabel, int buttonValue);
	void					setButtonOver(bool onButton);

private:
	ButtonType				m_ButtonType;
	int						m_ButtonValue;
	cocos2d::Sprite*		m_ButtonSprite;
	cocos2d::Rect			m_ButtonRect;
	cocos2d::Label*			m_ButtonLabel;

	void					getButtonRect(cocos2d::Point buttonPosition);
};