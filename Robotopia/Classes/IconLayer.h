/************************************************************************/
/*
CLASS			: IconLayer
Author			: 우재우
역할			: Icon 상호 작용에 관여
최종 수정일자	: 2014-11-28
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "UILayer.h"

class LabelLayer;

class IconLayer : public UILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC (IconLayer);

	void					setIconProperties(IconType iconType, cocos2d::Sprite* iconSprite, cocos2d::Point parentAnchorPoint, cocos2d::Point iconPosition);
	
	void					setIconDefault();
	void					setIconSelect();

private:
	bool					m_Selected = false;
	
	IconType				m_IconType = NO_ICON;
	LabelLayer*				m_IconLabel;
	cocos2d::Sprite*		m_IconFrame = nullptr;
	cocos2d::Sprite*		m_IconContents = nullptr;
	cocos2d::Rect			m_IconRect = cocos2d::Rect();

	void					setIconRect(cocos2d::Point parentAnchorPoint);

	
};